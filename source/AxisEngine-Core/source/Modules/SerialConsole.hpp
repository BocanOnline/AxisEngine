//
// ProjectAxisEngine
// SerialConsole.hpp
//
#pragma once

#include <memory>

#include "../Module.hpp"

namespace Core {

    class SerialConsole : public Module {

    public:
        SerialConsole();
        virtual ~SerialConsole() override;
        
        virtual void OnModuleLoaded() override;

        void OnMainLoop(std::shared_ptr<void> argument) override;
        void OnIdle(std::shared_ptr<void> argument) override;

    };

} // namespace Core
