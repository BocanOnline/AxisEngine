//
// ProjectAxisEngine
// EnableEvent.hpp
//
#pragma once

#include <string>

#include "../Event.hpp"


namespace Core {

    class EnableEvent : public Core::Event {

    public:
        EnableEvent();
        virtual ~EnableEvent() override;
        
        virtual std::string GetName() const override;

    };

} // namespace Core
