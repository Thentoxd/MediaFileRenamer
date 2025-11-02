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
    virtual time_t getCurrentDateTakenOriginal() = 0;
    virtual time_t getNewDateTakenOriginal() = 0;
    virtual void setFileName(string fileName) = 0;
    virtual void setNewFileName(string newFileName) = 0;
    virtual void setDateTaken(time_t dateTaken) = 0;
    virtual void setNewDateTaken(time_t newDateTaken) = 0;
};

class ModelInterface {
public:
    // virtual ~ModelInterface();

    virtual void setCurrentWorkingDirectory(string newCurrentWorkingDirectory) = 0;
    virtual string getCurrentWorkingDirectory() = 0;
    virtual void reload() = 0;
    virtual void clear() = 0;
    //...
};

#endif //MEDIAFILERENAMER_MODEL_INTERFACE_H