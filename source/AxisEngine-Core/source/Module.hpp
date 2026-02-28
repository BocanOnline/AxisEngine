////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-Core
// file: Module.hpp
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <functional>
#include <memory>

#include "Event.hpp"

namespace Core {

    class Module : public std::enable_shared_from_this<Module>{

    public:
        Module() {}
        virtual ~Module() = default;
        
        virtual void OnModuleLoaded() = 0;

        void RegisterForEvent(Core::Event&, 
                              std::function<void(std::shared_ptr<void>)> function);

        virtual void OnMainLoop(std::shared_ptr<void> argument) {}
        virtual void OnConsoleLineReceived(std::shared_ptr<void> argument) {}
        virtual void OnGcodeReceived(std::shared_ptr<void> argument) {}
        virtual void OnIdle(std::shared_ptr<void> argument) {}
        virtual void OnSecondTick(std::shared_ptr<void> argument) {}
        virtual void OnGetPublicData(std::shared_ptr<void> argument) {}
        virtual void OnSetPublicData(std::shared_ptr<void> argument) {}
        virtual void OnHalt(std::shared_ptr<void> argument) {}
        virtual void OnEnable(std::shared_ptr<void> argument) {}
        
        // TODO: look into std::any instead of void pointers for arg passing

    };

} // namespace Core
