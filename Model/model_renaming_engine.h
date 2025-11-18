//
// Created by Alex Nicklin on 18/11/2025.
//

#ifndef MEDIAFILERENAMER_MODEL_RENAMING_ENGINE_H
#define MEDIAFILERENAMER_MODEL_RENAMING_ENGINE_H

#include <string>

using namespace std;

class ModelRenamingEngine {
public:
    virtual ~ModelRenamingEngine() = default;

    virtual void init(int mode) = 0;
    virtual void clear() = 0;

    virtual pair<string, string> execute(pair<string, string> input_parameter) = 0;

};

#endif //MEDIAFILERENAMER_MODEL_RENAMING_ENGINE_H