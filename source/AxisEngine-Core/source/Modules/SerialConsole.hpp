////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-Core
// file: SerialConsole.hpp
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <memory>

#include "../Module.hpp"

#include "Utils/Streams/Stream.hpp"


namespace Core {

    class SerialConsole : public Module {

    public:
        SerialConsole();
        virtual ~SerialConsole() override;
        
        virtual void OnModuleLoaded() override;

        void OnMainLoop(std::shared_ptr<void> argument) override;
        void OnIdle(std::shared_ptr<void> argument) override;

        bool ReceivedExitCommand() { return m_ExitFlag; }

    private:
        std::shared_ptr<Core::Stream> m_Stream;
        std::string m_LineBuffer;

        bool m_HaltFlag = false;
        bool m_QueryFlag = false;
        bool m_ExitFlag = false;

    private:
        bool HasLine();
        bool HasChar(char letter);
    };

} // namespace Core
