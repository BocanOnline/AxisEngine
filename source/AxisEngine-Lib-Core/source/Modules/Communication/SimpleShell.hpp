////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-Core
// file: SimpleShell.hpp
////////////////////////////////////////////////////////////////////////////////
#pragma once

namespace Core {

    class SimpleShell : public Module {

    public:
        SimpleShell();
        virtual ~SimpleShell() override;
        
        virtual void OnModuleLoaded() override;

        virtual void OnConsoleLineReceived(std::shared_ptr<void> argument) override;
    };

} // namespace Core
