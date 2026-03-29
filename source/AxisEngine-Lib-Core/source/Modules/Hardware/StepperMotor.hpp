////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-Lib-Core
// file: StepperMotor.hpp
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "Utils/Pin.hpp"

namespace Core {

    class StepperMotor : public Module {

    public:
        StepperMotor(const Pin&, const Pin&, const Pin&);
        ~StepperMotor();

        virtual void OnModuleLoaded();

        virtual void OnHalt(std::shared_ptr<void> argument);
        virtual void OnEnable(std::shared_ptr<void> argument);

        void ChangeStepsPerMillimeter(float);
        void ChangeLastMilestone(float);
        void UpdateLastMilestone(float, int);
        void SetMaxRate(float);
        void SetAcceleration(float);

        float GetLastMilestone();
        float GetMaxRate();
        float GetAcceleration();
        
        bool IsSelected();

        int StepsToTarget(float);

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
            bool m_Selected: 1;
        };
        
    };

} // namespace Core
