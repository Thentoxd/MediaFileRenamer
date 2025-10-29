//
// Created by Alex Nicklin on 22/10/2025.
//

#ifndef MEDIAFILERENAMER_MODEL_H
#define MEDIAFILERENAMER_MODEL_H

#include "../model_interface.h"

class Model : public ModelInterface {
    public:
        Model();
        void updateCurrentWorkingDirectory(string newCurrentWorkingDirectory);
        void reload();
        void clear();
};


#endif //MEDIAFILERENAMER_MODEL_H