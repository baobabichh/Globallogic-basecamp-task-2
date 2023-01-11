#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "qmessagebox.h"
#include "qfiledialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // Setting UI.
    ui->setupUi(this);

    // Init CheckBoxController.
    setCheckBoxController();

    // Set validator to line edits. (Can be only digits)
    ui->SearchBySizeLine->setValidator( new QIntValidator() );
    ui->Depth->setValidator(new QIntValidator());

    
    m_traveler = std::make_unique<FileSystemTravelerQImpl>();
    m_XMLTraveler = std::make_unique<XMLFileTravelerQImpl>();

    // Connecting displayer to Table where it should be displayed.
    m_displayer = std::make_unique<FileInfoDisplayer>(*ui->Table);
    m_printAction = std::make_unique<FilePrintAction>(*m_displayer);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setCheckBoxController()
{
    //Search
    m_checkBoxController.add(*ui->SearchByNameLineEdit,*ui->SearchByNameCheckBox);
    m_checkBoxController.add(*ui->SearchByExtensionLine,*ui->SearchByExtensionCheckBox);
    m_checkBoxController.add(*ui->SearchByDateDate,*ui->SearchByDateCheckBox);
    m_checkBoxController.add(*ui->SearchBySizeLine,*ui->SearchBySizeCheckBox);
    //Index
    m_checkBoxController.add(*ui->Depth,*ui->UseDepthCheckBox);
}


void MainWindow::on_StartIndexing_clicked()
{
    // Cant start indexing while searching.
    if (StateMachine::State::Free != m_XMLTraveler->getState())
    {
        QMessageBox::warning(this, "Warning", "You should finish searching before you start indexing.");
        return;
    }

    // Cant start indexing if there is no file to write to.
    if(!m_filePathSet)
    {
        QMessageBox::warning(this, "Warning", "File is not selected.");
        return;
    }

    // Stop treveling and recreate Writer and action that stores to file.
    m_traveler->stop();
    m_XMLWriter = std::make_unique<XMLFileWriter>(QString(m_filePath));
    m_storeAction = std::make_unique<FileSaverAction>(*m_XMLWriter, *ui->IndexingState);

    // Selecting use depth or not.
    if (ui->UseDepthCheckBox->isChecked())
    {
        m_traveler->startTraveling(*m_storeAction, QDir::root().path(), ui->Depth->text().toInt());
    }
    else
    {
        m_traveler->startTraveling(*m_storeAction, QDir::root().path());
    }
}


void MainWindow::on_ResumeIndexing_clicked()
{
    m_traveler->resume();
}


void MainWindow::on_PauseIndexing_clicked()
{
    m_traveler->pause();
}


void MainWindow::on_StopIndexing_clicked()
{
    m_traveler->stop();
}

void MainWindow::on_ResumeSearch_clicked()
{
    m_XMLTraveler->resume();
}


void MainWindow::on_PauseSearch_clicked()
{
    m_XMLTraveler->pause();
}


void MainWindow::on_StopSearch_clicked()
{
    m_XMLTraveler->stop();
}


void MainWindow::on_StartSearch_clicked()
{
    // Cant start indexing while indexing.
    if (StateMachine::State::Free != m_traveler->getState())
    {
        QMessageBox::warning(this, "Warning", "You should finish indexing before you start searching.");
        return;
    }

    // Cant start indexing if there is no file to search in.
    if(!m_filePathSet)
    {
        QMessageBox::warning(this, "Warning", "File is not selected.");
        return;
    }

    // Stop XML traveler, clear table, recreate action that searching and displaying fileinfo.
    m_XMLTraveler->stop();
    m_displayer->clear();
    m_searchAction = std::make_unique<FileSearchAction>(*m_displayer);

    // Search by date.
    if (ui->SearchByDateCheckBox->isChecked())
    {
        m_searchAction->setSearchByDate(1);
        Date date;
        date.fromQDateTime(ui->SearchByDateDate->dateTime());
        m_searchAction->setDate(date);
    }
    else
    {
        m_searchAction->setSearchByDate(0);
    }

    // Search by extension.
    if (ui->SearchByExtensionCheckBox->isChecked())
    {
        m_searchAction->setSearchByExtension(1);
        m_searchAction->setExtansion(ui->SearchByExtensionLine->text());
    }
    else
    {
        m_searchAction->setSearchByExtension(0);
    }

    // Search by name.
    if (ui->SearchByNameCheckBox->isChecked())
    {
        m_searchAction->setSearchByName(1);
        m_searchAction->setName(ui->SearchByNameLineEdit->text());
    }
    else
    {
        m_searchAction->setSearchByName(0);
    }

    // Search by size.
    if (ui->SearchBySizeCheckBox->isChecked())
    {
        m_searchAction->setSearchBySize(1);
        m_searchAction->setSize(ui->SearchBySizeLine->text().toInt());
    }
    else
    {
        m_searchAction->setSearchBySize(0);
    }

    m_XMLTraveler->startSearching(*m_searchAction, m_filePath);
}


void MainWindow::on_SelectFilePath_clicked()
{
    if(StateMachine::State::Free == m_traveler->getState() && StateMachine::State::Free == m_XMLTraveler->getState())
    {
        m_filePathSet = 1;
        
        // Opens dialog to select file.
        m_filePath = QFileDialog::getOpenFileName(this,
                                                  tr("Open XML file"), "/", tr("*.xml"));
    }
    else
    {
        // Can not select file while searching or indexing.
        QMessageBox::warning(this, "Warning", "You should finish indexing and searching before you start searching.");
    }
}

