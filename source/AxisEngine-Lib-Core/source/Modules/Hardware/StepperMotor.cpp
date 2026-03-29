////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-Lib-Core
// file: StepperMotor.cpp
////////////////////////////////////////////////////////////////////////////////

#include "StepperMotor.hpp"

Core::StepperMotor::StepperMotor(const Pin& step, const Pin& dir, const Pin& en) :
    m_StepPin(step), m_DirectionPin(dir), m_EnablePin(en) {

}

Core::StepperMotor::~StepperMotor() {

}

void Core::StepperMotor::OnModuleLoaded() {

}

void Core::StepperMotor::OnHalt(std::shared_ptr<void> argument) {

}

void Core::StepperMotor::OnEnable(std::shared_ptr<void> argument) {

}

void Core::StepperMotor::ChangeStepsPerMillimeter(float new_steps) {

    m_StepsPerMillimeter = new_steps;
    m_LastMilestoneSteps = lroundf(m_LastMilestoneMillimeters * m_StepsPerMillimeter);
    m_CurrentPositionSteps = m_LastMilestoneSteps;
}

void Core::StepperMotor::ChangeLastMilestone(float new_milestone) {
    
    m_LastMilestoneMillimeters = new_milestone;
    m_LastMilestoneSteps = lroundf(m_LastMilestoneMillimeters * m_StepsPerMillimeter);
    m_CurrentPositionSteps = m_LastMilestoneSteps;
}

void Core::StepperMotor::UpdateLastMilestone(float mm, int steps) {

    m_LastMilestoneMillimeters = mm;
    m_LastMilestoneSteps += steps;
}

void Core::StepperMotor::SetMaxRate(float new_max_rate) {

    m_MaxRate = new_max_rate;
}

void Core::StepperMotor::SetAcceleration(float new_acceleration) {

    m_Acceleration = new_acceleration;
}

float Core::StepperMotor::GetLastMilestone() {

    return m_LastMilestoneMillimeters;
}

float Core::StepperMotor::GetMaxRate() {

    return m_MaxRate;
}

float Core::StepperMotor::GetAcceleration() {

    return m_Acceleration;
}

bool Core::StepperMotor::IsSelected() {

    return m_Selected;

}

int Core::StepperMotor::StepsToTarget(float target) {
    // TODO: this is not working yet
    // returns a non-zero value for debugging purposes for now

    //int target_steps = std::lroundf(target * m_StepsPerMillimeter);
    //return target_steps - m_LastMilestoneSteps;

    return 1;
}
////////////////////////////////////////////////////////////////////////////////
// TODO
// [ ] fix StepsToTarget method
