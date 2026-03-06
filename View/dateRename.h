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
    ModelInterface * p_model;
    QLineEdit * p_dateYearLineEdit;
    QLineEdit * p_dateMonthLineEdit;
    QLineEdit * p_dateDayLineEdit;
    mediaFileRenamerMainView * p_mainView;
    QGroupBox * p_dateQGroupBox;
    QCheckBox * p_dateTryExtractCheckBox;
    QCheckBox * p_dateUseMetadataOriginalDateCheckBox;
    void    extractEnteredDateAndSendToModel();
public:
    dateRename(ModelInterface * param_model, QGroupBox * param_dateQGroupBox, QCheckBox * param_dateTryExtractCheckBox,
        QLineEdit * param_dateYearLineEdit, QLineEdit * param_dateMonthLineEdit,
        QLineEdit * param_dateDayLineEdit, QCheckBox * param_useMatadataDateTakenOrigCheckBox,
        mediaFileRenamerMainView * param_mainView);
    void connectSlots();
    void disconnectSlots();
    int getID();

    // Slots
    void datePrefixGroupToggled(bool state);
    void setdateTryExtractButtonClicked(bool state);
    void setYear();
    void setMonth();
    void setDay();
    void tryUseMetadata(bool state);
};


#endif //MEDIAFILERENAMER_DATERENAME_H