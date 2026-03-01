//
// Created by Alex Nicklin on 01/03/2026.
//

#include <QObject>
#include <QGroupBox>

#include "dateRename.h"

int dateRename::nextID = 0;

dateRename::dateRename() {
    id = ++nextID;
}

int dateRename::getID() {
    return id;
}


void dateRename::datePrefixGroupToggled(bool state) {
    SPDLOG_INFO("dateRename::datePrefixGroupToggled");
    // p_model->setEngineDatePrefix(int instanceNumber, state);
    // onSelectedRowsChange();
}

void dateRename::connectSlots(mediaFileRenamerMainView * param_mediaFileRenamerMainView) {
    // These are the slots for the Date renaming widget
    QObject::connect(param_mediaFileRenamerMainView -> datePrefixGroup, &QGroupBox::toggled, this, &dateRename::datePrefixGroupToggled);
    // connect(this -> use_DateTaken_checkBox, &QCheckBox::checkStateChanged, this, &mediaFileRenamerMainView::setUseDateTakenButtonClicked);
    // connect(this -> set_DateTaken_checkBox, &QCheckBox::checkStateChanged, this, &mediaFileRenamerMainView::setDateTakenOriginalButtonClicked);
    // connect(this -> attempt_findDate_checkBox, &QCheckBox::checkStateChanged, this, &mediaFileRenamerMainView::setDateTryExtractDateButtonClicked);
    // connect(this -> year_lineEdit, &QLineEdit::textChanged, this, &mediaFileRenamerMainView::setYear);
    // connect(this -> month_lineEdit, &QLineEdit::textChanged, this, &mediaFileRenamerMainView::setMonth);
    // connect(this -> day_lineEdit, &QLineEdit::textChanged, this, &mediaFileRenamerMainView::setDay);
}

