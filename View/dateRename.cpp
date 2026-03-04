//
// Created by Alex Nicklin on 01/03/2026.
//

#include <QObject>
#include <QGroupBox>

#include "dateRename.h"

int dateRename::nextID = 0;

dateRename::dateRename(ModelInterface * param_model, QGroupBox * param_dateQGroupBox, QCheckBox * param_dateTryExtractCheckBox, QLineEdit * param_dateYearLineEdit,
        QLineEdit * param_dateMonthLineEdit, QLineEdit * param_dateDayLineEdit, QCheckBox * param_useMatadataDateTakenOrigCheckBox,
        mediaFileRenamerMainView * param_mainView) {
    id = ++nextID;
    p_model = param_model;
    p_dateQGroupBox = param_dateQGroupBox;
    p_dateTryExtractCheckBox = param_dateTryExtractCheckBox;
    p_dateYearLineEdit = param_dateYearLineEdit;
    p_dateMonthLineEdit = param_dateMonthLineEdit;
    p_dateDayLineEdit = param_dateDayLineEdit;
    p_mainView = param_mainView;
}

int dateRename::getID() {
    return id;
}


void dateRename::datePrefixGroupToggled(bool state) {
    SPDLOG_INFO("dateRename::datePrefixGroupToggled");
    p_model -> setEngineDatePrefix(id, state);
    p_mainView -> onSelectedRowsChange();
}


void dateRename::setdateTryExtractButtonClicked(bool state) {
    SPDLOG_INFO("dateRename::setdateTryExtractButtonClicked");
    p_model -> setRenamingEngineDateUseOriginalDateTaken(id, state);
    p_mainView -> onSelectedRowsChange();
}


void dateRename::connectSlots() {
    // These are the slots for the Date renaming widget
    QObject::connect(p_dateQGroupBox, &QGroupBox::toggled, this, &dateRename::datePrefixGroupToggled);
    QObject::connect(p_dateTryExtractCheckBox, &QCheckBox::checkStateChanged, this, &dateRename::setdateTryExtractButtonClicked);
    // connect(this -> set_DateTaken_checkBox, &QCheckBox::checkStateChanged, this, &mediaFileRenamerMainView::setDateTakenOriginalButtonClicked);
    // connect(this -> attempt_findDate_checkBox, &QCheckBox::checkStateChanged, this, &mediaFileRenamerMainView::setDateTryExtractDateButtonClicked);
    // connect(this -> year_lineEdit, &QLineEdit::textChanged, this, &mediaFileRenamerMainView::setYear);
    // connect(this -> month_lineEdit, &QLineEdit::textChanged, this, &mediaFileRenamerMainView::setMonth);
    // connect(this -> day_lineEdit, &QLineEdit::textChanged, this, &mediaFileRenamerMainView::setDay);
}

