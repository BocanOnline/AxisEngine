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
        BlockQueue();
        BlockQueue(int);
        ~BlockQueue();

        void SetLength(int);

        std::shared_ptr<Core::Block> HeadRef() { return m_Blocks.at(m_HeadIndex); }
        std::shared_ptr<Core::Block> MarkRef() { return m_Blocks.at(m_MarkIndex); }
        std::shared_ptr<Core::Block> TailRef() { return m_Blocks.at(m_TailIndex); }
        
        std::shared_ptr<Core::Block> BlockRef(int i);

        std::vector<std::shared_ptr<Core::Block>>::iterator Begin() { return m_Blocks.begin(); }
        std::vector<std::shared_ptr<Core::Block>>::iterator End()   { return m_Blocks.end();   }
        
        std::vector<std::shared_ptr<Core::Block>>::reverse_iterator r_Begin() { return m_Blocks.rbegin(); }
        std::vector<std::shared_ptr<Core::Block>>::reverse_iterator r_End()   { return m_Blocks.rend();   }

        void PushBlock(std::shared_ptr<Core::Block>);
        void PopBlock();

        void IncrementHeadIndex();
        void IncrementMarkIndex();
        void IncrementTailIndex();

        bool IsFull() { return m_IsFull; }
        bool IsEmpty() { return m_IsEmpty; }

        bool HasReadyBlock();
        bool HasConsumedBlock();

    private:
        std::vector<std::shared_ptr<Core::Block>> m_Blocks;

        int m_Length;

        int m_HeadIndex;
        int m_MarkIndex;
        int m_TailIndex;

        struct {

            bool m_IsFull: 1;
            bool m_IsEmpty: 1;
        };
    };
}

////////////////////////////////////////////////////////////////////////////////
//
// TODO
////////////////////////////////////////////////////////////////////////////////
