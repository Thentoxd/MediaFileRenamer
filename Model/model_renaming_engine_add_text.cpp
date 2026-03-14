//
// Created by Surface on 13/03/2026.
//

#include "model_renaming_engine_add_text.h"

ModelRenamingEngineAddText::ModelRenamingEngineAddText() {

}

ModelRenamingEngineAddText::~ModelRenamingEngineAddText() {

}

void ModelRenamingEngineAddText::init(int mode) {

}

void ModelRenamingEngineAddText::clear() {

}

void ModelRenamingEngineAddText::setTextToAdd(string textToAdd) {
    this->textToAdd = textToAdd;
}

void ModelRenamingEngineAddText::setStartingPosition(int startingPosition) {
    this->startingPosition = startingPosition;
}

pair<string, string> ModelRenamingEngineAddText::execute(pair<string, string> input_parameter) {
    SPDLOG_DEBUG("ModelRenamingEngineAddText::execute");
    pair<string, string> return_value;

    return_value.first = input_parameter.first + textToAdd;
    return_value.second = input_parameter.second;

    return return_value;
}


