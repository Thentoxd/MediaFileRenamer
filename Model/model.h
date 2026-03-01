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

    string separatorA = " ";
    string separatorB = " ";

    ModelConfigfile * p_ModelConfigfile;
    ModelRemamingQueue * p_ModelRemamingQueue;

    // In the old model, we had just three renaming engines in a fixed formation in the queue

    ModelRenamingEngineDate * p_ModelRenamingEngineDate;
    ModelRenamingEngineTextBody * p_ModelRenamingEngineTextBody;
    ModelRenamingEngineCounter * p_ModelRenamingEngineCounter;

public:
    Model();

    void initialise();
    void renameEXIFFile(FileEntry* newFile);
    void changeEXIFDateTakenOriginal(FileEntry* file);
    void setCurrentWorkingDirectory(string newCurrentWorkingDirectory) override;

    void reload() override ;
    void clear() override ;
    void resetToDefaultButtonClicked();

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

    void setRenamingEngineTextbody(int instanceNumber, string newText) override;

    void setCounterStart(int instanceNumber, int newValue) override;
    void setCounterPadding(int instanceNumber, int newValue) override;


    void setDateFormat(string format);
    string getDateFormat();
    void setRenamingEngineDateSetYear(int instanceNumber, string newText) override;
    void setRenamingEngineDateSetMonth(int instanceNumber, string newText) override;
    void setRenamingEngineDateSetDay(int instanceNumber, string newText) override;

    void setRenamingEngineDateTryExtractDate(int instanceNumber, bool newValue) override;
    void setRenamingEngineDateSetOriginalDateTaken(int instanceNumber, bool newValue) override;
    void setRenamingEngineDateUseOriginalDateTaken(int instanceNumber, bool newValue) override;

    void setSeperator(int instanceNumber, string newValue) override;

    vector<EngineTypes> getSavedEngineChain() override;

    void exitApplication() override;

    void clearRenamingChain() override;
    vector<pair<string, string>> executeRenamingChain(vector<int> row, bool renameFiles, bool renameDateTakenOriginal) override;
};


#endif //MEDIAFILERENAMER_MODEL_H