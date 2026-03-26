////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-Core
// file: BlockReceivedEvent.cpp
////////////////////////////////////////////////////////////////////////////////
#include <string>

#include "BlockReceivedEvent.hpp"

Core::BlockReceivedEvent::BlockReceivedEvent() {}

Core::BlockReceivedEvent::~BlockReceivedEvent() {}

std::string Core::BlockReceivedEvent::GetName() const {

    return "BLOCK_READY";
}
