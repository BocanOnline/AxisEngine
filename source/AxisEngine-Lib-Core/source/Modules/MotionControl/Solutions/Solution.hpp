////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-Core
// file: Solution.hpp
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "Modules/MotionControl/Utils/Types.hpp"

namespace Core {

    class Solution {

    public:
        Solution() {}
        virtual ~Solution() = default;

        virtual void CartesianToActuator(const CartesianCoordinates, ActuatorCoordinates&) = 0;
        virtual void ActuatorToCartesian(const ActuatorCoordinates, CartesianCoordinates&) = 0;

    };

} // namespace Core
