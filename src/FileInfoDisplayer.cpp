#include "FileInfoDisplayer.h"

FileInfoDisplayer::FileInfoDisplayer(QTableWidget& table)
    : m_table(table)
{
    createStructure();
}

void FileInfoDisplayer::clear()
{
    m_table.setRowCount(0);
}

void FileInfoDisplayer::addItem(const FileInfo &fileInfo)
{
    int rowNumber = m_table.rowCount();
    m_table.insertRow(rowNumber);

    // Creating widgets, QTableWindget controls QTableWidgetItem lifetime.
    QTableWidgetItem * name = new QTableWidgetItem();
    QTableWidgetItem * date = new QTableWidgetItem();
    QTableWidgetItem * size = new QTableWidgetItem();
    QTableWidgetItem * path = new QTableWidgetItem();

    name->setText(fileInfo.name);
    date->setText(fileInfo.date.toQString());
    size->setText(QString::number(fileInfo.size));
    path->setText(fileInfo.path);

    m_table.setItem(rowNumber, 0, name);
    m_table.setItem(rowNumber, 1, date);
    m_table.setItem(rowNumber, 2, size);
    m_table.setItem(rowNumber, 3, path);
}

void FileInfoDisplayer::createStructure()
{
    QStringList colums;
    colums << "Name" << "Date" << "Size" << "Path";
    m_table.setHorizontalHeaderLabels(colums);
}
