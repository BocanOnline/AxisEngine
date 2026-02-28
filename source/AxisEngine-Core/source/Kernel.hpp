////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-Core
// file: Kernel.hpp
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <functional>
#include <unordered_map>
#include <vector>
#include <memory>

#include "Module.hpp"
#include "Event.hpp"

namespace Core {

    class OnConsoleLineReceived;
    class OnEnable;
    class OnGcodeReceived;
    class OnHalt;
    class OnIdle;
    class OnMainLoop;
    class OnSecondTick;

    class SerialConsole;
    class GcodeDispatch;
    class SlowTicker;
    class Robot;
    class Conveyer;

    class Kernel {

    public:
        static Kernel& Get() { return s_Instance; } 

        void Run();

        void AddModule(std::shared_ptr<Module> module);
        void RegisterForEvent(Event& event, 
                              std::function<void(std::shared_ptr<void>)> function);
        void UnRegisterForEvent(Event& event, std::shared_ptr<Module> module);
        bool HasEvent(Event& event);
        void CallEvent(Event& event, std::shared_ptr<void> argument);

    public:
        std::shared_ptr<SerialConsole>          serialconsole;
        std::shared_ptr<GcodeDispatch>          gcodedispatch;
        std::shared_ptr<SlowTicker>             slowticker;
        std::shared_ptr<Robot>                  robot;
        std::shared_ptr<Conveyer>               conveyer;

    private:
         Kernel(); 
         Kernel(const Kernel&) = delete;
        ~Kernel();

    private:
        static Kernel s_Instance;

        std::unordered_map<std::string, 
                 std::vector<std::function<void(std::shared_ptr<void>)>>> m_CallbackTable;
        
        // TODO: add config data/methods

    };

} // namespace Core
