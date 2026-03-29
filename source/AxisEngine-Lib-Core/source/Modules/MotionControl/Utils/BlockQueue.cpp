////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-Lib-Core
// file: BlockQueue.cpp
////////////////////////////////////////////////////////////////////////////////

#include "Block.hpp"
#include "BlockQueue.hpp"


Core::BlockQueue::BlockQueue() { 

    m_HeadIndex = -1;
    m_MarkIndex = -1;
    m_TailIndex = -1;
    m_IsFull = false;
    m_IsEmpty = true;
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
    m_MarkIndex = 0;
    m_TailIndex = 0;
    m_IsFull = false;
    m_IsEmpty = true;
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
    m_MarkIndex = 0;
    m_TailIndex = 0;
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

    m_IsEmpty = false;
    
    for(auto space : m_Blocks) {
        if(space == nullptr) {

            m_IsFull = false;
            return;
        }
    }

    m_IsFull = true;
}

void Core::BlockQueue::PopBlock() {

    m_Blocks.at(m_TailIndex).reset();

    m_IsFull = false;

    for(auto space : m_Blocks) {
        if(space != nullptr) {

            m_IsEmpty = false;
            return;
        }
    }
    m_IsEmpty = true;
}

void Core::BlockQueue::IncrementHeadIndex() {

    m_HeadIndex--;
    if(m_HeadIndex < 0) {
        m_HeadIndex = m_Length - 1;
    }
}

void Core::BlockQueue::IncrementMarkIndex() {

    m_MarkIndex--;
    if(m_MarkIndex < 0) {
        m_MarkIndex = m_Length - 1;
    }
}

void Core::BlockQueue::IncrementTailIndex() {

    m_TailIndex--;
    if(m_TailIndex < 0) {
        m_TailIndex = m_Length - 1;
    }
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
