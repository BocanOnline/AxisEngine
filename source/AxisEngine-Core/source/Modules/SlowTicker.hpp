////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-Core
// file: SlowTicker.hpp
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <memory>

#include "../Module.hpp"

namespace Core {

    class SlowTicker : public Module {

    public:
        SlowTicker();
        virtual ~SlowTicker() override;
        
        virtual void OnModuleLoaded() override;

        void OnIdle(std::shared_ptr<void> argument) override;

    };

} // namespace Core
