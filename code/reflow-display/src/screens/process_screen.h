#ifndef PROCESS_SCREEN_H
#define PROCESS_SCREEN_H


#include <modm/ui/gui/view.hpp>
#include <lvgl/lvgl.h>

#include "../utils/timer.hpp"


class ProcScreen
{
    private:
    timer procTimer;
    lv_obj_t scr = *lv_obj_create(NULL);
    lv_obj_t chart;
    lv_obj_t lbl_time;
    public:

    ProcScreen(u_int16_t iSeconds);
    virtual ~ProcScreen() = default;

    void initProcScreen();

    lv_obj_t* getScreen() {return &scr;};

};

#endif //PROCESS_SCREEN_H