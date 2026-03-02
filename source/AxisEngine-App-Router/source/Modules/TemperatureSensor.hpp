////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-App-Router
// file: TemperatureSensor.hpp
////////////////////////////////////////////////////////////////////////////////
#include <memory>

#include "Module.hpp"

namespace Router::Module {

    class TemperatureSensor : public Core::Module {

    public:
        TemperatureSensor();
        virtual ~TemperatureSensor() override;
        
        virtual void OnModuleLoaded() override;

        void OnIdle(std::shared_ptr<void> argument) override;
    };

} // namespace Router::Module

