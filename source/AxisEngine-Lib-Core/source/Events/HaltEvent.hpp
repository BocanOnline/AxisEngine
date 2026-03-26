////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-Core
// file: HaltEvent.hpp
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <string>

#include "../Event.hpp"


namespace Core {

    class HaltEvent : public Core::Event {

    public:
        HaltEvent();
        virtual ~HaltEvent() override;
        
        virtual std::string GetName() const override;

    };

} // namespace Core
