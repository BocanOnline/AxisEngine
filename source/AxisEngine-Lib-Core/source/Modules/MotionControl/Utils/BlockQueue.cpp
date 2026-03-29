////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-Core
// file: BlockQueue.cpp
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <memory>

#include "Block.hpp"
#include "BlockQueue.hpp"


Core::BlockQueue::BlockQueue() { 

    m_HeadIndex = -1;
    m_MarkIndex = -1;
    m_TailIndex = -1;
    m_IsFull = false;
}
Core::BlockQueue::BlockQueue(int length) { 

    m_HeadIndex = -1;
    m_MarkIndex = -1;
    m_TailIndex = -1;

    m_Length = length;
    m_Blocks.reserve(length);

    for(int i = 0; i < length; i++) {

        std::shared_ptr<Core::Block> space;
        m_Blocks.push_back(space);
    }

    m_HeadIndex = 0;
}

Core::BlockQueue::~BlockQueue() { }

void Core::BlockQueue::SetLength(int length) { 

    m_Length = length;
    m_Blocks.reserve(length);

    for(int i = 0; i < length; i++) {

        std::shared_ptr<Core::Block> space;
        m_Blocks.push_back(space);
    }

    m_HeadIndex = 0;
}

std::shared_ptr<Core::Block> Core::BlockQueue::BlockRef(int i) { 

    if(i < 0) {
        
        i = m_Length-1;
    }

    if(i >= m_Length) {

        i = 0;
    }

    return m_Blocks.at(i); 
}

void Core::BlockQueue::PushBlock(std::shared_ptr<Core::Block> block) {

    // blockqueue has not been initialized; 'should' never happen
    if(m_HeadIndex < 0) {

        std::cout << "[BlockQueue.cpp] BlockQueue is not initialized..." << std::endl;
        return;
    }

    m_Blocks.at(m_HeadIndex) = block;
}

void Core::BlockQueue::PopBlock() {

    m_Blocks.at(m_TailIndex).reset();
}

void Core::BlockQueue::IncrementHeadIndex() {

}

void Core::BlockQueue::IncrementMarkIndex() {

}

void Core::BlockQueue::IncrementTailIndex() {

}

bool Core::BlockQueue::HasReadyBlock() {
   
    if(m_MarkIndex != m_HeadIndex) {
        return true;
    } else {
        return false;
    }
}

bool Core::BlockQueue::HasConsumedBlock() {

    if(m_TailIndex != m_MarkIndex) {
        return true;
    } else {
        return false;
    }
}
