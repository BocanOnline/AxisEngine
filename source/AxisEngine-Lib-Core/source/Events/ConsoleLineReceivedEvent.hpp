////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-Core
// file: ConsoleLineReceivedEvent.hpp
////////////////////////////////////////////////////////////////////////////////
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
