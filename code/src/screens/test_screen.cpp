#include "test_screen.h"

static uint16_t counter = 0;
static lv_obj_t* labelA;

void btn_event_cb(lv_event_t *event)
{
	static uint16_t btnCounter = 0;
	lv_label_set_text_fmt((lv_obj_t*) lv_event_get_user_data(event),
							"Button: %d", ++btnCounter);
}

void drawTestScreen(void)
{
    labelA =  lv_label_create(lv_screen_active());
	lv_label_set_text(labelA, "Hello world!");
	lv_obj_set_pos(labelA, 60, 10);
	lv_obj_set_size(labelA, 120, 50);

	lv_obj_t* btn = lv_button_create(lv_screen_active());
	lv_obj_set_pos(btn, 60, 135);
	lv_obj_set_size(btn, 120, 50);

	lv_obj_t* btnLabel = lv_label_create(btn);
	lv_label_set_text(btnLabel, "Button");

	static lv_style_t style_btn_pressed;
	lv_style_init(&style_btn_pressed);
	lv_style_set_bg_color(&style_btn_pressed, lv_palette_main(LV_PALETTE_ORANGE));

	lv_obj_add_style(btn, &style_btn_pressed, LV_STATE_PRESSED);
	
		lv_obj_add_event_cb(btn, btn_event_cb, LV_EVENT_PRESSED, btnLabel);

	lv_obj_t* labelB =  lv_label_create(lv_screen_active());
	lv_label_set_text(labelB, "Big Font");
	lv_obj_set_pos(labelB, 40, 260);
	lv_obj_set_style_text_font(labelB, &lv_font_montserrat_36, LV_PART_MAIN);
}

void setLblText(void)
{
    lv_label_set_text_fmt(labelA, "counter=%d", ++counter);
}