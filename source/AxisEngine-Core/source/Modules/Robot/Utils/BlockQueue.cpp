////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-Core
// file: BlockQueue.cpp
////////////////////////////////////////////////////////////////////////////////

#include <memory>

#include "Block.hpp"
#include "BlockQueue.hpp"


Core::BlockQueue::BlockQueue(int length) { 

    m_Length = length;
    m_BlockQueue.reserve(length);

    for(int i = 0; i < length; i++) {

        std::shared_ptr<Core::Block> block_space;
        m_BlockQueue.push_back(block_space);
    }
}

Core::BlockQueue::~BlockQueue() { 

    for(auto block_space : m_BlockQueue) {

        block_space.reset();
    }
}

void Core::BlockQueue::SetLength(int length) { 

    m_Length = length;
    m_BlockQueue.reserve(length);

    for(int i = 0; i < length; i++) {

        std::shared_ptr<Core::Block> block_space;
        m_BlockQueue.push_back(block_space);
    }
}
