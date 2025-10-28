//
// Created by Alex Nicklin on 28/10/2025.
//

#include "../main.h"

#include "view.h"
#include "ui.h"


mediaFileRenamerMainWindow::mediaFileRenamerMainWindow() {
    this -> setupUi(this);
    this -> show();

    // Connect a slot to the button's clicked signal
    // QObject::connect(this -> actionExit, &QPushButton::clicked, this, &mediaFileRenamerMainWindow::Exit);
}

void mediaFileRenamerMainWindow::Exit() {
    SPDLOG_DEBUG("Exit button pressed");
}