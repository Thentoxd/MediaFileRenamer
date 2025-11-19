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

    void updateTable();

    public:
        mediaFileRenamerMainView(ModelInterface * p_model);
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
        void setFilenameBody(const QString &text);
        void renameFilesButtonClicked();
};


#endif //MEDIAFILERENAMER_VIEW_H