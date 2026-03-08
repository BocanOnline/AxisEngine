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

#include "../Kernel.hpp"

#include "../Events/IdleEvent.hpp"
#include "../Events/GcodeReceivedEvent.hpp"
#include "../Events/SecondTickEvent.hpp"

#include "Modules/Utils/Robot/RobotTypes.hpp"
#include "Utils/Hardware/StepperMotor.hpp"
#include "Utils/Hardware/Pin.hpp"

#include "Utils/Robot/Solutions/CartesianSolution.hpp"

#include "Robot.hpp"


Core::Robot::Robot() {

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
    for(int i = 0; i < c_Max_Actuators; i++) {

        std::array<Core::Pin, 3> pins ;
        for(int j = 0; j < 3; j++) {
            pins.at(j).Set(j);
        }
       
        StepperMotor sm(pins.at(0), pins.at(1), pins.at(2));
        m_Actuators.push_back(sm);

        m_Actuators.at(i).ChangeStepsPerMillimeter(100.0F);
        m_Actuators.at(i).SetMaxRate(30000.0F / 60.0);
        m_Actuators.at(i).SetAcceleration(100.0F);
    }
    
    std::cout << "[Robot.cpp] StepperMotors initialized..." << std::endl;

    // set actuator positions to current cartesian position (X0, Y0, Z0) 
    m_MachinePosition = { 0.0F, 0.0F, 0.0F };
    m_MachineSolution->CartesianToActuator(m_MachinePosition, m_ActuatorPosition);
    for(int i = 0; i < c_Max_Actuators; i++) {
        m_Actuators.at(i).ChangeLastMilestone(m_ActuatorPosition.at(i));
    }
    
    std::cout << "[Robot.cpp] Actuator Positions initialized..." << std::endl;

    // set endstop positions
    m_SoftEndstopEnabled = false;
    m_SoftEndstopHalt = true;

    m_SoftEndstopMin = { 0.0F, 0.0F, 0.0F };
    m_SoftEndstopMax = { 200.0F, 200.0F, 50.0F };
    
    std::cout << "[Robot.cpp] Endstop Positions initialized..." << std::endl;
}

void Core::Robot::OnIdle(std::shared_ptr<void> argument) {

    std::cout << "[Robot.cpp] Robot called by IdleEvent..." << std::endl;
}

void Core::Robot::OnGcodeReceived(std::shared_ptr<void> argument) {

    std::cout << "[Robot.cpp] Robot called by GcodeReceivedEvent..." << std::endl; 
}

void Core::Robot::OnSecondTick(std::shared_ptr<void> argument) {

    std::cout << "[Robot.cpp] Robot called by SecondTickEvent..." << std::endl;
}
////////////////////////////////////////////////////////////////////////////////
// TODO
// [ ] add loadtime and runtime configuration capability
////////////////////////////////////////////////////////////////////////////////
