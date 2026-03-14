//
// Created by Alex Nicklin on 19/02/2026.
//

#include "chain_editor.h"
#include <fstream>

#include "../main.h"
#include "spdlog/spdlog.h"

chain_editor::chain_editor( QWidget * parent, mediaFileRenamerMainView * param_mediaFileRenamerMainView) : QDialog(parent) {

    setupUi(this);
    connect(cancelButton, &QPushButton::clicked, this, &chain_editor::onCancelClick);
    connect(okButton, &QPushButton::clicked, this, &chain_editor::onOkClick);
    connect(resetButton, &QPushButton::clicked, this, &chain_editor::onResetClick);

    // perform additional setup here ...
    p_mediaFileRenamerMainView = param_mediaFileRenamerMainView;
}

void chain_editor::onOkClick() {
    SPDLOG_INFO("chain_editor::onOkClick");
    std::vector<QComboBox*> chain = {chain1, chain2, chain3, chain4, chain5};
    std::vector<EngineTypes> parsed_renaming_engine;

    for (int i = 0; i < 5; i++) {
        std::string value = chain[i]->currentText().toStdString();

        if (value == "Date") {
            parsed_renaming_engine.push_back(DateEngine);
        } else if (value == "Seperator") {
            parsed_renaming_engine.push_back(SeperatorEngine);
        } else if (value == "Filename") {
            parsed_renaming_engine.push_back(FilenameBodyEngine);
        } else if (value == "Numbering") {
            parsed_renaming_engine.push_back(NumberingEngine);
        }
    }

    p_mediaFileRenamerMainView -> updateUIChain(parsed_renaming_engine);
    close();
}

void chain_editor::onCancelClick() {
    SPDLOG_INFO("chain_editor::onCancelClick");
    close();
}

void chain_editor::onResetClick() {
    SPDLOG_INFO("chain_editor::onResetClick");
}