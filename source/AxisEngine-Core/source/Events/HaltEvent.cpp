//
// ProjectAxisEngine
// HaltEvent.cpp
//

#include <string>

#include "HaltEvent.hpp"

Core::HaltEvent::HaltEvent() {}

Core::HaltEvent::~HaltEvent() {}

std::string Core::HaltEvent::GetName() const {

    return "HALT";
}
