#pragma once

#include <mutex>
#include <atomic>

class FileAction;

class StateMachine 
{
public:

	// State of state machine
	enum class State : unsigned char
	{
		// Working
		Working,

		// Paused, waiting for resume
		Paused,

		// Waiting for start
		Free,
	};

	StateMachine() = default;
	virtual ~StateMachine() = default;

	// Starts or restarts.
	void start();

	// Resumes traveler.
	bool resume();

	// Pauses.
	bool pause();

	// Stops.
	bool stop();

	// Returns state.
	State getState() const;

	// Is getState() free.
	bool isFree() const;

	// Is getState() paused.
	bool isPaused() const;

	// Is getState() working now.
	bool isWorking() const;

	// Is state machine can be resumed.
	bool canResume() const;

	// Is state machine can be paused.
	bool canPause() const;

	// Is state machine can be stopped.
	bool canStop() const;

private:

	// Traveler state.
	std::atomic<State> m_state = State::Free;
	
};
