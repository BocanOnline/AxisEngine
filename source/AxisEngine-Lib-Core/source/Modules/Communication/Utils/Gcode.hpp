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

namespace Core {

    class Gcode {
    
    public:

        Gcode() = default;
        ~Gcode() = default;

        float GetValue_F(char);
        int   GetValue_I(char);

        void AddWord(char, float);

    public:
        struct {
            bool Has_G: 1 = 0;
            bool Has_M: 1 = 0;
            bool Has_X: 1 = 0;
            bool Has_Y: 1 = 0;
            bool Has_Z: 1 = 0;
            bool Has_E: 1 = 0;
            bool Has_A: 1 = 0;
            bool Has_B: 1 = 0;
            bool Has_C: 1 = 0;
            bool Has_F: 1 = 0;
            bool Has_S: 1 = 0;
        };

    private:
        std::map<char, float> m_Word; 

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
//  - arguments are expected in order X Y Z E A B C for G0/G1/G2/G3
////////////////////////////////////////////////////////////////////////////////
