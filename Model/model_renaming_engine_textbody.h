//
// Created by Alex Nicklin on 18/11/2025.
//

#ifndef MEDIAFILERENAMER_MODEL_RENAMING_ENGINE_TEXTBODY_H
#define MEDIAFILERENAMER_MODEL_RENAMING_ENGINE_TEXTBODY_H

#include <string>

using namespace std;

#include "../main.h"

#include "model_renaming_engine.h"

// This is the date renaming engine
// Inserts a date into the incoming filename to generate an outgoing filename (and/or new EXIF Date Taken (Original)

class ModelRenamingEngineTextBody : public ModelRenamingEngine {

private:
    string textbody;

public:
    ModelRenamingEngineTextBody();
    ~ModelRenamingEngineTextBody();

    void clear() override;
    void init(int mode) override;
    pair<string, string> execute(pair<string, string> input_parameter) override;
};

#endif //MEDIAFILERENAMER_MODEL_RENAMING_ENGINE_TEXTBODY_H