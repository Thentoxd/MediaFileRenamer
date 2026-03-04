//
// Created by Alex Nicklin on 29/10/2025.
//



#ifndef MEDIAFILERENAMER_MODEL_INTERFACE_H
#define MEDIAFILERENAMER_MODEL_INTERFACE_H

#include <string>
#include <vector>

#include "../main.h"  // To bring in the EngineTypes enum

using namespace std;

class FileEntryInterface {
public:
    // virtual ~FileEntryInterface();

    virtual string getCurrentFileName() = 0;
    virtual string getNewFileName() = 0;
    virtual string getCurrentDateTakenOriginal() = 0;
    virtual string getNewDateTakenOriginal() = 0;
    virtual void setFileName(string fileName) = 0;
    virtual void setNewFileName(string newFileName) = 0;
    virtual void setNewFileNameToCurrentFileName() = 0;
    virtual void setDateTaken(string dateTaken) = 0;
    virtual void setNewDateTaken(string newDateTaken) = 0;
};



class ModelInterface {
public:
    // virtual ~ModelInterface();

    virtual void setCurrentWorkingDirectory(string newCurrentWorkingDirectory) = 0;
    virtual string getCurrentWorkingDirectory() = 0;
    virtual void reload() = 0;
    virtual void clear() = 0;
    // virtual vector<FileEntryInterface>::iterator getTableDataIterator() = 0;
    virtual int getEntryCount() = 0;
    virtual FileEntryInterface * getFileEntry(int row) = 0;
    virtual void setFileTypesToParse(const vector<string> fileTypesToParse) = 0;
    virtual void setMediaFileRenamerVersion(const std::string_view version) = 0;

    // This function is handled by an aggregate class in the Model
    virtual vector<string> getFolderHistory() = 0;

    // We use this to get the saved/current renaming chain - we can then build to bottom of the
    // main window. We default to a 0,1,2,1,3 chain. Date/Seperator/FilenameBody/Seperator/Counter
    virtual vector<EngineTypes> getSavedEngineChain() = 0;

    virtual void setRenamingEngineDateSetYear(int instanceNumber, string newText) = 0;
    virtual void setRenamingEngineDateSetMonth(int instanceNumber, string newText) = 0;
    virtual void setRenamingEngineDateSetDay(int instanceNumber, string newText) = 0;
    virtual void setRenamingEngineDateTryExtractDate(int instanceNumber, bool newValue) = 0;

    // The controls to set the metadata have been moved out of the Date renaming engine.
    // virtual void setRenamingEngineDateSetOriginalDateTaken(int instanceNumber, bool newValue) = 0;
    virtual void setRenamingEngineDateUseOriginalDateTaken(int instanceNumber, bool newValue) = 0;

    // These are the new "set metadata" controls - these are hardcoded into the UI and not part of the renaming chain
    virtual void setMetadataOriginalTakenDateFromFilename() = 0;;
    virtual void setMetadataOriginalTakenDateFromUserGivenYearMonthDay(string param_year, string param_month, string param_day) = 0;;

    virtual void setRenamingEngineTextbody(int instanceNumber, string newText) = 0;

    virtual void setCounterStart(int instanceNumber, int newValue) = 0;
    virtual void setCounterPadding(int instanceNumber, int newValue) = 0;

    virtual void setSeperator(int instanceNumber, string newValue) = 0;

    virtual void exitApplication() = 0;

    virtual void clearRenamingChain() = 0;
    virtual vector<pair<string, string>> executeRenamingChain(vector<int> rows, bool renameFiles, bool renameDateTakenOriginal) = 0;
};

#endif //MEDIAFILERENAMER_MODEL_INTERFACE_H