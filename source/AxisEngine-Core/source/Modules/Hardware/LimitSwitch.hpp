////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-Core
// file: LimitSwitch.hpp
////////////////////////////////////////////////////////////////////////////////

#include "Module.hpp"

namespace Core {

    class LimitSwitch : public Module {

    public:
        LimitSwitch();
        ~LimitSwitch();

        virtual void OnModuleLoaded() override;
    };

}
