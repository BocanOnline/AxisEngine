////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-Core
// file: Planner.hpp
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <memory>

#include "Module.hpp"

#include "Utils/Types.hpp"

namespace Core {

    class Block;

    class Planner : public Module {

    public:
        Planner();
        virtual ~Planner() override;
        
        virtual void OnModuleLoaded() override;
        
        virtual void OnBlockReady(std::shared_ptr<void> argument) override;

    private:
        bool AppendBlock(std::shared_ptr<Core::Block>);

        float m_PreviousUnitVector[static_cast<int>(Core::Axis::MaxPositionAxes)];

        float m_JuntionDeviation;
        float m_ZJunctionDeviation;
        float m_MinimumPlannerSpeed;
        
    };

} // namespace Core
