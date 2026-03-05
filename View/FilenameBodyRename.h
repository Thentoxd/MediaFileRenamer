//
// Created by Alex Nicklin on 05/03/2026.
//

#ifndef MEDIAFILERENAMER_FILENAMEBODYRENAME_H
#define MEDIAFILERENAMER_FILENAMEBODYRENAME_H

#include "view.h"

class FilenameBodyRename: public QObject {
protected:
    static int nextID;
private:
    int id;
    ModelInterface * p_model;
    mediaFileRenamerMainView * p_mainView;

    QGroupBox * p_filenameBodyGroupBox;
    QLineEdit * p_filenameBodyLineEdit;

public:
    FilenameBodyRename(ModelInterface * param_model, mediaFileRenamerMainView * param_mainView, QGroupBox *param_filenameBodyGroupBox, QLineEdit * param_filenameBodyLineEdit);
    void connectSlots();
    void disconnectSlots();
    int getID();

    // Slots
    void fileBodyToggled(bool state);
    void fileBodyTextChange();
};

#endif //MEDIAFILERENAMER_FILENAMEBODYRENAME_H