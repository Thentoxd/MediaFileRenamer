//
// Created by Alex Nicklin on 16/11/2025.
//

#ifndef MEDIAFILERENAMER_MODEL_CONFIGFILE_H
#define MEDIAFILERENAMER_MODEL_CONFIGFILE_H

using namespace std;

#include <nlohmann/json.hpp>
using json = nlohmann::json;

class ModelConfigfile {

    protected:

    json json_data_from_file;

    string current_working_directory;
    string config_file_name;
    vector<string> file_history;
    vector<string> file_types_processed;
    vector<string> date_formats_parsed;

    public:

    void loadConfigFile(const string config_file_name_param);
    void saveConfigFile();

    void appendFileHistory(string new_directory_parameter);

    vector<std::string> getFileTypesProcessed();
    vector<std::string> getDateFormatsParsed();

    void reloadFileTypesProcessed();

    void updateLastDirectories();

    vector<string> getFolderHistory();

    string getCurrentWorkingDirectory();

};

#endif //MEDIAFILERENAMER_MODEL_CONFIGFILE_H