////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-Lib-Core
// file: GcodeReceivedEvent.hpp
////////////////////////////////////////////////////////////////////////////////
#pragma once

namespace Core {

    class GcodeReceivedEvent : public Core::Event {

    public:
        GcodeReceivedEvent();
        virtual ~GcodeReceivedEvent() override;
        
        virtual std::string GetName() const override;

    };

} // namespace Core
