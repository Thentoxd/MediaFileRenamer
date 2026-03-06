//
// Created by Alex Nicklin on 19/02/2026.
//

#include "chain_editor.h"

#include "spdlog/spdlog.h"

chain_editor::chain_editor( QWidget * parent) : QDialog(parent) {

    setupUi(this);
    connect(cancelButton, &QPushButton::clicked, this, &chain_editor::onCancelClick);
    connect(okButton, &QPushButton::clicked, this, &chain_editor::onOkClick);

    // perform additional setup here ...
}

void chain_editor::reloadUI() {

}

void chain_editor::onOkClick() {
    SPDLOG_INFO("chain_editor::onOkClick");
    close();
}

void chain_editor::onCancelClick() {
    // only SPDLOG ERROR is producing an output???
    // no - only DEBUG doesn't produce an output
    SPDLOG_INFO("chain_editor::onCancelClick");
    close();
}
