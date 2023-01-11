#pragma once

#include <QString>
#include "Date.h"
#include <QFileInfo>

// Contains name of file, path to file, size of file, date last modifyed
struct FileInfo
{
    // Data of file.
    QString name;
    QString path;
    size_t size;
    Date date;

    // Converts from QFileInfo data to this object.
    void fromQFileInfo(const QFileInfo& info);
};

