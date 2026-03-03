//
// Created by Alex Nicklin on 22/10/2025.
//

#ifndef MEDIAFILERENAMER_VIEW_H
#define MEDIAFILERENAMER_VIEW_H

#include <QApplication>
#include <QMainWindow>

#include "ui_media_file_renamer.h"
#include "../model_interface.h"
#include "../Model/model_configfile.h"
#include "../Model/model_remaming_queue.h"
#include "../Model/model_renaming_engine_counter.h"
#include "../Model/model_renaming_engine_textbody.h"



class mediaFileRenamerMainView: public QMainWindow, public Ui::MediaFileRenamer {
    QApplication * p_QApplication;

    private:
    ModelInterface * p_model;
    bool loadPreviewsFlag = false;
    int columnOffset = 0;

    QVector<QWidget*> uiRenamingRootObjects;

    vector<EngineTypes> currentRenamingChain;

    void updateTable();
    void setYearMonthDayButtonsEnabled(bool newValue);

    public:
        mediaFileRenamerMainView(ModelInterface * p_model);
        void create_window();
        void reload_window();
        int displayWindow();

        void updateFolderComboBox();
        void selectFolderComboBox(int index);
        void onSelectedRowsChange();
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

        void seperatorAEntered();
        void seperatorBEntered();
};


#endif //MEDIAFILERENAMER_VIEW_H