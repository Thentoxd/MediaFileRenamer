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
    string inputFilename = "";
    string inputDateCreatedOriginal = ""; // Format is a string: "YYYY:MM:DD HH:MM:SS" with the time shown in 24-hour format

    string outputFilename = "";
    string outputDateCreatedOriginal = "";

    string year;
    string month;
    string day;

    bool tryExtractDate = true;
    // bool setDateTaken = false;
    bool useDateTaken = false;
    bool useGivenYearMonthDay = false;

    char separator = ' ';

    string dateFormat = "YYYY-MM-DD";

    vector<string> formats;

public:
    ModelRenamingEngineDate();
    ~ModelRenamingEngineDate();

    void init(int mode) override;
    void clear() override;
    pair<string, string> execute(pair<string, string> input_parameter) override;


    void setFormats(vector<string> formats);


    // void setRenamingEngineDateSetYear(string newValue);
    // void setRenamingEngineDateSetMonth(string newValue);
    // void setRenamingEngineDateSetDay(string newValue);
    void setRenamingEngineDateSetYearMonthDay(int instanceNumber, string param_Year, string param_Month, string Param_Day);
    void setRenamingEngineDateTryExtractDate(bool newValue);
    // void setRenamingEngineDateSetOriginalDateTaken(bool newValue);
    void setRenamingEngineDateUseOriginalDateTaken(bool newValue);

    string patternToRegex(const string& pattern);
};

#endif //MEDIAFILERENAMER_MODEL_RENAMING_ENGINE_DATE_H