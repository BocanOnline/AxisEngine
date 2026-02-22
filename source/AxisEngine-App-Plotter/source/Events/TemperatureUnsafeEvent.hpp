// ProjectAxisEngine
// TemperatureUnsafeEvent.hpp
//
#pragma once

#include <string>

#include "Event.hpp"


namespace Plotter {

    class TemperatureUnsafeEvent : public Core::Event {

    public:
        TemperatureUnsafeEvent();
        virtual ~TemperatureUnsafeEvent() override;
        
        virtual std::string GetName() const override;

    };

} // namespace Core
