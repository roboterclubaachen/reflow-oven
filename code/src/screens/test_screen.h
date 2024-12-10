#ifndef TEST_SCREEN_H
#define TEST_SCREEN_H

#pragma once

#include <lvgl/lvgl.h>

void drawTestScreen(void);
void setLblText(void);
void setTouchText(int16_t x, int16_t y, int16_t rawX, int16_t rawY);


#endif //TEST_SCREEN_H