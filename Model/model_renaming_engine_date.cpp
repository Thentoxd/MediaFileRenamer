//
// Created by Alex Nicklin on 17/11/2025.
//

#include "model_renaming_engine_date.h"
#include "../main.h"

ModelRenamingEngineDate::ModelRenamingEngineDate() {
    SPDLOG_INFO("ModelRenamingEngineDate::ModelRenamingEngineDate");
}

ModelRenamingEngineDate::~ModelRenamingEngineDate() {
    SPDLOG_INFO("ModelRenamingEngineDate::~ModelRenamingEngineDate");
}

void ModelRenamingEngineDate::init(int mode) {
    SPDLOG_INFO("ModelRenamingEngineDate::init");
}

pair<string, string> ModelRenamingEngineDate::execute(pair<string, string> input_parameter) {
    SPDLOG_INFO("ModelRemamingQueue::ModelRemamingQueue");
    // current file name, current date taken original
    string currentFileName = input_parameter.first;

    string year = "";
    int index = 0;
    for(int i = 0; i < currentFileName.length() - 4; i++) {
        bool four_digits = true;
        for(int j = 0; j < 4; j++) {
            four_digits &= isdigit(currentFileName[i + j]);
        }

        if(four_digits) {
            for(int j = 0; j < 4; j++) {
                year += currentFileName[i + j];
            }
            index = i;
            break;
        }
    }

    string month = "";
    for(int i = index + 4; i < currentFileName.length() - 2; i++) {
        bool two_digits = true;
        for(int j = 0; j < 2; j++) {
            two_digits &= isdigit(currentFileName[i + j]);
        }

        if(two_digits) {
            for(int j = 0; j < 2; j++) {
                month += currentFileName[i + j];
            }
            index = i;
            break;
        }
    }

    string date = "";
    for(int i = index + 2; i < currentFileName.length() - 2; i++) {
        bool two_digits = true;
        for(int j = 0; j < 2; j++) {
            two_digits &= isdigit(currentFileName[i + j]);
        }

        if(two_digits) {
            for(int j = 0; j < 2; j++) {
                date += currentFileName[i + j];
            }
            break;
        }
    }

    SPDLOG_DEBUG("{}-{}-{}", year, month, date);

    string return_string = year + "-" + month + "-" + date;

    return pair<string, string>(return_string, input_parameter.second);
}

void ModelRenamingEngineDate::setRenamingEngineDateSetYear(string newValue) {
    SPDLOG_INFO("ModelRenamingEngineDate::setRenamingEngineDateSetYear. Set year to {}", newValue);
    year = newValue;
}


void ModelRenamingEngineDate::setRenamingEngineDateSetMonth(string newValue) {
    SPDLOG_INFO("ModelRenamingEngineDate::setRenamingEngineDateSetMonth. Set month to {}", newValue);
    month = newValue;
}


void ModelRenamingEngineDate::setRenamingEngineDateSetDay(string newValue) {
    SPDLOG_INFO("ModelRenamingEngineDate::setRenamingEngineDateSetDay. Set day to {}", newValue);
    day = newValue;
}

void ModelRenamingEngineDate::clear() {
    SPDLOG_INFO("ModelRenamingEngineDate::clear");
}