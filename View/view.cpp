//
// Created by Alex Nicklin on 22/10/2025.
//

#include <QFileDialog>

#include "../main.h"
#include "view.h"

#include <fstream>
#include <iostream>

#include "../Model/model.h"

mediaFileRenamerMainView::mediaFileRenamerMainView(ModelInterface * modelParam) {
    SPDLOG_INFO("Initialising View ....");

    p_model = modelParam;

    this -> setupUi(this);
    this -> show();
}

void mediaFileRenamerMainView::create_window() {
    SPDLOG_INFO("Creating main window ....");

    QString qstr = QString::fromStdString(p_model -> getCurrentWorkingDirectory());

    tableWidget->setColumnCount(4);

    this -> updateTable();
    this -> updateFolderComboBox();

    // Disable editing directly
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

    QStringList m_TableHeader;
    m_TableHeader<<"Filename"<<"New Filename"<<"Date Taken (Original)" <<"New Date Taken (Original)";
    tableWidget->setHorizontalHeaderLabels(m_TableHeader);
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    connect(this -> selectFolderButton, &QPushButton::clicked, this, &mediaFileRenamerMainView::selectFolderButtonClicked);
    connect(this -> folderComboBox, &QComboBox::currentIndexChanged, this, &mediaFileRenamerMainView::selectFolderComboBox);
    connect(this -> useDateTakenButton, &QPushButton::clicked, this, &mediaFileRenamerMainView::setUseDateTakenButtonClicked);
    connect(this -> setDateTakenButton, &QPushButton::clicked, this, &mediaFileRenamerMainView::setDateTakenOriginalButtonClicked);


    connect(this -> filenamebody_lineEdit, &QLineEdit::textChanged, this, &mediaFileRenamerMainView::setFilenameBody);

    connect(this -> numSuffixStartSpinBox, QSpinBox::valueChanged, this, &mediaFileRenamerMainView::setCounterStart);
    connect(this -> numSuffixPadSpinBox, QSpinBox::valueChanged, this, &mediaFileRenamerMainView::setCounterPadding);

    connect(this -> renameFilesButton, &QPushButton::clicked, this, &mediaFileRenamerMainView::renameFilesButtonClicked);

}

void mediaFileRenamerMainView::selectFolderButtonClicked() {
    SPDLOG_DEBUG("mediaFileRenamerMainView::selectFolderButtonClicked");

    QString qstr = QString::fromStdString(p_model -> getCurrentWorkingDirectory());
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                            qstr,
                                            QFileDialog::ShowDirsOnly
                                            | QFileDialog::DontResolveSymlinks);

    if(dir == nullptr) {
        SPDLOG_INFO("No directory selected!");
    } else {

        string newCurrentWorkingDirectory = dir.toStdString();
        p_model -> setCurrentWorkingDirectory(newCurrentWorkingDirectory);

        int entryCount = p_model -> getEntryCount();
        SPDLOG_INFO("Number of files in the model: {}", entryCount);
        this -> updateFolderComboBox();
    }
}

void mediaFileRenamerMainView::setUseDateTakenButtonClicked() {
    SPDLOG_DEBUG("Use Date Taken (Original)");
}

void mediaFileRenamerMainView::setDateTakenOriginalButtonClicked() {
    SPDLOG_DEBUG("Set Date Taken (Original)");
}

void mediaFileRenamerMainView::selectFolderComboBox(int index) {
    SPDLOG_INFO("mediaFileRenamerMainView::selectFolderComboBox");
    SPDLOG_INFO("folder combo box index changed to {}", index);
    if (index != -1) {
        vector<string> folders = p_model -> getFolderHistory();
        p_model -> setCurrentWorkingDirectory(folders[index]);
        this -> updateTable();
    }
}

void mediaFileRenamerMainView::updateFolderComboBox() {
    SPDLOG_INFO("mediaFileRenamerMainView::updateFolderComboBox");
    vector<string> folders = p_model -> getFolderHistory();

    folderComboBox -> clear();

    for(const string folder : folders)
        folderComboBox -> addItem(QString::fromStdString(folder));
}

void mediaFileRenamerMainView::onSelectedRowsChange() {
    SPDLOG_INFO("mediaFileRenamerMainView::onSelectedRowsChange");
    vector<int> row_values;

    QItemSelectionModel *select = tableWidget->selectionModel();
    auto my_QList = select->selectedRows(); // return selected row(s)

    foreach(auto &item, my_QList)
    {
        row_values.insert(row_values.begin(), item.row());
    }

    vector<pair<string, string>> returnPairList = p_model -> executeRenamingChain(row_values);

    int counter = 0;
    for (auto returnPair : returnPairList)
    {
        SPDLOG_INFO("View number {} returned filename {}", counter, returnPair.first);
        SPDLOG_INFO("View number {} returned date created Original {}", counter, returnPair.second);

        QTableWidgetItem *item = new QTableWidgetItem;
        item->setText(QString::fromStdString((returnPair.first)));
        item -> setForeground(QBrush(QColor(255, 0, 0)));
        tableWidget->setItem(row_values[counter], 1, item);

        QTableWidgetItem *item2 = new QTableWidgetItem;
        item2->setText(QString::fromStdString((returnPair.second)));
        item2 -> setForeground(QBrush(QColor(255, 0, 0)));
        tableWidget->setItem(row_values[counter], 3, item2);

        counter++;
    }
}

void mediaFileRenamerMainView::updateTable() {
    disconnect(tableWidget, &QTableWidget::itemClicked, this, &mediaFileRenamerMainView::onSelectedRowsChange);

    // Make a call onto the model to get the table data
    // Model returns an iterable object. Each iteration returns a Line Interface which
    // has the following virtual methods implemented ..
    // getFilename, getNewFile, getOriginalDateTaken, getNewOriginalDateTaken

    int entryCount = p_model -> getEntryCount();
    SPDLOG_INFO("Number of files in the model: {}", entryCount);

    string status_message = "File count: " + std::to_string(entryCount);
    statusBar()->showMessage(tr(status_message.c_str()));

    tableWidget->setRowCount(0); // This will delete all the data in the current table
    tableWidget->setRowCount(entryCount);

    for (int row = 0; row < entryCount; row++) {
        FileEntryInterface *entry = p_model->getFileEntry(row);
        auto item1 = new QTableWidgetItem(), item2 = new QTableWidgetItem(), item3 = new QTableWidgetItem(), item4 = new QTableWidgetItem();

        item1->setText(QString::fromStdString(entry->getCurrentFileName()));
        tableWidget->setItem(row,0,item1);

        item2->setText(QString::fromStdString(entry->getNewFileName()));
        tableWidget->setItem(row,1,item2);

        item3->setText(QString::fromStdString(entry->getCurrentDateTakenOriginal()));
        tableWidget->setItem(row,2,item3);

        item4->setText(QString::fromStdString(entry->getNewDateTakenOriginal()));
        tableWidget->setItem(row,3,item4);
    }
    connect(tableWidget, &QTableWidget::itemClicked, this, &mediaFileRenamerMainView::onSelectedRowsChange);
}


void mediaFileRenamerMainView::setFilenameBody(const QString &text) {
    SPDLOG_INFO("mediaFileRenamerMainView::setFilenameBody");
    SPDLOG_INFO("Text entered: {}", text.toStdString());
    p_model -> setRenamingEngineTextbody(text.toStdString());
}

void mediaFileRenamerMainView::renameFilesButtonClicked() {
    SPDLOG_INFO("mediaFileRenamerMainView::renameFilesButtonClicked");
    // p_model -> executeRenamingChain(1);
}

void mediaFileRenamerMainView::setCounterStart(int newValue) {
    SPDLOG_INFO("mediaFileRenamerMainView::renameFilesButtonClicked");
    SPDLOG_INFO("Setting counter start to {}", newValue);
    p_model -> setCounterStart(newValue);
}

void mediaFileRenamerMainView::setCounterPadding(int newValue) {
    SPDLOG_INFO("mediaFileRenamerMainView::renameFilesButtonClicked");
    SPDLOG_INFO("Setting counter padding to {}", newValue);
    p_model -> setCounterPadding(newValue);
}



int mediaFileRenamerMainView::displayWindow() {
    return p_QApplication -> exec();
}

