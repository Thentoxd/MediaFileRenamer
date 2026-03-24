//
// Created by Surface on 13/03/2026.
//

#ifndef MEDIAFILERENAMER_MODEL_RENAMING_ENGINE_ADD_TEXT_H
#define MEDIAFILERENAMER_MODEL_RENAMING_ENGINE_ADD_TEXT_H
#include "model_renaming_engine.h"


class ModelRenamingEngineAddText : public ModelRenamingEngine {
private:
    int startingPosition = 1;
    string textToAdd = "";

public:
    ModelRenamingEngineAddText();
    ~ModelRenamingEngineAddText();

    void init(int mode) override;
    void clear() override;

    void setTextToAdd(string textToAdd);
    void setStartingPosition(int startingPosition);

    pair<string, string> execute(pair<string, string> input_parameter) override;

};


#endif //MEDIAFILERENAMER_MODEL_RENAMING_ENGINE_ADD_TEXT_H