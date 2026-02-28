////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-Core
// file: Robot.hpp
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <memory>

#include "../Module.hpp"

namespace Core {

    class Robot : public Module {

    public:
        Robot();
        virtual ~Robot() override;
        
        virtual void OnModuleLoaded() override;

        void OnIdle(std::shared_ptr<void> argument) override;
        void OnGcodeReceived(std::shared_ptr<void> argument) override;
        void OnSecondTick(std::shared_ptr<void> argument) override;

    };

} // namespace Core
