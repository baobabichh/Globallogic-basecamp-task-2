#pragma once

#include <QTableWidget>
#include "FileInfo.h"

// Displays file info in some table.
class FileInfoDisplayer
{
public:

    // Takes reference to table and manipualte after.
    FileInfoDisplayer(QTableWidget& table);

    // Clears Table.
    void clear();

    // Add one item to table.
    void addItem(const FileInfo& fileInfo);

private:

    // Sets column names.
    void createStructure();

    // Reference to table.
    QTableWidget& m_table;
};

