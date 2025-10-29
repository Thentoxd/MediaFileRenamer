//
// Created by Alex Nicklin on 29/10/2025.
//



#ifndef MEDIAFILERENAMER_MODEL_INTERFACE_H
#define MEDIAFILERENAMER_MODEL_INTERFACE_H

#include <string>
using namespace std;

class ModelInterface {
public:
    virtual ~ModelInterface();
    virtual void updateCurrentWorkingDirectory(string newCurrentWorkingDirectory) = 0;
    virtual void reload() = 0;
    virtual void clear() = 0;
    //...
};

#endif //MEDIAFILERENAMER_MODEL_INTERFACE_H