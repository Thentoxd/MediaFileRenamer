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
    counter = 1;
    padding = 1;
    SPDLOG_DEBUG("Set counter and paddingto 1");
}

void ModelRenamingEngineCounter::clear() {
    SPDLOG_DEBUG("ModelRenamingEngineCounter::clear");
    counter = counterStart;
    padding = 1;
    SPDLOG_DEBUG("Set counter and paddingto 1");
}

pair<string, string> ModelRenamingEngineCounter::execute(pair<string, string> input_parameter) {
    SPDLOG_DEBUG("ModelRenamingEngineCounter::execute");

    pair<string, string> return_value;

    return_value.first = std::to_string(counter);
    return_value.second = input_parameter.second;

    counter++;

    return return_value;
}

void ModelRenamingEngineCounter::setCounter(int value) {
    SPDLOG_DEBUG("ModelRenamingEngineCounter::setCounter");
    SPDLOG_DEBUG("Setting the numbering counter to {}", value);
    counter = value;
    counterStart = value;
}

void ModelRenamingEngineCounter::setPadding(int value) {
    SPDLOG_DEBUG("ModelRenamingEngineCounter::setPadding");
    SPDLOG_DEBUG("Setting the padding counter to {}", value);
    padding = value;
}