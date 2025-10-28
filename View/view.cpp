//
// Created by Alex Nicklin on 22/10/2025.
//

#include <QPushButton>
#include <QMainWindow>
#include <QHBoxLayout>
#include <QMenuBar>
#include <QGroupBox>
#include <qscreen.h>
#include <QComboBox>
#include <QDir>
#include <QFileDialog>
#include <QLineEdit>

#include "view.h"
#include "../main.h"
#include "ui_media_file_renamer.h"

int view::create_window(int argc, char *argv[]) {
    QApplication app(argc, argv);
    auto theMainWindow = new QMainWindow();
    Ui::MediaFileRenamer ui;
    ui.setupUi(theMainWindow);

    theMainWindow -> show();
    return app.exec();
}

int view::Exit() {
    SPDLOG_DEBUG("Exit button pressed");
    return 0;
}

