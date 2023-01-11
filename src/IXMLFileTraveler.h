#pragma once

#include "IFileSystemTraveler.h"
#include "Errorable.h"

enum class IXMLFileTravelerError : unsigned char
{
	// Can not open file.
	FailedToOpenFile,

	// File dont have root node.
	NoRootNode,

	// Else file structure error.
	BadFileStructure,

};

// Interface for class, that should iterate all file recordings in XML file and provide some action on each record.
class IXMLFileTraveler : public Errorable
{

signals:

	void stateChanged(StateMachine::State state);

public:

	IXMLFileTraveler() = default;

	virtual ~IXMLFileTraveler() = default;

	// Starts searching, should be run in non blocking mode.
	// If starts while Working or Paused state, stops previus travel and starts new.
	// filePath is path to file with should be parsed.
	virtual void startSearching(FileAction& action, const QString& filePath) = 0;
	
	virtual void resume() = 0;

	virtual void pause() = 0;

	virtual void stop() = 0;

	virtual StateMachine::State getState() const = 0;
	
};
