#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "CheckBoxController.h"
#include "FileSystemTraveler.h"
#include "FileInfoDisplayer.h"
#include <memory.h>
#include "XMLFileTravelerQImpl.h"
#include "XMLFileWriter.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    // Action on start indexing button.
    void on_StartIndexing_clicked();

    // Action on resume indexing button.
    void on_ResumeIndexing_clicked();

    // Action on pause indexing button.
    void on_PauseIndexing_clicked();

    // Action on stop indexing button.
    void on_StopIndexing_clicked();

    // Action on resume searching button.
    void on_ResumeSearch_clicked();

    // Action on pause searching button.
    void on_PauseSearch_clicked();

    // Action on stop searching button.
    void on_StopSearch_clicked();

    // Action on start searching button.
    void on_StartSearch_clicked();

    // Action on select file path button.
    void on_SelectFilePath_clicked();

private:

    // Ui of Main Window.
    Ui::MainWindow* ui;

    // CheckBoxController to all SearchMenu and IndexMenu checkboxes.
    CheckBoxController m_checkBoxController;

    // Action that prints to table.
    std::unique_ptr<FileAction> m_printAction;

    // Action that stores fileinfo to xml file.
    std::unique_ptr<FileAction> m_storeAction;

    // Action that searches in XML file.
    std::unique_ptr<FileSearchAction> m_searchAction;

    // Traveler, iterates through all filesystem, and uses some action on every file.
    std::unique_ptr<IFileSystemTraveler> m_traveler;

    // Display fileinfo to table.
    std::unique_ptr<FileInfoDisplayer> m_displayer;
    
    // Traveler travels through all fileinfo in XML file.
    std::unique_ptr<IXMLFileTraveler> m_XMLTraveler;

    // Writes fileinfo to XML file.
    std::unique_ptr<XMLFileWriter> m_XMLWriter;

    // Is path to XML file set.
    bool m_filePathSet = 0;

    // Path to XML file.
    QString m_filePath;

private:

    // Inits all check boxes.
    void setCheckBoxController();
};
#endif // MAINWINDOW_H
