////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-Core
// file: IdleEvent.hpp
////////////////////////////////////////////////////////////////////////////////
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
