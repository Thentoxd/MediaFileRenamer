//
// Created by Alex Nicklin on 03/03/2026.
//

#include "separator.h"

int separator::nextID = 0;

separator::separator(ModelInterface * param_model, QLineEdit * param_seperatorLineEdit, mediaFileRenamerMainView * param_mainView) {
    id = ++nextID;
    p_model = param_model;
    p_lineEdit = param_seperatorLineEdit;
    p_mainView = param_mainView;
}

int separator::getID() {
    return id;
}


void separator::separatorToggled(bool state) {
    SPDLOG_INFO("separator::separatorToggled");
    SPDLOG_INFO("Separator {} toggled", id);

    if (state == false) {
        p_model -> setSeperator(id, "");
    }
    else {
        QString separator = p_lineEdit -> text();
        string seperator = separator.toStdString();
        SPDLOG_INFO("String entered: {}", seperator);
        p_model -> setSeperator(id, seperator);
    }
    p_mainView -> onSelectedRowsChange();


    // p_model->setEngineDatePrefix(int instanceNumber, state);
    // onSelectedRowsChange();
}

void separator::connectSlots(QGroupBox * param_QGroupBox) {
    // These are the slots for the Date renaming widget
    QObject::connect(param_QGroupBox, &QGroupBox::toggled, this, &separator::separatorToggled);
    // connect(this -> use_DateTaken_checkBox, &QCheckBox::checkStateChanged, this, &mediaFileRenamerMainView::setUseDateTakenButtonClicked);
    // connect(this -> set_DateTaken_checkBox, &QCheckBox::checkStateChanged, this, &mediaFileRenamerMainView::setDateTakenOriginalButtonClicked);
    // connect(this -> attempt_findDate_checkBox, &QCheckBox::checkStateChanged, this, &mediaFileRenamerMainView::setDateTryExtractDateButtonClicked);
    // connect(this -> year_lineEdit, &QLineEdit::textChanged, this, &mediaFileRenamerMainView::setYear);
    // connect(this -> month_lineEdit, &QLineEdit::textChanged, this, &mediaFileRenamerMainView::setMonth);
    // connect(this -> day_lineEdit, &QLineEdit::textChanged, this, &mediaFileRenamerMainView::setDay);
}