////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-Lib-Core
// file: SecondTickEvent.hpp
////////////////////////////////////////////////////////////////////////////////
#pragma once

namespace Core {

    class SecondTickEvent : public Core::Event {

    public:
        SecondTickEvent();
        virtual ~SecondTickEvent() override;
        
        virtual std::string GetName() const override;

    };

} // namespace Core
