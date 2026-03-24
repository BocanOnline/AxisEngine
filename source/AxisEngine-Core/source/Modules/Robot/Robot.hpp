////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-Core
// file: Robot.hpp
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <memory>
#include <vector>

#include "Module.hpp"

#include "Utils/Types.hpp"

namespace Core {

    class StepperMotor;
    class Gcode;
    class Solution;
    class Conveyer;
    class Planner;

    class Robot : public Module {

    public:
        Robot();
        virtual ~Robot() override;
        
        virtual void OnModuleLoaded() override;

        virtual void OnIdle(std::shared_ptr<void> argument) override;
        virtual void OnGcodeReceived(std::shared_ptr<void> argument) override;
        virtual void OnSecondTick(std::shared_ptr<void> argument) override;

    public:
        struct {
            bool m_InchMode: 1;
            bool m_AbsoluteMode: 1;
            bool m_EAbsoluteMode: 1;
            bool m_NextCommandIsMCS: 1;
            bool m_DisableSegmentation: 1;
            bool m_DisableArmSolution: 1;
            bool m_SegmentZMoves: 1;
            bool m_SaveG92: 1;
            bool m_SaveG54: 1;
            bool m_IsG123: 1;
            bool m_SoftEndstopEnabled: 1;
            bool m_SoftEndstopHalt: 1;
            bool m_NoLaser: 1;
            int  m_PlaneAxis0: 2;
            int  m_PlaneAxis1: 2;
            int  m_PlaneAxis2: 2;
        };

    private:
        void ProcessMove(std::shared_ptr<Core::Gcode>, Core::MotionMode);
        bool AppendLine(std::shared_ptr<Core::Gcode>, Core::CartesianCoordinates, float);
        bool ComputeArc(std::shared_ptr<Core::Gcode>, Core::CartesianCoordinates, Core::MotionMode);
        bool AppendArc(std::shared_ptr<Core::Gcode>, Core::CartesianCoordinates, float, bool);
        bool AppendMilestone(Core::CartesianCoordinates, float);

    private:
        std::shared_ptr<Solution>  m_MachineSolution;
        std::vector<StepperMotor>  m_Actuators;
       
        Core::CartesianCoordinates m_MachinePosition;
        Core::CartesianCoordinates m_CompensatedMachinePosition;
        Core::ActuatorCoordinates  m_ActuatorPosition;

        struct {
            float m_SeekRate;
            float m_FeedRate;
            float m_MillimetersPerLineSegment;
            float m_MillimetersPerArcSegment;
            float m_MillimetersMaxArcError;
            float m_DeltaSegmentsPerSecond;
            float m_SecondsPerMinute;
            float m_DefaultAcceleration;
            float m_GlobalMaxSpeed;
            int   m_NumberOfActuators;
            int   m_ArcCorrections;
            std::array<float, static_cast<int>(Core::Axis::MaxPositionAxes)> m_AxisMaxSpeed;
            std::array<float, static_cast<int>(Core::Axis::MaxPositionAxes)> m_SoftEndstopMin;
            std::array<float, static_cast<int>(Core::Axis::MaxPositionAxes)> m_SoftEndstopMax;
        };

    };

} // namespace Core
