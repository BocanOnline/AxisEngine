////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-Core
// file: StepperMotor.hpp
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "Pin.hpp"

namespace Core {

    class StepperMotor {

    public:
        StepperMotor(const Pin&, const Pin&, const Pin&);
        ~StepperMotor();
       
        void ChangeStepsPerMillimeter(float);
        void ChangeLastMilestone(float);
        void SetMaxRate(float);
        void SetAcceleration(float);

        float GetLastMilestone();
        float GetMaxRate();
        float GetAcceleration();
        
        bool IsSelected();

    private:
        Pin m_StepPin;
        Pin m_DirectionPin;
        Pin m_EnablePin;

        volatile int m_CurrentPositionSteps;
        int m_LastMilestoneSteps;
        int m_LastMilestoneMillimeters;

        float m_StepsPerMillimeter;
        float m_MaxRate;
        float m_Acceleration;

        volatile struct {
            bool selected: 1;
        };
        
    };

} // namespace Core
