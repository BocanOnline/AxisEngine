////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-Core
// file: ConsoleStream.hpp
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "Stream.hpp"

namespace Core {

    class ConsoleStream : public Stream {

    public:
        ConsoleStream();
        virtual ~ConsoleStream() override;
       
        virtual char GetChar() override;
        virtual std::string GetLine() override;

        virtual bool PutChar() override;
        virtual bool PutLine() override;
    };

} // namespace Core

