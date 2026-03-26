////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-Core
// file: FileStream.hpp
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <fstream>

#include "Stream.hpp"

namespace Core {

    class FileStream : public Stream {

    public:
        FileStream();
        virtual ~FileStream() override;
       
        virtual char GetChar() override;
        virtual std::string GetLine() override;

        virtual bool PutChar() override;
        virtual bool PutLine() override;

    private:
        std::ifstream file;
    };

} // namespace Core


