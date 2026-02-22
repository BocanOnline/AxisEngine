//
// ProjectAxisEngine
// SecondTickEvent.hpp
//
#pragma once

#include <string>

#include "../Event.hpp"


namespace Core {

    class SecondTickEvent : public Core::Event {

    public:
        SecondTickEvent();
        virtual ~SecondTickEvent() override;
        
        virtual std::string GetName() const override;

    };

} // namespace Core
