////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-Core
// file: GcodeDispatch.hpp
////////////////////////////////////////////////////////////////////////////////
#pragma once

namespace Core {

    class GcodeDispatch : public Module {

    public:
        GcodeDispatch();
        virtual ~GcodeDispatch() override;
        
        virtual void OnModuleLoaded() override;

        virtual void OnConsoleLineReceived(std::shared_ptr<void> argument) override;
    };

} // namespace Core
