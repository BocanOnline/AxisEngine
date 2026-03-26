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

#include <array>
//#include <bitset>

#include "Types.hpp"

namespace Core {

    class Block {

    public:
        Block() = default;
        ~Block() = default;

        void MakeReady();
        
        std::array<int, 3> steps;           // number of steps for each axis for this block
        int steps_event_count;              // steps for longest axis
        float nominal_rate;                 // nominal rate in steps per second
        float nominal_speed;                // nominal speed in mm per second
        float millimeters;                  // distance for this move
        //float entry_speed;                  //  
        //float exit_speed;                   //
        float acceleration;                 // acceleration for this block
        //float initial_rate;                 // initial rate in steps per second
        //float maximum_rate;                 //
        //float max_entry_speed;              //
        
        Core::CartesianCoordinates unit_vector;
        
        // tick information needed for this block; applies to all motors
        //int accelerate_until;               //
        //int decelerate_after;               //
        //int total_move_ticks;               //
        //std::bitset<3> direction_bits;      // direction for eaach axis, relative to direction port mask

        // data needed to determine when each motor needs to be issued a step
        /*
        using tickinfo_t = struct {
            int steps_per_tick;             // 2.62 fixed point
            int counter;                    // 2.62 fixed point
            int acceleration_change;        // 2.62 fixed point signed
            int deceleration_change;        // 2.62 fixed point
            int plateau_rate;               // 2.62 fixed point
            int steps_to_move;              //
            int step_count;                 //
            int next_accel_event;           //
        };
        */

        //tickinfo_t *tick_info;

        int n_actuators;                    //

        struct {
            //bool recalculate_flag: 1;       // planner flag to recalculate trapezoids on entry juntion
            //bool nominal_length_flag: 1;    // planner flag for nominal speed always reached
            //bool is_ready: 1;               // 
            bool primary_axis: 1;           // set if this move is a primary axis
            bool is_g123: 1;                // set if this is a G1 or G2 or G3
            //volatile bool is_ticking: 1;    // set when block is being actively ticked by the stepticker
            //volatile bool locked: 1;        // set to true when critial data is being updated, stepticker has to skip if set
            //int s_value: 12;                // for laser 1.11 fixed point
        };

    };

} // namespace Core


