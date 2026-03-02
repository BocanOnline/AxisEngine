////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-App-Router
// file: Coolant.hpp
////////////////////////////////////////////////////////////////////////////////
#include <memory>

#include "Module.hpp"

namespace Router::Module {

    class Coolant : public Core::Module {

    public:
        Coolant();
        virtual ~Coolant() override;
        
        virtual void OnModuleLoaded() override;

        void OnTemperatureUnsafe(std::shared_ptr<void> argument);

    };

} // namespace Core
