//
// Created by Alex Nicklin on 05/03/2026.
//

#include "view.h"

int FilenameBodyRename::nextID = 0;

FilenameBodyRename::FilenameBodyRename(ModelInterface * param_model, mediaFileRenamerMainView * param_mainView, QGroupBox *param_filenameBodyGroupBox, QLineEdit * param_filenameBodyLineEdit) {
    id = ++nextID;
    p_model = param_model;
    p_mainView = param_mainView;

    p_filenameBodyGroupBox = param_filenameBodyGroupBox;
    p_filenameBodyLineEdit = param_filenameBodyLineEdit;
}


FilenameBodyRename::~FilenameBodyRename() {
    SPDLOG_INFO("FilenameBodyRename::~FilenameBodyRename");
    nextID--;
}


int FilenameBodyRename::getID() {
    return id;
}


void FilenameBodyRename::fileBodyToggled(bool state) {
    SPDLOG_INFO("FilenameBodyRename::fileBodyToggled");
    p_model -> setEngineTextBodyState(id, state);
    p_mainView -> onSelectedRowsChange();
}


void FilenameBodyRename::fileBodyTextChange() {
    SPDLOG_INFO("dFilenameBodyRename::fileBodyTextChange");
    QString filenameEnteredQstring = p_filenameBodyLineEdit -> text();
    string filenameEntered = filenameEnteredQstring.toStdString();
    SPDLOG_INFO("Extracted filename text: {}", filenameEntered);
    p_model -> setRenamingEngineTextbody(id, filenameEntered);
    p_mainView -> onSelectedRowsChange();
}


void FilenameBodyRename::connectSlots() {
    SPDLOG_INFO("FilenameBodyRename::connectSlots");
    // These are the slots for the Date renaming widget
    QObject::connect(p_filenameBodyGroupBox, &QGroupBox::toggled, this, &FilenameBodyRename::fileBodyToggled);
    QObject::connect(p_filenameBodyLineEdit, &QLineEdit::textChanged, this, &FilenameBodyRename::fileBodyTextChange);
}


void FilenameBodyRename::disconnectSlots() {
    SPDLOG_INFO("FilenameBodyRename::disconnectSlots");
    QObject::disconnect(p_filenameBodyGroupBox, &QGroupBox::toggled, this, &FilenameBodyRename::fileBodyToggled);
    QObject::disconnect(p_filenameBodyLineEdit, &QLineEdit::textChanged, this, &FilenameBodyRename::fileBodyTextChange);
}