////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-Core
// file: Block.hpp
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <vector>
#include <array>
#include <bitset>

#include "Types.hpp"

namespace Core {

    class TickData {
   
    public:
        TickData() = default;
        ~TickData() = default;
        
        int StepsPerTick;
        int Counter;
        int AccelerationChange;
        int DecelerationChange;
        int PlateauRate;
        int StepsToMove;
        int StepCount;
        int NextAccelerationEvent;

    };

    class Block {

    public:
        Block();
        ~Block() = default;

        static void Initialize(int);

        void  MakeReady();
        void  CalculateTrapezoid(float, float);
        void  PrepareForStepTicker(float, float);

        float CalculateReversePass(float);
        float CalculateForwardPass(float);
        float CalculateMaxAllowableSpeed(float, float, float);
        float CalculateMaxExitSpeed();

    public:
        
        static int s_NumberOfActuators; 

        std::array<int, 3> Steps;           // number of steps for each axis for this block
        
        int   StepsEventCount;              // steps for longest axis
        float NominalRate;                  // nominal rate in steps per second
        float NominalSpeed;                 // nominal speed in mm per second
        float Distance;                     // distance for this move
        float EntrySpeed;                   //  
        float ExitSpeed;                    //
        float Acceleration;                 // acceleration for this block
        float MaxEntrySpeed;                //
        float MaxExitSpeed;
        float InitialRate;                  // initial rate in steps per second
        float MaximumRate;
        int   AccelerateUntil;              //
        int   DecelerateAfter;              //
        int   TotalMoveTicks;               //
        
        Core::CartesianCoordinates UnitVector;
        
        std::bitset<3> DirectionBits;       // direction for eaach axis, relative to direction port mask
        std::vector<Core::TickData> MotorTickData;

        struct {
            bool RecalculateFlag: 1;        // planner flag to recalculate trapezoids on entry juntion
            bool NominalLengthFlag: 1;      // planner flag for nominal speed always reached
            bool IsReady: 1;                // 
            bool PrimaryAxis: 1;            // set if this move is a primary axis
            bool IsG123: 1;                 // set if this is a G1 or G2 or G3
            volatile bool IsTicking: 1;     // set when block is being actively ticked by the stepticker
            volatile bool Locked: 1;        // set to true when critial data is being updated, stepticker has to skip if set
        };

    private:
        static double s_FloatingPointScale;
    };

} // namespace Core


