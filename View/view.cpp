//
// Created by Alex Nicklin on 22/10/2025.
//

#include <QFileDialog>
#include <QPixmap>
#include <QSpinBox>

#include "../main.h"
#include "view.h"

#include <fstream>
#include <iostream>

#include "../Model/model.h"

#include "chain_editor.h"
#include "dateRename.h"
#include "separator.h"
#include "types.hpp"
#include "FilenameBodyRename.h"
#include "NumberingRename.h"

#include "CLI/App.hpp"


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
    connect(this -> renameFilesButton, &QPushButton::clicked, this, &mediaFileRenamerMainView::renameFilesButtonClicked);
    connect(this -> resetToDefaultsButton, &QPushButton::clicked,  this, &mediaFileRenamerMainView::resetToDefaultButtonClicked);
    connect(tableWidget->selectionModel(), &QItemSelectionModel::selectionChanged, this, &mediaFileRenamerMainView::onSelectedRowsChange);
    connect(this -> loadPreviews_checkBox, &QCheckBox::checkStateChanged, this, &mediaFileRenamerMainView::loadPreviews);

    // Menu signal
    // connect actionExit QAction::triggered   (bool checked = false)
    connect(this -> actionExit, &QAction::triggered, this, &mediaFileRenamerMainView::menuExit);
    connect(this -> actionChain_Editor, &QAction::triggered, this, &mediaFileRenamerMainView::menuChainEditor);

    // Connect up the slots for the metadata renaming widgets
    // setMetadataOriginalCreateDateCheckBox
    // connect(this -> setMetadataOriginalCreateDateCheckBox, &QCheckBox::checkStateChanged, this, &mediaFileRenamerMainView::setmetaDataCheckBoxToggled);
    connect(this -> metadataParseFilenameForDateCheckBox, &QCheckBox::checkStateChanged, this, &mediaFileRenamerMainView::metadataParseFilenameForDateCheckBoxToggled);
    connect(this -> useFixedDateCheckBox, &QCheckBox::checkStateChanged, this, &mediaFileRenamerMainView::metadataUseFixedDate);





    currentRenamingChain = p_model -> getSavedEngineChain();

    // We need to iterate down the currentRenamingChain creating the widgets (followed by a horizontal spacer to soak up the space on the right
    if (currentRenamingChain.size() == 0) {
        SPDLOG_CRITICAL("UI told to build an empty renaming chain. That doesn't make sense. Exiting ....");
        assert(0);
    }

    for(const EngineTypes eachEngine : currentRenamingChain) {

        // Create the widgets for each engine, adding to the renamingChainHorizontalLayout widget
        // We store the root widget for each engine in the uiRenamingRootObjects vector

        switch (eachEngine)
        {
            case DateEngine: {
                SPDLOG_INFO("Creating a Date engine widget");

                QGroupBox *dateGroupBox = new QGroupBox(this);
                dateGroupBox -> setTitle("Date");
                dateGroupBox -> setCheckable(TRUE);
                dateGroupBox -> setChecked(TRUE);
                dateGroupBox -> setMaximumWidth(300);

                QCheckBox *dateCheckBox = new QCheckBox("Try to extract date from existing filename", this);
                dateCheckBox -> setChecked(TRUE);
                // auto date1 = new dateRename();
                // date1 -> connectSlots(this);

                QHBoxLayout *dateComponentsLayout = new QHBoxLayout;
                dateComponentsLayout -> setSpacing(6);
                dateComponentsLayout -> setSizeConstraint(QLayout::SetDefaultConstraint);

                QDate todaysDate = QDate::currentDate();
                QString yearQString = todaysDate.toString("yyyy");
                QString monthQString = todaysDate.toString("MM");
                QString dayQString = todaysDate.toString("dd");

                QLabel *dateYearLabel = new QLabel("Year", this);
                dateYearLabel -> setEnabled(false);
                QLineEdit *dateYearLineEdit = new QLineEdit(this);
                dateYearLineEdit -> setText(yearQString);
                dateYearLineEdit -> setEnabled(false);


                QLabel *dateMonthLabel = new QLabel("Month", this);
                dateMonthLabel -> setEnabled(false);
                QLineEdit *dateMonthLineEdit = new QLineEdit(this);
                dateMonthLineEdit -> setText(monthQString);
                dateMonthLineEdit -> setEnabled(false);

                QLabel *dateDayLabel = new QLabel("Day", this);
                dateDayLabel -> setEnabled(false);
                QLineEdit *dateDayLineEdit = new QLineEdit(this);
                dateDayLineEdit -> setText(dayQString);
                dateDayLineEdit -> setEnabled(false);

                dateComponentsLayout->addWidget(dateYearLabel);
                dateComponentsLayout->addWidget(dateYearLineEdit);
                dateComponentsLayout->addWidget(dateMonthLabel);
                dateComponentsLayout->addWidget(dateMonthLineEdit);
                dateComponentsLayout->addWidget(dateDayLabel);
                dateComponentsLayout->addWidget(dateDayLineEdit);

                QCheckBox *dateUseMetadataOriginalDateCheckBox = new QCheckBox("If set, use Metadata Date Taken Original", this);

                QVBoxLayout *layout = new QVBoxLayout;
                layout -> addWidget(dateCheckBox);
                layout -> addLayout(dateComponentsLayout);
                layout -> addWidget(dateUseMetadataOriginalDateCheckBox);
                dateGroupBox -> setLayout(layout);

                uiRenamingRootObjects.append(dateGroupBox);
                renamingChainHorizontalLayout -> addWidget(dateGroupBox);

                auto p_date = new dateRename(p_model, dateGroupBox, dateCheckBox, dateYearLineEdit, dateMonthLineEdit, dateDayLineEdit, dateUseMetadataOriginalDateCheckBox, this);
                p_date -> connectSlots();

                break;
            }

            case SeperatorEngine: {
                SPDLOG_INFO("Creating a Seperator engine widget");

                // First create a QGroupBox
                QGroupBox *seperatorGroupBox = new QGroupBox(this);
                seperatorGroupBox -> setTitle("Separator");
                seperatorGroupBox -> setCheckable(TRUE);
                seperatorGroupBox -> setChecked(TRUE);
                seperatorGroupBox -> setFixedWidth(80);

                QLineEdit *seperatorLineEdit = new QLineEdit(this);
                seperatorLineEdit -> setFixedWidth(50);
                seperatorLineEdit -> setText(" ");

                QVBoxLayout *layout = new QVBoxLayout;
                layout->addWidget(seperatorLineEdit);
                seperatorGroupBox -> setLayout(layout);

                uiRenamingRootObjects.append(seperatorGroupBox);
                renamingChainHorizontalLayout -> addWidget(seperatorGroupBox);

                auto p_separator = new separator(p_model, seperatorLineEdit, seperatorGroupBox, this);
                int separatorID = p_separator ->getID();
                SPDLOG_INFO("Created separator instance with ID {}", separatorID);
                p_separator -> connectSlots();

                break;
            }

            case FilenameBodyEngine: {
                SPDLOG_INFO("Creating a FilenameBody engine widget");

                QGroupBox *filenameBodyGroupBox = new QGroupBox(this);
                filenameBodyGroupBox -> setTitle("Filename Body");
                filenameBodyGroupBox -> setCheckable(TRUE);
                filenameBodyGroupBox -> setChecked(TRUE);

                QLabel * p_QLabel = new QLabel("Fixed Text: ", this);

                QLineEdit *filenameBodyLineEdit = new QLineEdit(this);

                QHBoxLayout * filenameBodyHLayout = new QHBoxLayout();
                filenameBodyHLayout -> addWidget(p_QLabel);
                filenameBodyHLayout -> addWidget(filenameBodyLineEdit);
                filenameBodyGroupBox -> setLayout(filenameBodyHLayout);

                uiRenamingRootObjects.append(filenameBodyGroupBox);
                renamingChainHorizontalLayout -> addWidget(filenameBodyGroupBox);

                auto p_FilenameBody = new FilenameBodyRename(p_model, this, filenameBodyGroupBox, filenameBodyLineEdit);
                p_FilenameBody -> connectSlots();

                break;
            }

            case NumberingEngine: {
                SPDLOG_INFO("Creating a Numbering engine widget");
                QGroupBox *dateGroupBox = new QGroupBox(this);
                dateGroupBox -> setTitle("Numbering");
                dateGroupBox -> setCheckable(TRUE);
                dateGroupBox -> setChecked(TRUE);
                dateGroupBox->setMinimumWidth(200);

                QGridLayout *grid_layout = new QGridLayout;
                // grid_layout->setContentsMargins(0, 0, 0, 0);

                grid_layout->addWidget(new QLabel("Starting Value", this), 0, 0);
                grid_layout->addWidget(new QLabel("Padding", this), 1, 0);
                QSpinBox *spin_box1 = new QSpinBox(this);
                spin_box1->setMaximumWidth(60);

                QSpinBox *spin_box2 = new QSpinBox(this);
                spin_box2->setMaximumWidth(60);

                grid_layout->addWidget(spin_box1, 0, 1);
                grid_layout->addWidget(spin_box2, 1, 1);

                dateGroupBox->setLayout(grid_layout);

                uiRenamingRootObjects.append(dateGroupBox);
                renamingChainHorizontalLayout -> addWidget(dateGroupBox);

                auto p_NumberingRename = new NumberingRename(p_model, dateGroupBox, this, spin_box1, spin_box2);
                p_NumberingRename -> connectSlots();

                break;
            }

        }
    }
    // We add a final horizontal spacer at the end of the horizontal layout - just to make the spacing look OK
    QSpacerItem *horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Maximum);
    renamingChainHorizontalLayout->addSpacerItem(horizontalSpacer);


    // We need to add widgets to the renamingChainHorizontalLayout widget
    // QLabel *test_label = new QLabel(this);
    // test_label->setText("Random String");
    // renamingChainHorizontalLayout -> addWidget(test_label);
    //
    // QLabel *test_label2 = new QLabel(this);
    // test_label2->setText("Bob");
    // renamingChainHorizontalLayout -> addWidget(test_label2);


    // These slots were for the old model where the sequence of renaming "parts" was fixed in the UI
    // This meant we can hard-code slots into one running instance of the mediaFileRenamerMainView class




    // connect(this -> filenamebody_lineEdit, &QLineEdit::textChanged, this, &mediaFileRenamerMainView::setFilenameBody);


    // connect(this -> numSuffixStartSpinBox, qOverload<int>(&QSpinBox::valueChanged), this, &mediaFileRenamerMainView::setCounterStart);
    // connect(this -> numSuffixPadSpinBox, qOverload<int>(&QSpinBox::valueChanged), this, &mediaFileRenamerMainView::setCounterPadding);

    // // connect(this -> useNumberingSuffix, &QCheckBox::checkStateChanged, this, &mediaFileRenamerMainView::useNumberingSuffixClicked);
    //
    // connect(this -> seperatorA_lineEdit, &QLineEdit::textEdited, this, &mediaFileRenamerMainView::seperatorAEntered);
    // connect(this -> seperatorB_lineEdit, &QLineEdit::textEdited, this, &mediaFileRenamerMainView::seperatorBEntered);
    // connect(this->dateFormat, &QLineEdit::textEdited, this, &mediaFileRenamerMainView::setDateFormat);
    //

    // connect(this -> firstSeperatorGroup, &QGroupBox::toggled, this, &mediaFileRenamerMainView::firstSeperatorGroupToggled);
    // connect(this -> fileNameBodyGroup, &QGroupBox::toggled, this, &mediaFileRenamerMainView::fileNameBodyGroupToggled);
    // connect(this -> secondSeperatorGroup, &QGroupBox::toggled, this, &mediaFileRenamerMainView::secondSeperatorGroupToggled);
    // connect(this -> numberingSuffixGroup, &QGroupBox::toggled, this, &mediaFileRenamerMainView::numberingSuffixGroupToggled);
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


void mediaFileRenamerMainView::resetToDefaultButtonClicked() {
    SPDLOG_INFO("mediaFileRenamerMainView::resetToDefaultButtonClicked");
    reload_window();
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


void mediaFileRenamerMainView::renameFilesButtonClicked() {
    SPDLOG_INFO("mediaFileRenamerMainView::renameFilesButtonClicked");
    p_model->clearRenamingChain();
    p_model->executeRenamingChain(getSelectedUniqueRows(), true, true);
    reload_window();
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


void mediaFileRenamerMainView::updateFolderComboBox() {
    SPDLOG_INFO("mediaFileRenamerMainView::updateFolderComboBox");
    vector<string> folders = p_model -> getFolderHistory();

    folderComboBox -> clear();

    for(const string folder : folders)
        folderComboBox -> addItem(QString::fromStdString(folder));
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


vector<int> mediaFileRenamerMainView::getSelectedUniqueRows() {
    vector<int> row_values;

    QItemSelectionModel *select = tableWidget->selectionModel();
    auto my_QList = select->selectedRows(); // return selected row(s)

    for(auto& item : my_QList) {
        row_values.push_back(item.row());
    }

    return row_values;
}


void mediaFileRenamerMainView::menuChainEditor(bool newValue) {
    SPDLOG_INFO("mediaFileRenamerMainView::menuChainEditor");
    auto chain_editor_instance = new chain_editor(this);
    chain_editor_instance->exec();
}


void mediaFileRenamerMainView::menuExit(bool newValue) {
    SPDLOG_INFO("mediaFileRenamerMainView::menuExit");
    p_model -> exitApplication();
}


/*


void mediaFileRenamerMainView::fileNameBodyGroupToggled(bool state) {
    SPDLOG_INFO("mediaFileRenamerMainView::fileNameBodyGroupToggled");
    p_model->setEngineText(int instanceNumber, state);
    onSelectedRowsChange();
}


void mediaFileRenamerMainView::numberingSuffixGroupToggled(bool state) {
    SPDLOG_INFO("mediaFileRenamerMainView::numberingSuffixGroupToggled");
    p_model->setEngineCounterSuffix(int instanceNumber, state);
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















void mediaFileRenamerMainView::setFilenameBody(const QString &text) {
    SPDLOG_INFO("mediaFileRenamerMainView::setFilenameBody");
    SPDLOG_INFO("Text entered: {}", text.toStdString());
    p_model -> setRenamingEngineTextbody(text.toStdString());
    onSelectedRowsChange();
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
}*/


// void mediaFileRenamerMainView::setmetaDataCheckBoxToggled(bool state) {
//     if (state == false) {
//         SPDLOG_INFO("setmetaDataCheckBoxToggled to OFF");
//         metadataParseFilenameForDateCheckBox -> setEnabled(FALSE);
//         metadataParseFilenameForDateCheckBox -> setChecked(FALSE);
//     }
//     else {
//         SPDLOG_INFO("setmetaDataCheckBoxToggled to ON");
//         metadataParseFilenameForDateCheckBox -> setEnabled(TRUE);
//         metadataParseFilenameForDateCheckBox -> setChecked(TRUE);
//     }
//
//     onSelectedRowsChange();
// }


void mediaFileRenamerMainView::metadataParseFilenameForDateCheckBoxToggled(bool state) {
    if (state == false) {
        SPDLOG_INFO("metadataParseFilenameForDateCheckBoxToggled to OFF");
        // metadataParseFilenameForDateCheckBox -> setChecked(FALSE);
        // useFixedDateCheckBox -> setEnabled(TRUE);
        // useFixedDateCheckBox -> setChecked(TRUE);
        // fixedYearLabel -> setEnabled(TRUE);
        // fixedMonthLabel -> setEnabled(TRUE);
        // fixedDayLabel -> setEnabled(TRUE);
        // metadataYearlineEdit -> setEnabled(TRUE);
        // metadataMonthLineEdit -> setEnabled(TRUE);
        // metadataDayLineEdit -> setEnabled(TRUE);
        // metadataParseFilenameForDateCheckBox -> setEnabled(FALSE);
        // metadataParseFilenameForDateCheckBox -> setChecked(FALSE);
    }
    else {
        SPDLOG_INFO("metadataParseFilenameForDateCheckBoxToggled to ON");
        // metadataParseFilenameForDateCheckBox -> setEnabled(TRUE);
        // metadataParseFilenameForDateCheckBox -> setChecked(TRUE);
        p_model -> setMetadataOriginalTakenDateFromFilename();
    }

    onSelectedRowsChange();
}


void mediaFileRenamerMainView::metadataUseFixedDate(bool state) {
    if (state == false) {
        SPDLOG_INFO("mediaFileRenamerMainView::useFixedDate toggled to OFF");
    }
    else {
        SPDLOG_INFO("mediaFileRenamerMainView::useFixedDate toggled to ON");
        // metadataParseFilenameForDateCheckBox -> setEnabled(TRUE);
        // metadataParseFilenameForDateCheckBox -> setChecked(TRUE);

        // This is the call I want to make - not yet implemented
        // p_model -> setMetadataOriginalTakenDateFromUserGivenYearMonthDay(param_year, param_month, param_day);
    }

    onSelectedRowsChange();
}


int mediaFileRenamerMainView::displayWindow() {
    return p_QApplication -> exec();
}

