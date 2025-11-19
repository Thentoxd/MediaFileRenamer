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
    textbody = "";
}

void ModelRenamingEngineTextBody::init(int mode) {
    SPDLOG_DEBUG("ModelRenamingEngineTextBody::init");
}

void ModelRenamingEngineTextBody::setTextBody(string param_textbody) {
    SPDLOG_DEBUG("ModelRenamingEngineTextBody::setTextBody");
    SPDLOG_DEBUG("Setting text body in the model to {}", param_textbody);
    textbody = param_textbody;
}

pair<string, string> ModelRenamingEngineTextBody::execute(pair<string, string> input_parameter) {
    SPDLOG_DEBUG("ModelRenamingEngineTextBody::execute");

    pair<string, string> return_value;

    return_value.first = textbody;
    return_value.second = input_parameter.second;

    return return_value;
}
