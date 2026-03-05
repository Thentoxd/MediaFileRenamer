//
// Created by Alex Nicklin on 03/03/2026.
//

#ifndef MEDIAFILERENAMER_SEPARATOR_H
#define MEDIAFILERENAMER_SEPARATOR_H




#include "view.h"

class separator: public QObject {
protected:
    static int nextID;
private:
    int id;
    ModelInterface * p_model;
    QLineEdit * p_lineEdit;
    mediaFileRenamerMainView * p_mainView;
    QGroupBox * p_QGroupBox;
public:
    separator(ModelInterface * param_model, QLineEdit * param_seperatorLineEdit, QGroupBox * param_QGroupBox, mediaFileRenamerMainView * param_mainView);
    void connectSlots();
    void disconnectSlots();
    int getID();

    // Slots
    void separatorToggled(bool state);
    void setSeperator();
};


#endif //MEDIAFILERENAMER_SEPARATOR_H