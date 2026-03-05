//
// Created by Alex Nicklin on 28/02/2026.
//

#include "model_renaming_engine_seperator.h"

ModelRenamingEngineSeperator::ModelRenamingEngineSeperator() {
    SPDLOG_DEBUG("ModelRenamingEngineSeperator::ModelRenamingEngineSeperator");
}

ModelRenamingEngineSeperator::~ModelRenamingEngineSeperator() {
    SPDLOG_DEBUG("ModelRenamingEngineSeperator::~ModelRenamingEngineSeperator");
}

void ModelRenamingEngineSeperator::clear() {
    SPDLOG_DEBUG("ModelRenamingEngineSeperator::clear()");
}

void ModelRenamingEngineSeperator::init(int mode) {
    SPDLOG_DEBUG("ModelRenamingEngineSeperator::init");
}


void ModelRenamingEngineSeperator::setSeperator(string newValue) {
    SPDLOG_DEBUG("ModelRenamingEngineSeperator::setSeperator()");
    textbody = newValue;
}


pair<string, string> ModelRenamingEngineSeperator::execute(pair<string, string> input_parameter) {
    SPDLOG_DEBUG("ModelRenamingEngineSeperator::execute");

    pair<string, string> return_value;

    return_value.first = textbody;
    return_value.second = input_parameter.second;

    return return_value;
}