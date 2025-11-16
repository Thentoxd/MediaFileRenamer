//
// Created by Alex Nicklin on 16/11/2025.
//

#include <fstream>

#include "../main.h"

#include "model_configfile.h"

void ModelConfigfile::loadConfigFile(const string config_file_name_param) {
    SPDLOG_INFO("ModelConfigfile::loadConfigFile");

    config_file_name = config_file_name_param;

    ifstream f(config_file_name_param);
    json_data_from_file = json::parse(f);

    SPDLOG_INFO("Loaded config file");

    string install_directory_from_config_file = json_data_from_file["install_directory"];
    if (install_directory_from_config_file.empty()) {
        SPDLOG_ERROR("No install directory specified in the ");

        // Get the current working directory and set the install_directory to that
        current_working_directory = std::filesystem::current_path().string();
        std::replace( current_working_directory.begin(), current_working_directory.end(), '\\', '/' );
        SPDLOG_INFO("Setting install directory to {}", current_working_directory);

        json_data_from_file["install_directory"] = current_working_directory;

        this->saveConfigFile();

        SPDLOG_INFO("Updated config file {}", config_file_name);
    }

    SPDLOG_INFO("Install directory loaded from config file: {}", install_directory_from_config_file);

    file_history = json_data_from_file["directory_history"].get<std::vector<string>>();
    SPDLOG_INFO("Loaded file history from config file");

    if (!file_history[0].empty()) {
        current_working_directory = file_history[0];
    }
    else {
        current_working_directory = install_directory_from_config_file;
    }

    file_types_processed = json_data_from_file["filetypes_parsed"].get<std::vector<string>>();
    SPDLOG_INFO("Loaded filetypes_parsed from config file");
}

void ModelConfigfile::saveConfigFile() {
    SPDLOG_INFO("ModelConfigfile::saveConfigFile");

    std::ofstream file(config_file_name);

    file << std::setw(4) << json_data_from_file << std::endl;
}

void ModelConfigfile::updateLastDirectories() {
    SPDLOG_INFO("ModelConfigfile::updateLastDirectories");

    json_data_from_file["directory_history"] = file_history;
}