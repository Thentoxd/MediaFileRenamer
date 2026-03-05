//
// Created by Surface on 05/03/2026.
//

#include "NumberingRename.h"
#include <QSpinBox>

int NumberingRename::nextID = 0;

NumberingRename::NumberingRename(ModelInterface* param_model, QGroupBox * param_dateQGroupBox, mediaFileRenamerMainView * param_mainView, QSpinBox * spinBox1, QSpinBox * spinBox2) {
    id = ++nextID;
    p_model = param_model;
    p_spinBox1 = spinBox1;
    p_spinBox2 = spinBox2;
    p_mainView = param_mainView;
    p_dateQGroupBox = param_dateQGroupBox;
}

int NumberingRename::getID() {
    return id;
}

void NumberingRename::updateStartingValue(int newValue) {
    SPDLOG_DEBUG("NumberingRename::updateStartingValue: {}", newValue);
}

void NumberingRename::updateSeperatorValue(int newValue) {
    SPDLOG_DEBUG("NumberingRename::updateSeperatorValue: {}", newValue);
}

void NumberingRename::connectSlots() {
    connect(p_dateQGroupBox, &QGroupBox::toggled, this, &NumberingRename::groupBoxToggled);
    connect(p_spinBox1, &QSpinBox::valueChanged, this, &NumberingRename::updateStartingValue);
    connect(p_spinBox2, &QSpinBox::valueChanged, this, &NumberingRename::updateStartingValue);
}

void NumberingRename::disconnectSlots() {
    disconnect(p_dateQGroupBox, &QGroupBox::toggled, this, &NumberingRename::groupBoxToggled);
    disconnect(p_spinBox1, &QSpinBox::valueChanged, this, &NumberingRename::updateStartingValue);
    disconnect(p_spinBox2, &QSpinBox::valueChanged, this, &NumberingRename::updateStartingValue);
}
