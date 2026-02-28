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

pair<string, string> ModelRenamingEngineSeperator::execute(pair<string, string> input_parameter) {
    SPDLOG_DEBUG("ModelRenamingEngineSeperator::execute");
    assert(0);

    pair<string, string> return_value;

    return_value.first = textbody;
    return_value.second = input_parameter.second;

    return return_value;
}