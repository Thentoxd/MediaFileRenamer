//
// Created by Alex Nicklin on 22/10/2025.
//

#ifndef MEDIAFILERENAMER_VIEW_H
#define MEDIAFILERENAMER_VIEW_H

#include <QApplication>
#include <QMainWindow>
#include <QSpinBox>

#include "ui_media_file_renamer.h"
#include "../model_interface.h"
#include "../Model/model_configfile.h"
#include "../Model/model_remaming_queue.h"
#include "../Model/model_renaming_engine_counter.h"
#include "../Model/model_renaming_engine_textbody.h"


class dateRename;
class separator;
class FilenameBodyRename;
class NumberingRename;
class AddTextRename;
class RemoveTextRename;

class mediaFileRenamerMainView: public QMainWindow, public Ui::MediaFileRenamer {
    QApplication * p_QApplication;

private:
    ModelInterface * p_model;
    bool loadPreviewsFlag = false;
    int columnOffset = 0;

    QVector<QWidget*> uiRenamingRootObjects;

    vector<EngineTypes> currentRenamingChain;

    vector<dateRename *> dateRenameVector;
    vector<separator *> seperatorRenameVector;
    vector<FilenameBodyRename *> filenameBodyRenameVector;
    vector<NumberingRename *> numberingRenameVector;
    vector<AddTextRename *> addTextVector;
    vector<RemoveTextRename *> removeTextVector;

    vector<QGroupBox *> qGroupBoxVector;

    QSpacerItem *horizontalSpacer;

    void updateTable();
    void setYearMonthDayButtonsEnabled(bool newValue);
    void createChainWidgets();

public:
        mediaFileRenamerMainView(ModelInterface * p_model);
        void create_window();
        void reload_window();
        int displayWindow();

        void updateFolderComboBox();
        void selectFolderComboBox(int index);
        void onSelectedRowsChange();
        void updateUIChain(vector<EngineTypes> param_newChain);

        vector<int> getSelectedUniqueRows();

public slots:
        void selectFolderButtonClicked();
        // void onUpdateSelectedButton();
        void setUseDateTakenButtonClicked(Qt::CheckState newState);
        void setDateTakenOriginalButtonClicked(Qt::CheckState newState);
        void setFilenameBody(const QString &text);

        void setCounterStart(int newValue);
        void setCounterPadding(int newValue);
        void renameFilesButtonClicked();
        void resetToDefaultButtonClicked();

        void setDateFormat(const QString &text);
        void setDateTryExtractDateButtonClicked(Qt::CheckState newState);
        void setYear(const QString &text);
        void setMonth(const QString &text);
        void setDay(const QString &text);

        void datePrefixGroupToggled(bool state);
        void firstSeperatorGroupToggled(bool state);
        void fileNameBodyGroupToggled(bool state);
        void secondSeperatorGroupToggled(bool state);
        void numberingSuffixGroupToggled(bool state);

        void menuExit(bool newValue);
        void menuChainEditor(bool newValue);

        void loadPreviews(Qt::CheckState state);
        void redoTableColumnNames();

        //void seperatorAEntered();
        //void seperatorBEntered();

        // void setmetaDataCheckBoxToggled(bool state);
        void metadataParseFilenameForDateCheckBoxToggled(bool state);
        void metadataUseFixedDate(bool newValue);
        void metadataFetchDateAndCallInterface();
        void metadataYearLineEditChange();
        void metadataMonthLineEditChange();
        void metadataDayLineEditChange();
};

class dateRename: public QObject {
protected:
    static int nextID;
private:
    int id;
    ModelInterface * p_model;
    QLineEdit * p_dateYearLineEdit;
    QLineEdit * p_dateMonthLineEdit;
    QLineEdit * p_dateDayLineEdit;
    mediaFileRenamerMainView * p_mainView;
    QGroupBox * p_dateQGroupBox;
    QCheckBox * p_dateTryExtractCheckBox;
    QCheckBox * p_dateUseMetadataOriginalDateCheckBox;
    void    extractEnteredDateAndSendToModel();
public:
    dateRename(ModelInterface * param_model, QGroupBox * param_dateQGroupBox, QCheckBox * param_dateTryExtractCheckBox,
        QLineEdit * param_dateYearLineEdit, QLineEdit * param_dateMonthLineEdit,
        QLineEdit * param_dateDayLineEdit, QCheckBox * param_useMatadataDateTakenOrigCheckBox,
        mediaFileRenamerMainView * param_mainView);
    ~dateRename();
    void connectSlots();
    void disconnectSlots();
    int getID();

    // Slots
    void datePrefixGroupToggled(bool state);
    void setdateTryExtractButtonClicked(bool state);
    void setYear();
    void setMonth();
    void setDay();
    void tryUseMetadata(bool state);
};


class separator: public QObject {
protected:
    static int nextID;
private:
    int id;
    ModelInterface * p_model;
    QLineEdit * p_lineEdit;
    mediaFileRenamerMainView * p_mainView;
    QGroupBox * p_QGroupBox;
public:
    separator(ModelInterface * param_model, QLineEdit * param_seperatorLineEdit, QGroupBox * param_QGroupBox, mediaFileRenamerMainView * param_mainView);
    ~separator();
    void connectSlots();
    void disconnectSlots();
    int getID();

    // Slots
    void separatorToggled(bool state);
    void setSeperator();
};


class FilenameBodyRename: public QObject {
protected:
    static int nextID;
private:
    int id;
    ModelInterface * p_model;
    mediaFileRenamerMainView * p_mainView;

    QGroupBox * p_filenameBodyGroupBox;
    QLineEdit * p_filenameBodyLineEdit;

public:
    FilenameBodyRename(ModelInterface * param_model, mediaFileRenamerMainView * param_mainView, QGroupBox *param_filenameBodyGroupBox, QLineEdit * param_filenameBodyLineEdit);
    ~FilenameBodyRename();
    void connectSlots();
    void disconnectSlots();
    int getID();

    // Slots
    void fileBodyToggled(bool state);
    void fileBodyTextChange();
};


class NumberingRename: public QObject {
protected:
    static int nextID;
private:
    int id;
    ModelInterface* p_model;
    mediaFileRenamerMainView* p_mainView;
    QGroupBox * p_dateQGroupBox;
    QSpinBox* p_spinBox1;
    QSpinBox* p_spinBox2;
public:
    NumberingRename(ModelInterface* param_model, QGroupBox * param_QGroupBox, mediaFileRenamerMainView* param_mainView, QSpinBox* param_spinBox1, QSpinBox* param_spinBox2);
    ~NumberingRename();

    void connectSlots();
    void disconnectSlots();
    int getID();

    // Slots
    void updateStartingValue(int newValue);
    void updatePaddingValue(int newValue);
    void groupBoxToggled(bool state);
};


class AddTextRename: public QObject {
protected:
    static int nextID;
private:
    int id;
    ModelInterface* p_model;
    mediaFileRenamerMainView* p_mainView;
    QGroupBox * p_addtextQGroupBox;
    QLineEdit * p_addTextLineEdit;
    QSpinBox* p_addTextPositionSpinBox;

public:
    AddTextRename(ModelInterface* param_model, QGroupBox * param_addtextQGroupBox, mediaFileRenamerMainView* param_mainView, QLineEdit * param_addTextLineEdit, QSpinBox* param_addTextPositionSpimBox);

    ~AddTextRename();

    void connectSlots();
    void disconnectSlots();
    int getID();

    // Slots
    void updateTextToAdd();
    void updatePositionValue(int newValue);
    void groupBoxToggled(bool state);
};


class RemoveTextRename: public QObject {
protected:
    static int nextID;
private:
    int id;
    ModelInterface* p_model;
    mediaFileRenamerMainView* p_mainView;
    QGroupBox * p_removeTextQGroupBox;
    QSpinBox* p_removeTextPositionSpinBox;
    QSpinBox* p_removeTextCountSpimBox;

public:
    RemoveTextRename(ModelInterface* param_model, QGroupBox * param_removeTextQGroupBox, mediaFileRenamerMainView* param_mainView, QSpinBox* param_addTextPositionSpimBox, QSpinBox* param_removeTextCountSpimBox);

    ~RemoveTextRename();

    void connectSlots();
    void disconnectSlots();
    int getID();

    // Slots
    void groupBoxToggled(bool state);
    void updateTextToRemoveCount(int newValue);
    void updatePositionValue(int newValue);

};

#endif //MEDIAFILERENAMER_VIEW_H