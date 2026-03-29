////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-Lib-Core
// file: StepTicker.hpp
////////////////////////////////////////////////////////////////////////////////
#pragma once

namespace Core {

    class StepTicker : public Module, Worker {

    public:
        StepTicker();
        virtual ~StepTicker() override;
       
        // Module
        virtual void OnModuleLoaded() override;
        void OnIdle(std::shared_ptr<void> argument) override;
        
        // Worker
        virtual void RegisterForTask() override;
        virtual void Run() override;
        virtual void UnregisterForTask() override;

        void  SetFrequency(float frequency) { m_Frequency = frequency; }
        float GetFrequency()                { return m_Frequency; }

    private:

        struct {
            
            float m_Frequency;
        };
    };

} // namespace Core
