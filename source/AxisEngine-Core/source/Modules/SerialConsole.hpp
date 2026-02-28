////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-Core
// file: SerialConsole.hpp
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <memory>

#include "../Module.hpp"

////////////////////////////////////////////////////////////////////////////////
// PLAN
//
// 1. implement filesystem import line by line to parse .gcode program.
// 2. implement interrupt driven import line by line to parse .gcode program.
//
////////////////////////////////////////////////////////////////////////////////

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
