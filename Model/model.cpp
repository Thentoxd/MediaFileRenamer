//
// Created by Alex Nicklin on 22/10/2025.
//

#include "string"
#include "model.h"

#include <vector>

using namespace std;

#include "../main.h"

Model::Model() {
    SPDLOG_INFO("Initialising Model ....");
}

void Model::setCurrentWorkingDirectory(string newCurrentWorkingDirectory) {
    SPDLOG_INFO("Model: updating current working directory");
    currentWorkingDirectory = newCurrentWorkingDirectory;
}

string Model::getCurrentWorkingDirectory() {
    SPDLOG_INFO("Model: getting current working directory");
    return(currentWorkingDirectory);
}

void Model::reload() {
    SPDLOG_INFO("Model: reload");
}

void Model::clear(){
    SPDLOG_INFO("Model: clear");
}
