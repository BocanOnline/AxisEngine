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
    class Robot;

    class SlowTicker;
    class StepTicker;

    class Kernel {

    public:
        static Kernel& Get() { return s_Instance; } 

        void Run();

        void AddModule(std::shared_ptr<Module> module);
        void RegisterForEvent(Event& event, std::function<void(std::shared_ptr<void>)> function);
        void UnRegisterForEvent(Event& event, std::shared_ptr<Module> module);
        bool HasEvent(Event& event);
        void CallEvent(Event& event, std::shared_ptr<void> argument);

        bool IsHalted();
        bool GetFeedHold();

    public:
        std::shared_ptr<SerialConsole>          m_SerialConsole;
        std::shared_ptr<GcodeDispatch>          m_GcodeDispatch;
        std::shared_ptr<Robot>                  m_Robot;
        
        std::shared_ptr<SlowTicker>             m_SlowTicker;
        std::shared_ptr<StepTicker>             m_StepTicker;

    private:
         Kernel(); 
         Kernel(const Kernel&) = delete;
        ~Kernel();

    private:
        static Kernel s_Instance;

        std::unordered_map<std::string, 
                 std::vector<std::function<void(std::shared_ptr<void>)>>> m_CallbackTable;
    };

} // namespace Core
////////////////////////////////////////////////////////////////////////////////
// TODO
// [ ] add config file input and parsing (Configurator Class?)
// [ ] add multi-threading (goal: Kernel controls threads for application)
// [ ] add sophisticated logging (goal: Kernel controls logging streams)
// [ ] implement IsHalted and GetFeedHold
// [ ] add private config data
////////////////////////////////////////////////////////////////////////////////
