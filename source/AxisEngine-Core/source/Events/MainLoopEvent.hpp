//
// ProjectAxisEngine
// MainLoopEvent.hpp
//
#pragma once

#include <string>

#include "../Event.hpp"


namespace Core {

    class MainLoopEvent : public Core::Event {

    public:
        MainLoopEvent();
        virtual ~MainLoopEvent() override;
        
        virtual std::string GetName() const override;

    };

} // namespace Core
