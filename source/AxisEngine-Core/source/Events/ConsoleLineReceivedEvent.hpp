//
// ProjectAxisEngine
// ConsoleLineReceivedEvent.hpp
//
#pragma once

#include <string>

#include "../Event.hpp"


namespace Core {

    class ConsoleLineReceivedEvent : public Core::Event {

    public:
        ConsoleLineReceivedEvent();
        virtual ~ConsoleLineReceivedEvent() override;
        
        virtual std::string GetName() const override;

    };

} // namespace Core
