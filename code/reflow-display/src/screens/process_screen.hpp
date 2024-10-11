#ifndef PROCESS_SCREEN_H
#define PROCESS_SCREEN_H


#include <modm/ui/gui/view.hpp>

#include "screen.hpp"
#include "../utils/timer.hpp"
#include "../utils/plot.hpp"




class ProcessScreen : public Screen
{
    public:
    ProcessScreen(GuiViewStack* iViewStack, u_int8_t iIdentifier, timer& iTimer, cDisplay& iDisplay) :
    Screen::Screen(iViewStack, iIdentifier, iDisplay),
    procTimer(iTimer),
    lbl_title("Ovening", Rgb565(0xffff)),
    lbl_time("Time left: ", Rgb565(0xffff)),
    lbl_clock("00:00:00", Dimension(220, 60))
    {}

    void drawProcessScreen()
    {
        //Set up widget group for screen
        auto wGroup = getWidgetGroup();
        wGroup.setPosition(Point(0, 0));

        // Configure time widget
        lbl_time.setFont(modm::font::ArcadeClassic);
        lbl_time.markDrawn();
        lbl_clock.markDirty();

        // Pack all widgets into group for mass rendering
        wGroup.pack(&lbl_time, Point(120, 10));
        wGroup.pack(&lbl_clock, Point(120, 35));

    }


    void updateProcessScreen()
    {
        // Write remaining time
        lbl_clock.setValue(procTimer.getTime());   
        //lbl_clock.markDirty(); 

        // Render all widgets
        getWidgetGroup().markDirty();
   }

    // void connectTemperature(modm::Gpio Sck, modm::Gpio Mosi)
    // {
    //     /// TODO: connect to temp Sondor via Spi
    //     // tempSpi::connect(Sck::Sck, Mosi::Mosi);
    //     // tempSpi::initialize(Board::SystemClock, 24_MHz);
    // }

    private:
    timer procTimer;
    // Widgets
    modm::gui::Label lbl_title;
    modm::gui::Label lbl_time;
    modm::gui::StringField lbl_clock;
};

#endif //PROCESS_SCREEN_H