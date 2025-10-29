//
// Created by Alex Nicklin on 22/10/2025.
//

#include "../main.h"

#include "view.h"
#include "ui.h"

mediaFileRenamerMainView::mediaFileRenamerMainView() {

}

void mediaFileRenamerMainView::create_window(int argc, char *argv[]) {
    SPDLOG_INFO("Initialising View ....");
    QApplication * p_QApplication = new QApplication(argc, argv);
    auto p_mediaFileRenamerMainWindow = new mediaFileRenamerMainWindow();

    QPushButton * lpTestBtn = p_mediaFileRenamerMainWindow -> window()->findChild<QPushButton*>("pushButton");
    QObject::connect(lpTestBtn, &QPushButton::clicked, [=]() {
        SPDLOG_DEBUG("Select folder button pressed");
    });
}

int mediaFileRenamerMainView::displayWindow() {
    return p_QApplication -> exec();
}

