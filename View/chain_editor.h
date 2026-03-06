//
// Created by Alex Nicklin on 19/02/2026.
//

#ifndef MEDIAFILERENAMER_CHAIN_EDITOR_H
#define MEDIAFILERENAMER_CHAIN_EDITOR_H

#include "ui_chain_editor.h"
#include "view.h"

class chain_editor : public QDialog, public Ui::Dialog {
    Q_OBJECT

private:
    mediaFileRenamerMainView * p_mediaFileRenamerMainView;

public:
    chain_editor( QWidget * parent, mediaFileRenamerMainView * param_mediaFileRenamerMainView);

public slots:
    void onOkClick();
    void onCancelClick();
    void onResetClick();
};


#endif //MEDIAFILERENAMER_CHAIN_EDITOR_H