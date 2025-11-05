//
// Created by Alex Nicklin on 22/10/2025.
//

#ifndef MEDIAFILERENAMER_MODEL_H
#define MEDIAFILERENAMER_MODEL_H

#include <ctime>
#include <vector>

#include "../model_interface.h"

using namespace std;

class FileEntry : public FileEntryInterface {

    private:
    string currentFileName;
    string newFileName;
    time_t currentDateTakenOriginal{};
    time_t newDateTakenOriginal{};

public:
    FileEntry(string fileName, time_t currentDateTakenOriginal) {
        this->currentFileName = fileName;
        this->newFileName = fileName;
        this->currentDateTakenOriginal = currentDateTakenOriginal;
        this->newDateTakenOriginal = currentDateTakenOriginal;
    }

    FileEntry() {};

    string getCurrentFileName() override {
        return currentFileName;
    }
    string getNewFileName() override {
        return newFileName;
    }
    time_t getCurrentDateTakenOriginal() override {
        return currentDateTakenOriginal;
    }
    time_t getNewDateTakenOriginal() override {
        return newDateTakenOriginal;
    }

    void setFileName(string fileName) override {
        currentFileName = fileName;
        newFileName = fileName;
    }

    void setNewFileName(string newFileName) override {
        this->newFileName = newFileName;
    }

    void setDateTaken(time_t dateTaken) override {
        currentDateTakenOriginal = dateTaken;
        newDateTakenOriginal = dateTaken;
    }

    void setNewDateTaken(time_t newDateTaken) override {
        newDateTakenOriginal = newDateTaken;
    }
};


class Model : public ModelInterface {

private:
    string currentWorkingDirectory;
    vector<FileEntry> fileEntries;

public:
    Model();

    void setCurrentWorkingDirectory(string newCurrentWorkingDirectory) override;
    string getCurrentWorkingDirectory() override;
    void reload() override ;
    void clear() override ;

    FileEntry * getFileEntry(int row) override {
        FileEntry * p_entry = &fileEntries[row - 1];
        return p_entry;
    }

    // This function should do
    // return fileEntries.iterator();
    // This function should do
    // return fileEntries.iterator();
    //virtual vector<FileEntryInterface>::iterator getTableDataIterator() {
    //    return fileEntries.begin();
    //}


    void addEntry(string fileName, time_t currentDateTakenOriginal) {
        FileEntry newFileEntry(fileName, currentDateTakenOriginal);
        fileEntries.push_back(newFileEntry);
    }
    void addEntry(FileEntry entry, int row) {
        fileEntries.insert(fileEntries.begin() + row - 1, entry);
    }

    void removeBackEntry() {
        fileEntries.pop_back();
    }

    void removeEntry(int row) {
        fileEntries.erase(fileEntries.begin() + row - 1);
    }

    int getEntryCount() {
        return fileEntries.size();
    }



};


#endif //MEDIAFILERENAMER_MODEL_H