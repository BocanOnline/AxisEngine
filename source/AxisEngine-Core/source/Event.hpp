//
// ProjectAxisEngine
// Event.hpp
//
#pragma once

#include <string>

namespace Core {

    class Event {

    public:
        Event() {}
        virtual ~Event() = default;
        
        virtual std::string GetName() const = 0;
    private:

        bool m_Handled = false;
    };

} // namespace Core
