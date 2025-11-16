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
    vector<std::string> file_history;
    vector<std::string> file_types_processed;

    public:

    void loadConfigFile(const string config_file_name_param);
    void saveConfigFile();

    void appendFileHistory(string new_directory_parameter);

    vector<std::string> getFileTypesProcessed();
    void reloadFileTypesProcessed();

    void updateLastDirectories();

};

#endif //MEDIAFILERENAMER_MODEL_CONFIGFILE_H