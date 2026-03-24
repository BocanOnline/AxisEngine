////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-Core
// file: Conveyer.hpp
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "Module.hpp"

namespace Core {

    class Conveyer : public Module {

    public:
        Conveyer();
        virtual ~Conveyer() override;
        
        virtual void OnModuleLoaded() override;
     
        virtual void OnIdle(std::shared_ptr<void> argument) override;
        
    };

} // namespace Core
