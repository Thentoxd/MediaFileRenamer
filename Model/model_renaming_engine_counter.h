//
// Created by Alex Nicklin on 18/11/2025.
//

#ifndef MEDIAFILERENAMER_MODEL_RENAMING_ENGINE_COUNTER_H
#define MEDIAFILERENAMER_MODEL_RENAMING_ENGINE_COUNTER_H
#include <string>

using namespace std;

#include "../main.h"

#include "model_renaming_engine.h"

// This is the date renaming engine
// Inserts a date into the incoming filename to generate an outgoing filename (and/or new EXIF Date Taken (Original)

class ModelRenamingEngineCounter : public ModelRenamingEngine {

private:
    int counter = 1;
    int counterStart = 1;
    int padding = 1;
    int paddingStart = 1;

    bool usingCounterEngine = false;

public:
    ModelRenamingEngineCounter();
    ~ModelRenamingEngineCounter();

    void setCounter(int value);
    void setPadding(int value);

    void clear() override;
    void init(int mode) override;
    void setUsingCounterEngine(bool value);
    pair<string, string> execute(pair<string, string> input_parameter) override;
};

#endif //MEDIAFILERENAMER_MODEL_RENAMING_ENGINE_COUNTER_H