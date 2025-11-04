//
// Created by Alex Nicklin on 22/10/2025.
//

#ifndef MEDIAFILERENAMER_VIEW_H
#define MEDIAFILERENAMER_VIEW_H

#include <QApplication>

#include "ui_media_file_renamer.h"
#include "../model_interface.h"

class mediaFileRenamerMainView: public QMainWindow, public Ui::MediaFileRenamer {
    QApplication * p_QApplication;

    private:
    ModelInterface * p_model;

    public:
        mediaFileRenamerMainView(ModelInterface * p_model);
        void create_window();
        void setTextInCell(int row, int column, QString text);
        void populateTableView(QString currentWorkingDirectory);
        int displayWindow();

    public slots:
        void selectFolderButtonClicked();
};


#endif //MEDIAFILERENAMER_VIEW_H