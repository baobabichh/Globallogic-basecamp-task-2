#pragma once

#include "FileInfo.h"
#include <qdebug.h>
#include <qobject.h>
#include <qdialog.h>
#include <qlabel.h>
#include <qtextbrowser.h>

// Class to provide action for file
class FileAction
{
public:

    virtual ~FileAction() = default;

    // Action should be overloaded in derived class.
    virtual void operator()(FileInfo& file);

    // Calls when needs stop.
    virtual void stop();

    // Calls when needs pause.
    virtual void pause();

    // Calls when needs resume.
    virtual void resume();
};


class FileInfoDisplayer;

// This action add file to FileInfoDisplayer.
// Thread safe adds row to table using signals and slots.
class FilePrintAction :  public QObject, public FileAction
{
    Q_OBJECT

signals:

    // Signal imits when we need to add file.
    void fileShouldAdd(FileInfo fileInfo);

private slots:

    // Slot to add file to table.
    void addFile(const FileInfo& fileInfo);

public:

    // Inits displayer and connection.
    FilePrintAction(FileInfoDisplayer &displayer);

    // Disconnects connection.
    virtual ~FilePrintAction();

    // Action on file.
    void operator()(FileInfo &file) override;


private:

    // Reference to table where we add files.
    FileInfoDisplayer& m_displayer;

    // Connection void fileShouldAdd(FileInfo fileInfo) and void addFile(const FileInfo& fileInfo).
    QMetaObject::Connection m_connection;
};

class XMLFileWriter;

// Uses XMLFileWriter to write files.
class FileSaverAction : private QObject, public FileAction
{
    Q_OBJECT

private: signals:

    // Signal imits when we need change status.
    void shouldChangeStatus(QString status);

public:

    // Inits XMLFileWriter.
    FileSaverAction(XMLFileWriter& writer, QLabel& lable);

    virtual ~FileSaverAction();

    // Action on file.
    void operator()(FileInfo& file) override;

    // Saves file.
    void stop() override;

private:

    // Reference to writer which add files.
    XMLFileWriter& m_writer;

    // Connection to change lable.
    QMetaObject::Connection m_connection;
};

// This action add file to FileInfoDisplayer.
// Thread safe adds row to table using signals and slots.
class FileSearchAction : public FileAction
{
public:

    // Inits m_printAction.
    FileSearchAction(FileInfoDisplayer& displayer);

    virtual ~FileSearchAction() = default;

    // Action on file.
    void operator()(FileInfo& file) override;

    // Sets that file should be searched by name.
    void setSearchByName(bool val);

    // Sets name to search. (substring)
    void setName(const QString& name);

    // Sets that file should be searched by extension.
    void setSearchByExtension(bool val);

    // Sets extension to search.
    void setExtansion(const QString& exstansion);

    // Sets that file should be searched by date. (date only)
    void setSearchByDate(bool val);

    // Sets date to search.
    void setDate(const Date& date);

    // Sets that file should be searched by size.
    void setSearchBySize(bool val);

    // Sets size to search.
    void setSize(size_t size);

private:

    // Search criteria.
    bool m_searchByName = 0;
    bool m_searchByExtension = 0;
    bool m_searchByDate = 0;
    bool m_searchBySize = 0;

    // Search values.
    QString m_name;
    QString m_extansion;
    Date m_date;
    size_t m_size;

    // Action to print.
    FilePrintAction m_printAction;
};

