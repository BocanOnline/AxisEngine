//
// ProjectAxisEngine
// SecondTickEvent.cpp
//

#include <string>

#include "SecondTickEvent.hpp"

Core::SecondTickEvent::SecondTickEvent() {}

Core::SecondTickEvent::~SecondTickEvent() {}

std::string Core::SecondTickEvent::GetName() const {

    return "SECOND_TICK";
}
