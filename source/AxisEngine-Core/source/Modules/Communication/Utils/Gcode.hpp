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
#include <cmath>

namespace Core {

    struct Gcode {
    
    public:
        float get_fvalue(char letter) {
            
            if(auto iterator = word.find(letter); iterator != word.end()) {
                return iterator->second;
            }
            else {
                return std::nan("");
            } 
        }
        
        int get_ivalue(char letter) {
            
            if(auto iterator = word.find(letter); iterator != word.end()) {
                return static_cast<int>(iterator->second);
            }
            else {
                return std::nan("");
            } 
        }
        
        void add_word(char letter, float number) {
            
            word.insert(std::pair<char, float>(letter, number));
        }

    public:
        struct {
            bool has_g: 1 = 0;
            bool has_m: 1 = 0;
            bool has_x: 1 = 0;
            bool has_y: 1 = 0;
            bool has_z: 1 = 0;
            bool has_e: 1 = 0;
            bool has_a: 1 = 0;
            bool has_b: 1 = 0;
            bool has_c: 1 = 0;
            bool has_f: 1 = 0;
            bool has_s: 1 = 0;
        };

        std::map<char, float> word; 

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
