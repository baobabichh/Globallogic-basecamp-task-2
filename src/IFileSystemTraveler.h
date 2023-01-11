#pragma once

#include "FileAction.h"
#include <mutex>
#include <atomic>
#include "StateMachine.h"


// Interface for class, that should iterate all files in file system and provide some action on each file.
class IFileSystemTraveler : private QObject
{
    Q_OBJECT

signals:

    void stateChanged(StateMachine::State state);

public:

    IFileSystemTraveler() = default;

    virtual ~IFileSystemTraveler() = default;

    // Starts traveling in file system, uses action on every file. Should run worker in Non blocking mode.
    // If starts while Working or Paused state, stops previus travel and starts new.
    // Parameter 'where' is path from where traveling should start.
    virtual void startTraveling(FileAction& action, const QString& where) = 0;

    // Starts traveling in file system with depth, uses action on every file. Should run worker in Non blocking mode.
    // If starts while Traveling or Paused state, stops previus travel and starts new.
    // Parameter 'where' is path from where traveling should start.
    virtual void startTraveling(FileAction& action, const QString& where, size_t depth) = 0;

    // Resumes.
    virtual void resume() = 0;

    // Pauses.
    virtual void pause() = 0;

    // Stops.
    virtual void stop() = 0;

    // Return state.
    virtual StateMachine::State getState() const = 0;
};

