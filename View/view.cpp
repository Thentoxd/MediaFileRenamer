//
// Created by Alex Nicklin on 22/10/2025.
//

#include <QFileDialog>

#include "../main.h"
#include "view.h"

mediaFileRenamerMainView::mediaFileRenamerMainView(ModelInterface * modelParam) {
    SPDLOG_INFO("Initialising View ....");

    p_model = modelParam;

    this -> setupUi(this);
    this -> show();
}

void mediaFileRenamerMainView::create_window() {
    SPDLOG_INFO("Creating main window ....");

    QString qstr = QString::fromStdString("C:\\Users\\alex\\OneDrive\\Desktop\\arduino\\test\\first\\build\\sketch"); // test directory
    lineEdit -> setText(qstr);

    // tableWidget->setModel(model);
    // tableView->show();

    populateTableView(qstr);

    // Disable editing directly
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QStringList m_TableHeader;
    m_TableHeader<<"Filename"<<"New Filename"<<"Date Taken (Original)" <<"New Date Taken (Original)";
    tableWidget->setHorizontalHeaderLabels(m_TableHeader);
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QObject::connect(this -> selectFolderButton, &QPushButton::clicked, this, &mediaFileRenamerMainView::selectFolderButtonClicked);
}

void mediaFileRenamerMainView::populateTableView(QString currentWorkingDirectory) {
    const QDir root(currentWorkingDirectory);
    if (!root.exists()) {
        SPDLOG_CRITICAL("Directory does not exist!");
        return;
    }
    QFileInfoList list = root.entryInfoList(QDir::Filter::NoDotAndDotDot | QDir::Filter::Files);
    tableWidget->setRowCount(list.count());
    tableWidget->setColumnCount(4);

    int row = 0;
    for (QFileInfo file : list) {
        setTextInCell(row, 0, file.fileName());
        setTextInCell(row, 1, file.fileName());
        setTextInCell(row, 2, file.lastModified().toString());
        setTextInCell(row, 3, file.lastModified().toString());

        row++;
    }
}

void mediaFileRenamerMainView::setTextInCell(int row, int column, QString text) {
    QTableWidgetItem *item = tableWidget->item(row, column);
    if (!item) {
        item = new QTableWidgetItem();
        tableWidget->setItem(row, column, item);
    }
    item->setText(text);
}

void mediaFileRenamerMainView::selectFolderButtonClicked() {
    SPDLOG_DEBUG("Select folder button pressed");

    QString qstr = QString::fromStdString(p_model -> getCurrentWorkingDirectory());
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                            qstr,
                                            QFileDialog::ShowDirsOnly
                                            | QFileDialog::DontResolveSymlinks);

    lineEdit -> setText(dir);
    string newCurrentWorkingDirectory = dir.toStdString();
    p_model -> setCurrentWorkingDirectory(newCurrentWorkingDirectory);
}

int mediaFileRenamerMainView::displayWindow() {
    return p_QApplication -> exec();
}

