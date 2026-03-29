////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-Lib-Core
// file: ConsoleLineReceivedEvent.hpp
////////////////////////////////////////////////////////////////////////////////
#pragma once

namespace Core {

    class ConsoleLineReceivedEvent : public Core::Event {

    public:
        ConsoleLineReceivedEvent();
        virtual ~ConsoleLineReceivedEvent() override;
        
        virtual std::string GetName() const override;

    };

} // namespace Core
