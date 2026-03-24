////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-Core
// file: DoubleRingBuffer.hpp
////////////////////////////////////////////////////////////////////////////////
#pragma once


namespace Core {

    template<typename T>
    class DoubleRingBuffer;

    template<typename T>
    class DoubleRingBuffer {

    public: 
        DoubleRingBuffer();
        DoubleRingBuffer(unsigned int length);
        ~DoubleRingBuffer();

        T& Head();
        T& Mark();
        T& Tail();

        void PushFront(T&);
        T& PopBack();

        T* HeadRef();
        T* MarkRef();
        T* TailRef();

        void ProduceHead();
        void ConsumeTail();

        bool IsEmpty();
        bool IsFull();

        bool Resize(unsigned int length);

        T& At(unsigned int);
        T* RefAt(unsigned int);

        unsigned int Next(unsigned int) const;
        unsigned int Prev(unsigned int) const;

    private:

        unsigned int m_Length;

        volatile unsigned int m_Head_i;
        volatile unsigned int m_Mark_i;
        volatile unsigned int m_Tail_i;

        T* m_Ring;

    };

} // namespace Core

#include "DoubleRingBuffer.tpp"
