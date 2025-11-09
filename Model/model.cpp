//
// Created by Alex Nicklin on 22/10/2025.
//

#include "string"
#include "model.h"

#include <vector>

#include <filesystem>
#include <iostream>

using namespace std;

#include "../main.h"



Model::Model() {
    SPDLOG_INFO("Initialising Model ....");
    // myFileEntries = new FileEntries();
}

void Model::setCurrentWorkingDirectory(string newCurrentWorkingDirectory) {
    SPDLOG_INFO("Model: updating current working directory");
    currentWorkingDirectory = newCurrentWorkingDirectory;

    this -> clear();
    /*
    virtual void setFileName(string fileName) = 0;
    virtual void setNewFileName(string newFileName) = 0;
    virtual void setDateTaken(time_t dateTaken) = 0;
    virtual void setNewDateTaken(time_t newDateTaken) = 0;
    */

    // directory_iterator can be iterated using a range-for loop
    for (auto const& entry : filesystem::directory_iterator{currentWorkingDirectory}) {
        if(!entry.is_directory()) {
            filesystem::path outfilename = entry.path().filename();
            string outfilename_str = outfilename.string();

            if(outfilename_str[0] != '.') {
                SPDLOG_INFO("Filename found: {}", outfilename_str);
                addEntry(outfilename_str, time_t(nullptr));
            }
        }
    }
    SPDLOG_INFO("New model built");
}

string Model::getCurrentWorkingDirectory() {
    SPDLOG_INFO("Model: getting current working directory");
    return(currentWorkingDirectory);
}

void Model::reload() {
    SPDLOG_INFO("Model: reload");
}

void Model::clear(){
    SPDLOG_INFO("Model: clear fileEntries");
    fileEntries.clear();
}

void Model::setFileTypesToParse(const vector<string> fileTypesToParseParameter) {
    SPDLOG_INFO("Model::setFileTypesToParse");
    this -> fileTypesToParse = fileTypesToParseParameter;
}

void Model::setMediaFileRenamerVersion(const std::string_view versionParameter) {
    SPDLOG_INFO("Model::setMediaFileRenamerVersion: {}", versionParameter);
    this -> mediaFileRenamerVersion = versionParameter;
}
