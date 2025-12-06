//
// Created by Alex Nicklin on 17/11/2025.
//

#ifndef MEDIAFILERENAMER_MODEL_RENAMING_ENGINE_DATE_H
#define MEDIAFILERENAMER_MODEL_RENAMING_ENGINE_DATE_H
#include <string>
#include <vector>

using namespace std;

#include "model_renaming_engine.h"

// This is the date renaming engine
// Inserts a date into the incoming filename to generate an outgoing filename (and/or new EXIF Date Taken (Original)

class ModelRenamingEngineDate : public ModelRenamingEngine {

private:
    bool tryToExtractDateFromInputFilename = false;

    string inputFilename = "";
    string inputDateCreatedOriginal = ""; // Format is a string: "YYYY:MM:DD HH:MM:SS" with the time shown in 24-hour format

    string outputFilename = "";
    string outputDateCreatedOriginal = "";

    string year;
    string month;
    string day;

    bool setDataTaken = false;

    char separator = ' ';

    string dateFormat = "YYYY-MM-DD";

    vector<string> formats;

public:
    ModelRenamingEngineDate();
    ~ModelRenamingEngineDate();

    void init(int mode) override;
    void clear() override;
    pair<string, string> execute(pair<string, string> input_parameter) override;

    void setRenamingEngineDateSetYear(string newValue);
    void setRenamingEngineDateSetMonth(string newValue);
    void setRenamingEngineDateSetDay(string newValue);
    void setFormats(vector<string> formats);

    void setRenamingEngineDateSetOriginalDateTaken(bool newValue);

    string patternToRegex(const string& pattern);
};

#endif //MEDIAFILERENAMER_MODEL_RENAMING_ENGINE_DATE_H