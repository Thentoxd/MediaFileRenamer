//
// Created by Alex Nicklin on 13/11/2025.
//

#ifndef MEDIAFILERENAMER_CONFIGFILE_MODEL_H
#define MEDIAFILERENAMER_CONFIGFILE_MODEL_H
#include <string>
#include <vector>

using namespace std;

#include "../main.h"

#include <nlohmann/json.hpp>
using json = nlohmann::json;

// This class manages the reading and writing of the config file and methods to get/set values

class ConfigFileModel {
private:

    json json_data_from_file;

    string current_working_directory;
    string config_file_name;
    vector<std::string> file_history;
    vector<std::string> file_types_processed;

public:
    ConfigFileModel();
    ~ConfigFileModel();

    void loadConfigFile(const string config_file_name_param);
    void saveConfigFile();

    string getCurrentWorkingDirectory();
    void setCurrentWorkingDirectory(string path);

    vector<std::string> getFileHistory();
    void appendFileHistory(string new_directory_parameter);

    vector<std::string> getFileTypesProcessed();
    void reloadFileTypesProcessed();
};

#endif //MEDIAFILERENAMER_CONFIGFILE_MODEL_H