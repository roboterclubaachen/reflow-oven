#ifndef PROCESS_SCREEN_H
#define PROCESS_SCREEN_H

#pragma once

#include "lvgl/lvgl.h"
#include "utils/timer.hpp"

void drawProcessScreen();
void setTime(uint8_t uMinutes, uint8_t uSeconds);
void updateTime();
void setTemperature(uint16_t uTemp);


#endif //PROCESS_SCREEN_H
