////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-Lib-Core
// file: Stream.hpp
////////////////////////////////////////////////////////////////////////////////
#pragma once

namespace Core {

    class Stream {

    public:
        Stream() {}
        virtual ~Stream() = default;
       
        virtual char GetChar() = 0;
        virtual std::string GetLine() = 0;

        virtual bool PutChar() = 0;
        virtual bool PutLine() = 0;
    };

} // namespace Core
