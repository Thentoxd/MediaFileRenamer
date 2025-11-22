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
    connect(this -> resetToDefaultsButton, &QPushButton::clicked,  this, &mediaFileRenamerMainView::resetToDefaultButtonClicked);

    connect(tableWidget->selectionModel(), &QItemSelectionModel::selectionChanged, this, &mediaFileRenamerMainView::onSelectedRowsChange);
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

    // Need to activate the Year, Month and Day widgets
    year_label->setEnabled(true);
    month_label->setEnabled(true);
    day_label->setEnabled(true);

    year_lineEdit ->setEnabled(true);
    month_lineEdit ->setEnabled(true);
    day_lineEdit ->setEnabled(true);
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

    for(auto& item : my_QList) {
        row_values.push_back(item.row());
    }

    ranges::sort(row_values);

    for(int i = 0; i < tableWidget->rowCount(); i++) {
        bool found = false;
        for(int j = 0; j < row_values.size(); j++) {
            if(row_values[j] == i) {
                found = true;
                break;
            }
        }

        if(!found) {
            QTableWidgetItem *item = new QTableWidgetItem;
            QFont font = item->font();
            font.setItalic(true);
            item->setFont(font);
            item->setText("(unchanged)");
            tableWidget->setItem(i, 1, item);

            QTableWidgetItem *item2 = new QTableWidgetItem;
            QFont font2 = item2->font();
            font.setItalic(true);
            item2->setFont(font);
            item2->setText("(unchanged)");
            tableWidget->setItem(i, 3, item2);
        }
    }

    p_model ->clearRenamingChain();
    vector<pair<string, string>> returnPairList = p_model -> executeRenamingChain(row_values);

    int counter = 0;
    for (auto returnPair : returnPairList)
    {
        SPDLOG_INFO("View number {} returned filename {}", counter, returnPair.first);
        SPDLOG_INFO("View number {} returned date created Original {}", counter, returnPair.second);

        // If the new filename or new Create Date (Original) matches the old values
        // show the test (unchanged)

        // First, let's get the current filename and Create Date (Original) being displayed

        auto currentFilename = (tableWidget->item(row_values[counter], 0) -> text()).toStdString();

        QTableWidgetItem *item = new QTableWidgetItem;

        if (currentFilename == returnPair.first) {
            returnPair.first = "(unchanged)";
        }

        item->setText(QString::fromStdString((returnPair.first)));
        item -> setForeground(QBrush(QColor(255, 0, 0)));
        tableWidget->setItem(row_values[counter], 1, item);

        auto currentCreateDate = (tableWidget->item(row_values[counter], 2) -> text()).toStdString();

        if (currentCreateDate == returnPair.second) {
            returnPair.second = "(unchanged)";
        }

        QTableWidgetItem *item2 = new QTableWidgetItem;
        item2->setText(QString::fromStdString((returnPair.second)));
        item2 -> setForeground(QBrush(QColor(255, 0, 0)));
        tableWidget->setItem(row_values[counter], 3, item2);

        counter++;
    }
}

void mediaFileRenamerMainView::updateTable() {
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

        string oldFilename = entry->getCurrentFileName();
        item1->setText(QString::fromStdString(oldFilename));
        tableWidget->setItem(row,0,item1);

        string newFilename = entry->getNewFileName();

        if (oldFilename == newFilename) {
            newFilename = "(unchanged)";
        }

        item2->setText(QString::fromStdString(newFilename));

        QFont font = item2->font();
        font.setItalic(true);
        item2->setFont(font);

        tableWidget->setItem(row,1,item2);

        string currentDateTakenOriginal = entry->getCurrentDateTakenOriginal();
        item3->setText(QString::fromStdString(currentDateTakenOriginal));
        tableWidget->setItem(row,2,item3);

        string newDateTakenOriginal = entry->getNewDateTakenOriginal();

        if (currentDateTakenOriginal == newDateTakenOriginal) {
            if (!currentDateTakenOriginal.empty())
                newDateTakenOriginal = "(unchanged)";
        }

        QFont font2 = item4->font();
        font2.setItalic(true);
        item4->setFont(font2);

        item4->setText(QString::fromStdString(newDateTakenOriginal));
        tableWidget->setItem(row,3,item4);
    }
}

void mediaFileRenamerMainView::resetToDefaultButtonClicked() {
    SPDLOG_INFO("mediaFileRenamerMainView::resetToDefaultButtonClicked");
    p_model -> reload();
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

