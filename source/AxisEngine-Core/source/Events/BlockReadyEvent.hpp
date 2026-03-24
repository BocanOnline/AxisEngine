////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-Core
// file: BlockReadyEvent.hpp
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <string>

#include "../Event.hpp"


namespace Core {

    class BlockReadyEvent : public Core::Event {

    public:
        BlockReadyEvent();
        virtual ~BlockReadyEvent() override;
        
        virtual std::string GetName() const override;

    };

} // namespace Core
