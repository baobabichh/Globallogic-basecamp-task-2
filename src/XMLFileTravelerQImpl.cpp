#include "XMLFileTravelerQImpl.h"

#include "XMLFileStructure.h"

XMLFileTravelerQImpl::~XMLFileTravelerQImpl()
{
	if (m_worker.joinable())
	{
		m_worker.join();
	}
}

void XMLFileTravelerQImpl::startSearching(FileAction& action, const QString& filePath)
{
	stop();
	if (m_worker.joinable())
	{
		m_worker.join();
	}

	m_stateMachine.start();
	m_action = &action;
	m_file.setFileName(filePath);
	if (!m_file.open(QFile::ReadOnly | QFile::Text))
	{
		// Bad file.
		pushError((int)IXMLFileTravelerError::FailedToOpenFile);
		stop();
		return;
	}

	m_reader.setDevice(&m_file);

	if (m_reader.readNextStartElement())
	{
		if (m_reader.name() == ROOT_TAG)
		{
			m_worker = std::thread(&XMLFileTravelerQImpl::workerThread, this);
		}
		else
		{
			// No root node.
			pushError((int)IXMLFileTravelerError::NoRootNode);
			stop();
		}
	}
	else
	{
		// Else error.
		pushError((int)IXMLFileTravelerError::BadFileStructure);
		stop();
	}

}

void XMLFileTravelerQImpl::resume()
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
		m_worker = std::thread(&XMLFileTravelerQImpl::workerThread, this);
	}
}

void XMLFileTravelerQImpl::pause()
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

void XMLFileTravelerQImpl::stop()
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
		m_file.close();
		m_action = nullptr;
	}
}

StateMachine::State XMLFileTravelerQImpl::getState() const
{
	return m_stateMachine.getState();
}

void XMLFileTravelerQImpl::workerThread()
{

	// How to stop thread in this thread.
	auto finish = [this]()
	{
		m_stateMachine.stop();
		m_action->stop();
		m_file.close();
		m_action = nullptr;
	};

	while (m_reader.readNextStartElement())
	{

		FileInfo info;

		if (m_reader.name() == FILE_TAG) // Found file node.
		{
		}
		else
		{
			// Not file node.
			finish();
			pushError((int)IXMLFileTravelerError::BadFileStructure);
			return;
		}


		
		// Name node.
		if (m_reader.readNextStartElement())
		{
			if (m_reader.name() == NAME_TAG) // Found name node.
			{
				info.name = m_reader.readElementText();
			}
			else
			{
				// Not name node.
				finish();
				pushError((int)IXMLFileTravelerError::BadFileStructure);
				return;
			}
		}
		else
		{
			// Name node empty.
			finish();
			pushError((int)IXMLFileTravelerError::BadFileStructure);
			return;
		}

		// Path node.
		if (m_reader.readNextStartElement())
		{
			if (m_reader.name() == PATH_TAG) // Found path node.
			{
				info.path = m_reader.readElementText();
			}
			else
			{
				// Not path node.
				finish();
				pushError((int)IXMLFileTravelerError::BadFileStructure);
				return;
			}
		}
		else
		{
			// File path empty.
			finish();
			pushError((int)IXMLFileTravelerError::BadFileStructure);
			return;
		}

		// Size node.
		if (m_reader.readNextStartElement())
		{
			if (m_reader.name() == SIZE_TAG) // Found size node.
			{
				info.size = m_reader.readElementText().toInt();
			}
			else
			{
				// Not size node.
				finish();
				pushError((int)IXMLFileTravelerError::BadFileStructure);
				return;
			}
		}
		else
		{
			// File size empty.
			finish();
			pushError((int)IXMLFileTravelerError::BadFileStructure);
			return;
		}

		// Date node.
		if (m_reader.readNextStartElement())
		{
			if (m_reader.name() == DATE_TAG) // Found date node.
			{
				if (info.date.fromQString(m_reader.readElementText())) // Date good.
				{
				}
				else // Bad date.
				{
					finish();
					pushError((int)IXMLFileTravelerError::BadFileStructure);
					return;
				}
			}
			else
			{
				// Not date node.
				finish();
				pushError((int)IXMLFileTravelerError::BadFileStructure);
				return;
			}
		}
		else
		{
			// File date empty.
			finish();
			pushError((int)IXMLFileTravelerError::BadFileStructure);
			return;
		}

		
		m_reader.readNextStartElement();
		(*m_action)(info);

		if (StateMachine::State::Working != m_stateMachine.getState())
		{
			return;
		}

	}
	finish();
}
