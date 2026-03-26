////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-Core
// file: Planner.cpp
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <memory>

#include "Kernel.hpp"

#include "Events/BlockReceivedEvent.hpp"

#include "Modules/MotionControl/Utils/Block.hpp"

#include "Planner.hpp"


Core::Planner::Planner() {

    m_JuntionDeviation = 0.05F;
    m_ZJunctionDeviation = NAN;
    m_MinimumPlannerSpeed = 0.0F;
}

Core::Planner::~Planner() {

}

void Core::Planner::OnModuleLoaded() {

    Core::BlockReceivedEvent on_block_received_event;
    auto on_block_received_function = [this](std::shared_ptr<void> argument){ this->Core::Planner::OnBlockReceived(argument); }; 
    this->RegisterForEvent(on_block_received_event, on_block_received_function);
    std::cout << "[Planner.cpp] Planner registered for BlockReceivedEvent..." << std::endl;
}

void Core::Planner::OnBlockReceived(std::shared_ptr<void> argument) {

    std::shared_ptr<Core::Block> block = std::static_pointer_cast<Core::Block>(argument);

    // set speed (rate) and acceleration and juntion deviation settings

    block->MakeReady();
    AppendBlock(block);

}
    
void Core::Planner::AppendBlock(std::shared_ptr<Core::Block> block) {

    // set Conveyer::BlockQueue::HeadRef = block (add block to blockqueue)
    // set Conveyer::BlockQueue::HeadRef to next available block

    RecalculateProfiles();
}

////////////////////////////////////////////////////////////////////////////////
// TODO
// [ ] Calculate speed profile of new block in OnBlockReady()
// [ ] Add block to Conveyer in AppendBlock()
// [ ] Add configurator for settings to constructor
////////////////////////////////////////////////////////////////////////////////
