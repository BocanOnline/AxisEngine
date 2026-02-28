////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-App-Plotter
// file: Actuator.hpp
////////////////////////////////////////////////////////////////////////////////
#include <memory>

#include "Module.hpp"

namespace Plotter::Module {

    class Actuator : public Core::Module {

    public:
        Actuator();
        virtual ~Actuator() override;
        
        virtual void OnModuleLoaded() override;

        void OnGcodeReceived(std::shared_ptr<void> argument) override;

    };

} // namespace Core
