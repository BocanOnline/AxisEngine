////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-Core
// file: CartesianSolution.hpp
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "Solution.hpp"

#include "../Types.hpp"

namespace Core {

    class CartesianSolution : public Solution {

    public:
        CartesianSolution();
        virtual ~CartesianSolution() override;
       
        virtual void CartesianToActuator(const CartesianCoordinates, ActuatorCoordinates&) override;
        virtual void ActuatorToCartesian(const ActuatorCoordinates, CartesianCoordinates&) override;
       
    };

} // namespace Core
////////////////////////////////////////////////////////////////////////////////
// CartesianSolution
//
// - generally the most simple CNC machine solution
// - one motor per axis (or identical motors on same axis)
// - each motor drives the movement of each axis independent of other motors
////////////////////////////////////////////////////////////////////////////////
