//
// Created by Alex Nicklin on 22/10/2025.
//

#include "../main.h"

#include "view.h"
#include "ui.h"

mediaFileRenamerMainView::mediaFileRenamerMainView() {

}

int mediaFileRenamerMainView::create_window(int argc, char *argv[]) {
    QApplication a(argc, argv);
    auto p_mediaFileRenamerMainWindow = new mediaFileRenamerMainWindow();

    QPushButton * lpTestBtn = p_mediaFileRenamerMainWindow -> window()->findChild<QPushButton*>("pushButton");
    QObject::connect(lpTestBtn, &QPushButton::clicked, [=]() {
        SPDLOG_DEBUG("Select folder button pressed");
    });

    return a.exec();
}

