//
// Created by Alex Nicklin on 13/11/2025.
//

#include "configfile_model.h"

#include <fstream>







ConfigFileModel::ConfigFileModel() {
    SPDLOG_INFO("In ConfigFileModel::ConfigFileModel");
}

ConfigFileModel::~ConfigFileModel() {
    SPDLOG_INFO("ConfigFileModel::~ConfigFileModel");
}

void ConfigFileModel::loadConfigFile(string config_file_name_param) {
    SPDLOG_INFO("ConfigFileModel::loadConfigFile");

    config_file_name = config_file_name_param;

    ifstream f(config_file_name_param);
    json_data_from_file = json::parse(f);

    SPDLOG_INFO("Loaded config file");

    string install_directory_from_config_file = json_data_from_file["install_directory"];
    if (install_directory_from_config_file == "") {
        SPDLOG_ERROR("No install directory specified in the ");

        // Get the current working directory and set the install_directory to that
        current_working_directory = std::filesystem::current_path().string();
        std::replace( current_working_directory.begin(), current_working_directory.end(), '\\', '/' );
        SPDLOG_INFO("Setting install directory to {}", current_working_directory);

        json_data_from_file["install_directory"] = current_working_directory;

        this->saveConfigFile();

        SPDLOG_INFO("Updated config file {}", config_file_name);
    }
    current_working_directory = json_data_from_file["install_directory"];

    SPDLOG_INFO("Install directory loaded from config file: {}", install_directory_from_config_file);

    file_history = json_data_from_file["directory_history"].get<std::vector<string>>();
    SPDLOG_INFO("Loaded file history from config file");

    file_types_processed = json_data_from_file["filetypes_parsed"].get<std::vector<string>>();
    SPDLOG_INFO("Loaded filetypes_parsed from config file");
}

void ConfigFileModel::saveConfigFile() {
    SPDLOG_INFO("ConfigFileModel::saveConfigFile");

    std::ofstream file(config_file_name);

    file << std::setw(4) << json_data_from_file << std::endl;
}

string ConfigFileModel::getCurrentWorkingDirectory() {
    SPDLOG_INFO("ConfigFileModel::getCurrentWorkingDirectory");

    return current_working_directory;
}

void ConfigFileModel::updateLastDirectories() {
    SPDLOG_INFO("ConfigFileModel::updateLastDirectories");

    json_data_from_file["directory_history"] = file_history;
}

void ConfigFileModel::setCurrentWorkingDirectory(string path) {
    SPDLOG_INFO("ConfigFileModel::setCurrentWorkingDirectory");

    bool seen_this_directory_before = false;
    for(const string each_directory : file_history)
        if (each_directory == path) {
            seen_this_directory_before = true;
        }
    if (!seen_this_directory_before) {
        file_history.push_back(path);
        if (file_history.size() > 10) {
            file_history.erase(file_history.begin());
        }
        SPDLOG_INFO("ConfigFileModel::setCurrentWorkingDirectory: Stored a new working directory {}", path);

        this -> updateLastDirectories();

        this -> saveConfigFile();
    }
}

vector<std::string> ConfigFileModel::getFolderHistory() {
    SPDLOG_INFO("ConfigFileModel::getFolderHistory");
    return file_history;
}

void ConfigFileModel::appendFileHistory(string new_directory_parameter) {
    SPDLOG_INFO("ConfigFileModel::appendFileHistory");
}

vector<std::string> ConfigFileModel::getFileTypesProcessed() {
    SPDLOG_INFO("ConfigFileModel::getFileTypesProcessed");
}

void ConfigFileModel::reloadFileTypesProcessed() {
    SPDLOG_INFO("ConfigFileModel::reloadFileTypesProcessed");
}