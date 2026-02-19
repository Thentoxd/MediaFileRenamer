//
// Created by Alex Nicklin on 19/02/2026.
//

#ifndef MEDIAFILERENAMER_CHAIN_EDITOR_H
#define MEDIAFILERENAMER_CHAIN_EDITOR_H

#include "ui_chain_editor.h"

class chain_editor : public QDialog, public Ui::Dialog {
    Q_OBJECT

public:
    chain_editor( QWidget * parent = 0);
};


#endif //MEDIAFILERENAMER_CHAIN_EDITOR_H