//
// ProjectAxisEngine
// IdleEvent.hpp
//
#pragma once

#include <string>

#include "../Event.hpp"


namespace Core {

    class IdleEvent : public Core::Event {

    public:
        IdleEvent();
        virtual ~IdleEvent() override;
        
        virtual std::string GetName() const override;

    };

} // namespace Core
