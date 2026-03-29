////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-Lib-Core
// file: EnableEvent.hpp
////////////////////////////////////////////////////////////////////////////////
#pragma once

namespace Core {

    class EnableEvent : public Core::Event {

    public:
        EnableEvent();
        virtual ~EnableEvent() override;
        
        virtual std::string GetName() const override;

    };

} // namespace Core
