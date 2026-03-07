//
// Created by Alex Nicklin on 22/10/2025.
//

#ifndef MEDIAFILERENAMER_MODEL_H
#define MEDIAFILERENAMER_MODEL_H

#include <vector>

using namespace std;

#include "../model_interface.h"
#include "model_configfile.h"
#include "model_remaming_queue.h"
#include "model_renaming_engine_counter.h"
#include "model_renaming_engine_textbody.h"


class FileEntry : public FileEntryInterface {

    private:
    string currentFileName;
    string newFileName;
    string currentDateTakenOriginal;
    string newDateTakenOriginal;

public:
    FileEntry(string fileName, string currentDateTakenOriginal) {
        this->currentFileName = fileName;
        this->newFileName = fileName;
        this->currentDateTakenOriginal = currentDateTakenOriginal;
        this->newDateTakenOriginal = currentDateTakenOriginal;
    }

    string getCurrentFileName() override {
        return currentFileName;
    }
    string getNewFileName() override {
        return newFileName;
    }
    string getCurrentDateTakenOriginal() override {
        return currentDateTakenOriginal;
    }
    string getNewDateTakenOriginal() override {
        return newDateTakenOriginal;
    }

    void setFileName(string fileName) override {
        currentFileName = fileName;
        newFileName = fileName;
    }

    void setNewFileName(string newFileName) override {
        this->newFileName = newFileName;
    }

    void setNewFileNameToCurrentFileName() {
        this->newFileName = currentFileName;
    }

    void setDateTaken(string dateTaken) override {
        currentDateTakenOriginal = dateTaken;
        newDateTakenOriginal = dateTaken;
    }

    void setNewDateTaken(string newDateTaken) override {
        newDateTakenOriginal = newDateTaken;
    }
};


class Model : public ModelInterface {

private:
    string mediaFileRenamerVersion;
    string currentWorkingDirectory;
    string dateFormat = "YYYY-MM-DD";
    vector<FileEntry> fileEntries;

    ModelConfigfile * p_ModelConfigfile;
    ModelRemamingQueue * p_ModelRemamingQueue;

    vector<string> date_formats_parsed;

    // When setting metadata, we run in one of two modes
    // If this is true, we parse the resulting filename for the Metadata Create Date (Original)
    bool parseResultFilenameForMetadataCreateDateOriginal;
    // If this is true, we use the Year, Month, Date given
    bool setMetadataCreateDateOriginalFromGivenValues;
    string metadataYear;
    string metadataMonth;
    string metadataDay;


public:
    Model();

    void initialise();
    void renameEXIFFile(FileEntry* newFile);
    void changeEXIFDateTakenOriginal(FileEntry* file);
    void setCurrentWorkingDirectory(string newCurrentWorkingDirectory) override;


    // virtual void setEngineDateState(int instanceNumber, bool state) = 0;
    // virtual void setRenamingEngineDateSetYear(int instanceNumber, string newText) = 0;
    // virtual void setRenamingEngineDateSetMonth(int instanceNumber, string newText) = 0;
    // virtual void setRenamingEngineDateSetDay(int instanceNumber, string newText) = 0;
    // virtual void setRenamingEngineDateTryExtractDate(int instanceNumber, bool newValue) = 0;
    // virtual void setRenamingEngineDateUseOriginalDateTaken(int instanceNumber, bool newValue) = 0;


    // This block defines the interfaces for the Date engines
    void setEngineDateState(int instanceNumber, bool state) override;
    void setRenamingEngineDateSetYearMonthDay(int instanceNumber, string param_Year, string param_Month, string Param_Day) override;
    void setRenamingEngineDateTryExtractDate(int instanceNumber, bool newValue) override;
    void setRenamingEngineDateUseOriginalDateTaken(int instanceNumber, bool state) override;


    // This block defines the interfaces for the Textbody engines
    void setEngineTextBodyState(int instanceNumber, bool state) override;
    void setRenamingEngineTextbody(int instanceNumber, string newText) override;


    // This block defines the interfaces for the Counter engines
    void setEngineCounterState(int instanceNumber, bool state) override;
    void setCounterStart(int instanceNumber, int newValue) override;
    void setCounterPadding(int instanceNumber, int newValue) override;


    // This block defines the interfaces for the Seperator engines
    void setEngineSeparatorState(int instanceNumber, bool state) override;
    void setSeperator(int instanceNumber, string newValue) override;



    void reload() override ;
    void clear() override ;
    void resetToDefaultButtonClicked();
    void resetRenamingChain();

    FileEntry * getFileEntry(int row) override {
        FileEntry * p_entry = &fileEntries[row];
        return p_entry;
    }

    // This function should do
    // return fileEntries.iterator();
    // This function should do
    // return fileEntries.iterator();
    //virtual vector<FileEntryInterface>::iterator getTableDataIterator() {
    //    return fileEntries.begin();
    //}


    void addEntry(string fileName, string currentDateTakenOriginal) {
        FileEntry newFileEntry(fileName, currentDateTakenOriginal);
        fileEntries.push_back(newFileEntry);
    }
    void addEntry(FileEntry entry, int row) {
        fileEntries.insert(fileEntries.begin() + row, entry);
    }

    void removeBackEntry() {
        fileEntries.pop_back();
    }

    void removeEntry(int row) {
        fileEntries.erase(fileEntries.begin() + row);
    }

    int getEntryCount() {
        return fileEntries.size();
    }

    void updateCurrentWorkingDirectory(string newDirectory) {
        currentWorkingDirectory = newDirectory;
    }

    string getCurrentWorkingDirectory() {
        return currentWorkingDirectory;
    }

    void setFileTypesToParse(const vector<string> fileTypesToParse) override;

    void setMediaFileRenamerVersion(const std::string_view) override;

    vector<string> getFolderHistory() override;



    void setDateFormat(string format);
    string getDateFormat();

    // void setRenamingEngineDateSetOriginalDateTaken(int instanceNumber, bool newValue) override;
    void setMetadataOriginalTakenDateFromFilename(bool state) override;
    void setMetadataOriginalTakenDateFromUserGivenYearMonthDay(bool state, string param_year, string param_month, string param_day) override;



    vector<EngineTypes> getSavedEngineChain() override;

    void exitApplication() override;

    void clearRenamingChain() override;
    vector<pair<string, string>> executeRenamingChain(vector<int> row, bool renameFiles, bool renameDateTakenOriginal) override;
    void emptyRenamningChainAndRebuild(vector<EngineTypes> newChain) override;
};


#endif //MEDIAFILERENAMER_MODEL_H