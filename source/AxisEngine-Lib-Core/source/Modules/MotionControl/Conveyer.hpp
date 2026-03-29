////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-Core
// file: Conveyer.hpp
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "Module.hpp"

#include "Modules/MotionControl/Utils/BlockQueue.hpp"
#include "Modules/MotionControl/Utils/Types.hpp"

namespace Core {

    class Conveyer : public Module {

    public:
        Conveyer();
        virtual ~Conveyer() override;
        
        virtual void OnModuleLoaded() override;
     
        virtual void OnBlockReceived(std::shared_ptr<void> argument) override;
        virtual void OnIdle(std::shared_ptr<void> argument) override;

        void Start(int);

        std::shared_ptr<Core::Block> GetHeadBlock() { return m_BlockQueue.HeadRef(); }
        std::shared_ptr<Core::Block> GetMarkBlock() { return m_BlockQueue.MarkRef(); }
        std::shared_ptr<Core::Block> GetTailBlock() { return m_BlockQueue.TailRef(); }

        std::shared_ptr<Core::Block> GetPreviousBlock(std::shared_ptr<Core::Block>);
        std::shared_ptr<Core::Block> GetNextBlock    (std::shared_ptr<Core::Block>);

    private:
        // Conveyer functions
        void AppendHeadBlock(std::shared_ptr<Core::Block>);
        void SetHeadBlockReady();
        void SetMarkBlockConsumed();
        void DeleteTailBlock();

        // Planner functions
        void  PlanJunctionVelocity();
        void  PlanKinematicProfiles();

        float CalculateMaxAllowableSpeed(float, float, float);

    private:
        Core::BlockQueue m_BlockQueue;

        struct {

            int   m_BlockQueueSize;
            int   m_BlockQueueDelayTime;
            
            Core::CartesianCoordinates m_PreviousUnitVector;

            float m_JunctionDeviation;
            float m_ZJunctionDeviation;
            float m_MinimumPlannerSpeed;
        };

        struct {
            
            volatile bool m_Running: 1;
            volatile bool m_AllowFetch: 1;
            bool          m_Flush: 1;
        };

    };

} // namespace Core
