////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-Core
// file: KillSwitch.hpp
////////////////////////////////////////////////////////////////////////////////

#include "Module.hpp"

namespace Core {

    class KillSwitch : public Module {

    public:
        KillSwitch();
        ~KillSwitch();

        virtual void OnModuleLoaded() override;
    };

}
