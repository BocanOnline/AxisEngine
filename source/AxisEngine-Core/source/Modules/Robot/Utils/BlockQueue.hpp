////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-Core
// file: BlockQueue.hpp
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <memory>
#include <vector>

#include "Block.hpp"

namespace Core {

    class BlockQueue {

    public:
        BlockQueue() = default;
        BlockQueue(int);
        ~BlockQueue();

        void SetLength(int);

        std::shared_ptr<Core::Block> HeadRef() { return m_BlockQueue.at(m_HeadIndex); }
        std::shared_ptr<Core::Block> MarkRef() { return m_BlockQueue.at(m_MarkIndex); }
        std::shared_ptr<Core::Block> TailRef() { return m_BlockQueue.at(m_TailIndex); }

        std::vector<std::shared_ptr<Core::Block>>::iterator Begin() { return m_BlockQueue.begin(); }
        std::vector<std::shared_ptr<Core::Block>>::iterator End()   { return m_BlockQueue.end();   }
        
        std::vector<std::shared_ptr<Core::Block>>::reverse_iterator r_Begin() { return m_BlockQueue.rbegin(); }
        std::vector<std::shared_ptr<Core::Block>>::reverse_iterator r_End()   { return m_BlockQueue.rend();   }
        
    private:
        std::vector<std::shared_ptr<Core::Block>> m_BlockQueue;

        int m_Length;

        int m_HeadIndex;
        int m_MarkIndex;
        int m_TailIndex;
    };
}

////////////////////////////////////////////////////////////////////////////////
//
// TODO
////////////////////////////////////////////////////////////////////////////////
