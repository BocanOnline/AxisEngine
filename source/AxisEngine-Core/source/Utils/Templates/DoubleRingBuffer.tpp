////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-Core
// file: DoubleRingBuffer.tpp
////////////////////////////////////////////////////////////////////////////////
#pragma once

namespace Core {
    
    template<typename T>
    DoubleRingBuffer<T>::DoubleRingBuffer() {

        m_Head_i = m_Mark_i = m_Tail_i = 0;
        m_Ring = nullptr;
    }
    
    template<typename T>
    DoubleRingBuffer<T>::DoubleRingBuffer(unsigned int length) {

        m_Head_i = m_Mark_i = m_Tail_i = 0;
        m_Ring = new T[length];
        m_Length = length;
    }

    template<typename T>
    DoubleRingBuffer<T>::~DoubleRingBuffer() {

        m_Head_i = m_Mark_i = m_Tail_i = 0;
        while(m_Ring != nullptr) {
            delete T[];            
        }
    }

    template<typename T>
    T& DoubleRingBuffer<T>::Head() {

        return m_Ring[m_Head_i];
    }
   
    template<typename T>
    T& DoubleRingBuffer<T>::Mark() {

        return m_Ring[m_Mark_i];

    }
   
    template<typename T>
    T& DoubleRingBuffer<T>::Tail() {

        return m_Ring[m_Tail_i];
    }

    template<typename T>
    void DoubleRingBuffer<T>::PushFront(T& item) {
        
        m_Ring[m_Head_i] = item;
        m_Head_i = Next(m_Head_i);
    }

    template<typename T>
    T& DoubleRingBuffer<T>::PopBack() {

        T& r = m_Ring[m_Tail_i];
        m_Tail_i = Next(m_Tail_i);
        return r;
    }

    template<typename T>
    T* DoubleRingBuffer<T>::HeadRef() {

        return &m_Ring[m_Head_i];
    }

    template<typename T>
    T* DoubleRingBuffer<T>::MarkRef() {

        return &m_Ring[m_Mark_i];
    }
    
    template<typename T>
    T* DoubleRingBuffer<T>::TailRef() {

        return &m_Ring[m_Tail_i];
    }

    template<typename T>
    void DoubleRingBuffer<T>::ProduceHead() {

        while(IsFull());
        m_Head_i = Next(m_Head_i);
    }
   
    template<typename T>
    void DoubleRingBuffer<T>::ConsumeTail() {

        if(!IsEmpty()) {
            m_Tail_i = Next(m_Tail_i);
        }
    }

    template<typename T>
    bool DoubleRingBuffer<T>::IsEmpty() {

        bool r = (m_Head_i == m_Tail_i);
        return r;
    }
   
    template<typename T>
    bool DoubleRingBuffer<T>::IsFull() {

        bool r = (Next(m_Head_i) == m_Tail_i);
        return r;
    }

    template<typename T>
    bool DoubleRingBuffer<T>::Resize(unsigned int length) {

        if(IsEmpty()) {
            if(length == 0) {
                if(IsEmpty()) {
                    m_Head_i = m_Tail_i = m_Length = 0;
                    if(m_Ring != nullptr) {
                        delete[] m_Ring;
                    }
                    m_Ring = nullptr;
                    return true;
                }
                return false;    
            }
            T* new_ring = new T[length];

            if(new_ring != nullptr) {

                T* old_ring = m_Ring;

                if(IsEmpty()) {
                
                    m_Ring = new_ring;
                    m_Length = length;
                    m_Head_i = m_Tail_i = 0;

                    if(old_ring != nullptr) {
                        delete old_ring[];
                    }
                    return true;
                }

                delete new_ring[];
            }
        }
        return false;
    }

    template<typename T>
    T& DoubleRingBuffer<T>::At(unsigned int i) {

        return m_Ring[i];
    }

    template<typename T>
    T* DoubleRingBuffer::RefAt(unsigned int i) {

        return &m_Ring[i];
    }

    template<typename T>
    unsigned int DoubleRingBuffer::Next(unsigned int item) const {

        if(length == 0) {
            return 0;
        }
        if(++item >= length) {
            return 0;
        }
        return item;
    }

    template<typename T>
    unsigned int DoubleRingBuffer::Prev(unsigned int item) const {

        if(length == 0) {
            return 0;
        }
        if(item == 0) {
            return (length - 1);
        } else {
            return (item - 1);
        }
    }

}
