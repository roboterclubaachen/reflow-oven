#include "screen.hpp"

Screen::Screen(GuiViewStack* iViewStack, u_int8_t iIdentifier, cDisplay& iDisplay, Dimension iDimensions, modm::gui::WidgetGroup& iGroup) :
    View(iViewStack, iIdentifier, iDimensions),
    display(iDisplay),
    wGroup(iGroup)
    {}

Screen::Screen(GuiViewStack* iViewStack, u_int8_t iIdentifier, cDisplay& iDisplay) :
    View(iViewStack, iIdentifier, Dimension(240, 320)),
    display(iDisplay),
    wGroup(Dimension(240, 320))
    {}