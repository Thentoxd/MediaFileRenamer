//
// Created by Alex Nicklin on 17/11/2025.
//

#ifndef MEDIAFILERENAMER_MODEL_REMAMING_QUEUE_H
#define MEDIAFILERENAMER_MODEL_REMAMING_QUEUE_H

#include <vector>

// This class models a chain of renaming engines. Each renaming engine specialises in one type of function (extracting or generating a date for example).
// A new filename and EXIF Date Take (Original) is generated from passing the original filename and EXIF Date Take (Original) though a chain
// of these renaming engines.

// In the basic modes, we have a few fixed chains. The user can customise the individual engines, but not the sequence or seperator.
// In a later advanced mode, the end user can custom create a chain

#include "model_renaming_engine_date.h"
#include "model_renaming_engine_counter.h"
#include "model_renaming_engine_textbody.h"

class ModelRemamingQueue {
private:

    int mode; // This is a first default chain. A date-seperator-text-seperator-number" filename

    vector<ModelRenamingEngine *> renaming_engine;

public:

    ModelRemamingQueue();
    ~ModelRemamingQueue();

    void init(int mode, ModelRenamingEngineDate * p_ModelRenamingEngineDate, ModelRenamingEngineTextBody * p_ModelRenamingEngineTextBody, ModelRenamingEngineCounter * p_ModelRenamingEngineCounter);
    void clear();

    pair<string, string> executeQueue(const pair<string, string>& input_parameter, vector<string> separators);

};

#endif //MEDIAFILERENAMER_MODEL_REMAMING_QUEUE_H