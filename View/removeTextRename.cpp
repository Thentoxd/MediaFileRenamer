//
// Created by Alex Nicklin on 11/03/2026.
//

#include "view.h"

int RemoveTextRename::nextID = 0;

RemoveTextRename::RemoveTextRename(ModelInterface* param_model, QGroupBox * param_removeTextQGroupBox, mediaFileRenamerMainView* param_mainView, QSpinBox* param_addTextPositionSpimBox, QSpinBox* param_removeTextCountSpimBox) {
    SPDLOG_INFO("RemoveTextRename::~RemoveTextRename");
    id = ++nextID;
    p_model = param_model;
    p_removeTextQGroupBox = param_removeTextQGroupBox;
    p_mainView = param_mainView;
    p_removeTextPositionSpinBox = param_addTextPositionSpimBox;
    p_removeTextCountSpimBox = param_removeTextCountSpimBox;
}


RemoveTextRename::~RemoveTextRename() {
    SPDLOG_INFO("RemoveTextRename::~RemoveTextRename");
    nextID--;
}


int RemoveTextRename::getID() {
    SPDLOG_INFO("RemoveTextRename::getID");
    return id;
}


void RemoveTextRename::groupBoxToggled(bool state) {
    SPDLOG_DEBUG("RemoveTextRename::groupBoxToggled: {}", state);
    p_model -> setRemoveTextState(id, state);
    p_mainView -> onSelectedRowsChange();
}


void RemoveTextRename::updateTextToRemoveCount(int newValue) {
SPDLOG_DEBUG("RemoveTextRename::updateTextToRemoveCount: {}", newValue);
    p_model -> setRemoveTextCount(id, newValue);
    p_mainView -> onSelectedRowsChange();
}


void RemoveTextRename::updatePositionValue(int newValue) {
    SPDLOG_DEBUG("AddTextRename::updatePositionValue: {}", newValue);
    p_model -> setAddTextPosition(id, newValue);
    p_mainView -> onSelectedRowsChange();
}

// void setRemoveTextState(int instanceNumber, bool state) override;
// void setRemoveTextPositiom(int instanceNumber, int newValue) override;
// void setRemoveTextCount(int instanceNumber, int newValue) override;



void RemoveTextRename::connectSlots() {
    connect(p_removeTextQGroupBox, &QGroupBox::toggled, this, &RemoveTextRename::groupBoxToggled);
    connect(p_removeTextPositionSpinBox, &QSpinBox::valueChanged, this, &RemoveTextRename::updatePositionValue);
    connect(p_removeTextCountSpimBox, &QSpinBox::valueChanged, this, &RemoveTextRename::updateTextToRemoveCount);
}



void RemoveTextRename::disconnectSlots() {
    disconnect(p_removeTextQGroupBox, &QGroupBox::toggled, this, &RemoveTextRename::groupBoxToggled);
    disconnect(p_removeTextPositionSpinBox, &QSpinBox::valueChanged, this, &RemoveTextRename::updatePositionValue);
    disconnect(p_removeTextCountSpimBox, &QSpinBox::valueChanged, this, &RemoveTextRename::updateTextToRemoveCount);
}
