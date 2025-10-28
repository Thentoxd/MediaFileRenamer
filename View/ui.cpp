//
// Created by Alex Nicklin on 28/10/2025.
//

#include "../main.h"

#include "view.h"
#include "ui.h"


mediaFileRenamerMainWindow::mediaFileRenamerMainWindow() {
    this -> setupUi(this);
    this -> show();
}

int mediaFileRenamerMainWindow::Exit() {
    SPDLOG_DEBUG("Exit button pressed");
    return 0;
}