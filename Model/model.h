//
// Created by Alex Nicklin on 22/10/2025.
//

#ifndef MEDIAFILERENAMER_MODEL_H
#define MEDIAFILERENAMER_MODEL_H

#include <ctime>
#include <vector>

#include "../model_interface.h"

namespace std {
    class any;
}

class FileEntry {

    private:
    string currentFileName;
    string newFileName;
    time_t currentDateTakenOriginal;
    time_t newDateTakenOriginal;

public:
    FileEntry(string fileName, time_t currentDateTakenOriginal) {
        this->currentFileName = fileName;
        this->newFileName = fileName;
        this->currentDateTakenOriginal = currentDateTakenOriginal;
        this->newDateTakenOriginal = currentDateTakenOriginal;
    }

    string getCurrentFileName() {
        return currentFileName;
    }
    string getNewFileName() {
        return newFileName;
    }
    time_t getCurrentDateTakenOriginal() {
        return currentDateTakenOriginal;
    }
    time_t getNewDateTakenOriginal() {
        return newDateTakenOriginal;
    }

    void setFileName(string fileName) {
        currentFileName = fileName;
        newFileName = fileName;
    }

    void setNewFileName(string newFileName) {
        this->newFileName = newFileName;
    }

    void setDateTaken(time_t dateTaken) {
        currentDateTakenOriginal = dateTaken;
        newDateTakenOriginal = dateTaken;
    }

    void setNewDateTaken(time_t newDateTaken) {
        newDateTakenOriginal = newDateTaken;
    }
};

class FileEntries {
    vector<FileEntry> fileEntries;

public:

    void populateTable(const vector<pair<string, time_t>>& values) {
       for (const auto& value : values) {
           fileEntries.emplace_back(value.first, value.second);
       }
    }

    void addEntry(FileEntry entry) {
        fileEntries.push_back(entry);
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

    FileEntry getFileEntry(int row) {
        return fileEntries[row - 1];
    }


};

class Model : public ModelInterface {

    private:
        string currentWorkingDirectory;

    public:
        Model();
        void setCurrentWorkingDirectory(string newCurrentWorkingDirectory);
        string getCurrentWorkingDirectory();
        void reload();
        void clear();
};


#endif //MEDIAFILERENAMER_MODEL_H