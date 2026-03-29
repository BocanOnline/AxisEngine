////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-Lib-Core
// file: BlockReceivedEvent.hpp
////////////////////////////////////////////////////////////////////////////////
#pragma once

namespace Core {

    class BlockReceivedEvent : public Core::Event {

    public:
        BlockReceivedEvent();
        virtual ~BlockReceivedEvent() override;
        
        virtual std::string GetName() const override;

    };

} // namespace Core
