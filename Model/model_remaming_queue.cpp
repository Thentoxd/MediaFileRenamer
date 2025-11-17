//
// Created by Alex Nicklin on 17/11/2025.
//

#include "../main.h"

#include "model_remaming_queue.h"

ModelRemamingQueue::ModelRemamingQueue() {
    SPDLOG_INFO("ModelRemamingQueue::ModelRemamingQueue");
}

ModelRemamingQueue::~ModelRemamingQueue() {
    SPDLOG_INFO("ModelRemamingQueue::~ModelRemamingQueue");

}

void ModelRemamingQueue::init(int mode) {
    SPDLOG_INFO("ModelRemamingQueue::init");
    auto executeQueueEngine = new ModelRenamingEngineDate();
    renaming_engine.push_back(executeQueueEngine);
}

void ModelRemamingQueue::clear() {
    SPDLOG_INFO("ModelRemamingQueue::clear");

}

void ModelRemamingQueue::executeQueue(pair<string, string> input_parameter) {
    SPDLOG_INFO("ModelRemamingQueue::executeQueue");
    for(ModelRenamingEngineDate * each_engine : renaming_engine)
        each_engine -> execute(input_parameter);

}