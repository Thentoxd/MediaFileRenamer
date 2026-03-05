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
    p_dateUseMetadataOriginalDateCheckBox = param_useMatadataDateTakenOrigCheckBox;
}

int dateRename::getID() {
    return id;
}


void dateRename::datePrefixGroupToggled(bool state) {
    SPDLOG_INFO("dateRename::datePrefixGroupToggled");
    p_model -> setEngineDateState(id, state);
    p_mainView -> onSelectedRowsChange();
}


void dateRename::setdateTryExtractButtonClicked(bool state) {
    SPDLOG_INFO("dateRename::setdateTryExtractButtonClicked");
    p_model -> setRenamingEngineDateUseOriginalDateTaken(id, state);
    p_mainView -> onSelectedRowsChange();
}


void dateRename::setYear() {
    SPDLOG_INFO("dateRename::setYear");
    QString yearEnteredQstring = p_dateYearLineEdit -> text();
    string yearEntered = yearEnteredQstring.toStdString();
    SPDLOG_INFO("Extracted year: {}", yearEntered);
    p_model -> setRenamingEngineDateSetYear(id, yearEntered);
    p_mainView -> onSelectedRowsChange();
}


void dateRename::setMonth() {
    SPDLOG_INFO("dateRename::setMonth");
    QString monthEnteredQstring = p_dateMonthLineEdit -> text();
    string monthEntered = monthEnteredQstring.toStdString();
    SPDLOG_INFO("Extracted month: {}", monthEntered);
    p_model -> setRenamingEngineDateSetMonth(id, monthEntered);
    p_mainView -> onSelectedRowsChange();
}


void dateRename::setDay() {
    SPDLOG_INFO("dateRename::setDay");
    QString dayEnteredQstring = p_dateDayLineEdit -> text();
    string dayEntered = dayEnteredQstring.toStdString();
    SPDLOG_INFO("Extracted month: {}", dayEntered);
    p_model -> setRenamingEngineDateSetMonth(id, dayEntered);
    p_mainView -> onSelectedRowsChange();
}


void dateRename::tryUseMetadata(bool state) {
    SPDLOG_INFO("dateRename::tryUseMetadata");
    p_model -> setRenamingEngineDateUseOriginalDateTaken(id, state);
    p_mainView -> onSelectedRowsChange();
}


void dateRename::connectSlots() {
    SPDLOG_INFO("dateRename::connectSlots");
    // These are the slots for the Date renaming widget
    QObject::connect(p_dateQGroupBox, &QGroupBox::toggled, this, &dateRename::datePrefixGroupToggled);
    QObject::connect(p_dateTryExtractCheckBox, &QCheckBox::checkStateChanged, this, &dateRename::setdateTryExtractButtonClicked);
    QObject::connect(p_dateYearLineEdit, &QLineEdit::textChanged, this, &dateRename::setYear);
    QObject::connect(p_dateMonthLineEdit, &QLineEdit::textChanged, this, &dateRename::setMonth);
    QObject::connect(p_dateDayLineEdit, &QLineEdit::textChanged, this, &dateRename::setDay);
    QObject::connect(p_dateUseMetadataOriginalDateCheckBox, &QCheckBox::checkStateChanged, this, &dateRename::tryUseMetadata);
}


void dateRename::disconnectSlots() {
    SPDLOG_INFO("dateRename::disconnectSlots");
    QObject::disconnect(p_dateQGroupBox, &QGroupBox::toggled, this, &dateRename::datePrefixGroupToggled);
    QObject::disconnect(p_dateTryExtractCheckBox, &QCheckBox::checkStateChanged, this, &dateRename::setdateTryExtractButtonClicked);
    QObject::disconnect(p_dateYearLineEdit, &QLineEdit::textChanged, this, &dateRename::setYear);
    QObject::disconnect(p_dateMonthLineEdit, &QLineEdit::textChanged, this, &dateRename::setMonth);
    QObject::disconnect(p_dateDayLineEdit, &QLineEdit::textChanged, this, &dateRename::setDay);
    QObject::disconnect(p_dateUseMetadataOriginalDateCheckBox, &QCheckBox::checkStateChanged, this, &dateRename::tryUseMetadata);

}

