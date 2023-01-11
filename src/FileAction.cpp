#include "FileAction.h"
#include "FileInfoDisplayer.h"
#include "XMLFileWriter.h"

//
// FileAction
//

void FileAction::operator()(FileInfo& file)
{

}

void FileAction::stop()
{
}

void FileAction::pause()
{
}

void FileAction::resume()
{
}




//
// FilePrintAction
//

FilePrintAction::FilePrintAction(FileInfoDisplayer &displayer)
    : m_displayer(displayer)
{
    m_connection = QObject::connect(this, &FilePrintAction::fileShouldAdd, this, &FilePrintAction::addFile);
}

FilePrintAction::~FilePrintAction()
{
    QObject::disconnect(m_connection);
}

void FilePrintAction::operator()(FileInfo &file)
{
    emit fileShouldAdd(file);
}

void FilePrintAction::addFile(const FileInfo& fileInfo)
{
    m_displayer.addItem(fileInfo);
}




//
// FilePrintAction
//

FileSaverAction::FileSaverAction(XMLFileWriter& writer, QLabel& lable)
    : m_writer(writer)
{
    m_connection = QObject::connect(this, SIGNAL(shouldChangeStatus(QString)), &lable, SLOT(setText(const QString&)));
}

FileSaverAction::~FileSaverAction()
{
    QObject::disconnect(m_connection);
}

void FileSaverAction::operator()(FileInfo& file)
{
    emit shouldChangeStatus(file.path);
    m_writer.add(file);
}

void FileSaverAction::stop()
{
    m_writer.save(); 
    m_writer.clear();
    m_writer.close();
}




//
// FileSearchAction
//

FileSearchAction::FileSearchAction(FileInfoDisplayer& displayer)
    : m_printAction(displayer)
{

}

void FileSearchAction::operator()(FileInfo& file)
{
    if (m_searchByName)
    {
        if (!file.name.contains(m_name))
        {
            return;
        }
    }

    if (m_searchByExtension)
    {
        QFileInfo fi(file.name);
        QString ext = fi.suffix();
        if (ext != m_extansion)
        {
            return;
        }
    }

    if (m_searchByDate)
    {
        if (file.date != m_date)
        {
            return;
        }
    }
    if (m_searchBySize)
    {
        if (file.size != m_size)
        {
            return;
        }
    }

    m_printAction(file);
}

void FileSearchAction::setSearchByName(bool val)
{
    m_searchByName = val;
}

void FileSearchAction::setName(const QString& name)
{
    m_name = name;
}

void FileSearchAction::setSearchByExtension(bool val)
{
    m_searchByExtension = val;
}

void FileSearchAction::setExtansion(const QString& exstansion)
{
    m_extansion = exstansion;
}

void FileSearchAction::setSearchByDate(bool val)
{
    m_searchByDate = val;
}

void FileSearchAction::setDate(const Date& date)
{
    m_date = date;
}

void FileSearchAction::setSearchBySize(bool val)
{
    m_searchBySize = val;
}

void FileSearchAction::setSize(size_t size)
{
    m_size = size;
}
