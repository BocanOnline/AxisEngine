//
// ProjectAxisEngine
// TemperatureSensor.hpp
//
#pragma once

#include <memory>

#include "Module.hpp"

namespace Plotter::Module {

    class TemperatureSensor : public Core::Module {

    public:
        TemperatureSensor();
        virtual ~TemperatureSensor() override;
        
        virtual void OnModuleLoaded() override;

        void OnIdle(std::shared_ptr<void> argument) override;
    };

} // namespace Core
