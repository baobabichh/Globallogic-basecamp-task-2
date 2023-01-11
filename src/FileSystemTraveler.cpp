#include "FileSystemTraveler.h"
#include <QDirIterator>


FileSystemTravelerQImpl::~FileSystemTravelerQImpl()
{
    stop();
    if(m_worker.joinable())
    {
        m_worker.join();
    }
}

void FileSystemTravelerQImpl::startTraveling(FileAction& action, const QString& where)
{
    stop();
    if (m_worker.joinable())
    {
        m_worker.join();
    }

    m_stateMachine.start();
    m_action = &action;
    m_directoryStack.push({ where,0 });
    m_isDepthLimited = 0;
    m_depth = 0;


    m_worker = std::thread(&FileSystemTravelerQImpl::workerMethod, this);
}

void FileSystemTravelerQImpl::startTraveling(FileAction& action, const QString& where, size_t depth)
{
    stop();
    if (m_worker.joinable())
    {
        m_worker.join();
    }

    m_stateMachine.start();
    m_action = &action;
    m_directoryStack.push({ where,0 });
    m_isDepthLimited = 1;
    m_depth = depth;


    m_worker = std::thread(&FileSystemTravelerQImpl::workerMethod, this);
}

void FileSystemTravelerQImpl::resume()
{
    m_workerLock.lock();
    bool canResume = m_stateMachine.canResume();
    if (canResume)
    {
        m_stateMachine.resume();
    }
    m_workerLock.unlock();

    if (canResume)
    {
        if (m_action)
        {
            m_action->resume();
        }
        m_worker = std::thread(&FileSystemTravelerQImpl::workerMethod, this);
    }

}

void FileSystemTravelerQImpl::pause()
{
    m_workerLock.lock();
    bool canPause = m_stateMachine.canPause();
    if (canPause)
    {
        m_stateMachine.pause();
    }
    m_workerLock.unlock();

    if (canPause)
    {
        if (m_worker.joinable())
        {
            m_worker.join();
        }
        if (m_action)
        {
            m_action->pause();
        }
    }
}

void FileSystemTravelerQImpl::stop()
{
    m_workerLock.lock();
    bool canStop = m_stateMachine.canStop();
    if (canStop)
    {
        m_stateMachine.stop();
    }
    m_workerLock.unlock();

    if (canStop)
    {
        if (m_worker.joinable())
        {
            m_worker.join();
        }
        if (m_action)
        {
            m_action->stop();
        }
        m_directoryStack = std::stack<TravelerDirectory>();
        m_action = nullptr;
    }
}

StateMachine::State FileSystemTravelerQImpl::getState() const
{
    return m_stateMachine.getState();
}


void FileSystemTravelerQImpl::workerMethod()
{

    auto isDirectoryStackEmpty = [this]() { return m_directoryStack.empty(); };

    // Finished working beacause has no data to wok with.
    auto finishedWorking = [this]()
    {
        m_stateMachine.stop();
        if (m_action)
        {
            m_action->stop();
        }
        m_directoryStack = std::stack<TravelerDirectory>();
        m_action = nullptr;
    };

    while(StateMachine::State::Working == m_stateMachine.getState())
    {
        m_workerLock.lock();

        if(isDirectoryStackEmpty()) 
        {
            // Finished working beacause has no data to wok with.
            finishedWorking();
            m_workerLock.unlock();
            return;
        }
        else
        {
            auto dir = std::move(m_directoryStack.top());
            m_directoryStack.pop();

            if(!m_isDepthLimited)
            {
                travelDirectory(*m_action, dir);
            }
            else if(dir.depth < m_depth && m_isDepthLimited)
            {
                travelDirectory(*m_action, dir);
            }
        }

        m_workerLock.unlock();
    }
}

void FileSystemTravelerQImpl::travelDirectory(FileAction& action,const TravelerDirectory& dir)
{
    QDirIterator it(dir.path);
    for(QString elementPath; it.hasNext();  )
    {
        elementPath = it.next();
        QString name = it.fileName();
        if("." == name || ".." == name )
        {
            continue;
        }
        QFileInfo info(elementPath);
        if(info.isFile())
        {
            FileInfo myInfo;
            myInfo.fromQFileInfo(info);
            action(myInfo);
        }
        else if(info.isDir())
        {
            m_directoryStack.push({info.absoluteFilePath(),(dir.depth + 1)});
        }
    }
}
