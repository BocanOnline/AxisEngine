////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-Lib-Core
// file: MainLoopEvent.hpp
////////////////////////////////////////////////////////////////////////////////
#pragma once

namespace Core {

    class MainLoopEvent : public Core::Event {

    public:
        MainLoopEvent();
        virtual ~MainLoopEvent() override;
        
        virtual std::string GetName() const override;

    };

} // namespace Core
