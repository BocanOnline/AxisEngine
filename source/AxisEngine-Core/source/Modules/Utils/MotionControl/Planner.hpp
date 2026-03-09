////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-Core
// file: Planner.hpp
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "Modules/Utils/MotionControl/Types.hpp"

namespace Core {

    class Planner {

    public:
        Planner();
        ~Planner();

        bool AppendBlock(Core::ActuatorCoordinates, int, float, float, float*, float, bool);
        
    };

} // namespace Core
