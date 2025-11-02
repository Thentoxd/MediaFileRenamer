//
// Created by Alex Nicklin on 22/10/2025.
//

#ifndef MEDIAFILERENAMER_MODEL_H
#define MEDIAFILERENAMER_MODEL_H

#include <ctime>

#include "../model_interface.h"

class FileEntry {

    private:
    string currentFileName;
    string newFileName;
    time_t currentDateTakenOriginal;
    time_t newDateTakenOriginal;
    string deleteme;


};

class FileEntries {

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