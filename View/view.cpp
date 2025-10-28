//
// Created by Alex Nicklin on 22/10/2025.
//

#include "view.h"
#include "ui.h"

mediaFileRenamerMainView::mediaFileRenamerMainView() {

}

int mediaFileRenamerMainView::create_window(int argc, char *argv[]) {
    QApplication a(argc, argv);
    auto p_mediaFileRenamerMainWindow = new mediaFileRenamerMainWindow();
    return a.exec();
}

