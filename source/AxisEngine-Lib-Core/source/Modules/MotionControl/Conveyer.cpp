////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-Core
// file: Conveyer.cpp
////////////////////////////////////////////////////////////////////////////////

#include <iostream>

#include "Kernel.hpp"

#include "Events/BlockReceivedEvent.hpp"
#include "Events/IdleEvent.hpp"

#include "Conveyer.hpp"


Core::Conveyer::Conveyer() {

}

Core::Conveyer::~Conveyer() {

}

void Core::Conveyer::OnModuleLoaded() {

    Core::IdleEvent on_idle_event;
    auto on_idle_function = [this](std::shared_ptr<void> argument){ this->Core::Conveyer::OnIdle(argument); };
    this->RegisterForEvent(on_idle_event, on_idle_function);
    std::cout << "[Conveyer.cpp] Conveyer registered for IdleEvent..." << std::endl;
    
    Core::BlockReceivedEvent on_block_received_event;
    auto on_block_received_function = [this](std::shared_ptr<void> argument){ this->Core::Conveyer::OnBlockReceived(argument); };
    this->RegisterForEvent(on_block_received_event, on_block_received_function);
    std::cout << "[Conveyer.cpp] Conveyer registered for BlockReceivedEvent..." << std::endl;

    m_BlockQueueSize = 32;
    m_BlockQueueDelayTime = 100;
}

void Core::Conveyer::OnBlockReceived(std::shared_ptr<void> argument) {

    std::shared_ptr<Core::Block> block = std::static_pointer_cast<Core::Block>(argument);

    AppendHeadBlock(block);
    
    PlanJunctionVelocity();
    PlanKinematicProfiles();

    SetHeadBlockReady();
}

void Core::Conveyer::OnIdle(std::shared_ptr<void> argument) {

    DeleteTailBlock();
}
        
void Core::Conveyer::Start(int n) {

    Block::Initialize(n);
    m_BlockQueue.SetLength(m_BlockQueueSize);
    m_Running = true;
}

std::shared_ptr<Core::Block> Core::Conveyer::GetPreviousBlock(std::shared_ptr<Core::Block> block) {

    int i = 0;

    for(auto b = m_BlockQueue.Begin(); b != m_BlockQueue.End(); b++) {
        
        if(block == *b) {

           return m_BlockQueue.BlockRef(i+1); 
        }
        i++;
    }
    return nullptr;
}

std::shared_ptr<Core::Block> Core::Conveyer::GetNextBlock(std::shared_ptr<Core::Block> block) {

    int i = 0;

    for(auto b = m_BlockQueue.Begin(); b != m_BlockQueue.End(); b++) {
        
        if(block == *b) {

           return m_BlockQueue.BlockRef(i-1); 
        }
        i++;
    }
    return nullptr;
}
        
void Core::Conveyer::AppendHeadBlock(std::shared_ptr<Core::Block> block) {
    
    while(m_BlockQueue.IsFull() && !Core::Kernel::Get().IsHalted()) {

        Core::IdleEvent on_idle_event; 
        Core::Kernel::Get().CallEvent(on_idle_event, nullptr);
    }

    m_BlockQueue.PushBlock(block);

}

void Core::Conveyer::SetHeadBlockReady() {

    m_BlockQueue.HeadRef()->MakeReady();
    m_BlockQueue.IncrementHeadIndex();
}

void Core::Conveyer::SetMarkBlockConsumed() {

    m_BlockQueue.IncrementMarkIndex();
}
        
void Core::Conveyer::DeleteTailBlock() {

    if(m_BlockQueue.HasConsumedBlock()) {

        m_BlockQueue.PopBlock();
    }
}

void Core::Conveyer::PlanJunctionVelocity() {
   
    // get head block, was just added to queue
    std::shared_ptr<Core::Block> block = GetHeadBlock();
    std::shared_ptr<Core::Block> prev_block = GetPreviousBlock(block);

    float junction_deviation = m_JunctionDeviation;

    block->PrimaryAxis = true;
    if(block->Steps.at(0) == 0 && block->Steps.at(1) == 0) {
        
        // z-axis only move
        if(block->Steps.at(2) != 0) {

            if(!std::isnan(m_ZJunctionDeviation)) {

                junction_deviation = m_ZJunctionDeviation;
            }

        // not a primary axis move
        } else {
            
            block->PrimaryAxis = false;
        }

    }

    // calculate max entry speed
    float vmax_junction = m_MinimumPlannerSpeed;

    if(!block->UnitVector.empty() && !m_BlockQueue.IsEmpty()) {
      
       float previous_nominal_speed = prev_block->PrimaryAxis ? prev_block->NominalSpeed : 0;         

       if(junction_deviation > 0.0F && previous_nominal_speed > 0.0F) {
           
            // compute cosine of angle between previous and current path
            float cos_theta = - m_PreviousUnitVector.at(static_cast<int>(Core::Axis::X)) * block->UnitVector.at(static_cast<int>(Core::Axis::X))
                              - m_PreviousUnitVector.at(static_cast<int>(Core::Axis::Y)) * block->UnitVector.at(static_cast<int>(Core::Axis::Y))
                              - m_PreviousUnitVector.at(static_cast<int>(Core::Axis::Z)) * block->UnitVector.at(static_cast<int>(Core::Axis::Z));

            // zero degree junction; skip and use default max junction speed
            if(cos_theta <= 0.9999F) {

                vmax_junction = std::min(previous_nominal_speed, block->NominalSpeed);

                // 180 degree juntion; skip and avoid divide by zero error
                if(cos_theta >= -0.9999F) {

                    // compute maximum junction velocity based on maximum acceleration and junction deviation
                    // trig half identity; always positive
                    float sin_theta_d2 = std::sqrtf(0.5F * (1.0F - cos_theta));
                    vmax_junction = std::min(vmax_junction, std::sqrtf(block->Acceleration * junction_deviation * sin_theta_d2 / (1.0F - sin_theta_d2)));
                }
            }
       }
    }

    block->MaxEntrySpeed = vmax_junction;

    // calculate entry speed
    float v_allowable = CalculateMaxAllowableSpeed(-block->Acceleration, m_MinimumPlannerSpeed, block->Distance);
    block->EntrySpeed = std::min(vmax_junction, v_allowable);

    // planner efficiency flags
    if(block->NominalSpeed <= v_allowable) {

        block->NominalLengthFlag = true;
    } else {

        block->NominalLengthFlag = false;
    }

    // set recalculate flag
    block->RecalculateFlag = true;

    // update previous_unit_vector and nominal_speed
    if(!block->UnitVector.empty()) {

        m_PreviousUnitVector = block->UnitVector;
    } else {

        m_PreviousUnitVector = { 0.0F, 0.0F, 0.0F };
    }

}

void Core::Conveyer::PlanKinematicProfiles() {

    std::shared_ptr<Core::Block> curr_block = GetHeadBlock();
    std::shared_ptr<Core::Block> prev_block;

    // TODO: iterator may not be a good choice here, may need to expose an index
    auto i = m_BlockQueue.Begin();

    // find maximum entry speed for all blocks in the queue
    float entry_speed = m_MinimumPlannerSpeed;
    if(!m_BlockQueue.IsEmpty()) {  
        while((i != m_BlockQueue.End()) && curr_block->RecalculateFlag) {
            
            entry_speed = curr_block->CalculateReversePass(entry_speed);
            curr_block = GetPreviousBlock(curr_block);
            i++;
        }
    }

    // find maximum exit speed and calculate trapezoid
    float exit_speed = curr_block->MaxEntrySpeed;
    while(i != m_BlockQueue.Begin()) {
        prev_block = curr_block;
        curr_block = GetNextBlock(curr_block);
        i--;

        exit_speed = curr_block->CalculateForwardPass(exit_speed);
        prev_block->CalculateTrapezoid(prev_block->EntrySpeed, curr_block->EntrySpeed);
    }

    // calculate trapezoid for HeadBlock (newest in the queue)
    curr_block->CalculateTrapezoid(curr_block->EntrySpeed, m_MinimumPlannerSpeed);

}

float Core::Conveyer::CalculateMaxAllowableSpeed(float acceleration, float target_velocity, float distance) {

    return std::sqrtf(target_velocity * target_velocity - 2.0F * acceleration * distance);
}

////////////////////////////////////////////////////////////////////////////////
// TODO
// [ ] add configurator for settings to OnModuleLoaded
// [ ] implement queue timing checks in CheckQueue
// [ ] implement tasks if kernel is halted
// [ ] implement for more than three primary axes
////////////////////////////////////////////////////////////////////////////////
