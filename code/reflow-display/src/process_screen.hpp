#ifndef PROCESS_SCREEN_H
#define PROCESS_SCREEN_H


#include "screen.hpp"
#include "timer.hpp"




class ProcessScreen : public Screen
{
    public:
    ProcessScreen(timer& iTimer, cDisplay& iDisplay) :
    Screen::Screen(iDisplay),
    procTimer(iTimer),
    tTitle("Time left: ", Rgb565(0xffff)),
    tTime("00:00:00", dimension(220, 60))
    {}

    void drawProcessScreen()
    {
        //Set up widget group for screen
        auto wGroup = getWidgetGroup();
        wGroup.setPosition(Point(0, 0));

        // Configure time widget
        tTitle.setFont(modm::font::ArcadeClassic);
        tTitle.markDrawn();
        tTime.markDirty();

        // Pack all widgets into group for mass rendering
        wGroup.pack(&tTitle, Point(120, 10));
        wGroup.pack(&tTime, Point(120, 35));

    }


    void updateProcessScreen()
    {
        // Write remaining time
        tTime.setValue(procTimer.getTime());   
        tTime.markDirty(); 

        // Render all widgets
         getWidgetGroup().markDirty();
   }

    void connectTemperature(modm::Gpio Sck, modm::Gpio Mosi)
    {
        /// TODO: connect to temp Sondor via Spi
        // tempSpi::connect(Sck::Sck, Mosi::Mosi);
        // tempSpi::initialize(Board::SystemClock, 24_MHz);
    }

    private:
    timer procTimer;
    modm::gui::Label tTitle;
    modm::gui::StringField tTime;
};

#endif //PROCESS_SCREEN_H