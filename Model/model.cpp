//
// Created by Alex Nicklin on 22/10/2025.
//

#include "model.h"
#include "../main.h"

Model::Model() {
    SPDLOG_INFO("Initialising Model ....");
}

void Model::updateCurrentWorkingDirectory(string newCurrentWorkingDirectory) {
    SPDLOG_INFO("Model: updating current working directory");
}

void Model::reload() {
    SPDLOG_INFO("Model: reload");
}

void Model::clear(){
    SPDLOG_INFO("Model: clear");
}
