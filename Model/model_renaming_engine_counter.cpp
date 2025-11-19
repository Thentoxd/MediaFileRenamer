//
// Created by Alex Nicklin on 18/11/2025.
//

#include "model_renaming_engine_counter.h"

#include "spdlog/spdlog.h"

ModelRenamingEngineCounter::ModelRenamingEngineCounter() {
    SPDLOG_DEBUG("ModelRenamingEngineCounter::ModelRenamingEngineCounter");
}

ModelRenamingEngineCounter::~ModelRenamingEngineCounter() {
    SPDLOG_DEBUG("ModelRenamingEngineCounter::~ModelRenamingEngineCounter");
}

void ModelRenamingEngineCounter::init(int mode) {
    SPDLOG_DEBUG("ModelRenamingEngineCounter::init");
}

void ModelRenamingEngineCounter::clear() {
    SPDLOG_DEBUG("ModelRenamingEngineCounter::clear");
}

pair<string, string> ModelRenamingEngineCounter::execute(pair<string, string> input_parameter) {
    SPDLOG_DEBUG("ModelRenamingEngineCounter::execute");
    return input_parameter;
}

void ModelRenamingEngineCounter::setCounter(int value) {
    SPDLOG_DEBUG("ModelRenamingEngineCounter::setCounter");
    SPDLOG_DEBUG("Setting the numbering counter to {}", value);
    counter = value;
}

void ModelRenamingEngineCounter::setPadding(int value) {
    SPDLOG_DEBUG("ModelRenamingEngineCounter::setPadding");
    SPDLOG_DEBUG("Setting the padding counter to {}", value);
    padding = value;
}