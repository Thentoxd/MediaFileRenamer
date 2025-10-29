//
// Created by Alex Nicklin on 22/10/2025.
//

#ifndef MEDIAFILERENAMER_CONTROLLER_H
#define MEDIAFILERENAMER_CONTROLLER_H

#include "../controller_interface.h"
#include "../model_interface.h"
#include "../View/view.h"
#include "../main.h"

class Controller : public ControllerInterface {

    const ModelInterface * p_mfrModel;
    const mediaFileRenamerMainView * p_mfrView;

    public:
        Controller(const ModelInterface * mfrModel, const mediaFileRenamerMainView * mfrView):
            p_mfrModel(mfrModel), p_mfrView(mfrView) {
            SPDLOG_INFO("Initialising Controller ....");
        }
};


#endif //MEDIAFILERENAMER_CONTROLLER_H