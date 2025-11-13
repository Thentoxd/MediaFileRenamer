//
// Created by Alex Nicklin on 13/11/2025.
//

#ifndef MEDIAFILERENAMER_MEDIA_FILE_RENAMER_EXCEPTIONS_H
#define MEDIAFILERENAMER_MEDIA_FILE_RENAMER_EXCEPTIONS_H

#include <string>

using namespace std;

class media_file_renamer_exception : public std::exception
{
public:
    const char * what() {
        return "Custom C++ Exception";
    }
};

#endif //MEDIAFILERENAMER_MEDIA_FILE_RENAMER_EXCEPTIONS_H