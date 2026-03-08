////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-Core
// file: Types.hpp
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <array>

namespace Core {

    enum class Axis {

        X = 0,
        Y = 1,
        Z = 2,
        NumberOfPositionAxes = 3,
        A = 3,
        B = 4,
        C = 5,
        NumberOfRotationAxes = 3,
        Total = 6
    };

    enum class MotionMode {

        Seek = 0,
        Linear = 1,
        ClockwiseArc = 2,
        CounterArc = 3,
        None = 4,
    };

    const int c_Max_Actuators = 3;

    using CartesianCoordinates = std::array<float, static_cast<int>(Axis::NumberOfPositionAxes)>;
    using ActuatorCoordinates = std::array<float, c_Max_Actuators>;

} // namespace Core
////////////////////////////////////////////////////////////////////////////////
// TODO:
// [ ] add support for more than three axes in the future
//      axes of position (check)
//      axes of rotation (future)
// [ ] set c_Max_Actuators in config file
////////////////////////////////////////////////////////////////////////////////
