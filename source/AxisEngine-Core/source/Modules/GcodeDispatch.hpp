//
// ProjectAxisEngine
// GcodeDispatch.hpp
//
#pragma once

#include <memory>

#include "../Module.hpp"

namespace Core {

    class GcodeDispatch : public Module {

    public:
        GcodeDispatch();
        virtual ~GcodeDispatch() override;
        
        virtual void OnModuleLoaded() override;

        void OnConsoleLineReceived(std::shared_ptr<void> argument) override;

    };

} // namespace Core
