//
// Created by Alex Nicklin on 01/03/2026.
//

#include <QObject>
#include <QGroupBox>

#include "view.h"

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

dateRename::~dateRename() {
    SPDLOG_INFO("dateRename::~dateRename");
    nextID--;
}

int dateRename::getID() {
    return id;
}


void dateRename::datePrefixGroupToggled(bool state) {
    if (state == true) {
        SPDLOG_INFO("dateRename::datePrefixGroupToggled On");

    }
    else {
        SPDLOG_INFO("dateRename::datePrefixGroupToggled Off");
    }

    p_model -> setEngineDateState(id, state);
    p_mainView -> onSelectedRowsChange();
}


void dateRename::setdateTryExtractButtonClicked(bool state) {
    if (state == true) {
        SPDLOG_INFO("dateRename::setdateTryExtractButtonClicked On");
        p_dateYearLineEdit -> setEnabled(false);
        p_dateMonthLineEdit -> setEnabled(false);
        p_dateDayLineEdit -> setEnabled(false);
        p_dateUseMetadataOriginalDateCheckBox -> setChecked(false);
        p_model -> setRenamingEngineDateTryExtractDate(id, state);
    }
    else {
        SPDLOG_INFO("dateRename::setdateTryExtractButtonClicked Off");
        p_dateYearLineEdit -> setEnabled(true);
        p_dateMonthLineEdit -> setEnabled(true);
        p_dateDayLineEdit -> setEnabled(true);

        QString yearString = p_dateYearLineEdit -> text();
        string yearEntered = yearString.toStdString();

        QString monthString = p_dateMonthLineEdit -> text();
        string monthEntered = monthString.toStdString();

        QString dayString = p_dateDayLineEdit -> text();
        string dayEntered = dayString.toStdString();

        p_model -> setRenamingEngineDateSetYearMonthDay(id, yearEntered, monthEntered, dayEntered);
    }

    p_mainView -> onSelectedRowsChange();
}


void dateRename::extractEnteredDateAndSendToModel() {
    SPDLOG_INFO("dateRename::extractEnteredDateAndSendToModel");

    QString yearEnteredQstring = p_dateYearLineEdit -> text();
    string yearEntered = yearEnteredQstring.toStdString();

    QString monthString = p_dateMonthLineEdit -> text();
    string monthEntered = monthString.toStdString();

    QString dayString = p_dateDayLineEdit -> text();
    string dayEntered = dayString.toStdString();

    p_model -> setRenamingEngineDateSetYearMonthDay(id, yearEntered, monthEntered, dayEntered);
    p_mainView -> onSelectedRowsChange();
}


void dateRename::setYear() {
    SPDLOG_INFO("dateRename::setYear");
    this -> extractEnteredDateAndSendToModel();
}


void dateRename::setMonth() {
    SPDLOG_INFO("dateRename::setMonth");
    this -> extractEnteredDateAndSendToModel();
}


void dateRename::setDay() {
    this -> extractEnteredDateAndSendToModel();
}


void dateRename::tryUseMetadata(bool state) {
    SPDLOG_INFO("dateRename::tryUseMetadata");
    // p_dateTryExtractCheckBox -> setEnabled((false));
    p_dateTryExtractCheckBox -> setChecked(false);
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

