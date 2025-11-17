//
// Created by Alex Nicklin on 17/11/2025.
//

#include "model_renaming_engine_date.h"
#include "../main.h"

ModelRenamingEngineDate::ModelRenamingEngineDate() {
    SPDLOG_INFO("ModelRemamingQueue::ModelRemamingQueue");
}

pair<string, string> ModelRenamingEngineDate::execute(pair<string, string> input_parameter) {
    SPDLOG_INFO("ModelRemamingQueue::ModelRemamingQueue");
    return pair<string, string>(input_parameter.first, input_parameter.second);
}