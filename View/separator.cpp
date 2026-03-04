//
// Created by Alex Nicklin on 03/03/2026.
//

#include "separator.h"

int separator::nextID = 0;

separator::separator(ModelInterface * param_model, QLineEdit * param_seperatorLineEdit, QGroupBox * param_QGroupBox, mediaFileRenamerMainView * param_mainView) {
    id = ++nextID;
    p_model = param_model;
    p_lineEdit = param_seperatorLineEdit;
    p_mainView = param_mainView;
    p_QGroupBox = param_QGroupBox;
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


void separator::setSeperator() {
    SPDLOG_INFO("separator::setSeperator");
    QString separator = p_lineEdit -> text();
    string seperator = separator.toStdString();
    SPDLOG_INFO("String entered: {}", seperator);
    p_model -> setSeperator(id, seperator);
    p_mainView -> onSelectedRowsChange();
}


void separator::connectSlots() {
    // These are the slots for the Seperator renaming widget
    QObject::QObject::connect(p_QGroupBox, &QGroupBox::toggled, this, &separator::separatorToggled);
    QObject::connect(p_lineEdit, &QLineEdit::textChanged, this, &separator::setSeperator);
}