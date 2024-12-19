#ifndef PROFILE_SELECT_SCREEN_H
#define PROFILE_SELECT_SCREEN_H

#pragma once

#include <modm/container/dynamic_array.hpp>
#include <lvgl/lvgl.h>

#include "../utils/profile.hpp"

class profile_select_screen
{
public:
    profile_select_screen();
    profile_select_screen(size_t size);
    ~profile_select_screen();

private:
    modm::DynamicArray<Profile> p_profiles;

    lv_obj_t* lbl_Name;
    lv_obj_t* chrt_Preview;
    lv_obj_t* flex_container;
};

#endif