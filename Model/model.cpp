//
// Created by Alex Nicklin on 22/10/2025.
//

#include "string"
#include "model.h"

#include <vector>

#include <filesystem>
#include <QApplication>
#include <qstring.h>


#include "model_renaming_engine_seperator.h"
#include "exiv2/exiv2.hpp"

using namespace std;

#include "../main.h"


Model::Model() {
    SPDLOG_INFO("Model Constructor");
}


void Model::initialise() {

    p_ModelConfigfile = new ModelConfigfile();
    p_ModelRemamingQueue = new ModelRemamingQueue;

    // In the first version of this program we hardcoded the sequence of renaming components
    // We now allow dynamic chains, so first read the last chain from the config file and
    // create the renaming queue

    SPDLOG_INFO("Model::initialise");

    p_ModelConfigfile -> loadConfigFile("config.json");
    this -> setCurrentWorkingDirectory(p_ModelConfigfile -> getCurrentWorkingDirectory());
    auto date_formats_parsed = p_ModelConfigfile -> getDateFormatsParsed();

    auto renaming_chain = p_ModelConfigfile -> getSavedEngineChain();
    SPDLOG_INFO("Loaded renaming chain saved in the config file");

    // Let's iterate down the renaming_chain, creating instances of engines and appending those to the queue
    for (EngineTypes eachEngineType: renaming_chain) {
        // Create an instance of EngineType and append to the p_ModelRemamingQueue
        switch(eachEngineType) {
            case EngineTypes::DateEngine: {
                SPDLOG_INFO("Appending a date renaming engine to the renaming queue");
                auto * p_newRenamingDataEngine = new ModelRenamingEngineDate();
                p_newRenamingDataEngine -> setFormats(date_formats_parsed);
                p_ModelRemamingQueue -> appendEngine(p_newRenamingDataEngine);
                break;
            }

            case EngineTypes::SeperatorEngine: {
                SPDLOG_INFO("Appending a seperator renaming engine to the renaming queue");
                auto * newRenamingSeperatorEngine = new ModelRenamingEngineSeperator();
                // newEngine -> setFormats(date_formats_parsed);
                p_ModelRemamingQueue -> appendEngine(newRenamingSeperatorEngine);
                break;
            }

            case EngineTypes::FilenameBodyEngine: {
                SPDLOG_INFO("Appending a filename body renaming engine to the renaming queue");
                auto * p_newRenamingFilename = new ModelRenamingEngineTextBody();
                p_ModelRemamingQueue -> appendEngine(p_newRenamingFilename);
                break;
            }

            case EngineTypes::NumberingEngine: {
                SPDLOG_INFO("Appending a numbering renaming engine to the renaming queue");
                auto * p_newRenamingNumbering = new ModelRenamingEngineCounter();
                p_ModelRemamingQueue -> appendEngine(p_newRenamingNumbering);
                break;
            }
        }
    }
}


void Model::setCurrentWorkingDirectory(string newCurrentWorkingDirectory) {
    SPDLOG_INFO("Model::setCurrentWorkingDirectory");
    updateCurrentWorkingDirectory(newCurrentWorkingDirectory);
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
                bool file_type_we_can_only_edit_filename = false;

                int dot_position = outfilename_str.rfind('.');
                if (dot_position != string::npos) {
                    string extension = outfilename_str.substr(dot_position + 1);

                    vector<std::string> file_types_processed = p_ModelConfigfile -> getFileTypesProcessed();
                    for(const string& each_file_type : file_types_processed)
                        if (extension == each_file_type) {
                            allowed_file_type = true;
                        }

                    vector<std::string> file_types_filename_only = p_ModelConfigfile -> getFileTypesFilenameOnlyProcessed();
                    for(const string& each_file_type : file_types_filename_only)
                        if (extension == each_file_type) {
                            file_type_we_can_only_edit_filename = true;
                        }
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

                if (file_type_we_can_only_edit_filename) {
                    addEntry(outfilename_str, "");
                }
            }
        }
    }

    p_ModelConfigfile -> appendFileHistory(current_working_directory);

    SPDLOG_INFO("Model::setCurrentWorkingDirectory. New model built");
}


void Model::renameEXIFFile(FileEntry* newFile) {
    rename((getCurrentWorkingDirectory() + "/" + newFile->getCurrentFileName()).c_str(), (getCurrentWorkingDirectory() + "/" + newFile->getNewFileName()).c_str());
    newFile->setFileName(newFile->getNewFileName());
}


void Model::changeEXIFDateTakenOriginal(FileEntry* file) {
    try {
        //TODO
        int year = 0, month = 0, day = 0;
        int formatPointer = 0;

        string fullFilePath = getCurrentWorkingDirectory() + "/" + file->getCurrentFileName();
        string newDate = format("{:04d}:{:02d}:{:02d}", year, month, day);

        Exiv2::Image::UniquePtr image = Exiv2::ImageFactory::open(fullFilePath);
        Exiv2::ExifData &exifData = image->exifData();

        exifData["Exif.Photo.DateTimeOriginal"] = newDate;

        image->writeMetadata();

        SPDLOG_INFO("Renamed {}'s date time original to {}", file->getCurrentFileName(), newDate);
    } catch(Exiv2::Error& e) {
        SPDLOG_ERROR("Couldn't rename {}'s EXIF Current Date Taken Original");
    }
}


void Model::setDateFormat(string format) {
    dateFormat = format;
}


string Model::getDateFormat() {
    return dateFormat;
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


void Model::clearRenamingChain() {
    p_ModelRemamingQueue -> clearEngines();
}


vector<pair<string, string>> Model::executeRenamingChain(vector<int> rows, bool renameFiles, bool renameDateTakenOriginal) {
    SPDLOG_INFO("Model::executeRenamingChain");
    vector<pair<string, string>> returnPairList;

    for (auto rowNumber : rows)
    {
        SPDLOG_INFO("Executing the chain on row {}", rowNumber);
        FileEntry* entry = getFileEntry(rowNumber);

        // Need to store the file extension
        string currentFilename = entry->getCurrentFileName();
        string currentFileExtension = currentFilename.substr(currentFilename.find("."));

        pair<string, string> returnPair = p_ModelRemamingQueue->executeQueue(make_pair(entry->getCurrentFileName(), entry->getCurrentDateTakenOriginal()));

        SPDLOG_INFO("RETURNED VALUE: {}", returnPair.first);

        returnPair.first += currentFileExtension;

        returnPairList.push_back(returnPair);

        if(renameFiles) {
            SPDLOG_INFO("Renaming file {} to {}", getCurrentWorkingDirectory() + "/" + currentFilename, getCurrentWorkingDirectory() + "/" + returnPair.first);
            rename((getCurrentWorkingDirectory() + "/" + currentFilename).c_str(), (getCurrentWorkingDirectory() + "/" + returnPair.first).c_str());
        }

        if(renameDateTakenOriginal) {

            // If currentFileExtension is not in the list of filetypes we can only edit the filenames, try to edit the metadata
            bool file_type_we_can_only_edit_filename = false;
            vector<std::string> file_types_filename_only = p_ModelConfigfile -> getFileTypesFilenameOnlyProcessed();
            for(const string& each_file_type : file_types_filename_only)
                if (currentFileExtension == each_file_type) {
                    file_type_we_can_only_edit_filename = true;
                }

            if (!file_type_we_can_only_edit_filename) {
                try {
                    // int year = 0, month = 0, day = 0;
                    //
                    string fullFilePath = getCurrentWorkingDirectory() + "/" + currentFilename;
                    // string newDate = format("{:04d}:{:02d}:{:02d}", year, month, day);
                    //
                    Exiv2::Image::UniquePtr image = Exiv2::ImageFactory::open(fullFilePath);
                    Exiv2::ExifData &exifData = image->exifData();
                    //
                    // exifData["Exif.Photo.DateTimeOriginal"] = newDate;

                    exifData["Exif.Photo.DateTimeOriginal"] = returnPair.second;

                    image->writeMetadata();

                    SPDLOG_INFO("Renamed {}'s date time original to {}", currentFilename, returnPair.second);
                } catch(Exiv2::Error& e) {
                    SPDLOG_ERROR("Couldn't rename {}'s EXIF Current Date Taken Original");
                }
            }
        }
    }

    return returnPairList;
}


void Model::setMetadataOriginalTakenDateFromFilename() {
    SPDLOG_INFO("Model::setMetadataOriginalTakenDateFromFilename");
}


void Model::setMetadataOriginalTakenDateFromUserGivenYearMonthDay(string param_year, string param_month, string param_day) {
    SPDLOG_INFO("Model::setMetadataOriginalTakenDateFromFilename");
}


void Model::exitApplication() {
    SPDLOG_INFO("Model::exitApplication");
    QApplication::exit(0);
    // always throws QThreadStorageError: thread 0x201f97a9da0
}


vector<EngineTypes> Model::getSavedEngineChain() {
    SPDLOG_INFO("Model::getSavedEngineChain");
    return p_ModelConfigfile ->getSavedEngineChain();
}


void Model::emptyRenamningChainAndRebuild(vector<EngineTypes> newChain) {
    SPDLOG_INFO("Model::emptyRenamningChainAndRebuild");

}



//
// This block handles all the Data methods
//

void Model::setEngineDateState(int instanceNumber, bool state) {
    SPDLOG_INFO("Model::setEngineDatePrefix: {}", instanceNumber);

    // Work down the p_ModelRemamingQueue, find the nth (instance number) of a date engine
    // And then call the setActive on that engine
    ModelRenamingEngineDate * p_DateEngine = p_ModelRemamingQueue -> getNthDateEngine(instanceNumber);
    assert(p_DateEngine != nullptr);
    p_DateEngine->setActive(state);
}

void Model::setRenamingEngineDateSetYear(int instanceNumber, string newText) {
    SPDLOG_INFO("Model::setRenamingEngineDateSetYear");
    ModelRenamingEngineDate * p_DateEngine = p_ModelRemamingQueue -> getNthDateEngine(instanceNumber);
    assert(p_DateEngine != nullptr);
    p_DateEngine -> setRenamingEngineDateSetYear(newText);
}

void Model::setRenamingEngineDateSetMonth(int instanceNumber, string newText) {
    SPDLOG_INFO("Model::setRenamingEngineDateSetMonth");
    ModelRenamingEngineDate * p_DateEngine = p_ModelRemamingQueue -> getNthDateEngine(instanceNumber);
    assert(p_DateEngine != nullptr);
    p_DateEngine -> setRenamingEngineDateSetMonth(newText);
}


void Model::setRenamingEngineDateSetDay(int instanceNumber, string newText) {
    SPDLOG_INFO("Model::setRenamingEngineDateSetDay");
    ModelRenamingEngineDate * p_DateEngine = p_ModelRemamingQueue -> getNthDateEngine(instanceNumber);
    assert(p_DateEngine != nullptr);
    p_DateEngine -> setRenamingEngineDateSetDay(newText);
}


void Model::setRenamingEngineDateTryExtractDate(int instanceNumber, bool newValue) {
    SPDLOG_INFO("Model::setRenamingEngineDateTryExtractDate");
    ModelRenamingEngineDate * p_DateEngine = p_ModelRemamingQueue -> getNthDateEngine(instanceNumber);
    assert(p_DateEngine != nullptr);
    p_DateEngine -> setRenamingEngineDateTryExtractDate(newValue);
}


// void Model::setRenamingEngineDateSetOriginalDateTaken(int instanceNumber, bool newValue) {
//     SPDLOG_INFO("Model::setRenamingEngineDateSetOriginalDateTaken");
//     p_ModelRenamingEngineDate -> setRenamingEngineDateSetOriginalDateTaken(newValue);
// }


void Model::setRenamingEngineDateUseOriginalDateTaken(int instanceNumber, bool state) {
    SPDLOG_INFO("Model::setRenamingEngineDateUseOriginalDateTaken");
    ModelRenamingEngineDate * p_DateEngine = p_ModelRemamingQueue -> getNthDateEngine(instanceNumber);
    assert(p_DateEngine != nullptr);
    p_DateEngine -> setRenamingEngineDateUseOriginalDateTaken(state);
}




//
// This block handles all the Textbody methods
//


void Model::setEngineTextBodyState(int instanceNumber, bool state) {
    SPDLOG_INFO("Model::setEngineTextBodyState: {}", instanceNumber);
    ModelRenamingEngineTextBody * p_TextBodyEngine = p_ModelRemamingQueue -> getNthTextbodyEngine(instanceNumber);
    assert(p_TextBodyEngine != nullptr);
    p_TextBodyEngine->setActive(state);
}

void Model::setRenamingEngineTextbody(int instanceNumber, string newText) {
    SPDLOG_INFO("Model::setRenamingEngineTextbody");
    ModelRenamingEngineTextBody * p_ModelRenamingEngineTextBody = p_ModelRemamingQueue -> getNthTextbodyEngine(instanceNumber);
    assert(p_ModelRenamingEngineTextBody != nullptr);
    p_ModelRenamingEngineTextBody -> setTextBody(newText);
}



//
// This block handles all the Counter methods
//


void Model::setEngineCounterState(int instanceNumber, bool state) {
    SPDLOG_INFO("Model::setEngineCounterSuffix: {}", instanceNumber);
    ModelRenamingEngineCounter * p_ModelRenamingEngineCounter = p_ModelRemamingQueue -> getNthCounterEngine(instanceNumber);
    assert(p_ModelRenamingEngineCounter != nullptr);
    p_ModelRenamingEngineCounter->setActive(state);
}


void Model::setCounterStart(int instanceNumber, int newValue) {
    SPDLOG_INFO("Model::setCounterStart");
    ModelRenamingEngineCounter * p_ModelRenamingEngineCounter = p_ModelRemamingQueue -> getNthCounterEngine(instanceNumber);
    assert(p_ModelRenamingEngineCounter != nullptr);
    p_ModelRenamingEngineCounter -> setCounter(newValue);
}


void Model::setCounterPadding(int instanceNumber, int newValue) {
    SPDLOG_INFO("Model::setCounterPadding");
    ModelRenamingEngineCounter * p_ModelRenamingEngineCounter = p_ModelRemamingQueue -> getNthCounterEngine(instanceNumber);
    assert(p_ModelRenamingEngineCounter != nullptr);
    p_ModelRenamingEngineCounter -> setPadding(newValue);
}



//
// This block handles all the Seperator methods
//


void Model::setEngineSeparatorState(int instanceNumber, bool state) {
    SPDLOG_INFO("Model::Model::setEngineSeparatorState: {}", instanceNumber);
    ModelRenamingEngineSeperator * p_ModelRenamingEngineSeperator = p_ModelRemamingQueue -> getNthSeperatorEngine(instanceNumber);
    assert(p_ModelRenamingEngineSeperator != nullptr);
    p_ModelRenamingEngineSeperator -> setActive(state);
}


void Model::setSeperator(int instanceNumber, string newValue) {
    SPDLOG_INFO("Model::setSeperator. Set separator instance {} to {}", instanceNumber, newValue);
    ModelRenamingEngineSeperator * p_ModelRenamingEngineSeperator = p_ModelRemamingQueue -> getNthSeperatorEngine(instanceNumber);
    assert(p_ModelRenamingEngineSeperator != nullptr);
    p_ModelRenamingEngineSeperator -> setSeperator(newValue);
}



