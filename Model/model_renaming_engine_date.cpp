//
// Created by Alex Nicklin on 17/11/2025.
//

#include "model_renaming_engine_date.h"

#include <regex>

#include "../main.h"

ModelRenamingEngineDate::ModelRenamingEngineDate() {
    SPDLOG_INFO("ModelRenamingEngineDate::ModelRenamingEngineDate");
}


ModelRenamingEngineDate::~ModelRenamingEngineDate() {
    SPDLOG_INFO("ModelRenamingEngineDate::~ModelRenamingEngineDate");
}


void ModelRenamingEngineDate::init(int mode) {
    SPDLOG_INFO("ModelRenamingEngineDate::init");
}

string ModelRenamingEngineDate::patternToRegex(const string& pattern) {
    string regex;
    size_t n = pattern.size();
    for (size_t i = 0; i < n; ++i) {
        char c = pattern[i];
        int count = 1;

        while (i + 1 < n && pattern[i + 1] == c) {
            count++;
            i++;
        }

        if (c == 'Y' || c == 'M' || c == 'D') {
            regex += "\\d{" + to_string(count) + "}";
        }
        else {
            if (c == '.' || c == '^' || c == '$' || c == '*' || c == '+' ||
                c == '?' || c == '{' || c == '}' || c == '[' || c == ']' ||
                c == '\\' || c == '|' || c == '(' || c == ')') {
                regex += "\\";
                }
            regex += c;
        }
    }

    return regex;
}

pair<string, string> ModelRenamingEngineDate::execute(pair<string, string> input_parameter) {
    SPDLOG_INFO("ModelRemamingQueue::ModelRemamingQueue");
    // current file name, current date taken original
    string currentFileName = input_parameter.first;
    string day = "", month = "", year = "";


    // bool tryExtractDate = true;
    // bool useDataTaken = false; // If set
    // bool setDataTaken = false;

    for(string& it : formats) {
        bool found = false;
        string found_equivalent = "";
        regex regex_format(patternToRegex(it));
        smatch match;

        std::string::const_iterator searchStart(currentFileName.cbegin());
        while(regex_search(searchStart, currentFileName.cend(), match, regex_format)) {
            found = true;
            found_equivalent = match[0];
            break;
        }

        if(found) {
            for(int i = 0; i < it.size(); i++) {
                if(it[i] == 'Y') {
                    year.push_back(found_equivalent[i]);
                } else if(it[i] == 'M') {
                    month.push_back(found_equivalent[i]);
                } else if(it[i] == 'D') {
                    day.push_back(found_equivalent[i]);
                }
            }

            break;
        }
    }


    if(!this->year.empty()) {
        year = this->year;
    } else if(!this->month.empty()) {
        month = this->month;
    } else if(!this->day.empty()) {
        day = this->day;
    }

    int day_int = 0, month_int = 0;

    if(!day.empty()) {
        day_int = stoi(day);
    }

    if(!month.empty()) {
        month_int = stoi(month);
    }

    string return_string = year + "-" + month + "-" + day;

    if(day_int > 31 || day_int < 1) {
        SPDLOG_ERROR("Rejected inputted day");
        day = "00";
        return_string = "";
    }
    if(month_int > 12 || month_int < 1) {
        SPDLOG_ERROR("Rejected inputted month");
        month = "00";
        return_string = "";
    }

    SPDLOG_DEBUG("{}-{}-{}", year, month, day);

    string newDateTakenOriginal = input_parameter.second;
    // Do we need to set the Create Date Taken (Original)?
    if (setDataTaken) {
        SPDLOG_DEBUG("Need to set the Create Date Taken (Original)");
        string currentDateTakenOriginal = input_parameter.second;

        SPDLOG_DEBUG("Current Create Date Taken (Original): {}", currentDateTakenOriginal);
        if (currentDateTakenOriginal.empty()) {
            newDateTakenOriginal = year + ":" + month + ":" + day + " 12:00:00";
        }
    }

    return make_pair(return_string, newDateTakenOriginal);
}


void ModelRenamingEngineDate::setFormats(vector<string> formats) {
    for(string& it : formats) {
        this->formats.push_back(it);
    }
}


void ModelRenamingEngineDate::setRenamingEngineDateSetYear(string newValue) {
    SPDLOG_INFO("ModelRenamingEngineDate::setRenamingEngineDateSetYear. Set year to {}", newValue);
    year = newValue;
}


void ModelRenamingEngineDate::setRenamingEngineDateSetMonth(string newValue) {
    SPDLOG_INFO("ModelRenamingEngineDate::setRenamingEngineDateSetMonth. Set month to {}", newValue);
    month = newValue;
}


void ModelRenamingEngineDate::setRenamingEngineDateSetDay(string newValue) {
    SPDLOG_INFO("ModelRenamingEngineDate::setRenamingEngineDateSetDay. Set day to {}", newValue);
    day = newValue;
}


void ModelRenamingEngineDate::clear() {
    SPDLOG_INFO("ModelRenamingEngineDate::clear");
}

void ModelRenamingEngineDate::setRenamingEngineDateTryExtractDate(bool newValue) {
    SPDLOG_INFO("setRenamingEngineDateTryExtractDate to {}", newValue);
    tryExtractDate = newValue;
}


void ModelRenamingEngineDate::setRenamingEngineDateSetOriginalDateTaken(bool newValue) {
    SPDLOG_INFO("setRenamingEngineDateSetOriginalDateTaken to {}", newValue);
    setDataTaken = newValue;
}

void ModelRenamingEngineDate::setRenamingEngineDateUseOriginalDateTaken(bool newValue) {
    SPDLOG_INFO("setRenamingEngineDateUseOriginalDateTaken to {}", newValue);
    useDataTaken = newValue;
}