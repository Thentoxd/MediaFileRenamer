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
#include "configfile_model.h"


Model::Model() {
    SPDLOG_INFO("Initialising Model ....");
    // myFileEntries = new FileEntries();
}

void Model::initialise() {
    SPDLOG_INFO("Initialising Model");

    p_config_model = new ConfigFileModel();

    p_config_model -> loadConfigFile("config.json");

    string install_directory_from_config_file = p_config_model -> getCurrentWorkingDirectory();

    this -> setCurrentWorkingDirectory(install_directory_from_config_file);
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

                // std::ifstream stream(getCurrentWorkingDirectory() + "/" + outfilename_str, std::ios::binary);
                // TinyEXIF::EXIFInfo imageEXIF(stream);

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

                // assert(image.get() != nullptr);
                // image->readMetadata();
                //
                // Exiv2::ExifData &exifData = image->exifData();
                // if (exifData.empty()) {
                //     SPDLOG_INFO("No EXIF data found in: {}", outfilename_str);
                // }

                // addEntry(outfilename_str, imageEXIF.DateTimeOriginal);
                addEntry(outfilename_str, dateTakenOriginal);
            }
        }
    }
    SPDLOG_INFO("New model built");
}

string Model::getCurrentWorkingDirectory() {
    SPDLOG_INFO("Model: getting current working directory");
    return(currentWorkingDirectory);
}

// void Model::updateEntries() {
//     int entryCount = getEntryCount();
//     for(int row = 0; row < entryCount; row++) {
//         FileEntryInterface* p_fileEntryInterface = getFileEntry(row);
//         string fileName = p_fileEntryInterface->getCurrentFileName();
//
//         std::ifstream stream(getCurrentWorkingDirectory() + "/" + fileName, std::ios::binary);
//         TinyEXIF::EXIFInfo imageEXIF(stream);
//
//         addEntry(fileName, imageEXIF.DateTimeOriginal);
//     }
// }

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
