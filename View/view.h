//
// Created by Alex Nicklin on 22/10/2025.
//

#ifndef MEDIAFILERENAMER_VIEW_H
#define MEDIAFILERENAMER_VIEW_H

#include <QApplication>

class mediaFileRenamerMainView {
    QApplication * p_QApplication;
    public:
        mediaFileRenamerMainView();
        void create_window(int argc, char *argv[]);
        int displayWindow();
};


#endif //MEDIAFILERENAMER_VIEW_H