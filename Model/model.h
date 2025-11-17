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
    vector<FileEntry> fileEntries;

    ModelConfigfile * p_ModelConfigfile;

    ModelRemamingQueue * renaming_queue;

public:
    Model();

    void initialise(ModelConfigfile * parameter_ModelConfigfile);
    void renameEXIFFile(FileEntry* newFile);
    void setCurrentWorkingDirectory(string newCurrentWorkingDirectory) override;
    string getCurrentWorkingDirectory() override;
    void reload() override ;
    void clear() override ;

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

    void setFileTypesToParse(const vector<string> fileTypesToParse) override;

    void setMediaFileRenamerVersion(const std::string_view) override;

    vector<string> getFolderHistory() override;

};


#endif //MEDIAFILERENAMER_MODEL_H