////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-Core
// file: SerialMessage.hpp
////////////////////////////////////////////////////////////////////////////////
#pragma once

namespace Core {

    class SerialMessage {

    public:
        SerialMessage() = default;
        ~SerialMessage() = default;

        std::string Message;
    };

} // namespace Core

