////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-Core
// file: BlockReceivedEvent.hpp
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <string>

#include "../Event.hpp"


namespace Core {

    class BlockReceivedEvent : public Core::Event {

    public:
        BlockReceivedEvent();
        virtual ~BlockReceivedEvent() override;
        
        virtual std::string GetName() const override;

    };

} // namespace Core
