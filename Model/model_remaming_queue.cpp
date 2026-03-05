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


void ModelRemamingQueue::appendEngine(ModelRenamingEngine * engine) {
    SPDLOG_INFO("ModelRemamingQueue::appendEngine");
    renaming_engine.push_back(engine);
}


void ModelRemamingQueue::clearEngines() {
    SPDLOG_INFO("ModelRemamingQueue::clearEngines");

    for (auto eachEngine : renaming_engine)
    {
        eachEngine -> clear();
    }
}


void ModelRemamingQueue::deleteAllEngines() {
    SPDLOG_INFO("ModelRemamingQueue::deleteAllEngines");
    assert(0);
}


pair<string, string> ModelRemamingQueue::executeQueue(const pair<string, string>& input_parameter) {
    SPDLOG_INFO("ModelRemamingQueue::executeQueue");

    string renamed_filename = "";
    string renamed_datecreated = "";

    for(ModelRenamingEngine * each_engine : renaming_engine) {
        if(each_engine->isActive()) {
            pair<string, string> return_pair = each_engine -> execute(input_parameter);

            if (return_pair.first != input_parameter.first) {
                renamed_filename += return_pair.first;
            }

            if (return_pair.second != input_parameter.second) {
                renamed_datecreated += return_pair.second;
            }
        }
    }

    // Strip last seperator off
    //renamed_filename.erase(renamed_filename.find_last_not_of(" ") + 1);

    //SPDLOG_INFO("Renamed filename: {}", renamed_filename);
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


ModelRenamingEngineCounter * ModelRemamingQueue::getNthCounterEngine(int instanceNumber) {
    SPDLOG_INFO("ModelRemamingQueue::getNthCounterEngine");
    // Work down the renaming_engine vector. Find the nth (instance number) of type ModelRenamingEngineCounter *
    int count = 1;
    for (auto each_engine : renaming_engine) {
        if (typeid(*each_engine) == typeid(ModelRenamingEngineCounter)) {
            if (count == instanceNumber) {
                return(dynamic_cast<ModelRenamingEngineCounter*>(each_engine));
            }
            count++;
        }
    }
    return(nullptr);
}


ModelRenamingEngineSeperator * ModelRemamingQueue::getNthSeperatorEngine(int instanceNumber) {
    SPDLOG_INFO("ModelRemamingQueue::getNthSeperatorEngine");
    // Work down the renaming_engine vector. Find the nth (instance number) of type ModelRenamingEngineSeperator *
    int count = 1;
    for (auto each_engine : renaming_engine) {
        if (typeid(*each_engine) == typeid(ModelRenamingEngineSeperator)) {
            if (count == instanceNumber) {
                return(dynamic_cast<ModelRenamingEngineSeperator*>(each_engine));
            }
            count++;
        }
    }
    return(nullptr);
}


ModelRenamingEngineTextBody * ModelRemamingQueue::getNthTextbodyEngine(int instanceNumber) {
    SPDLOG_INFO("ModelRemamingQueue::getNthTextbodyEngine");
    // Work down the renaming_engine vector. Find the nth (instance number) of type ModelRenamingEngineTextBody *
    int count = 1;
    for (auto each_engine : renaming_engine) {
        if (typeid(*each_engine) == typeid(ModelRenamingEngineTextBody)) {
            if (count == instanceNumber) {
                return(dynamic_cast<ModelRenamingEngineTextBody*>(each_engine));
            }
            count++;
        }
    }
    return(nullptr);
}


ModelRenamingEngineDate * ModelRemamingQueue::getNthDateEngine(int instanceNumber) {
    SPDLOG_INFO("ModelRemamingQueue::getNthDateEngine");
    // Work down the renaming_engine vector. Find the nth (instance number) of type ModelRenamingEngineDate *
    int count = 1;
    for (auto each_engine : renaming_engine) {
        if (typeid(*each_engine) == typeid(ModelRenamingEngineDate)) {
            if (count == instanceNumber) {
                return(dynamic_cast<ModelRenamingEngineDate*>(each_engine));
            }
            count++;
        }
    }
    return(nullptr);
}
