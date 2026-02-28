////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-App-Plotter
// file: TemperatureUnsafeEvent.hpp
////////////////////////////////////////////////////////////////////////////////
#include <string>

#include "Event.hpp"


namespace Plotter {

    class TemperatureUnsafeEvent : public Core::Event {

    public:
        TemperatureUnsafeEvent();
        virtual ~TemperatureUnsafeEvent() override;
        
        virtual std::string GetName() const override;

    };

} // namespace Core
