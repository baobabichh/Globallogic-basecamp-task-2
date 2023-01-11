#include "StateMachine.h"
#include "FileAction.h"

void StateMachine::start()
{
    m_state = State::Working;
}

bool StateMachine::resume()
{
    if (State::Paused == m_state)
    {
        m_state = State::Working;
        return 1;
    }
    return 0;

}

bool StateMachine::pause()
{
    if (State::Working == m_state)
    {
        m_state = State::Paused;
        return 1;
    }
    return 0;
}

bool StateMachine::stop()
{
    if (State::Working == m_state || State::Paused == m_state)
    {
        m_state = State::Free;
        return 1;
    }
    return 0;
}

StateMachine::State StateMachine::getState() const
{
    return m_state;
}

bool StateMachine::isFree() const
{
    return State::Free == m_state;
}

bool StateMachine::isPaused() const
{ 
    return State::Paused == m_state; 
}

bool StateMachine::isWorking() const
{ 
    return State::Working == m_state; 
}

bool StateMachine::canResume() const
{
    return State::Paused == m_state;
}

bool StateMachine::canPause() const
{
    return State::Working == m_state;
}

bool StateMachine::canStop() const
{
    return State::Paused == m_state || State::Working == m_state;
}
