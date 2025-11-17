//
// Created by Alex Nicklin on 22/10/2025.
//

#include "string"
#include "model.h"

#include <vector>

#include <filesystem>


#include "exiv2/exiv2.hpp"

using namespace std;

#include "../main.h"


Model::Model() {
    SPDLOG_INFO("Model Contructor");
}

void Model::initialise(ModelConfigfile * parameter_ModelConfigfile) {
    SPDLOG_INFO("Model::initialise");

    p_ModelConfigfile = parameter_ModelConfigfile;

    p_ModelConfigfile -> loadConfigFile("config.json");
    this -> setCurrentWorkingDirectory(p_ModelConfigfile -> getCurrentWorkingDirectory());

    renaming_queue = new ModelRemamingQueue();
    renaming_queue -> init(0);
}

void Model::setCurrentWorkingDirectory(string newCurrentWorkingDirectory) {
    SPDLOG_INFO("Model::setCurrentWorkingDirectory");
    string current_working_directory = newCurrentWorkingDirectory;

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

                    vector<std::string> file_types_processed = p_ModelConfigfile -> getFileTypesProcessed();
                    for(const string& each_file_type : file_types_processed)
                        if (extension == each_file_type) {
                            allowed_file_type = true;
                        }
                }
                else {
                    allowed_file_type = true;
                }

                if (allowed_file_type) {
                    string media_file_to_read = newCurrentWorkingDirectory + "/" + outfilename_str;
                    string dateTakenOriginal;

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
                        string exception_text = "Caught Exiv2 exception '";
                        exception_text.append(e.what());
                        SPDLOG_INFO("Exiv2 exception trying to process file {}: {}", outfilename_str[0], exception_text);
                    }

                    addEntry(outfilename_str, dateTakenOriginal);
                }
            }
        }
    }

    p_ModelConfigfile -> appendFileHistory(current_working_directory);

    SPDLOG_INFO("Model::setCurrentWorkingDirectory. New model built");
}


void Model::renameEXIFFile(FileEntry* newFile) {
    rename((getCurrentWorkingDirectory() + newFile->getCurrentFileName()).c_str(), newFile->getNewFileName().c_str());
    newFile->setFileName(newFile->getNewFileName());
}


string Model::getCurrentWorkingDirectory() {
    SPDLOG_INFO("Model::getCurrentWorkingDirectory");
    return(p_ModelConfigfile -> getCurrentWorkingDirectory());
}


void Model::reload() {
    SPDLOG_INFO("Model::reload");
}


void Model::clear(){
    SPDLOG_INFO("Model::clear");
    fileEntries.clear();
}


void Model::setFileTypesToParse(const vector<string> fileTypesToParseParameter) {
    SPDLOG_INFO("Model::setFileTypesToParse");
    assert(0);
    // this -> file_types_processed = fileTypesToParseParameter;
}


void Model::setMediaFileRenamerVersion(const std::string_view versionParameter) {
    SPDLOG_INFO("Model::setMediaFileRenamerVersion: {}", versionParameter);
    this -> mediaFileRenamerVersion = versionParameter;
}

vector<string> Model::getFolderHistory() {
    SPDLOG_INFO("Model::getFolderHistory");
    return p_ModelConfigfile -> getFolderHistory();
}



