//
// Created by Alex Nicklin on 28/10/2025.
//

#ifndef MEDIAFILERENAMER_UI_H
#define MEDIAFILERENAMER_UI_H

#include "ui_media_file_renamer.h"

class mediaFileRenamerMainWindow : public QMainWindow, private Ui::MediaFileRenamer {
public:
    mediaFileRenamerMainWindow();
    int Exit();
};

#endif //MEDIAFILERENAMER_UI_H