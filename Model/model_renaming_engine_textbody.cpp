//
// Created by Alex Nicklin on 18/11/2025.
//

#include "model_renaming_engine_textbody.h"

#include "spdlog/spdlog.h"

ModelRenamingEngineTextBody::ModelRenamingEngineTextBody() {
    SPDLOG_DEBUG("ModelRenamingEngineTextBody::ModelRenamingEngineTextBody");
}

ModelRenamingEngineTextBody::~ModelRenamingEngineTextBody() {
    SPDLOG_DEBUG("~ModelRenamingEngineTextBody");
}

void ModelRenamingEngineTextBody::clear() {
    SPDLOG_DEBUG("ModelRenamingEngineTextBody::clear()");
}

void ModelRenamingEngineTextBody::init(int mode) {
    SPDLOG_DEBUG("ModelRenamingEngineTextBody::init");
}

pair<string, string> ModelRenamingEngineTextBody::execute(pair<string, string> input_parameter) {
    SPDLOG_DEBUG("ModelRenamingEngineTextBody::execute");
    return input_parameter;
}
