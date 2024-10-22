#include <modm/board.hpp>
#include <modm/driver/display/ili9341.hpp>
#include <modm/driver/display/ili9341_spi.hpp>
#include <modm/driver/touch/touch2046.hpp>

#include <modm/debug/logger.hpp>

#include <modm/processing/timer/periodic_timer.hpp>

#include <lvgl/lvgl.h>

#include "screens/process_screen.h"

// Define pins
using DisplaySpi = modm::platform::SpiMaster1;
using Cs = Board::D10;
using Dc = Board::D9;
using Rst = Board::D8;
using Backlight = Board::D7;

using Mosi = Board::D11;
using Miso = Board::D12;
using Sck = Board::D13;
// Defining aliases
using Rgb565 = modm::color::Rgb565;

// Define the display
modm::Ili9341Spi<DisplaySpi, Cs, Dc, Rst, Backlight> display;

//----------------------//
//      STATICS         //
//----------------------//
//static uint16_t* displayBuffer;

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[240 * 32];
/*Declare a buffer for full screen size*/
static lv_disp_drv_t disp_drv;        /*Descriptor of a display driver*/
static lv_disp_t disp;

// END STATIC

void my_flush_cb(lv_disp_drv_t* disp_drv, const lv_area_t* area, lv_color_t* color_p)
{
    int32_t x, y;
    /*It's a very slow but simple implementation.*/
    for(y = area->y1; y <= area->y2; y++) {
        for(x = area->x1; x <= area->x2; x++) {
            display.setColor(lv_color_to16(*color_p));
            display.setPixel(x, y);
            color_p++;
        }
    }
    lv_disp_flush_ready(disp_drv);         /* Indicate you are ready with the flushing*/
}

// void
// my_touchpad_read(lv_indev_drv_t*, lv_indev_data_t* data)
// {
// 	RF_CALL_BLOCKING(touch.readTouches());
// 	Touch::touch_t tp;
// 	touch.getData().getTouch(&tp, 0);
// 	// mirror and rotate correctly
// 	uint16_t x{tp.y}, y{uint16_t(480 - tp.x)};
// 	data->state = (tp.event == Touch::Event::Contact) ? LV_INDEV_STATE_PR : LV_INDEV_STATE_REL;
// 	if (data->state == LV_INDEV_STATE_PR)
// 	{
// 		data->point.x = x;
// 		data->point.y = y;
// 	}
// }


void lvglDriverInit()
{


    lv_disp_draw_buf_init(&draw_buf, &buf, NULL, 240 * 32);  /*Initialize the display buffer.*/

    lv_disp_drv_init(&disp_drv);          /*Basic initialization*/
    disp_drv.flush_cb = my_flush_cb;    /*Set your driver function*/
    disp_drv.draw_buf = &draw_buf;        /*Assign the buffer to the display*/
    disp_drv.hor_res = 240;   /*Set the horizontal resolution of the display*/
    disp_drv.ver_res = 320;   /*Set the vertical resolution of the display*/
    disp = *lv_disp_drv_register(&disp_drv);      /*Finally register the driver*/

    lv_disp_set_default(&disp);

    // Initialize touchscreen driver:
	// lv_indev_drv_t indev_drv;
	// lv_indev_drv_init(&indev_drv);
	// indev_drv.type = LV_INDEV_TYPE_POINTER;
	// indev_drv.read_cb = my_touchpad_read;
	// lv_indev_drv_register(&indev_drv);

}

void initializeDisp()
{
    // Initialize Display SPI
    // TODO: Get display to listen to SPI correctly
    DisplaySpi::connect<Sck::Sck, Mosi::Mosi, Miso::Miso>();
    DisplaySpi::initialize<Board::SystemClock, 24_MHz>();


    // initialize and turn on display
    display.initialize();
    display.turnOn();

    display.setIdle(false);
    display.clear();

}

void init()
{
    // Startup Dev Board
    Board::initialize();

    lv_init();

    // Initialize Display and Touchscreen
    initializeDisp();
    lvglDriverInit();
}




int main()
{
    init();
    MODM_LOG_DEBUG << "reflow oven display initialized!" << modm::endl;

    // TESTING //
    ProcScreen procScreen(360);
    procScreen.initProcScreen();
    lv_scr_load_anim(procScreen.getScreen(), LV_SCR_LOAD_ANIM_FADE_IN, 50, 0, true);
    // Initialize Timer to update screen
    modm::ShortPeriodicTimer updateTimer{1ms};
    while(true) 
    {
        // Update process screen every second
        if( updateTimer.execute() )
        {
            lv_task_handler();
        }
    }
    return 0;
}