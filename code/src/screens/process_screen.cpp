#include "process_screen.h"

static lv_obj_t* scr;
static lv_obj_t* chart;
static lv_obj_t* lbl_time;
static lv_obj_t* lbl_temperature;
static lv_obj_t* btn_stop;

Timer remainingTime(0, 0);

void setTime(uint8_t uMinutes, uint8_t uSeconds)
{
    remainingTime.setMinutes(uMinutes);
    remainingTime.setSeconds(uSeconds);

    lv_label_set_text_fmt(lbl_time, "%u:%u", uMinutes, uSeconds);
}

/**
 * @brief Counts down the timer and displays on screen
 * 
 */
void updateTime()
{
    remainingTime.countDown();
    lv_label_set_text_fmt(lbl_time, "%u:%u", remainingTime.getMinutes(), remainingTime.getSeconds());
}

void setTemperature(uint16_t uTemp)
{
    lv_label_set_text_fmt(lbl_temperature, "%u°C", uTemp);
}

void stop_button_callback(lv_event_t* e)
{
    // Handle stop button press
    // TODO: Implement stop functionality
}

void drawProcessScreen()
{
    // Create a new screen
    scr = lv_obj_create(NULL);
    lv_obj_set_size(scr, lv_pct(100), lv_pct(100));
    lv_obj_center(scr);

    // Load the screen
    lv_scr_load(scr);

    // Create a time label container directly on the screen
    lv_obj_t* label_container = lv_obj_create(scr);
    // Adjust position and size
    lv_obj_set_size(label_container, 100, 100);
    lv_obj_align(label_container, LV_ALIGN_TOP_LEFT, 10, 10);
    lv_obj_set_style_border_color(label_container, lv_color_hex(0xbcbcbc), 0); // Gray color
    lv_obj_set_style_border_width(label_container, 2, 0); // Border width
    lv_obj_set_style_radius(label_container, 10, 0); // Rounded corners
    lv_obj_clear_flag(label_container, LV_OBJ_FLAG_SCROLLABLE);

    // Add a new label with a smaller font:
    lv_obj_t* lbl_remaining = lv_label_create(label_container);
    lv_obj_set_align(lbl_remaining, LV_ALIGN_TOP_MID);
    lv_obj_set_width(lbl_remaining, lv_pct(100));
    lv_label_set_long_mode(lbl_remaining, LV_LABEL_LONG_CLIP);
    lv_obj_set_style_text_align(lbl_remaining, LV_TEXT_ALIGN_CENTER, 0);
    lv_label_set_text(lbl_remaining, "Verbleib.\nZeit:");

    // Stylize the smaller label:
    static lv_style_t remaining_label_style;
    lv_style_init(&remaining_label_style);
    lv_style_set_text_font(&remaining_label_style, &lv_font_montserrat_16);
    lv_obj_add_style(lbl_remaining, &remaining_label_style, LV_PART_MAIN);

    // Add time label:
    lbl_time = lv_label_create(label_container);
    lv_obj_set_align(lbl_time, LV_ALIGN_BOTTOM_MID);
    lv_label_set_text_fmt(lbl_time, "--:--");

    // Stylize the time label:
    static lv_style_t time_label_style;
    lv_style_init(&time_label_style);
    lv_style_set_pad_top(&time_label_style, 3);
    lv_style_set_text_font(&time_label_style, &lv_font_montserrat_24);
    lv_obj_add_style(lbl_time, &time_label_style, LV_PART_MAIN);

    // Create a container for current temperature directly on the screen
    lv_obj_t* temp_container = lv_obj_create(scr);
    // Adjust position and size
    lv_obj_set_size(temp_container, 100, 100);
    lv_obj_align(temp_container, LV_ALIGN_TOP_RIGHT, -10, 10);
    lv_obj_set_style_border_color(temp_container, lv_color_hex(0xbcbcbc), 0); // Gray color
    lv_obj_set_style_border_width(temp_container, 2, 0); // Border width
    lv_obj_set_style_radius(temp_container, 10, 0); // Rounded corners
    lv_obj_clear_flag(temp_container, LV_OBJ_FLAG_SCROLLABLE);

    // Add a new label with a smaller font for temperature
    lv_obj_t* lbl_temp = lv_label_create(temp_container);
    lv_obj_set_align(lbl_temp, LV_ALIGN_TOP_MID);
    lv_obj_set_width(lbl_temp, lv_pct(100));
    lv_label_set_long_mode(lbl_temp, LV_LABEL_LONG_CLIP);
    lv_obj_set_style_text_align(lbl_temp, LV_TEXT_ALIGN_CENTER, 0);
    lv_label_set_text(lbl_temp, "Aktuelle\nTemp.:");

    // Stylize the smaller label
    static lv_style_t temp_label_style;
    lv_style_init(&temp_label_style);
    lv_style_set_text_font(&temp_label_style, &lv_font_montserrat_16);
    lv_obj_add_style(lbl_temp, &temp_label_style, LV_PART_MAIN);

    // Add temperature value label
    lbl_temperature = lv_label_create(temp_container);
    lv_obj_set_align(lbl_temperature, LV_ALIGN_BOTTOM_MID);
    lv_label_set_text_fmt(lbl_temperature, "---°C");

    // Stylize the temperature label
    static lv_style_t temperature_value_style;
    lv_style_init(&temperature_value_style);
    lv_style_set_pad_top(&temperature_value_style, 3);
    lv_style_set_text_font(&temperature_value_style, &lv_font_montserrat_24);
    lv_obj_add_style(lbl_temperature, &temperature_value_style, LV_PART_MAIN);

    // Create chart container directly on the screen
    lv_obj_t* chart_container = lv_obj_create(scr);
    // Adjust position and size
    lv_obj_set_size(chart_container, lv_pct(100), 200);
    lv_obj_align(chart_container, LV_ALIGN_BOTTOM_MID, 0, -10);
    lv_obj_set_style_pad_all(chart_container, 5, 0);
    lv_obj_set_style_pad_top(chart_container, 0, 0);
    lv_obj_set_flex_grow(chart_container, 0);
    lv_obj_clear_flag(chart_container, LV_OBJ_FLAG_SCROLLABLE);

    // Add a label on top of the chart
    lv_obj_t* lbl_chart_title = lv_label_create(chart_container);
    lv_obj_set_align(lbl_chart_title, LV_ALIGN_TOP_MID);
    lv_label_set_text(lbl_chart_title, "Temperaturverlauf");

    // Stylize the chart title label
    static lv_style_t chart_title_style;
    lv_style_init(&chart_title_style);
    lv_style_set_text_font(&chart_title_style, &lv_font_montserrat_24); // Bigger font
    lv_style_set_pad_top(&chart_title_style, 10); // Padding from the top
    lv_obj_add_style(lbl_chart_title, &chart_title_style, LV_PART_MAIN);

    /*Create a chart*/
    chart = lv_chart_create(chart_container);
    lv_obj_set_size(chart, 200, 120);
    lv_obj_set_align(chart, LV_ALIGN_BOTTOM_RIGHT); // Positioned at the bottom
    lv_chart_set_type(chart, LV_CHART_TYPE_LINE);   /*Show lines and points too*/

    // Pad the chart from the bottom and right side
    lv_obj_set_style_pad_bottom(chart, 10, 0);
    lv_obj_set_style_pad_right(chart, 10, 0);

    // Make background grid finer, remove time division lines
    lv_chart_set_div_line_count(chart, 4, 0);

    /*Add a data series*/
    lv_chart_series_t* data = lv_chart_add_series(chart, lv_palette_main(LV_PALETTE_RED), LV_CHART_AXIS_PRIMARY_Y);

    // Stylize the graph points (remove):
    static lv_style_t chart_items_style;
    lv_style_init(&chart_items_style);
    lv_style_set_size(&chart_items_style, 0, 0);

    // Define the style for the chart border
    static lv_style_t chart_border_style;
    lv_style_init(&chart_border_style);
    lv_style_set_border_color(&chart_border_style, lv_color_hex(0xbcbcbc)); // Gray color
    lv_style_set_border_width(&chart_border_style, 2); // Border width
    lv_style_set_radius(&chart_border_style, 0); // Rectangular corners
    lv_style_set_pad_right(&chart_border_style, 10);
    lv_style_set_pad_left(&chart_border_style, 0);

    // Add style(s) to chart
    lv_obj_add_style(chart, &chart_items_style, LV_PART_INDICATOR);
    lv_obj_add_style(chart, &chart_border_style, 0);


    lv_chart_set_next_value(chart, data, 50);
    lv_chart_set_next_value(chart, data, 55);
    lv_chart_set_next_value(chart, data, 100);
    lv_chart_set_next_value(chart, data, 120);
    lv_chart_set_next_value(chart, data, 180);
    lv_chart_set_next_value(chart, data, 200);
    lv_chart_set_next_value(chart, data, 190);

    // Configure scale on left side:
    int32_t lowRange = 0;
    int32_t highRange = 300;
    lv_chart_set_range(chart, LV_CHART_AXIS_PRIMARY_Y, lowRange, highRange);

    lv_obj_t* scaleLeft = lv_scale_create(chart_container);
    lv_scale_set_range(scaleLeft, lowRange, highRange);
    lv_scale_set_mode(scaleLeft, LV_SCALE_MODE_VERTICAL_LEFT);
    lv_obj_set_size(scaleLeft, 25, 100);
    lv_scale_set_total_tick_count(scaleLeft, 10);
    lv_scale_set_major_tick_every(scaleLeft, 3);
    lv_obj_set_align(scaleLeft, LV_ALIGN_OUT_LEFT_TOP);
    lv_obj_set_pos(scaleLeft, 4, 80); // Adjusted position to be flush with the chart
    lv_obj_set_style_pad_all(scaleLeft, 0, 0);

    // Create a stop button
    btn_stop = lv_btn_create(scr);
    lv_obj_set_size(btn_stop, 50, 50); // Set button size
    lv_obj_set_style_bg_color(btn_stop, lv_color_hex(0xFF0000), LV_PART_MAIN); // Red color
    lv_obj_set_style_bg_opa(btn_stop, LV_OPA_COVER, LV_PART_MAIN); // Ensure opacity is full
    lv_obj_set_style_radius(btn_stop, LV_RADIUS_CIRCLE, 0); // Make it round
    lv_obj_align(btn_stop, LV_ALIGN_BOTTOM_RIGHT, -10, -10); // Position at bottom right
    lv_obj_add_event_cb(btn_stop, stop_button_callback, LV_EVENT_CLICKED, NULL);
    lv_obj_move_foreground(btn_stop); // Move stop button to the top layer

    // Add a white rectangle to the stop button
    lv_obj_t* rect_stop = lv_obj_create(btn_stop);
    lv_obj_set_size(rect_stop, 20, 20); // Set rectangle size
    lv_obj_set_style_bg_color(rect_stop, lv_color_white(), LV_PART_MAIN); // White color
    lv_obj_set_style_radius(rect_stop, 0, LV_PART_MAIN); // No rounded corners
    lv_obj_set_style_border_color(rect_stop, lv_color_white(), LV_PART_MAIN); // White border
    lv_obj_center(rect_stop); // Center the rectangle within the button


}
