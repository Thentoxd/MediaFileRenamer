//
// Created by Alex Nicklin on 18/11/2025.
//

#ifndef MEDIAFILERENAMER_MODEL_RENAMING_ENGINE_H
#define MEDIAFILERENAMER_MODEL_RENAMING_ENGINE_H

#include <string>
#include "../main.h"

using namespace std;

class ModelRenamingEngine {
private:
    bool EngineActive = true;

public:
    virtual ~ModelRenamingEngine() = default;

    virtual void init(int mode) = 0;
    virtual void clear() = 0;

    virtual void setActive(bool state) {
        SPDLOG_INFO("ModelRenamingEngine::setActive to {}", state);
        EngineActive = state;
    }

    virtual bool isActive() {
        SPDLOG_INFO("ModelRenamingEngine::isActive. Returning {}");
        return EngineActive;
    }

    virtual pair<string, string> execute(pair<string, string> input_parameter) = 0;

};

#endif //MEDIAFILERENAMER_MODEL_RENAMING_ENGINE_H