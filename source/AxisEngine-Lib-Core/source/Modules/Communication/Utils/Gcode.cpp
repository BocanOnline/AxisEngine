////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-Core
// file: Gcode.cpp
////////////////////////////////////////////////////////////////////////////////

#include "Gcode.hpp"


float Core::Gcode::GetValue_F(char letter) {

    if(auto iterator = m_Word.find(letter); iterator != m_Word.end()) {
        return iterator->second;
    }
    else {
        return std::nan("");
    } 
}   

int Core::Gcode::GetValue_I(char letter) {

    if(auto iterator = m_Word.find(letter); iterator != m_Word.end()) {
        return static_cast<int>(iterator->second);
    }
    else {
        return std::nan("");
    } 
}

void Core::Gcode::AddWord(char letter, float number) {

    m_Word.insert(std::pair<char, float>(letter, number));
}
