//
// Created by Alex Nicklin on 22/10/2025.
//

#include "string"
#include "model.h"

#include <vector>

#include <filesystem>

using namespace std;

#include "../main.h"



Model::Model() {
    SPDLOG_INFO("Initialising Model ....");
    // myFileEntries = new FileEntries();
}

void Model::setCurrentWorkingDirectory(string newCurrentWorkingDirectory) {
    SPDLOG_INFO("Model: updating current working directory");
    currentWorkingDirectory = newCurrentWorkingDirectory;

    // this -> clear();
    /*
    virtual void setFileName(string fileName) = 0;
    virtual void setNewFileName(string newFileName) = 0;
    virtual void setDateTaken(time_t dateTaken) = 0;
    virtual void setNewDateTaken(time_t newDateTaken) = 0;
    */

    // directory_iterator can be iterated using a range-for loop
    for (auto const& dir_entry : filesystem::directory_iterator{currentWorkingDirectory}) {
        if (!dir_entry.is_directory()) {
            string raw_filename = dir_entry.path().string();
            raw_filename = raw_filename.substr(2);

            if (raw_filename[0] != '.') {
                int dot_position = raw_filename.find(".");
                string final_filename;

                if (dot_position == -1)
                    final_filename = raw_filename;
                else {
                    final_filename = raw_filename.substr(0, dot_position);
                }

                time_t current_time = time(nullptr);

                // p_model -> addEntry(final_filename, current_time);
                SPDLOG_INFO("File in CWD: {}", final_filename);

                this -> addEntry(final_filename, current_time);
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
    SPDLOG_INFO("Model: clear");
}
