////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-Core
// file: Pin.hpp
////////////////////////////////////////////////////////////////////////////////
#pragma once

namespace Core {

    class Pin {

    public:
        Pin();
        ~Pin();
        
        void Set(int);

    private:
        int pin;
    };

} // namespace Core
