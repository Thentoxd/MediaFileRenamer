//
// Created by Alex Nicklin on 01/03/2026.
//

#ifndef MEDIAFILERENAMER_DATERENAME_H
#define MEDIAFILERENAMER_DATERENAME_H

#include "view.h"

class dateRename: public QObject {
protected:
    static int nextID;
private:
    int id;
public:
    dateRename();
    void connectSlots(mediaFileRenamerMainView * param_mediaFileRenamerMainView);
    int getID();

    // Slots
    void datePrefixGroupToggled(bool state);
};


#endif //MEDIAFILERENAMER_DATERENAME_H