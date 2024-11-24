#include "process_screen.h"

static lv_obj_t* scr;
static lv_obj_t* chart;
static lv_obj_t* lbl_time;

void drawProcessScreen()
{
    // Create a new screen:
    scr = lv_obj_create(NULL);
    lv_obj_set_size(scr, lv_pct(100), lv_pct(100));
    lv_obj_center(scr);

    // Create a wrapper for the labels
    lv_obj_t* label_wrapper = lv_obj_create(scr);
    lv_obj_set_align(label_wrapper, LV_ALIGN_TOP_MID);
    lv_obj_set_size(label_wrapper, lv_pct(100), 120); // Increased height to 100
    lv_obj_set_style_pad_all(label_wrapper, 5, 0);
    lv_obj_set_style_border_color(label_wrapper, lv_color_hex(0xbcbcbc), 0); // Gray color
    lv_obj_set_style_border_width(label_wrapper, 2, 0); // Border width
    lv_obj_set_style_radius(label_wrapper, 10, 0); // Rounded corners
    lv_obj_clear_flag(label_wrapper, LV_OBJ_FLAG_SCROLLABLE);

    // Add a new label with a smaller font:
    lv_obj_t* lbl_small = lv_label_create(label_wrapper);
    lv_obj_set_align(lbl_small, LV_ALIGN_TOP_MID);
    lv_label_set_text(lbl_small, "Verbleibende Zeit");

    // Stylize the smaller label:
    static lv_style_t small_label_style;
    lv_style_init(&small_label_style);
    lv_style_set_text_font(&small_label_style, &lv_font_montserrat_16);
    lv_obj_add_style(lbl_small, &small_label_style, LV_PART_MAIN);

    // Add time label:
    lbl_time = lv_label_create(label_wrapper);
    lv_obj_set_align(lbl_time, LV_ALIGN_BOTTOM_MID);
    // receive a seconds number as test:
    uint16_t totalSeconds = 210;
    // Convert to minutes + seconds:
    uint8_t minutes = totalSeconds / 60;
    uint8_t seconds = totalSeconds % 60;
    lv_label_set_text_fmt(lbl_time, "%u:%u", minutes, seconds);

    // Stylize the time label:
    static lv_style_t time_label_style;
    lv_style_init(&time_label_style);
    lv_style_set_pad_top(&time_label_style, 3);
    lv_style_set_text_font(&time_label_style, &lv_font_montserrat_36);
    lv_obj_add_style(lbl_time, &time_label_style, LV_PART_MAIN);

    // Create container for chart:
    lv_obj_t* wrapper = lv_obj_create(scr);
    lv_obj_set_align(wrapper, LV_ALIGN_BOTTOM_MID); // Adjusted position to bottom
    lv_obj_set_size(wrapper, lv_pct(100), 200); // Increased height to 200
    lv_obj_set_style_pad_all(wrapper, 2, 0);
    lv_obj_set_flex_grow(wrapper, 0);
    lv_obj_clear_flag(wrapper, LV_OBJ_FLAG_SCROLLABLE);

    // Add a label on top of the chart
    lv_obj_t* lbl_chart_title = lv_label_create(wrapper);
    lv_obj_set_align(lbl_chart_title, LV_ALIGN_TOP_MID);
    lv_label_set_text(lbl_chart_title, "Temperaturverlauf");

    // Stylize the chart title label
    static lv_style_t chart_title_style;
    lv_style_init(&chart_title_style);
    lv_style_set_text_font(&chart_title_style, &lv_font_montserrat_24); // Bigger font
    lv_style_set_pad_top(&chart_title_style, 10); // Padding from the top
    lv_obj_add_style(lbl_chart_title, &chart_title_style, LV_PART_MAIN);

    /*Create a chart*/
    chart = lv_chart_create(wrapper);
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

    // Add a cursor to the chart
    lv_chart_cursor_t* cursor = lv_chart_add_cursor(chart, lv_palette_main(LV_PALETTE_ORANGE), LV_DIR_BOTTOM);
    lv_chart_set_cursor_point(chart, cursor, data, 5);


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

    lv_obj_t* scaleLeft = lv_scale_create(wrapper);
    lv_scale_set_range(scaleLeft, lowRange, highRange);
    lv_scale_set_mode(scaleLeft, LV_SCALE_MODE_VERTICAL_LEFT);
    lv_obj_set_size(scaleLeft, 25, 100);
    lv_scale_set_total_tick_count(scaleLeft, 10);
    lv_scale_set_major_tick_every(scaleLeft, 3);
    lv_obj_set_align(scaleLeft, LV_ALIGN_OUT_LEFT_TOP);
    lv_obj_set_pos(scaleLeft, 9, 80); // Adjusted position to be flush with the chart
    lv_obj_set_style_pad_all(scaleLeft, 0, 0);

    // Load the screen when it's ready
    lv_scr_load(scr);
}
