//
// Created by Alex Nicklin on 17/11/2025.
//

#include "../main.h"

#include "model_remaming_queue.h"
#include "model_renaming_engine_textbody.h"
#include "model_renaming_engine_counter.h"

ModelRemamingQueue::ModelRemamingQueue() {
    SPDLOG_INFO("ModelRemamingQueue::ModelRemamingQueue");
}

ModelRemamingQueue::~ModelRemamingQueue() {
    SPDLOG_INFO("ModelRemamingQueue::~ModelRemamingQueue");

}

void ModelRemamingQueue::init(int mode, ModelRenamingEngineDate * p_ModelRenamingEngineDate, ModelRenamingEngineTextBody * p_ModelRenamingEngineTextBody, ModelRenamingEngineCounter * p_ModelRenamingEngineCounter) {
    SPDLOG_INFO("ModelRemamingQueue::init");

    renaming_engine.push_back(p_ModelRenamingEngineDate);
    renaming_engine.push_back(p_ModelRenamingEngineTextBody);
    renaming_engine.push_back(p_ModelRenamingEngineCounter);
}

void ModelRemamingQueue::clear() {
    SPDLOG_INFO("ModelRemamingQueue::clear");

}

pair<string, string> ModelRemamingQueue::executeQueue(pair<string, string> input_parameter) {
    SPDLOG_INFO("ModelRemamingQueue::executeQueue");
    for(ModelRenamingEngine * each_engine : renaming_engine) {
        each_engine -> execute(input_parameter);
    }
    return input_parameter;
}