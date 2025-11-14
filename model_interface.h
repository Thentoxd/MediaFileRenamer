//
// Created by Alex Nicklin on 29/10/2025.
//



#ifndef MEDIAFILERENAMER_MODEL_INTERFACE_H
#define MEDIAFILERENAMER_MODEL_INTERFACE_H

#include <string>
#include <vector>

using namespace std;

class FileEntryInterface {
public:
    // virtual ~FileEntryInterface();

    virtual string getCurrentFileName() = 0;
    virtual string getNewFileName() = 0;
    virtual string getCurrentDateTakenOriginal() = 0;
    virtual string getNewDateTakenOriginal() = 0;
    virtual void setFileName(string fileName) = 0;
    virtual void setNewFileName(string newFileName) = 0;
    virtual void setDateTaken(string dateTaken) = 0;
    virtual void setNewDateTaken(string newDateTaken) = 0;
};

class ModelInterface {
public:
    // virtual ~ModelInterface();

    virtual void setCurrentWorkingDirectory(string newCurrentWorkingDirectory) = 0;
    virtual string getCurrentWorkingDirectory() = 0;
    virtual void reload() = 0;
    virtual void clear() = 0;
    // virtual vector<FileEntryInterface>::iterator getTableDataIterator() = 0;
    virtual int getEntryCount() = 0;
    virtual FileEntryInterface * getFileEntry(int row) = 0;
    virtual void setFileTypesToParse(const vector<string> fileTypesToParse) = 0;
    virtual void setMediaFileRenamerVersion(const std::string_view version) = 0;

    virtual vector<string> getFolderHistory() = 0;
    //...
};

#endif //MEDIAFILERENAMER_MODEL_INTERFACE_H