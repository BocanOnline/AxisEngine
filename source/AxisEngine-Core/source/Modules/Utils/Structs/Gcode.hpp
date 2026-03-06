////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-Core
// file: Gcode.hpp
////////////////////////////////////////////////////////////////////////////////
#pragma once


#include <map>

namespace Core {

    struct Gcode {

        bool has_g = 0;
        bool has_m = 0;

        int command; 

        std::map<char, float> args; 
    };

} // namespace Core

////////////////////////////////////////////////////////////////////////////////
// g-code format:
//
// M3 S1000                         ; this is a comment
// M8                               ; this is a comment
// M250
// G1 X50.0000 Y70.0000 Z0.0000     ; this is a comment
//
// description:
//  - first character is 'G' or 'M"
//  - first character immediately followed by command code
//  - arguments are separated by ' '
//  - arguments are of form <char><float>
//  - comments begin with ; and are not machine executable
//  - comments always at the end of the line
////////////////////////////////////////////////////////////////////////////////
