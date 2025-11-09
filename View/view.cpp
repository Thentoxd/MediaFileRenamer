//
// Created by Alex Nicklin on 22/10/2025.
//

#include <QFileDialog>

#include "../TinyEXIF/TinyEXIF.h"
#include "../main.h"
#include "view.h"

#include <fstream>
#include <iostream>

mediaFileRenamerMainView::mediaFileRenamerMainView(ModelInterface * modelParam) {
    SPDLOG_INFO("Initialising View ....");

    p_model = modelParam;

    this -> setupUi(this);
    this -> show();
}

void mediaFileRenamerMainView::create_window() {
    SPDLOG_INFO("Creating main window ....");

    QString qstr = QString::fromStdString(p_model -> getCurrentWorkingDirectory());
    lineEdit -> setText(qstr);

    // tableWidget->setModel(model);
    // tableView->show();

    tableWidget->setRowCount(10);
    tableWidget->setColumnCount(4);

    // This function should do
    // return fileEntries.iterator();
    //auto tableDataIterator = p_model -> getTableDataIterator();
    //for (auto eachTableModel: tableDataIterator) {
    //    string currentFileName = eachTableModel -> getNewFileName();
    //    SPDLOG_INFO("Table data (name): {}", currentFileName);
    //}

    this -> updateTable();

    // Disable editing directly
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QStringList m_TableHeader;
    m_TableHeader<<"Filename"<<"New Filename"<<"Date Taken (Original)" <<"New Date Taken (Original)";
    tableWidget->setHorizontalHeaderLabels(m_TableHeader);
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Make a call onto the model to get the table data
    // Model returns an iterable object. Each iteration returns a Line Interface which
    // has the following virtual methods implemented ..
    // getFilename, getNewFile, getOriginalDateTaken, getNewOriginalDateTaken
    //

    QObject::connect(this -> selectFolderButton, &QPushButton::clicked, this, &mediaFileRenamerMainView::selectFolderButtonClicked);
}

void mediaFileRenamerMainView::selectFolderButtonClicked() {
    SPDLOG_DEBUG("Select folder button pressed");

    QString qstr = QString::fromStdString(p_model -> getCurrentWorkingDirectory());
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                            qstr,
                                            QFileDialog::ShowDirsOnly
                                            | QFileDialog::DontResolveSymlinks);

    if(dir == nullptr) {
        SPDLOG_INFO("No directory selected!");
    } else {
        lineEdit -> setText(dir);
        string newCurrentWorkingDirectory = dir.toStdString();
        p_model -> setCurrentWorkingDirectory(newCurrentWorkingDirectory);

        int entryCount = p_model -> getEntryCount();
        SPDLOG_INFO("Number of files in the model: {}", entryCount);
        this -> updateTable();
    }
}

void mediaFileRenamerMainView::updateTable() {

    // Make a call onto the model to get the table data
    // Model returns an iterable object. Each iteration returns a Line Interface which
    // has the following virtual methods implemented ..
    // getFilename, getNewFile, getOriginalDateTaken, getNewOriginalDateTaken

    int entryCount = p_model -> getEntryCount();
    SPDLOG_INFO("Number of files in the model: {}", entryCount);

    tableWidget->setRowCount(0); // This will delete all the data in the current table
    tableWidget->setRowCount(entryCount);

    for (int row = 0; row < entryCount; row++) {
        FileEntryInterface * p_fileEntryInterface = p_model -> getFileEntry(row);

        string fileName = p_fileEntryInterface->getCurrentFileName();
        // SPDLOG_INFO("Filename 1: {}", fileName);
        auto item = new QTableWidgetItem();
        item->setText(QString::fromStdString(fileName));
        tableWidget->setItem(row,0,item);

        string newFileName = p_fileEntryInterface->getNewFileName();
        // SPDLOG_INFO("Filename 1: {}", newFileName);
        auto item2 = new QTableWidgetItem();
        item2->setText(QString::fromStdString(newFileName));
        tableWidget->setItem(row,1,item2);

        time_t currentOrigTakenDate = p_fileEntryInterface->getCurrentDateTakenOriginal();
        // SPDLOG_INFO("Filename 1: {}", newFileName);
        auto item3 = new QTableWidgetItem();

        std::ifstream my_stream(p_model->getCurrentWorkingDirectory() + "/" + fileName, std::ios::binary);
        TinyEXIF::EXIFInfo imageEXIF(my_stream);

        item3->setText(QString::fromStdString(imageEXIF.DateTimeOriginal));
        tableWidget->setItem(row,2,item3);

        auto item4 = new QTableWidgetItem();

        item4->setText(QString::fromStdString(imageEXIF.DateTimeOriginal));
        tableWidget->setItem(row,3,item4);
    }
}

int mediaFileRenamerMainView::displayWindow() {
    return p_QApplication -> exec();
}

