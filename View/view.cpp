//
// Created by Alex Nicklin on 22/10/2025.
//

#include <QFileDialog>
#include <QPixmap>

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

void mediaFileRenamerMainView::reload_window() {
    QString qstr = QString::fromStdString(p_model -> getCurrentWorkingDirectory());

    tableWidget->setColumnCount(4 + columnOffset);

    this -> updateTable();
    this -> updateFolderComboBox();

    // Disable editing directly
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

    this -> redoTableColumnNames();
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
    folderComboBox->setEditable(true);

    this -> redoTableColumnNames();



    connect(this -> selectFolderButton, &QPushButton::clicked, this, &mediaFileRenamerMainView::selectFolderButtonClicked);
    connect(this -> folderComboBox, &QComboBox::currentIndexChanged, this, &mediaFileRenamerMainView::selectFolderComboBox);
    connect(this -> use_DateTaken_checkBox, &QCheckBox::checkStateChanged, this, &mediaFileRenamerMainView::setUseDateTakenButtonClicked);
    connect(this -> set_DateTaken_checkBox, &QCheckBox::checkStateChanged, this, &mediaFileRenamerMainView::setDateTakenOriginalButtonClicked);
    connect(this -> filenamebody_lineEdit, &QLineEdit::textChanged, this, &mediaFileRenamerMainView::setFilenameBody);
    connect(this -> numSuffixStartSpinBox, qOverload<int>(&QSpinBox::valueChanged), this, &mediaFileRenamerMainView::setCounterStart);
    connect(this -> numSuffixPadSpinBox, qOverload<int>(&QSpinBox::valueChanged), this, &mediaFileRenamerMainView::setCounterPadding);
    connect(this -> renameFilesButton, &QPushButton::clicked, this, &mediaFileRenamerMainView::renameFilesButtonClicked);
    connect(this -> resetToDefaultsButton, &QPushButton::clicked,  this, &mediaFileRenamerMainView::resetToDefaultButtonClicked);
    connect(tableWidget->selectionModel(), &QItemSelectionModel::selectionChanged, this, &mediaFileRenamerMainView::onSelectedRowsChange);

    connect(this -> attempt_findDate_checkBox, &QCheckBox::checkStateChanged, this, &mediaFileRenamerMainView::setDateTryExtractDateButtonClicked);
    connect(this -> year_lineEdit, &QLineEdit::textChanged, this, &mediaFileRenamerMainView::setYear);
    connect(this -> month_lineEdit, &QLineEdit::textChanged, this, &mediaFileRenamerMainView::setMonth);
    connect(this -> day_lineEdit, &QLineEdit::textChanged, this, &mediaFileRenamerMainView::setDay);

    connect(this -> loadPreviews_checkBox, &QCheckBox::checkStateChanged, this, &mediaFileRenamerMainView::loadPreviews);

    // connect(this -> useNumberingSuffix, &QCheckBox::checkStateChanged, this, &mediaFileRenamerMainView::useNumberingSuffixClicked);

    connect(this -> seperatorA_lineEdit, &QLineEdit::textEdited, this, &mediaFileRenamerMainView::seperatorAEntered);
    connect(this -> seperatorB_lineEdit, &QLineEdit::textEdited, this, &mediaFileRenamerMainView::seperatorBEntered);
    connect(this->dateFormat, &QLineEdit::textEdited, this, &mediaFileRenamerMainView::setDateFormat);


    connect(this -> datePrefixGroup, &QGroupBox::toggled, this, &mediaFileRenamerMainView::datePrefixGroupToggled);
    connect(this -> firstSeperatorGroup, &QGroupBox::toggled, this, &mediaFileRenamerMainView::firstSeperatorGroupToggled);
    connect(this -> fileNameBodyGroup, &QGroupBox::toggled, this, &mediaFileRenamerMainView::fileNameBodyGroupToggled);
    connect(this -> secondSeperatorGroup, &QGroupBox::toggled, this, &mediaFileRenamerMainView::secondSeperatorGroupToggled);
    connect(this -> numberingSuffixGroup, &QGroupBox::toggled, this, &mediaFileRenamerMainView::numberingSuffixGroupToggled);


    // Menu signal
    // connect actionExit QAction::triggered   (bool checked = false)
    connect(this -> actionExit, &QAction::triggered, this, &mediaFileRenamerMainView::menuExit);
}

void mediaFileRenamerMainView::datePrefixGroupToggled(bool state) {
    SPDLOG_INFO("mediaFileRenamerMainView::datePrefixGroupToggled");
    p_model->setEngineDatePrefix(state);
    onSelectedRowsChange();
}


void mediaFileRenamerMainView::fileNameBodyGroupToggled(bool state) {
    SPDLOG_INFO("mediaFileRenamerMainView::fileNameBodyGroupToggled");
    p_model->setEngineText(state);
    onSelectedRowsChange();
}


void mediaFileRenamerMainView::numberingSuffixGroupToggled(bool state) {
    SPDLOG_INFO("mediaFileRenamerMainView::numberingSuffixGroupToggled");
    p_model->setEngineCounterSuffix(state);
    onSelectedRowsChange();
}


void mediaFileRenamerMainView::firstSeperatorGroupToggled(bool state) {
    SPDLOG_INFO("mediaFileRenamerMainView::firstSeperatorGroupToggled");

    if (state == false) {
        p_model -> setSeperatorA("");
    }
    else {
        QString separator = seperatorB_lineEdit -> text();
        string seperatorA = separator.toStdString();
        SPDLOG_INFO("String entered: {}", seperatorA);
        p_model -> setSeperatorB(seperatorA);
    }
    onSelectedRowsChange();
}


void mediaFileRenamerMainView::secondSeperatorGroupToggled(bool state) {
    SPDLOG_INFO("mediaFileRenamerMainView::secondSeperatorGroupToggled");
    if (state == false) {
        p_model -> setSeperatorB("");
    }
    else {
        QString separator = seperatorB_lineEdit -> text();
        string seperatorB = separator.toStdString();
        SPDLOG_INFO("String entered: {}", seperatorB);
        p_model -> setSeperatorB(seperatorB);
    }
    onSelectedRowsChange();
    onSelectedRowsChange();
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


void mediaFileRenamerMainView::setYearMonthDayButtonsEnabled(bool newValue) {
    year_label->setEnabled(newValue);
    month_label->setEnabled(newValue);
    day_label->setEnabled(newValue);

    year_lineEdit ->setEnabled(newValue);
    month_lineEdit ->setEnabled(newValue);
    day_lineEdit ->setEnabled(newValue);
}

void mediaFileRenamerMainView::setDateTryExtractDateButtonClicked(Qt::CheckState newState) {
    SPDLOG_INFO("mediaFileRenamerMainView::setDateTryExtractDate");
    if (newState == Qt::Checked) {
        this -> setYearMonthDayButtonsEnabled(false);

        if(use_DateTaken_checkBox->isChecked()) {
            use_DateTaken_checkBox -> setChecked(false);
        }
        p_model -> setRenamingEngineDateTryExtractDate(true);
    }
    else {
        this -> setYearMonthDayButtonsEnabled(true);
        p_model -> setRenamingEngineDateTryExtractDate(false);
    }
    onSelectedRowsChange();
}

void mediaFileRenamerMainView::setUseDateTakenButtonClicked(Qt::CheckState newState) {
    SPDLOG_DEBUG("Use Date Taken (Original)");
    if (newState == Qt::Checked) {
        p_model -> setRenamingEngineDateUseOriginalDateTaken(true);
        attempt_findDate_checkBox->setChecked(false);
        p_model -> setRenamingEngineDateTryExtractDate(false);

        set_DateTaken_checkBox->setChecked(false);
        p_model -> setRenamingEngineDateSetOriginalDateTaken(false);
    }
    else {
        p_model -> setRenamingEngineDateUseOriginalDateTaken(false);

        attempt_findDate_checkBox->setChecked(true);
        p_model -> setRenamingEngineDateTryExtractDate(true);
    }
    onSelectedRowsChange();
}


void mediaFileRenamerMainView::setDateTakenOriginalButtonClicked(Qt::CheckState newState) {
    SPDLOG_DEBUG("Set Date Taken (Original)");
    if (newState == Qt::Checked) {
        // this -> setYearMonthDayButtonsEnabled(false);
        use_DateTaken_checkBox -> setChecked(false);
        // attempt_findDate_checkBox -> setChecked(false);

        p_model -> setRenamingEngineDateSetOriginalDateTaken(true);
        // p_model -> setRenamingEngineDateTryExtractDate(false);
    }
    else {
        p_model -> setRenamingEngineDateSetOriginalDateTaken(false);
    }
    onSelectedRowsChange();
}


void mediaFileRenamerMainView::selectFolderComboBox(int index) {
    SPDLOG_INFO("mediaFileRenamerMainView::selectFolderComboBox");
    SPDLOG_INFO("folder combo box index changed to {}", index);
    if (index != -1) {
        vector<string> folders = p_model -> getFolderHistory();

        // Have we entered a new dirrectory?
        if (index > folders.size() - 1) {
            string newFolder = (folderComboBox -> currentText()).toStdString();
            SPDLOG_INFO("New folder entered: {}", newFolder);
            p_model -> setCurrentWorkingDirectory(newFolder);
        }
        else {
            p_model -> setCurrentWorkingDirectory(folders[index]);
        }

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
    vector<int> row_values = getSelectedUniqueRows();

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
            tableWidget->setItem(i, 1 + columnOffset, item);

            QTableWidgetItem *item2 = new QTableWidgetItem;
            QFont font2 = item2->font();
            font.setItalic(true);
            item2->setFont(font);
            item2->setText("(unchanged)");
            tableWidget->setItem(i, 3 + columnOffset, item2);
        }
    }

    p_model ->clearRenamingChain();
    vector<pair<string, string>> returnPairList = p_model -> executeRenamingChain(row_values, false, false);

    int counter = 0;
    for (auto returnPair : returnPairList)
    {
        SPDLOG_INFO("Execute on row {} returned filename {}", row_values[counter]+1, returnPair.first);
        SPDLOG_INFO("Execute on row {} returned date created Original {}", row_values[counter]+1, returnPair.second);

        // If the new filename or new Create Date (Original) matches the old values
        // show the test (unchanged)

        // First, let's get the current filename and Create Date (Original) being displayed

        auto currentFilename = (tableWidget->item(row_values[counter], 0 + columnOffset) -> text()).toStdString();

        QTableWidgetItem *item = new QTableWidgetItem;

        if (currentFilename == returnPair.first) {
            returnPair.first = "(unchanged)";
        }

        item->setText(QString::fromStdString((returnPair.first)));
        item -> setForeground(QBrush(QColor(255, 0, 0)));
        tableWidget->setItem(row_values[counter], 1 + columnOffset, item);

        auto currentCreateDate = (tableWidget->item(row_values[counter], 2 + columnOffset) -> text()).toStdString();

        if (currentCreateDate == returnPair.second) {
            returnPair.second = "(unchanged)";
        }

        QTableWidgetItem *item2 = new QTableWidgetItem;
        item2->setText(QString::fromStdString((returnPair.second)));
        item2 -> setForeground(QBrush(QColor(255, 0, 0)));
        tableWidget->setItem(row_values[counter], 3 + columnOffset, item2);

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

    string currentWorkingDir = p_model -> getCurrentWorkingDirectory();

    for (int row = 0; row < entryCount; row++) {
        int columnCount = 0;
        FileEntryInterface *entry = p_model->getFileEntry(row);
        auto item1 = new QTableWidgetItem(), item2 = new QTableWidgetItem(), item3 = new QTableWidgetItem(), item4 = new QTableWidgetItem(), item5 = new QTableWidgetItem();

        string oldFilename = entry->getCurrentFileName();

        if (loadPreviewsFlag == true) {
            string fileName = currentWorkingDir.append("/");
            fileName.append(oldFilename);

            QPixmap image;
            image.load(QString::fromStdString(fileName));

            if(image.width()>512 || image.height()>512){
                image = image.scaled(100,100,Qt::KeepAspectRatio);
            }

            QLabel *lblTest = new QLabel;
            lblTest->setPixmap(image);
            lblTest->setAlignment(Qt::AlignCenter);

            // item5 -> setData(Qt::DecorationRole, QPixmap(image));
            tableWidget->setCellWidget(row,columnCount, lblTest);
            // tableWidget->setItem(row,columnCount,item5);
            columnCount++;
        }

        item1->setText(QString::fromStdString(oldFilename));
        tableWidget->setItem(row,columnCount,item1);
        columnCount++;

        string newFilename = entry->getNewFileName();

        if (oldFilename == newFilename) {
            newFilename = "(unchanged)";
        }

        item2->setText(QString::fromStdString(newFilename));

        QFont font = item2->font();
        font.setItalic(true);
        item2->setFont(font);
        tableWidget->setItem(row,columnCount,item2);
        columnCount++;

        string currentDateTakenOriginal = entry->getCurrentDateTakenOriginal();
        item3->setText(QString::fromStdString(currentDateTakenOriginal));
        tableWidget->setItem(row,columnCount,item3);
        columnCount++;

        string newDateTakenOriginal = entry->getNewDateTakenOriginal();

        if (newDateTakenOriginal == currentDateTakenOriginal) {
            if (!newDateTakenOriginal.empty()) {
                newDateTakenOriginal = "(unchanged)";
            }
        }

        item4->setText(QString::fromStdString(newDateTakenOriginal));

        QFont font2 = item4->font();
        font2.setItalic(true);
        item4->setFont(font2);
        tableWidget->setItem(row,columnCount,item4);
        columnCount++;

        if (loadPreviewsFlag == true) {
            tableWidget-> setRowHeight(row, 100);
        }
    }

}

void mediaFileRenamerMainView::resetToDefaultButtonClicked() {
    SPDLOG_INFO("mediaFileRenamerMainView::resetToDefaultButtonClicked");
    reload_window();
}


void mediaFileRenamerMainView::setFilenameBody(const QString &text) {
    SPDLOG_INFO("mediaFileRenamerMainView::setFilenameBody");
    SPDLOG_INFO("Text entered: {}", text.toStdString());
    p_model -> setRenamingEngineTextbody(text.toStdString());
    onSelectedRowsChange();
}


vector<int> mediaFileRenamerMainView::getSelectedUniqueRows() {
    vector<int> row_values;

    QItemSelectionModel *select = tableWidget->selectionModel();
    auto my_QList = select->selectedRows(); // return selected row(s)

    for(auto& item : my_QList) {
        row_values.push_back(item.row());
    }

    return row_values;
}


void mediaFileRenamerMainView::renameFilesButtonClicked() {
    SPDLOG_INFO("mediaFileRenamerMainView::renameFilesButtonClicked");
    p_model->clearRenamingChain();
    p_model->executeRenamingChain(getSelectedUniqueRows(), true, true);
    reload_window();
}


void mediaFileRenamerMainView::setCounterStart(int newValue) {
    SPDLOG_INFO("mediaFileRenamerMainView::setCounterStart");
    SPDLOG_INFO("Setting counter start to {}", newValue);
    p_model -> setCounterStart(newValue);
    onSelectedRowsChange();
}


void mediaFileRenamerMainView::setCounterPadding(int newValue) {
    SPDLOG_INFO("mediaFileRenamerMainView::setCounterPadding");
    SPDLOG_INFO("Setting counter padding to {}", newValue);
    p_model -> setCounterPadding(newValue);
    onSelectedRowsChange();
}


void mediaFileRenamerMainView::setDateFormat(const QString &text) {
    SPDLOG_INFO("mediaFileRenamerMainView::setDateFormat");
    SPDLOG_INFO("Date Format: {}", text.toStdString());
    onSelectedRowsChange();
}


void mediaFileRenamerMainView::setYear(const QString &text) {
    SPDLOG_INFO("mediaFileRenamerMainView::setYear");
    SPDLOG_INFO("Text entered: {}", text.toStdString());
    p_model -> setRenamingEngineDateSetYear(text.toStdString());
    onSelectedRowsChange();
}


void mediaFileRenamerMainView::setMonth(const QString &text) {
    SPDLOG_INFO("mediaFileRenamerMainView::setMonth");
    SPDLOG_INFO("Text entered: {}", text.toStdString());
    p_model -> setRenamingEngineDateSetMonth(text.toStdString());
    onSelectedRowsChange();
}


void mediaFileRenamerMainView::setDay(const QString &text) {
    SPDLOG_INFO("mediaFileRenamerMainView::setDay");
    SPDLOG_INFO("Text entered: {}", text.toStdString());
    p_model -> setRenamingEngineDateSetDay(text.toStdString());
    onSelectedRowsChange();
}


void mediaFileRenamerMainView::menuExit(bool newValue) {
    SPDLOG_INFO("mediaFileRenamerMainView::menuExit");
    p_model -> exitApplication();
}


void mediaFileRenamerMainView::loadPreviews(Qt::CheckState state) {
    SPDLOG_INFO("mediaFileRenamerMainView::loadPreviews");
    if (state == Qt::Checked) {
        loadPreviewsFlag = true;
        tableWidget->setColumnCount(5);
        // Need to reset Column Names
    }
    else {
        loadPreviewsFlag = false;
        tableWidget->setColumnCount(4);
    }
    this -> redoTableColumnNames();
    this -> updateTable();
}


void mediaFileRenamerMainView::redoTableColumnNames() {
    SPDLOG_INFO("mediaFileRenamerMainView::redoTableColumnNames");

    QStringList m_TableHeader;
    if (loadPreviewsFlag == true) {
        m_TableHeader<< "Preview" << "Filename"<<"New Filename"<<"Date Taken (Original)" <<"New Date Taken (Original)";
        columnOffset = 1;
    }
    else {

        m_TableHeader<<"Filename"<<"New Filename"<<"Date Taken (Original)" <<"New Date Taken (Original)";
        columnOffset = 0;
    }
    tableWidget->setHorizontalHeaderLabels(m_TableHeader);

    if (loadPreviewsFlag == true) {
        tableWidget -> horizontalHeader() -> setSectionResizeMode(0, QHeaderView::ResizeToContents);
        tableWidget -> horizontalHeader() -> setSectionResizeMode(1, QHeaderView::Stretch);
        tableWidget -> horizontalHeader() -> setSectionResizeMode(2, QHeaderView::Stretch);
        tableWidget -> horizontalHeader() -> setSectionResizeMode(3, QHeaderView::Stretch);
        tableWidget -> horizontalHeader() -> setSectionResizeMode(4, QHeaderView::Stretch);
    }
    else {
        tableWidget -> horizontalHeader() -> setSectionResizeMode(0, QHeaderView::Stretch);
        tableWidget -> horizontalHeader() -> setSectionResizeMode(1, QHeaderView::Stretch);
        tableWidget -> horizontalHeader() -> setSectionResizeMode(2, QHeaderView::Stretch);
        tableWidget -> horizontalHeader() -> setSectionResizeMode(3, QHeaderView::Stretch);
    }
}


void mediaFileRenamerMainView::seperatorAEntered() {
    SPDLOG_INFO("mediaFileRenamerMainView::seperatorAEntered");
    QString separator = seperatorA_lineEdit -> text();
    string seperatorA = separator.toStdString();
    SPDLOG_INFO("String entered: {}", seperatorA);
    p_model -> setSeperatorA(seperatorA);
    onSelectedRowsChange();
}


void mediaFileRenamerMainView::seperatorBEntered() {
    SPDLOG_INFO("mediaFileRenamerMainView::seperatorBEntered");
    QString separator = seperatorB_lineEdit -> text();
    string seperatorB = separator.toStdString();
    SPDLOG_INFO("String entered: {}", seperatorB);
    p_model -> setSeperatorB(seperatorB);
    onSelectedRowsChange();
}


int mediaFileRenamerMainView::displayWindow() {
    return p_QApplication -> exec();
}

