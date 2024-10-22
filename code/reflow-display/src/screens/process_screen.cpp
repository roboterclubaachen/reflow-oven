#include "process_screen.h"


ProcScreen::ProcScreen(uint16_t iSeconds) :
    procTimer(iSeconds),
    chart(*lv_obj_create(&scr)),
    lbl_time(*lv_obj_create(&scr))
{}


void ProcScreen::initProcScreen()
{
    // Set screen size
    lv_obj_set_size(&scr, LV_HOR_RES, LV_VER_RES);
    lv_obj_center(&scr);
    /*Create a chart*/
    chart = *lv_chart_create(&scr);
    lv_obj_set_size(&chart, 200, 150);
    lv_obj_center(&chart);
    lv_chart_set_type(&chart, LV_CHART_TYPE_LINE);   /*Show lines and points too*/
    //Tick marks
    lv_chart_set_range(&chart, LV_CHART_AXIS_PRIMARY_Y, 0, 300);
    lv_chart_set_axis_tick(&chart, LV_CHART_AXIS_PRIMARY_Y, 10, 5, 6, 2, true, 50);

    /*Add two data series*/
    lv_chart_series_t * data = lv_chart_add_series(&chart, lv_palette_main(LV_PALETTE_RED), LV_CHART_AXIS_PRIMARY_Y);

    lv_chart_set_next_value(&chart, data, 20);
    lv_chart_set_next_value(&chart, data, 15);
    lv_chart_set_next_value(&chart, data, 15);
    lv_chart_set_next_value(&chart, data, 30);
}