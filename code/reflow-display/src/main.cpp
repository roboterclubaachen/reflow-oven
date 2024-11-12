#include <modm/board.hpp>
#include <modm/driver/display/ili9341.hpp>
#include <modm/driver/display/ili9341_spi.hpp>
#include <modm/driver/touch/touch2046.hpp>

#include <modm/debug/logger.hpp>

#include <modm/processing.hpp>


#include <lvgl/lvgl.h>

// #include <lv_conf.h>

#undef MODM_LOG_LEVEL
#define MODM_LOG_LEVEL modm::log::DEBUG

// Define display pins
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

static lv_disp_draw_buf_t disp_buf;
static constexpr size_t bufSize = (LV_HOR_RES_MAX * LV_VER_RES_MAX) / 10;
static lv_color_t buf[bufSize];

// END STATIC

void my_flush_cb(lv_disp_drv_t* disp_drv, const lv_area_t* area, lv_color_t* color_p)
{
    /*It's a very slow but simple implementation.*/
    for(uint8_t y = area->y1; y <= area->y2; y++) {
        for(uint8_t x = area->x1; x <= area->x2; x++) {
            // Convert color to RGB565
            lv_color16_t c16;
            c16.full = lv_color_to16(*color_p);
            Rgb565 c565 = Rgb565(c16.full);
            display.setColor(c565);
            display.setPixel(x, y);
            MODM_LOG_DEBUG << "Setting pixel (" << x << ", " << y << ") to color " << lv_color_to16(*color_p) << modm::endl;
            color_p++;
        }
    }
    lv_disp_flush_ready(disp_drv);         /* Indicate you are ready with the flushing*/
}

int main()
{
    // Startup Dev Board
    Board::initialize();

    // Initialize Display SPI
    DisplaySpi::connect<Sck::Sck, Mosi::Mosi, Miso::Miso>();
    DisplaySpi::initialize<Board::SystemClock, 24_MHz>();


    // initialize and turn on display
    display.initialize();
    display.turnOn();

    display.setIdle(false);
    display.clear();

    lv_init();


    lv_disp_draw_buf_init(&disp_buf, &buf, NULL, sizeof(buf));  /*Initialize the display buffer.*/

    // Initialize the display:
	lv_disp_drv_t disp_drv;
	lv_disp_drv_init(&disp_drv);
	disp_drv.draw_buf = &disp_buf;
	disp_drv.flush_cb = my_flush_cb;
    // disp_drv.direct_mode = true;
	disp_drv.hor_res = LV_HOR_RES_MAX;
	disp_drv.ver_res = LV_VER_RES_MAX;
	lv_disp_drv_register(&disp_drv);

    


    MODM_LOG_DEBUG << "[Info] reflow oven display initialized!" << modm::endl;

    // TESTING //
    //ProcScreen procScreen(360);
    //procScreen.initProcScreen();

    // DEBUGGING //
    // lv_obj_t* scr = lv_obj_create(NULL);
    // lv_obj_t* btn1 = lv_btn_create(scr);
    // lv_obj_set_x(btn1, 30);
    // lv_obj_set_y(btn1, 10);
    // lv_scr_load(scr);

    modm::ShortPeriodicTimer tmr{5ms};
    while(true) 
    {
        if(tmr.execute())
        {
            lv_timer_handler();
            lv_task_handler();
        }
    }
    return 0;
}