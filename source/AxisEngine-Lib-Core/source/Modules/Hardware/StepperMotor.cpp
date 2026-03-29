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

void Core::StepperMotor::SetMaxRate(float new_max_rate) {

    m_MaxRate = new_max_rate;
}

void Core::StepperMotor::SetAcceleration(float new_acceleration) {

    m_Acceleration = new_acceleration;
}
