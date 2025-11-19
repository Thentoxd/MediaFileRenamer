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

    string renamed_filename = "";
    string renamed_datecreated = "";

    for(ModelRenamingEngine * each_engine : renaming_engine) {
        pair<string, string> return_pair = each_engine -> execute(input_parameter);

        if (return_pair.first != input_parameter.first) {
            renamed_filename += return_pair.first;
            renamed_filename += " ";
        }

        if (return_pair.second != input_parameter.second) {
            renamed_datecreated += return_pair.second;
        }


    }

    SPDLOG_INFO("Renamed filename: {}", renamed_filename);
    // SPDLOG_INFO("Return string2: {}", return_pair.second);


    pair<string, string> returnPair;

    if (renamed_filename.empty()) {
        returnPair.first = input_parameter.first;
    }
    else {
        returnPair.first = renamed_filename;
    }

    if (renamed_datecreated.empty()) {
        returnPair.second = input_parameter.second;
    }
    else {
        returnPair.second = renamed_datecreated;
    }

    return returnPair;
}