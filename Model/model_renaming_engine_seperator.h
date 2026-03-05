//
// Created by Alex Nicklin on 28/02/2026.
//

#ifndef MEDIAFILERENAMER_MODEL_RENAMING_ENGINE_SEPERATOR_H
#define MEDIAFILERENAMER_MODEL_RENAMING_ENGINE_SEPERATOR_H


#include <string>

using namespace std;

#include "../main.h"

#include "model_renaming_engine.h"

// This is the date renaming engine
// Inserts a date into the incoming filename to generate an outgoing filename (and/or new EXIF Date Taken (Original)

class ModelRenamingEngineSeperator : public ModelRenamingEngine {

private:
    string textbody;

public:
    ModelRenamingEngineSeperator();
    ~ModelRenamingEngineSeperator();

    void clear() override;
    void init(int mode) override;

    void setSeperator(string newValue);

    pair<string, string> execute(pair<string, string> input_parameter) override;
};


#endif //MEDIAFILERENAMER_MODEL_RENAMING_ENGINE_SEPERATOR_H