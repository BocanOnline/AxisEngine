////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-Core
// file: Planner.cpp
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <memory>

#include "Kernel.hpp"

#include "Events/BlockReadyEvent.hpp"

#include "Utils/Block.hpp"

#include "Planner.hpp"


Core::Planner::Planner() {

}

Core::Planner::~Planner() {

}

void Core::Planner::OnModuleLoaded() {

    Core::BlockReadyEvent on_block_ready_event;
    auto on_block_ready_function = [this](std::shared_ptr<void> argument)
                                { this->Core::Planner::OnBlockReady(argument); };
    this->RegisterForEvent(on_block_ready_event, on_block_ready_function);

    std::cout << "[Planner.cpp] Planner registered for BlockReadyEvent..." << std::endl;
}

void Core::Planner::OnBlockReady(std::shared_ptr<void> argument) {

    std::shared_ptr<Core::Block> block = std::static_pointer_cast<Core::Block>(argument);
}
    
bool Core::Planner::AppendBlock(std::shared_ptr<Core::Block> block) {


    return false;
}

////////////////////////////////////////////////////////////////////////////////
// TODO
// [ ] Calculate speed profile of new block in OnBlockReady()
// [ ] Add block to Conveyer in AppendBlock()
////////////////////////////////////////////////////////////////////////////////
