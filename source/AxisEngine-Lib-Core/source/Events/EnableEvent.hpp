////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-Core
// file: EnableEvent.hpp
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <string>

#include "../Event.hpp"


namespace Core {

    class EnableEvent : public Core::Event {

    public:
        EnableEvent();
        virtual ~EnableEvent() override;
        
        virtual std::string GetName() const override;

    };

} // namespace Core
