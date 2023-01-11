#pragma once

#include "IXMLFileTraveler.h"
#include "qxmlstream.h"
#include <thread>

// IXMLFileTraveler implementation with QXmlSimpleReader.
class XMLFileTravelerQImpl  : public IXMLFileTraveler
{
public:

	virtual ~XMLFileTravelerQImpl();

	void startSearching(FileAction& action, const QString& filePath) override;

	// Resumes.
	void resume() override;

	// Pauses.
	void pause() override;

	// Stops.
	void stop() override;

	// Return state.
	StateMachine::State getState() const override;

private:

	// Worker thread function.
	void workerThread();

	// Worker thread. 
	std::thread m_worker;

	// Worker lock.
	std::mutex m_workerLock;

	// File to file.
	QFile m_file;

	// XML reader.
	QXmlStreamReader m_reader;

	// Action.
	FileAction* m_action = nullptr;

	// State machine.
	StateMachine m_stateMachine;
};
