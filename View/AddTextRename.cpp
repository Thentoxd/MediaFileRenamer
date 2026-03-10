//
// Created by Alex Nicklin on 10/03/2026.
//

#include "view.h"

int AddTextRename::nextID = 0;

AddTextRename::AddTextRename(ModelInterface* param_model, QGroupBox * param_addtextQGroupBox, mediaFileRenamerMainView* param_mainView, QLineEdit * param_addTextLineEdit, QSpinBox* param_addTextPositionSpimBox) {
    SPDLOG_INFO("AddTextRename::~AddTextRename");
    id = ++nextID;
    p_model = param_model;
    p_addtextQGroupBox = param_addtextQGroupBox;
    p_addTextLineEdit = param_addTextLineEdit;
    p_addTextPositionSpinBox = param_addTextPositionSpimBox;
    p_mainView = param_mainView;

}


AddTextRename::~AddTextRename() {
    SPDLOG_INFO("AddTextRename::~AddTextRename");
    nextID--;
}


int AddTextRename::getID() {
    SPDLOG_INFO("AddTextRename::getID");
    return id;
}


void AddTextRename::updateTextToAdd() {
    QString addTextEnteredQstring = p_addTextLineEdit -> text();
    string addTextEntered = addTextEnteredQstring.toStdString();

    SPDLOG_DEBUG("AddTextRename::updateTextToAdd: {}", addTextEntered);
    p_model -> setAddTextText(id, addTextEntered);
    p_mainView -> onSelectedRowsChange();
}


void AddTextRename::updatePositionValue(int newValue) {
    SPDLOG_DEBUG("AddTextRename::updatePositionValue: {}", newValue);
    p_model -> setAddTextPosition(id, newValue);
    p_mainView -> onSelectedRowsChange();
}


void AddTextRename::groupBoxToggled(bool state) {
    SPDLOG_DEBUG("AddTextRename::groupBoxToggled: {}", state);
    p_model -> setAddTextState(id, state);
    p_mainView -> onSelectedRowsChange();
}


void AddTextRename::connectSlots() {
    connect(p_addtextQGroupBox, &QGroupBox::toggled, this, &AddTextRename::groupBoxToggled);
    connect(p_addTextPositionSpinBox, &QSpinBox::valueChanged, this, &AddTextRename::updatePositionValue);
    connect(p_addTextLineEdit, &QLineEdit::textChanged, this, &AddTextRename::updateTextToAdd);
}


void AddTextRename::disconnectSlots() {
    disconnect(p_addtextQGroupBox, &QGroupBox::toggled, this, &AddTextRename::groupBoxToggled);
    disconnect(p_addTextPositionSpinBox, &QSpinBox::valueChanged, this, &AddTextRename::updatePositionValue);
    disconnect(p_addTextLineEdit, &QLineEdit::textChanged, this, &AddTextRename::updateTextToAdd);
}
