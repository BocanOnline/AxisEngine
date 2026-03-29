////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-Lib-Core
// file: KillSwitch.hpp
////////////////////////////////////////////////////////////////////////////////

namespace Core {

    class KillSwitch : public Module {

    public:
        KillSwitch();
        ~KillSwitch();

        virtual void OnModuleLoaded() override;
    };

}
