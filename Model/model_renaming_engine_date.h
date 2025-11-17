//
// Created by Alex Nicklin on 17/11/2025.
//

#ifndef MEDIAFILERENAMER_MODEL_RENAMING_ENGINE_DATE_H
#define MEDIAFILERENAMER_MODEL_RENAMING_ENGINE_DATE_H
#include <string>

using namespace std;

// This is the date renaming engine
// Inserts a date into the incoming filename to generate an outgoing filename (and/or new EXIF Date Taken (Original)

class ModelRenamingEngineDate {

private:
    bool tryToExtractDateFromInputFilename = false;

    string inputFilename = "";
    string inputDateCreatedOriginal = ""; // Format is a string: "YYYY:MM:DD HH:MM:SS" with the time shown in 24-hour format

    string outputFilename = "";
    string outputDateCreatedOriginal = "";

    char separator = ' ';

    string dateFormat = "YYYY-MM-DD";

public:
    ModelRenamingEngineDate();
    ~ModelRenamingEngineDate();

    void init(int mode);

    pair<string, string> execute(pair<string, string> input_parameter);
};

#endif //MEDIAFILERENAMER_MODEL_RENAMING_ENGINE_DATE_H