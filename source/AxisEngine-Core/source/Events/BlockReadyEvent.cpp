////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-Core
// file: BlockReadyEvent.cpp
////////////////////////////////////////////////////////////////////////////////
#include <string>

#include "BlockReadyEvent.hpp"

Core::BlockReadyEvent::BlockReadyEvent() {}

Core::BlockReadyEvent::~BlockReadyEvent() {}

std::string Core::BlockReadyEvent::GetName() const {

    return "BLOCK_READY";
}
