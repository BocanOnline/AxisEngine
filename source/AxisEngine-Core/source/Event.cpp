//
// ProjectAxisEngine
// Event.cpp
//

#include "Event.hpp"

// Events are created on the stack by the Module that calls them.
// Their lifetime ends when the event is handled and they fall out of scope.
