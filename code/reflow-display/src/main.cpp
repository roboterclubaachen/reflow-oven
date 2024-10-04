#include <modm/board.hpp>
#include <modm/driver/display/ili9341.hpp>
#include <modm/driver/display/ili9341_spi.hpp>

#include <modm/debug/logger.hpp>
#include <modm/io/iostream.hpp>
#include <modm/ui/display/graphic_display.hpp>
#include <modm/ui/display/font/assertion.hpp>
#include <modm/ui/color/rgb565.hpp>

#include <modm/processing/timer/periodic_timer.hpp>

#include "timer.hpp"
#include "process_screen.hpp"

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

void init()
{
    // Startup Dev Board
    Board::initialize();
    // Initialize Display SPI
    // TODO: Get display to listen to SPI correctly
    DisplaySpi::connect<Sck::Sck, Mosi::Mosi, Miso::Miso>();
    DisplaySpi::initialize<Board::SystemClock, 24_MHz>();


    // initialize and turn on display
    display.initialize();
    display.turnOn();
    //Backlight::set();

    // Configuration: //
    // set colors
    display.setBackgroundColor(Rgb565(0x0000)); // dark blue
    display.setColor(Rgb565(0xffff)); // white OBSOLETE
    // set brightness
    display.setBrightness(0xFF); // full bright
    // reduce color depth
    display.setIdle(true);
    display.setFont(modm::font::Assertion);
    // clear all screen content on start
    display.clear();
    display.flush();
}




int main()
{
    init();
    MODM_LOG_DEBUG << "reflow oven display initialized!" << modm::endl;
    //Create new object process screen
    timer testTimer(0, 2); //DEBUG add timer for testing
    ProcessScreen procScreen(testTimer, display);
    procScreen.drawProcessScreen();
    // Initialize Timer to update screen
    modm::ShortPeriodicTimer updateTimer(1s);
    while(true) 
    {
        // Update process screen every second
        if( updateTimer.execute() )
        {
            testTimer.update();
            procScreen.updateProcessScreen();
            display.update();
        }
    }
    return 0;
}