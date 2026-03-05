//
// Created by Surface on 05/03/2026.
//

#ifndef MEDIAFILERENAMER_NUMBERINGRENAME_H
#define MEDIAFILERENAMER_NUMBERINGRENAME_H

#include <QSpinBox>

#include "view.h"

class NumberingRename: public QObject {
protected:
    static int nextID;
private:
    int id;
    ModelInterface* p_model;
    mediaFileRenamerMainView* p_mainView;
    QGroupBox * p_dateQGroupBox;
    QSpinBox* p_spinBox1;
    QSpinBox* p_spinBox2;
public:
    NumberingRename(ModelInterface* param_model, QGroupBox * param_QGroupBox, mediaFileRenamerMainView* param_mainView, QSpinBox* param_spinBox1, QSpinBox* param_spinBox2);

    void connectSlots();
    void disconnectSlots();
    int getID();

    // Slots
    void updateStartingValue(int newValue);
    void updateSeperatorValue(int newValue);
    void groupBoxToggled(bool state);

};


#endif //MEDIAFILERENAMER_NUMBERINGRENAME_H