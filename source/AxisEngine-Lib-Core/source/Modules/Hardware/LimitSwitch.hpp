////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-Lib-Core
// file: LimitSwitch.hpp
////////////////////////////////////////////////////////////////////////////////

namespace Core {

    class LimitSwitch : public Module {

    public:
        LimitSwitch();
        ~LimitSwitch();

        virtual void OnModuleLoaded() override;
    };

}
