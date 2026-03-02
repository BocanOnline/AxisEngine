////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-App-Router
// file: TemperatureUnsafeEvent.hpp
////////////////////////////////////////////////////////////////////////////////
#include <string>

#include "Event.hpp"


namespace Router {

    class TemperatureUnsafeEvent : public Core::Event {

    public:
        TemperatureUnsafeEvent();
        virtual ~TemperatureUnsafeEvent() override;
        
        virtual std::string GetName() const override;

    };

} // namespace Router

