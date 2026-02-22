//
// ProjectAxisEngine
// Conveyer.hpp
//
#pragma once

#include <memory>

#include "../Module.hpp"

namespace Core {

    class Conveyer : public Module {

    public:
        Conveyer();
        virtual ~Conveyer() override;
        
        virtual void OnModuleLoaded() override;

        void OnIdle(std::shared_ptr<void> argument) override;
        void OnHalt(std::shared_ptr<void> argument) override;

    };

} // namespace Core
