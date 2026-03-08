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
#include <vector>

#include "../Kernel.hpp"

#include "../Events/IdleEvent.hpp"
#include "../Events/GcodeReceivedEvent.hpp"
#include "../Events/SecondTickEvent.hpp"

#include "Utils/Hardware/StepperMotor.hpp"
#include "Utils/Hardware/Pin.hpp"

#include "Utils/Messages/Gcode.hpp"

#include "Utils/MotionControl/Solutions/CartesianSolution.hpp"
#include "Utils/MotionControl/Conveyer.hpp"
#include "Utils/MotionControl/Planner.hpp"
#include "Utils/MotionControl/Types.hpp"

#include "Robot.hpp"


Core::Robot::Robot() {
    
    m_Conveyer = std::make_shared<Conveyer>();
    m_Planner  = std::make_shared<Planner>();

    m_NumberOfActuators = 0;

    std::cout << "[Robot.cpp] Robot created..." << std::endl;
}

Core::Robot::~Robot() {

    std::cout << "[Robot.cpp] Robot destroyed..." << std::endl;
}
    
void Core::Robot::OnModuleLoaded() {

    Core::IdleEvent on_idle_event;
    auto on_idle_function = [this](std::shared_ptr<void> argument)
                                { this->Core::Robot::OnIdle(argument); };

    this->RegisterForEvent(on_idle_event, on_idle_function);

    std::cout << "[Robot.cpp] Robot registered for IdleEvent..." << std::endl;
    
    Core::GcodeReceivedEvent on_gcode_received_event;
    auto on_gcode_received_function = [this](std::shared_ptr<void> argument)
                                { this->Core::Robot::OnGcodeReceived(argument); };
   
    this->RegisterForEvent(on_gcode_received_event, on_gcode_received_function);

    std::cout << "[Robot.cpp] Robot registered for GcodeReceivedEvent..." << std::endl;
    
    Core::SecondTickEvent on_second_tick_event;
    auto on_second_tick_function = [this](std::shared_ptr<void> argument)
                                { this->Core::Robot::OnSecondTick(argument); };
   
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
    m_MachinePosition = { 0.0F, 0.0F, 0.0F };
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
    
    if(gcode->has_g) {
        switch(gcode->get_ivalue('G')) {
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

void Core::Robot::ProcessMove(std::shared_ptr<Core::Gcode> gcode, Core::MotionMode motion_mode) {
    
    // extract parameters from gcode (X Y Z E A B C)
    // NOTE: this is how Smoothie did it, however we compare to gcode directly below

    // calculate target position in machine coordinates (except compensation transform) X Y Z
    Core::CartesianCoordinates target_position;

    if(!m_NextCommandIsMCS) {

        // work coordinate system
        if(m_AbsoluteMode) {
        
            // absolute mode; need to add wcs and tcs offsets 
            if(gcode->has_x) {
                target_position.at(static_cast<int>(Core::Axis::X)) = gcode->get_fvalue('X');
            }
            if(gcode->has_y) {
                target_position.at(static_cast<int>(Core::Axis::Y)) = gcode->get_fvalue('Y');
            }
            if(gcode->has_z) {
                target_position.at(static_cast<int>(Core::Axis::Z)) = gcode->get_fvalue('Z');
            }
        } else { 

            // relative mode 
            if(gcode->has_x) {
                target_position.at(static_cast<int>(Core::Axis::X)) = gcode->get_fvalue('X') + m_MachinePosition.at(static_cast<int>(Core::Axis::X));
            }
            if(gcode->has_y) {
                target_position.at(static_cast<int>(Core::Axis::Y)) = gcode->get_fvalue('Y') + m_MachinePosition.at(static_cast<int>(Core::Axis::X));
            }
            if(gcode->has_z) {
                target_position.at(static_cast<int>(Core::Axis::Z)) = gcode->get_fvalue('Z') + m_MachinePosition.at(static_cast<int>(Core::Axis::X));
            }
        }
    } else {

        // machine coordinate system
        if(gcode->has_x) {
            target_position.at(static_cast<int>(Core::Axis::X)) = gcode->get_fvalue('X');
        }
        if(gcode->has_y) {
            target_position.at(static_cast<int>(Core::Axis::Y)) = gcode->get_fvalue('Y');
        }
        if(gcode->has_z) {
            target_position.at(static_cast<int>(Core::Axis::Z)) = gcode->get_fvalue('Z');
        }
    }

    // calculate target in machine coordinates (except compensation transform) E A B C
    // TODO

    // process changes to SeekRate and FeedRate with F argument
    if(gcode->has_f) {
        if(motion_mode == Core::MotionMode::Seek) {
            m_SeekRate = gcode->get_fvalue('F');
        } else {
            m_FeedRate = gcode->get_fvalue('F');
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

    return false;
}

bool Core::Robot::ComputeArc(std::shared_ptr<Core::Gcode> gcode, Core::CartesianCoordinates target_position, Core::MotionMode motion_mode) {

    return false;
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
////////////////////////////////////////////////////////////////////////////////
