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

#include "Module.hpp"
#include "Worker.hpp"

#include "Streams/Stream.hpp"


namespace Core {

    class SerialConsole : public Module, Worker {

    public:
        SerialConsole();
        virtual ~SerialConsole() override;
       
        // Module
        virtual void OnModuleLoaded() override;     
        virtual void OnMainLoop(std::shared_ptr<void> argument) override;
        virtual void OnIdle(std::shared_ptr<void> argument) override;
       
        // Worker
        virtual void RegisterForTask() override;
        virtual void Run() override;
        virtual void UnregisterForTask() override;

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
