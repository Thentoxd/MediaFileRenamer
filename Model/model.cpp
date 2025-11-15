//
// Created by Alex Nicklin on 22/10/2025.
//

#include "string"
#include "model.h"

#include <vector>

#include <filesystem>
#include <fstream>
#include <iostream>

#include "exiv2/exiv2.hpp"

using namespace std;

#include "../main.h"


Model::Model() {
    SPDLOG_INFO("Initialising Model ....");
    // myFileEntries = new FileEntries();
}

void Model::initialise() {
    SPDLOG_INFO("Initialising Model");

    this -> loadConfigFile("config.json");

    this -> setCurrentWorkingDirectory(current_working_directory);
}

void Model::setCurrentWorkingDirectory(string newCurrentWorkingDirectory) {
    SPDLOG_INFO("Model: updating current working directory");
    current_working_directory = newCurrentWorkingDirectory;

    this -> clear();
    /*
    virtual void setFileName(string fileName) = 0;
    virtual void setNewFileName(string newFileName) = 0;
    virtual void setDateTaken(time_t dateTaken) = 0;
    virtual void setNewDateTaken(time_t newDateTaken) = 0;
    */

    // directory_iterator can be iterated using a range-for loop
    for (auto const& entry : filesystem::directory_iterator{current_working_directory}) {
        if(!entry.is_directory()) {
            filesystem::path outfilename = entry.path().filename();
            string outfilename_str = outfilename.string();

            if(outfilename_str[0] != '.') {
                SPDLOG_INFO("Filename found: {}", outfilename_str);

                bool allowed_file_type = false;
                int dot_position = outfilename_str.rfind('.');
                if (dot_position != string::npos) {
                    string extension = outfilename_str.substr(dot_position + 1);

                    for(const string each_file_type : file_types_processed)
                        if (extension == each_file_type) {
                            allowed_file_type = true;
                        }
                }
                else {
                    allowed_file_type = true;
                }

                if (allowed_file_type) {
                    string media_file_to_read = getCurrentWorkingDirectory() + "/" + outfilename_str;
                    string dateTakenOriginal = "";

                    try {
                        Exiv2::Image::UniquePtr image = Exiv2::ImageFactory::open(media_file_to_read);
                        if(!image.get()) {
                            SPDLOG_INFO("Failed to open image: {}", media_file_to_read);
                        } else {
                            image->readMetadata();
                            Exiv2::ExifData &exifData = image->exifData();

                            if(exifData.empty()) {
                                SPDLOG_INFO("No EXIF data found in: {}", media_file_to_read);
                            } else {
                                Exiv2::ExifKey key("Exif.Photo.DateTimeOriginal");
                                auto pos = exifData.findKey(key);
                                if (pos != exifData.end()) {
                                    dateTakenOriginal = pos->toString();
                                } else {
                                    SPDLOG_INFO("DateTimeOriginal not found.");
                                }
                            }
                        }

                    }
                    catch (Exiv2::Error& e) {
                        SPDLOG_INFO("Exiv2 exception - usually means no EXIF data found in {}", outfilename_str);
                    }

                    addEntry(outfilename_str, dateTakenOriginal);
                }
            }
        }
    }

    bool seen_this_directory_before = false;
    for(const string each_directory : file_history)
        if (newCurrentWorkingDirectory == each_directory) {
            seen_this_directory_before = true;
        }
    if (!seen_this_directory_before) {
        file_history.insert(file_history.begin(),newCurrentWorkingDirectory);
        if (file_history.size() > 10) {
            file_history.erase(file_history.begin());
        }
        SPDLOG_INFO("ConfigFileModel::setCurrentWorkingDirectory: Stored a new working directory {}", newCurrentWorkingDirectory);

        this -> updateLastDirectories();
        this -> saveConfigFile();
    }

    SPDLOG_INFO("New model built");
}


void Model::renameEXIFFile(FileEntry* newFile) {
    rename((getCurrentWorkingDirectory() + newFile->getCurrentFileName()).c_str(), newFile->getNewFileName().c_str());
    newFile->setFileName(newFile->getNewFileName());
}

string Model::getCurrentWorkingDirectory() {
    SPDLOG_INFO("Model: getting current working directory");
    return(current_working_directory);
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
    this -> file_types_processed = fileTypesToParseParameter;
}


void Model::setMediaFileRenamerVersion(const std::string_view versionParameter) {
    SPDLOG_INFO("Model::setMediaFileRenamerVersion: {}", versionParameter);
    this -> mediaFileRenamerVersion = versionParameter;
}


vector<std::string> Model::getFolderHistory() {
    SPDLOG_INFO("ConfigFileModel::getFolderHistory");
    return file_history;
}


void Model::loadConfigFile(string config_file_name_param) {
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

    SPDLOG_INFO("Install directory loaded from config file: {}", install_directory_from_config_file);

    file_history = json_data_from_file["directory_history"].get<std::vector<string>>();
    SPDLOG_INFO("Loaded file history from config file");

    if (file_history[0] != "") {
        current_working_directory = file_history[0];
    }
    else {
        current_working_directory = install_directory_from_config_file;
    }

    file_types_processed = json_data_from_file["filetypes_parsed"].get<std::vector<string>>();
    SPDLOG_INFO("Loaded filetypes_parsed from config file");
}

void Model::saveConfigFile() {
    SPDLOG_INFO("ConfigFileModel::saveConfigFile");

    std::ofstream file(config_file_name);

    file << std::setw(4) << json_data_from_file << std::endl;
}

void Model::updateLastDirectories() {
    SPDLOG_INFO("ConfigFileModel::updateLastDirectories");

    json_data_from_file["directory_history"] = file_history;
}
