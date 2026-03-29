////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-Lib-Core
// file: HaltEvent.hpp
////////////////////////////////////////////////////////////////////////////////
#pragma once

namespace Core {

    class HaltEvent : public Core::Event {

    public:
        HaltEvent();
        virtual ~HaltEvent() override;
        
        virtual std::string GetName() const override;

    };

} // namespace Core
