#include "FileInfo.h"

void FileInfo::fromQFileInfo(const QFileInfo& info)
{
    name = info.fileName();
    path = info.absoluteFilePath();
    size = info.size();
    date.fromQDateTime(info.lastModified());
}