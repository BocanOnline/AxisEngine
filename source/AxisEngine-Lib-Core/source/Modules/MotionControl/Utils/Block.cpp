////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-Lib-Core
// file: Block.cpp
////////////////////////////////////////////////////////////////////////////////

#include "Block.hpp"
        
int    Core::Block::s_NumberOfActuators  = 0;
double Core::Block::s_FloatingPointScale = 0;

Core::Block::Block() {

    IsReady = false;
    Steps.fill(0);
    StepsEventCount = 0;
    NominalRate = 0.0F;
    NominalSpeed = 0.0F;
    Distance = 0.0F;
    EntrySpeed = 0.0F;
    ExitSpeed = 0.0F;
    Acceleration = 100.0F;
    InitialRate = 0.0F;
    AccelerateUntil = 0;
    DecelerateAfter = 0;
    DirectionBits = 0;
    RecalculateFlag = false;
    NominalLengthFlag = false;
    MaxEntrySpeed = 0.0F;
    IsTicking = false;
    IsG123 = false;
    Locked = false;
    TotalMoveTicks = 0;

    MotorTickData.reserve(s_NumberOfActuators);
    for(int i = 0; i < s_NumberOfActuators; i++) {

        TickData data;
        data.StepsPerTick = 0;
        data.Counter = 0;
        data.AccelerationChange = 0;
        data.DecelerationChange = 0;
        data.PlateauRate = 0;
        data.StepsToMove = 0;
        data.StepCount = 0;
        data.NextAccelerationEvent = 0;

        MotorTickData.push_back(data);
    }
}

void Core::Block::Initialize(int n) {

    std::cout << "[Block.cpp] Block initialized..." << std::endl; 

    s_NumberOfActuators = n;
    s_FloatingPointScale = static_cast<double>(1LL<<62) / std::pow(static_cast<double>(Core::Kernel::Get().GetStepTickerFrequency()), 2.0);
}

void Core::Block::MakeReady() {

    IsReady = true;
}

float Core::Block::CalculateReversePass(float exit_speed) {

    if(EntrySpeed != MaxEntrySpeed) {
    
        if(!NominalLengthFlag && MaxEntrySpeed > exit_speed) {

            float max_entry_speed = CalculateMaxAllowableSpeed(-Acceleration, exit_speed, Distance);

            EntrySpeed = std::min(max_entry_speed, MaxEntrySpeed);

            return EntrySpeed;
        } else {

            EntrySpeed = MaxEntrySpeed;
        }
    }
    return EntrySpeed;
}

float Core::Block::CalculateForwardPass(float prev_max_exit_speed) {

    if(prev_max_exit_speed > NominalSpeed) {

        prev_max_exit_speed = NominalSpeed;
    }
    if(prev_max_exit_speed > MaxEntrySpeed) {

        prev_max_exit_speed = MaxEntrySpeed;
    }
    if(prev_max_exit_speed <= EntrySpeed) {

        // accel limited
        EntrySpeed = prev_max_exit_speed;
        RecalculateFlag = false;
    }

    // else, decel limited; do nothing

    return CalculateMaxExitSpeed();
}

void Core::Block::CalculateTrapezoid(float entry_speed, float exit_speed) {

    // if block is currently executing, do nothing
    if(IsTicking) 
        return;

    float initial_rate = NominalRate * (entry_speed / NominalSpeed);
    float final_rate = NominalRate * (exit_speed / NominalSpeed);
    float acceleration_per_second = (Acceleration * StepsEventCount) / Distance;
    float maximum_possible_rate = std::sqrtf((StepsEventCount * acceleration_per_second) + ((std::powf(initial_rate, 2) + std::powf(final_rate, 2)) / 2.0F));

    MaximumRate = std::min(maximum_possible_rate, NominalRate);

    float time_to_accelerate = (MaximumRate - initial_rate) / acceleration_per_second;
    float time_to_decelerate = (final_rate - MaximumRate)   / -acceleration_per_second;
    float plateau_time;
    
    if(maximum_possible_rate > NominalRate) {

        float acceleration_distance = ((initial_rate + MaximumRate) / 2.0F) * time_to_accelerate;
        float deceleration_distance = ((MaximumRate + final_rate)   / 2.0F) * time_to_decelerate;
        float plateau_distance      = StepsEventCount - acceleration_distance - deceleration_distance;

        plateau_time = plateau_distance / MaximumRate;
    }

    float total_move_time = time_to_accelerate + time_to_decelerate + plateau_time;
    
    int acceleration_ticks = std::floorf(time_to_accelerate * Core::Kernel::Get().GetStepTickerFrequency());
    int deceleration_ticks = std::floorf(time_to_decelerate * Core::Kernel::Get().GetStepTickerFrequency());
    int total_move_ticks   = std::floorf(total_move_time    * Core::Kernel::Get().GetStepTickerFrequency());

    float acceleration_time = acceleration_ticks / Core::Kernel::Get().GetStepTickerFrequency();
    float deceleration_time = deceleration_ticks / Core::Kernel::Get().GetStepTickerFrequency();

    float acceleration_in_steps = (acceleration_time > 0.0F) ? (MaximumRate - initial_rate) / acceleration_time : 0;
    float deceleration_in_steps = (deceleration_time > 0.0F) ? (MaximumRate - final_rate  ) / deceleration_time : 0;

    Locked = true;

    AccelerateUntil = acceleration_ticks;
    DecelerateAfter = total_move_ticks - deceleration_ticks;
    TotalMoveTicks  = total_move_ticks;
    InitialRate     = initial_rate;
    ExitSpeed       = exit_speed;

    PrepareForStepTicker(acceleration_in_steps, deceleration_in_steps);

    Locked = false;
}
    
void Core::Block::PrepareForStepTicker(float acceleration_in_steps, float deceleration_in_steps) {

    float inv = 1.0F / StepsEventCount;

    double acceleration_per_tick = acceleration_in_steps * s_FloatingPointScale;
    double deceleration_per_tick = deceleration_in_steps * s_FloatingPointScale;

    for(int m = 0; m < s_NumberOfActuators; m++) {

        int steps = Steps.at(m);
        MotorTickData.at(m).StepsToMove = steps;
        if(steps == 0) 
            continue;

        float aratio = inv * steps;

        MotorTickData.at(m).StepsPerTick = static_cast<int>(std::round((static_cast<double>(InitialRate) * aratio) / Core::Kernel::Get().GetStepTickerFrequency()) * (1LL<<62));
        MotorTickData.at(m).Counter = 0;
        MotorTickData.at(m).StepCount = 0;
        MotorTickData.at(m).NextAccelerationEvent = TotalMoveTicks + 1;

        double acceleration_change = 0;
        if(AccelerateUntil != 0) {
    
            MotorTickData.at(m).NextAccelerationEvent = AccelerateUntil;
            acceleration_change = acceleration_per_tick;

        } else if(DecelerateAfter == 0) {

            acceleration_change = -deceleration_per_tick;

        } else if(DecelerateAfter != TotalMoveTicks) {

            MotorTickData.at(m).NextAccelerationEvent = DecelerateAfter;
        }

        MotorTickData.at(m).AccelerationChange = static_cast<int>(std::round(acceleration_change * aratio));
        MotorTickData.at(m).DecelerationChange = static_cast<int>(std::round(deceleration_per_tick * aratio));
        MotorTickData.at(m).PlateauRate        = static_cast<int>(std::round(((MaximumRate * aratio) / Core::Kernel::Get().GetStepTickerFrequency()) * (1LL<<62)));
    }
}
        
float Core::Block::CalculateMaxAllowableSpeed(float acceleration, float target_velocity, float distance) {

    return std::sqrtf(target_velocity * target_velocity - 2.0F * acceleration * distance);
}

float Core::Block::CalculateMaxExitSpeed() {

    if(IsTicking) {

        return ExitSpeed;
    }

    if(NominalLengthFlag) {

        return NominalSpeed;
    }

    float max = CalculateMaxAllowableSpeed(-Acceleration, EntrySpeed, Distance);

    return std::min(max, NominalSpeed);
}
