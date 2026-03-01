//
// Created by Alex Nicklin on 16/11/2025.
//

#include <fstream>

#include "../main.h"

#include "model_configfile.h"

void ModelConfigfile::loadConfigFile(const string config_file_name_param) {
    SPDLOG_INFO("ModelConfigfile::loadConfigFile");

    config_file_name = config_file_name_param;
    current_working_directory = std::filesystem::current_path().string();

    if (!std::filesystem::exists(config_file_name_param)) {
        SPDLOG_CRITICAL("No config file found - building one from scratch ");
        json_data_from_file["install_directory"] = current_working_directory;
        file_history.push_back(current_working_directory);
        json_data_from_file["directory_history"] = file_history;

        date_formats_parsed.push_back("YYYY-MM-DD");
        date_formats_parsed.push_back("YYYYMMDD");
        json_data_from_file["date_formats_parsed"] = date_formats_parsed;

        file_types_processed.push_back("jpg");
        file_types_processed.push_back("JPG");
        file_types_processed.push_back("jpeg");
        file_types_processed.push_back("png");
        json_data_from_file["filetypes_parsed"] = file_types_processed;

        filetypes_can_only_edit_filename.push_back("mp4");
        filetypes_can_only_edit_filename.push_back("CR2");
        json_data_from_file["filetypes_can_only_edit_filename"] = filetypes_can_only_edit_filename;

        this->saveConfigFile();
        return;
    }
    else {
        ifstream f(config_file_name_param);
        json_data_from_file = json::parse(f);
        SPDLOG_INFO("Loaded config file");
    }


    string install_directory_from_config_file = json_data_from_file["install_directory"];
    if (install_directory_from_config_file.empty()) {
        SPDLOG_ERROR("No install directory specified in the ");

        // Get the current working directory and set the install_directory to that

        std::replace( current_working_directory.begin(), current_working_directory.end(), '\\', '/' );
        SPDLOG_INFO("Setting install directory to {}", current_working_directory);

        json_data_from_file["install_directory"] = current_working_directory;

        this->saveConfigFile();

        SPDLOG_INFO("Updated config file {}", config_file_name);
    }

    SPDLOG_INFO("Install directory loaded from config file: {}", install_directory_from_config_file);

    file_history = json_data_from_file["directory_history"].get<std::vector<string>>();
    SPDLOG_INFO("Loaded file history from config file");

    if (file_history.empty()) {
        current_working_directory = install_directory_from_config_file;
        vector<string> dir_history;
        dir_history.push_back(current_working_directory);
        json_data_from_file["directory_history"] = dir_history;
        this->saveConfigFile();
    }
    else {
        if (!file_history[0].empty()) {
            current_working_directory = file_history[0];
        }
    }


    date_formats_parsed = json_data_from_file["date_formats_parsed"].get<vector<string>>();
    SPDLOG_INFO("Loaded file history from config file");
    if (date_formats_parsed.empty()) {
        date_formats_parsed.push_back("YYYY-MM-DD");
        date_formats_parsed.push_back("YYYYMMDD");
        json_data_from_file["date_formats_parsed"] = date_formats_parsed;
        this->saveConfigFile();
    }

    file_types_processed = json_data_from_file["filetypes_parsed"].get<std::vector<string>>();
    SPDLOG_INFO("Loaded filetypes_parsed from config file");

    filetypes_can_only_edit_filename = json_data_from_file["filetypes_can_only_edit_filename"].get<std::vector<string>>();
    SPDLOG_INFO("Loaded filetypes_can_only_edit_filename from config file");

    vector<EngineTypes> renaming_chain = json_data_from_file["renaming_chain"];
    SPDLOG_INFO("Loaded last renaming chain from config file");
    if (renaming_chain.empty()) {
        SPDLOG_CRITICAL("Renaming chain from config file is empty");
        assert(0);
    }
    renaming_chain_parsed = renaming_chain;
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


vector<std::string> ModelConfigfile::getFolderHistory() {
    SPDLOG_INFO("Model::getFolderHistory");
    return file_history;
}


string ModelConfigfile::getCurrentWorkingDirectory() {
    SPDLOG_INFO("Model::getCurrentWorkingDirectory");
    return current_working_directory;
}


void ModelConfigfile::appendFileHistory(string new_directory_parameter) {

    if (new_directory_parameter.empty()) {
        SPDLOG_ERROR("Ignoring empty directory");
        return;
    }

    bool seen_this_directory_before = false;
    for(const string& each_directory : file_history)
        if (new_directory_parameter == each_directory) {
            seen_this_directory_before = true;
        }

    // If we have seen this folder before, move it to the first element in the list
    if (seen_this_directory_before) {
        file_history.erase(std::remove(file_history.begin(), file_history.end(), new_directory_parameter), file_history.end());
        file_history.insert(file_history.begin(), new_directory_parameter);
    }

    if (!seen_this_directory_before) {
        file_history.insert(file_history.begin(),new_directory_parameter);
        // file_history.push_back(new_directory_parameter);
        if (file_history.size() > 10) {
            file_history.erase(file_history.begin());
        }
        SPDLOG_INFO("ConfigFileModel::setCurrentWorkingDirectory: Stored a new working directory {}", new_directory_parameter);
    }
    this -> updateLastDirectories();
    this -> saveConfigFile();
}


vector<std::string> ModelConfigfile::getFileTypesProcessed() {
    SPDLOG_INFO("Model::getFileTypesProcessed");
    return file_types_processed;
}


vector<std::string> ModelConfigfile::getFileTypesFilenameOnlyProcessed() {
    SPDLOG_INFO("Model::getFileTypesFilenameOnlyProcessed");
    return filetypes_can_only_edit_filename;
}


vector<std::string> ModelConfigfile::getDateFormatsParsed() {
    SPDLOG_INFO("Model::getDateFormatParsed");
    return date_formats_parsed;
}


vector<EngineTypes> ModelConfigfile::getSavedEngineChain() {
    SPDLOG_INFO("Model::getSavedEngineChain");
    return renaming_chain_parsed;
}



void ModelConfigfile::updateSavedEngineChain(vector<EngineTypes>) {
    SPDLOG_INFO("Model::updateSavedEngineChain");
    assert(0);
}



void ModelConfigfile::restoreSavedEngineChain() {
    SPDLOG_INFO("Model::restoreSavedEngineChain");
    assert(0);
}
