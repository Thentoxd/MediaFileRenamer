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
    ModelRemamingQueue * p_ModelRemamingQueue;
    ModelRenamingEngineDate * p_ModelRenamingEngineDate;
    ModelRenamingEngineTextBody * p_ModelRenamingEngineTextBody;
    ModelRenamingEngineCounter * p_ModelRenamingEngineCounter;

    void updateTable();

    public:
        mediaFileRenamerMainView(ModelInterface * p_model, ModelConfigfile * parameter_ModelConfigfile, ModelRemamingQueue * parameter_ModelRemamingQueue, ModelRenamingEngineDate * parameter_ModelRenamingEngineDate, ModelRenamingEngineTextBody * parameter_ModelRenamingEngineTextBody, ModelRenamingEngineCounter * parameter_ModelRenamingEngineCounter);
        void create_window();
        int displayWindow();

        void updateFolderComboBox();
        void selectFolderComboBox(int index);
        void onSelectedRowsChange();

    public slots:
        void selectFolderButtonClicked();
        void onUpdateSelectedButton();
        void setUseDateTakenButtonClicked();
        void setDateTakenOriginalButtonClicked();
};


#endif //MEDIAFILERENAMER_VIEW_H