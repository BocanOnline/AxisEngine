////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-Core
// file: Robot.cpp
////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <memory>
#include <array>

#include <cmath>

#include "Kernel.hpp"

#include "Events/BlockReceivedEvent.hpp"
#include "Events/GcodeReceivedEvent.hpp"
#include "Events/IdleEvent.hpp"
#include "Events/SecondTickEvent.hpp"

#include "Modules/Communication/Utils/Gcode.hpp"
#include "Modules/Hardware/StepperMotor.hpp"
#include "Modules/Hardware/Utils/Pin.hpp"
#include "Modules/MotionControl/Solutions/CartesianSolution.hpp"
#include "Modules/MotionControl/Utils/Block.hpp"
#include "Modules/MotionControl/Utils/Types.hpp"

#include "Robot.hpp"


Core::Robot::Robot() {
    
    m_NumberOfActuators = 0;

    std::cout << "[Robot.cpp] Robot created..." << std::endl;
}

Core::Robot::~Robot() {

    std::cout << "[Robot.cpp] Robot destroyed..." << std::endl;
}
    
void Core::Robot::OnModuleLoaded() {

    Core::IdleEvent on_idle_event;
    auto on_idle_function = [this](std::shared_ptr<void> argument){ this->Core::Robot::OnIdle(argument); };
    this->RegisterForEvent(on_idle_event, on_idle_function);
    std::cout << "[Robot.cpp] Robot registered for IdleEvent..." << std::endl;
    
    Core::GcodeReceivedEvent on_gcode_received_event;
    auto on_gcode_received_function = [this](std::shared_ptr<void> argument){ this->Core::Robot::OnGcodeReceived(argument); }; 
    this->RegisterForEvent(on_gcode_received_event, on_gcode_received_function);
    std::cout << "[Robot.cpp] Robot registered for GcodeReceivedEvent..." << std::endl;
    
    Core::SecondTickEvent on_second_tick_event;
    auto on_second_tick_function = [this](std::shared_ptr<void> argument){ this->Core::Robot::OnSecondTick(argument); }; 
    this->RegisterForEvent(on_second_tick_event, on_second_tick_function); 
    std::cout << "[Robot.cpp] Robot registered for SecondTickEvent..." << std::endl;

    // read configuration and register machine solution
    m_MachineSolution = std::make_shared<Core::CartesianSolution>();
    
    std::cout << "[Robot.cpp] Machine Solution set to Cartesian..." << std::endl;

    // read configuration and set values (default if no config)
    m_SeekRate = 100.0F;                    // mm/min
    m_FeedRate = 100.0F;                    // mm/min
    m_MillimetersPerLineSegment = 0.0F;     // split lines into segments
    m_MillimetersPerArcSegment = 0.0F;      // split arcs into segments
    m_MillimetersMaxArcError = 0.01F;       // limit total arc segments to max error
    m_DeltaSegmentsPerSecond = 0.0F;        // mm/s^2
    m_SecondsPerMinute = 60.0F;             // real-time speed change
    m_DefaultAcceleration = 100.0F;         // mm/s^2
    m_ArcCorrections = 5;                   // how often to rectify arc computation
    m_GlobalMaxSpeed = 1.0F;                // max feedrate defined by F parameter
    m_AxisMaxSpeed.at(static_cast<int>(Core::Axis::X)) = 1000.0F; // mm/s
    m_AxisMaxSpeed.at(static_cast<int>(Core::Axis::Y)) = 1000.0F; // mm/s
    m_AxisMaxSpeed.at(static_cast<int>(Core::Axis::Z)) = 50.0F;   // mm/s
    
    std::cout << "[Robot.cpp] Configuration set..." << std::endl;

    // create StepperMotors
    for(int i = 0; i < c_MaxActuators; i++) {

        std::array<Core::Pin, 3> pins ;
        for(int j = 0; j < 3; j++) {
            pins.at(j).Set(j);
        }
       
        Core::StepperMotor sm(pins.at(0), pins.at(1), pins.at(2));
        m_Actuators.push_back(sm);

        m_Actuators.at(i).ChangeStepsPerMillimeter(100.0F);
        m_Actuators.at(i).SetMaxRate(30000.0F / 60.0);
        m_Actuators.at(i).SetAcceleration(100.0F);

        m_NumberOfActuators++;
    }
    
    std::cout << "[Robot.cpp] StepperMotors initialized..." << std::endl;

    // set actuator positions to current cartesian position (X0, Y0, Z0) 
    m_MachinePosition            = { 0.0F, 0.0F, 0.0F };
    m_CompensatedMachinePosition = { 0.0F, 0.0F, 0.0F };
    m_MachineSolution->CartesianToActuator(m_MachinePosition, m_ActuatorPosition);
    for(int i = 0; i < c_MaxActuators; i++) {
        m_Actuators.at(i).ChangeLastMilestone(m_ActuatorPosition.at(i));
    }
    
    std::cout << "[Robot.cpp] Actuator Positions initialized..." << std::endl;

    // set endstop positions
    m_SoftEndstopEnabled = false;
    m_SoftEndstopHalt    = true;
    m_SoftEndstopMin     = { 0.0F, 0.0F, 0.0F };
    m_SoftEndstopMax     = { 200.0F, 200.0F, 50.0F };
    
    std::cout << "[Robot.cpp] Endstop Positions initialized..." << std::endl;
}

void Core::Robot::OnIdle(std::shared_ptr<void> argument) {

    std::cout << "[Robot.cpp] Robot called by IdleEvent..." << std::endl;
}

void Core::Robot::OnGcodeReceived(std::shared_ptr<void> argument) {

    std::cout << "[Robot.cpp] Robot called by GcodeReceivedEvent..." << std::endl; 
    
    std::shared_ptr<Core::Gcode> gcode = std::static_pointer_cast<Core::Gcode>(argument);

    Core::MotionMode motion_mode;
    
    if(gcode->Has_G) {
        switch(gcode->GetValue_I('G')) {
            case 0:
                motion_mode = Core::MotionMode::Seek; 
                std::cout << "[Robot.cpp] G0 received..." << std::endl; 
                break;
            case 1:
                motion_mode = Core::MotionMode::Linear;
                std::cout << "[Robot.cpp] G1 received..." << std::endl; 
                break;
            case 2:
                motion_mode = Core::MotionMode::ClockwiseArc;
                std::cout << "[Robot.cpp] G2 received..." << std::endl; 
                break;
            case 3:
                motion_mode = Core::MotionMode::CounterArc;
                std::cout << "[Robot.cpp] G3 received..." << std::endl; 
                break;
            default:
                motion_mode = Core::MotionMode::None;
                std::cout << "[Robot.cpp] G-Code is not a motion command..." << std::endl; 
                break;
        }
    }
    if(motion_mode != Core::MotionMode::None) {
        ProcessMove(gcode, motion_mode);
    } else {  
        m_IsG123 = false;
    }

    m_NextCommandIsMCS = false;
}

void Core::Robot::OnSecondTick(std::shared_ptr<void> argument) {

    std::cout << "[Robot.cpp] Robot called by SecondTickEvent..." << std::endl;
}
        
int Core::Robot::GetNumberRegisteredMotors() {

    return m_NumberOfActuators;
}

void Core::Robot::ProcessMove(std::shared_ptr<Core::Gcode> gcode, Core::MotionMode motion_mode) {
    
    // extract parameters from gcode (X Y Z E A B C)
    // NOTE: this is how Smoothie did it, however we compare to gcode directly below

    // calculate target position in machine coordinates (except compensation transform) X Y Z
    Core::CartesianCoordinates target_position;

    if(!m_NextCommandIsMCS) {

        // work coordinate system
        if(m_AbsoluteMode) {
        
            // absolute mode; need to add wcs and tcs offsets 
            if(gcode->Has_X) {
                target_position.at(static_cast<int>(Core::Axis::X)) = gcode->GetValue_F('X');
            }
            if(gcode->Has_Y) {
                target_position.at(static_cast<int>(Core::Axis::Y)) = gcode->GetValue_F('Y');
            }
            if(gcode->Has_Z) {
                target_position.at(static_cast<int>(Core::Axis::Z)) = gcode->GetValue_F('Z');
            }
        } else { 

            // relative mode 
            if(gcode->Has_X) {
                target_position.at(static_cast<int>(Core::Axis::X)) = gcode->GetValue_F('X') + m_MachinePosition.at(static_cast<int>(Core::Axis::X));
            }
            if(gcode->Has_Y) {
                target_position.at(static_cast<int>(Core::Axis::Y)) = gcode->GetValue_F('Y') + m_MachinePosition.at(static_cast<int>(Core::Axis::X));
            }
            if(gcode->Has_Z) {
                target_position.at(static_cast<int>(Core::Axis::Z)) = gcode->GetValue_F('Z') + m_MachinePosition.at(static_cast<int>(Core::Axis::X));
            }
        }
    } else {

        // machine coordinate system
        if(gcode->Has_X) {
            target_position.at(static_cast<int>(Core::Axis::X)) = gcode->GetValue_F('X');
        }
        if(gcode->Has_Y) {
            target_position.at(static_cast<int>(Core::Axis::Y)) = gcode->GetValue_F('Y');
        }
        if(gcode->Has_Z) {
            target_position.at(static_cast<int>(Core::Axis::Z)) = gcode->GetValue_F('Z');
        }
    }

    // calculate target in machine coordinates (except compensation transform) E A B C
    // TODO

    // process changes to SeekRate and FeedRate with F argument
    if(gcode->Has_F) {
        if(motion_mode == Core::MotionMode::Seek) {
            m_SeekRate = gcode->GetValue_F('F');
        } else {
            m_FeedRate = gcode->GetValue_F('F');
        }
    }

    // call append_line or compute_line to process motion
    bool moved = false;
    switch(motion_mode) {
        case Core::MotionMode::Seek:
            moved = AppendLine(gcode, target_position, m_SeekRate / m_SecondsPerMinute);
            break;
        case Core::MotionMode::Linear:
            moved = AppendLine(gcode, target_position, m_FeedRate / m_SecondsPerMinute);
            break;
        case Core::MotionMode::ClockwiseArc:
            moved = ComputeArc(gcode, target_position, motion_mode);
            break;
        case Core::MotionMode::CounterArc:
            moved = ComputeArc(gcode, target_position, motion_mode);
            break;
        case Core::MotionMode::None:
            break;
        default:
            break;
    }

    if(moved) {
        m_MachinePosition = target_position;
    }

}

bool Core::Robot::AppendLine(std::shared_ptr<Core::Gcode> gcode, Core::CartesianCoordinates target_position, float rate) {

    // catch negative or zero feed/seek rate
    if(rate <= 0.0F) {
        return false;
    }

    // calculate straight line distance of move
    // pythagorean theorem 3d
    float distance = sqrtf( std::powf(target_position.at(static_cast<int>(Core::Axis::X)) - m_MachinePosition.at(static_cast<int>(Core::Axis::X)), 2) +
                            std::powf(target_position.at(static_cast<int>(Core::Axis::Y)) - m_MachinePosition.at(static_cast<int>(Core::Axis::Y)), 2) +
                            std::powf(target_position.at(static_cast<int>(Core::Axis::Z)) - m_MachinePosition.at(static_cast<int>(Core::Axis::Z)), 2) );

    // determine number of segments to cut
    int segments;

    // segmentation settings disabled or Z only move
    if(m_DisableSegmentation || (!m_SegmentZMoves && !gcode->Has_X && !gcode->Has_Y)) {
        segments = 1;

    // for delta robots
    } else if (m_DeltaSegmentsPerSecond > 1.0F) {
        float seconds = distance / rate;
        segments = std::max(1.0F, std::ceilf(m_DeltaSegmentsPerSecond * seconds));

    // most cases for cartesian robots
    } else {
        if(m_MillimetersPerLineSegment == 0.0F) {
            segments = 1;
        } else {
            segments = std::ceilf(distance / m_MillimetersPerLineSegment);
        }
    }

    // cut line into segments 
    bool moved = false;
    if(segments > 1) {
      
        // this currently only accounts for three axes and no extruder
        // m_NumberOfActuators and Core::CartesianCoordinates could not match
        // TODO
        Core::CartesianCoordinates segment_change;
        Core::CartesianCoordinates segment_end;

        // distance per segment
        for(int i = 0; i < m_NumberOfActuators; i++) {
            segment_change.at(i) = (target_position.at(i) - m_MachinePosition.at(i)) / segments;
        }
        
        // cut segments and append to milestone
        // segment.at(0) is the end point of the previous move
        // start at segment.at(1)
        // stop at segments - 1 (i < segments)
        for(int i = 1; i < segments; i++) {
            if(Core::Kernel::Get().IsHalted()) {
                return false;
            }
            for(int j = 0; j < m_NumberOfActuators; j++) {
                segment_end.at(j) += segment_change.at(j);
            }

            bool b = AppendMilestone(segment_end, rate);
            moved = moved || b;
        } 
    }

    // append end of each section to the queue, call append_milestone 
    if(AppendMilestone(target_position, rate)) {
        moved = true;
    }
    m_NextCommandIsMCS = false;

    return moved;
}

bool Core::Robot::ComputeArc(std::shared_ptr<Core::Gcode> gcode, Core::CartesianCoordinates target_position, Core::MotionMode motion_mode) {

    // TODO
    return false;
}

bool Core::Robot::AppendArc(std::shared_ptr<Core::Gcode> gcode, Core::CartesianCoordinates target_position, float radius, bool is_clockwise) {

    // TODO
    return false;
}

bool Core::Robot::AppendMilestone(Core::CartesianCoordinates target_position, float rate) {

    Core::CartesianCoordinates transformed_target_position;
    Core::CartesianCoordinates distance_per_axis;
    Core::CartesianCoordinates unit_vector;

    // unity transform by default
    transformed_target_position = target_position;

    // compensation transform
    // TODO

    // check soft endstops
    // TODO
  
    // determine distance moved by each axis using transformed target from compensated machine position
    bool moved = false;
    float sum_of_squares = 0;

    for(int i = 0; i < m_NumberOfActuators; i++) {
        distance_per_axis.at(i) = transformed_target_position.at(i) - m_CompensatedMachinePosition.at(i);
        
        if(std::fabsf(distance_per_axis.at(i)) < 0.00001F)
              continue;
        
        moved = true;
        if(i < static_cast<int>(Core::Axis::MaxPositionAxes)) {
            sum_of_squares += std::powf(distance_per_axis.at(i), 2); 
        }
    }

    if(!moved)
        return false;

    // determine if this is a primary axis move
    bool auxillary_move = true;

    for(int i = 0; i < static_cast<int>(Core::Axis::MaxPositionAxes); i++) {
        if(std::fabsf(distance_per_axis.at(i)) >= 0.00001F) {
            auxillary_move = false;
            break;
        }
    }

    // determine total distance moved
    // pythagorean theorem 3d
    float total_distance = auxillary_move ? 0 : std::sqrtf(sum_of_squares);

    // catch divide by zero errors
    if(!auxillary_move && total_distance < 0.0000F)
        return false;

    // catch rate exceeds configured max speeds
    if(!auxillary_move) {
        for(int i = static_cast<int>(Core::Axis::X); i < static_cast<int>(Core::Axis::MaxPositionAxes); i++) {
            
            // find unit vectors
            unit_vector.at(i) = distance_per_axis.at(i) / total_distance;

            if(i < static_cast<int>(Core::Axis::MaxPositionAxes) && m_AxisMaxSpeed.at(i) > 0) {
                float axis_speed = std::fabsf(unit_vector.at(i) * rate);

                if(axis_speed > m_AxisMaxSpeed.at(i)) {
                    rate *= (m_AxisMaxSpeed.at(i) / axis_speed);
                }
            }

            if(m_GlobalMaxSpeed > 0 && rate > m_GlobalMaxSpeed) {
                rate = m_GlobalMaxSpeed;
            }
        }
    }

    // determine target actuator position from compensated target position X Y Z
    Core::ActuatorCoordinates target_actuator_position;
    if(!m_DisableArmSolution) {
        m_MachineSolution->CartesianToActuator(transformed_target_position, target_actuator_position);
        if(Core::Kernel::Get().IsHalted()) {
            return false;    
        }
    } else {
    
        // used in special situations (SCARA)
        for(int i = static_cast<int>(Core::Axis::X); i < static_cast<int>(Core::Axis::MaxPositionAxes); i++) {
            target_actuator_position.at(i) = transformed_target_position.at(i);
        }
    }

    // determine target actuator position from compensated target position E A B C
    // TODO

    // start with default acceleration
    float acceleration = m_DefaultAcceleration;
    float seconds = rate / total_distance;

    // catch actuator speeds exceed configured max actuator speeds
    for(int actuator = 0; actuator < m_NumberOfActuators; actuator++) {
        float d = std::fabsf(target_actuator_position.at(actuator) - m_Actuators.at(actuator).GetLastMilestone());
        if(d < 0.00001F || !m_Actuators.at(actuator).IsSelected()) {
            continue;
        }

        float actuator_rate = d * seconds;
        if(actuator_rate > m_Actuators.at(actuator).GetMaxRate()) {
            rate *= (m_Actuators.at(actuator).GetMaxRate() / actuator_rate);
            seconds = rate / total_distance;
        }

        // adjust acceleration to lowest found
        float ma = m_Actuators.at(actuator).GetAcceleration();
        if(!std::isnan(ma)) {
            float ca = (d / total_distance) * acceleration;
            if(ca > ma) {
                acceleration *= (ma / ca); 
            }
        }
    }
    
    // check feed hold status
    while(Core::Kernel::Get().GetFeedHold()) {
        Core::IdleEvent idle_event;
        Core::Kernel::Get().CallEvent(idle_event, nullptr);
        
        if(Core::Kernel::Get().IsHalted()) {
            return false;
        }
    }
    
    // Smoothie Way: append block to the planner
    /*
    if(m_Planner->AppendBlock(target_actuator_position, m_NumberOfActuators, rate, total_distance, auxillary_move ? nullptr : &unit_vector, acceleration, m_IsG123)) {
        m_CompensatedMachinePosition = transformed_target_position;
        return true;
    }
    */

    // AxisEngine Way: create block and call OnBlockReceived for Conveyer to grab and complete
    // acceleration and velocity computation
    std::shared_ptr<Core::Block> block = std::make_shared<Core::Block>();
    
    if(total_distance > 0.0F) {
    
        block->nominal_speed = rate;
        block->nominal_rate = block->steps_event_count * rate / total_distance;
    } else {

        block->nominal_speed = 0.0F;
        block->nominal_rate = 0;
    }

    bool has_steps = false;
    for(int i = 0; i < m_NumberOfActuators; i++) {

        int steps = m_Actuators.at(i).StepsToTarget(target_actuator_position.at(i));
        
        if(steps != 0) {

            m_Actuators.at(i).UpdateLastMilestone(target_actuator_position.at(i), steps);
            has_steps = true;
        }
        
        block->direction_bits[i] = (steps < 0) ? 1 : 0;

        block->steps.at(i) = std::labs(steps);
    }

    if(!has_steps) {

        return false;
    }

    auto mi = std::max_element(block->steps.begin(), block->steps.end());
    block->steps_event_count = *mi;
    
    block->n_actuators = m_NumberOfActuators;
    block->millimeters = total_distance;
    block->acceleration = acceleration;
    block->unit_vector = unit_vector;
    block->is_g123 = m_IsG123;

    Core::BlockReceivedEvent on_block_received_event;
    Core::Kernel::Get().CallEvent(on_block_received_event, block);

    return true;
}
////////////////////////////////////////////////////////////////////////////////
// Machine Coordinate System - physical machine axes
// Work Coordinate System    - reference frame for workpiece
// Tool Coordinate System    - reference frame for tool
//
// TODO
// [ ] add loadtime and runtime configuration capability
// [ ] add other G and M codes required by standard
// [ ] implement work and tool coordinate systems and offsets
// [ ] implement extruder parameters with E argument
// [ ] implement Extruder object to offload from Robot?
// [ ] implement compensation transform
// [ ] implement arc G2 G3
// [ ] implement parameters with Q argument
// [ ] add actuator/stepper motor enum class separate from Axis enum class
////////////////////////////////////////////////////////////////////////////////
