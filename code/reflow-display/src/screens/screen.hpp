#ifndef SCREEN_H
#define SCREEN_H

#include <modm/ui/display/color_graphic_display.hpp>
#include <modm/ui/gui.hpp>

using cDisplay = modm::ColorGraphicDisplay;
using Dimension = modm::gui::Dimension;
using Point = modm::glcd::Point;
using GuiViewStack = modm::gui::GuiViewStack;

class Screen : public modm::gui::View
{
    public:
    Screen(GuiViewStack* iViewStack, u_int8_t iIdentifier, cDisplay& iDisplay, Dimension iDimensions, modm::gui::WidgetGroup& iGroup);

    // Overload for portrait display ili9431 full display
    Screen(GuiViewStack* iViewStack, u_int8_t iIdentifier, cDisplay& iDisplay);

    bool hasChanged()
    {
        return true;
    }

    modm::gui::WidgetGroup& getWidgetGroup() {return wGroup;}
    cDisplay& getDisplay() const{return display;}

    protected:
    cDisplay& display;
    modm::gui::WidgetGroup wGroup;
};

#endif //SCREEN_H