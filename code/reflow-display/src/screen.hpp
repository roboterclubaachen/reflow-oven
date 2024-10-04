#ifndef SCREEN_H
#define SCREEN_H

#include <modm/ui/display/color_graphic_display.hpp>
#include <modm/ui/gui.hpp>

using cDisplay = modm::ColorGraphicDisplay;
using dimension = modm::gui::Dimension;
using Point = modm::glcd::Point;

class Screen
{
    public:
    Screen(cDisplay& iDisplay, modm::gui::WidgetGroup& iGroup) :
    display(iDisplay),
    wGroup(iGroup)
    {}

    // Overload for portrait display ili9431 full display
    Screen(cDisplay& iDisplay) :
    display(iDisplay),
    wGroup(modm::gui::Dimension(240,320))
    {}

    modm::gui::WidgetGroup& getWidgetGroup() const{return wGroup;}
    cDisplay& getDisplay() const{return display;}

    private:
    cDisplay& display;
    modm::gui::WidgetGroup wGroup;
};

#endif //SCREEN_H