#pragma once

#include "FileAction.h"
#include <stack>
#include <thread>
#include "IFileSystemTraveler.h"

// Structure to store directory path and its depth.
struct TravelerDirectory
{
    // Directory path.
    QString path;

    // Directory depth.
    size_t depth = 0;
};

// IFileSystemTraveler implementation with QDirIterator.
class FileSystemTravelerQImpl : public IFileSystemTraveler
{
public:

    FileSystemTravelerQImpl() = default;

    virtual ~FileSystemTravelerQImpl();

protected:

    // Starts traveling.
    void startTraveling(FileAction& action, const QString& where) override;

    // Starts traveling with depth.
    void startTraveling(FileAction& action, const QString& where, size_t depth) override;

    // Resume traveling.
    void resume() override;

    // Pause traveling.
    void pause() override;

    // Stop traveling.
    void stop() override;

    // Returns state.
    StateMachine::State getState() const override;

private:

    // Worker function.
    // Should run while it has data in stack or it paused or stopped.
    void workerMethod();

    // Function to travel single directory.
    void travelDirectory(FileAction& action,const TravelerDirectory& dir);

    // Stack of directories that should be traveled.
    std::stack<TravelerDirectory> m_directoryStack;

    // Mutex for worker. Locks when worker can't be stopped or when it pauses, stops, resumes.
    std::mutex m_workerLock;

    // Working thread.
    std::thread m_worker;

    // Action to be done on every file.
    FileAction* m_action = nullptr;

    // State machine from traveler.
    StateMachine m_stateMachine;

    // Is depth limited.
    bool m_isDepthLimited = 0;

    // Depth
    size_t m_depth = 0;

};
