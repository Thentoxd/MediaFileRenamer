//
// Created by Alex Nicklin on 22/10/2025.
//

#ifndef MEDIAFILERENAMER_MAIN_H
#define MEDIAFILERENAMER_MAIN_H

using namespace std;

#define MFR_VERSION "0.1"

#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#include "spdlog/spdlog.h"

// SPDLOG_TRACE("This is a trace level message");
// SPDLOG_DEBUG("This is a debug level message");
// SPDLOG_INFO("This is a info level message");
// SPDLOG_WARN("This is a warning level message");
// SPDLOG_ERROR("This is a error level message {}", 1);
// SPDLOG_CRITICAL("This is a critical level message");

enum EngineTypes {DateEngine, SeperatorEngine, FilenameBodyEngine, NumberingEngine};

#endif //MEDIAFILERENAMER_MAIN_H