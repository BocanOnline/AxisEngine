////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-Core
// file: NetworkStream.hpp
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "Stream.hpp"

namespace Core {

    class NetworkStream : public Stream {

    public:
        NetworkStream();
        virtual ~NetworkStream() override;
       
        virtual char GetChar() override;
        virtual std::string GetLine() override;

        virtual bool PutChar() override;
        virtual bool PutLine() override;
    };

} // namespace Core


