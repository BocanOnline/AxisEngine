//
// ProjectAxisEngine
// GcodeReceivedEvent.hpp
//
#pragma once

#include <string>

#include "../Event.hpp"


namespace Core {

    class GcodeReceivedEvent : public Core::Event {

    public:
        GcodeReceivedEvent();
        virtual ~GcodeReceivedEvent() override;
        
        virtual std::string GetName() const override;

    };

} // namespace Core
