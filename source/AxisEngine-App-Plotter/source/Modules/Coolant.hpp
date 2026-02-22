//
// ProjectAxisEngine
// Coolant.hpp
//
#pragma once

#include <memory>

#include "Module.hpp"

namespace Plotter::Module {

    class Coolant : public Core::Module {

    public:
        Coolant();
        virtual ~Coolant() override;
        
        virtual void OnModuleLoaded() override;

        void OnTemperatureUnsafe(std::shared_ptr<void> argument);

    };

} // namespace Core
