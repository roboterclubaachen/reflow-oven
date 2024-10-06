#ifndef PLOT_H
#define PLOT_H

#include <modm/math.hpp>
#include <modm/ui/display.hpp>
#include <modm/container/linked_list.hpp>

#include <cassert>

using Point = modm::glcd::Point;
using Rgb565 = modm::color::Rgb565;

/** @brief Class for plotting data on a square plot on a display
 *  This is a class which draws a 2D square plot with size x size.
 *  Written to fit many applications when drawing plots on displays.
 * 
 * TODO: Redo all the hard work with a plotting submodule like gnuplot
*/ 
class Plot
{
    public:
    Plot(Point iPosition, uint16_t iSize ,modm::ColorGraphicDisplay& iDisplay, Rgb565 iColor = 0xF800/*red*/, Rgb565 iAltColor = 0xFFFF /*white*/, bool iConnectData = true) :
    position(iPosition),
    size(iSize),
    display(iDisplay),
    color(iColor),
    altColor(iAltColor),
    connectData(iConnectData)
    {
        // Make sure that size is a proper number
        assert(size > 40);
        assert(size < 240);
    }
    /// @brief Add a singular datapoint to the plot
    /// @param dPoint Point to be added
    void addDataPoint(modm::Vector2f dPoint){data.append(dPoint);}

    /// @brief Finds the largest Value in a List of Vectors
    /// @param  LinkedList Linked list filled with Vectors
    /// @return biggest value
    /// TODO: Untested. May contain a lot of bugs
    uint16_t biggestValue()
    {
        //Find largest data value
        uint16_t biggestVal = 0;
        for (auto it = data.begin(); it != data.end(); it++)
        {
            if(it->getY() > biggestVal) biggestVal = it->getY();
        }
        return biggestVal;
    }
    /// @brief Function for Drawing a rectangular empty plot on a display
    /// @param xLabel label for x axis (char)
    /// @param yLabel label for y axis (char)
    /// @param color color in which the plot should be drawn
    /// @param biggestVal biggestValue of the datapoints
    void drawPlot(char xLabel, char yLabel, uint16_t biggestVal)
    {
        // Set color
        display.setColor(altColor);

        uint16_t posX = position.getX();
        uint16_t posY = position.getY();
        uint8_t offset = size/10;
        //Draw axes
        display.drawLine(Point(posX+offset, posY), Point(posX+offset, posY+size));
        display.drawLine(Point(posX+offset, posY+size), Point(posX+size, posY+size));

        uint16_t biggestStamp = data.end()->getX();
        //Look up if the plot is too smol
        if(!(offset < 10))
        {
            //Label axes
            display.setFont(modm::font::AllCaps3x5);
            display.setCursor(position);
            display.write(xLabel);
            display.setCursor(Point(posX+size, posY+size+2));
            display.write(yLabel);

            //Make those tiny lines on the side
            uint16_t lineDiff = (size)/8;
            for(uint8_t i = 0; i < 8; i++)
            {
                display.drawLine(Point(posX+offset, posY+(i*lineDiff)), Point(posX, posY+(i*lineDiff)));
            }
            //Write largest value on the highest line
            display.setFont(modm::font::AllCaps3x5);
            display.ascii();
            display.setCursor(Point(posX, posY+3));
            display << biggestVal;
        }

    }

    /// @brief Function for drawing the points into the plot and connecting them together
    /// @param biggestVal biggest Value of data
    /// @param biggestStamp last datapoint x of data
    /// @param offset offset, by which the plot is moved to the right to fit additional stuff
    void drawPoints(uint16_t biggestVal, uint16_t biggestStamp, uint16_t offset)
    {
        uint16_t posX = position.getX();
        uint16_t posY = position.getY();
        // Draw data
        float yScale = static_cast<float>(size) / biggestVal;
        float xScale = static_cast<float>(size - offset) / biggestStamp;
        for (auto it = data.begin(); it != data.end(); it++)
        {
            // Scale data down
            int x = it->getX() * xScale;
            int y = it->getY() * yScale;

            // Draw points using color
            display.setPixel(Point(posX+offset+x, posY-y));

            // If user wants to connect the dots
            if(connectData)
            {
                //Connect points to line:
                display.setColor(color);
                auto next = std::next(it);
                if (next != data.end())
                {
                    int nextX = next->getX() * xScale;
                    int nextY = next->getY() * yScale;
                    display.drawLine(Point(posX+offset+x, posY-y), Point(posX+offset+nextX, posY-nextY));
                }
            }
        }
    }

    /// @brief Draw the whole plot with datapoints
    /// @param xLabel label for x axis (char)
    /// @param yLabel label for y axis (char)
    /// @param color color in which the plot should be drawn
    /// @param biggestVal biggestValue of the datapoints
    void draw(char xLabel, char yLabel, modm::color::Rgb565 color, uint16_t offset)
    {
        int biggestVal = biggestValue();
        int biggestStamp = data.end()->getX();
        drawPlot(xLabel, yLabel, biggestVal);
        drawPoints(biggestVal, biggestStamp, offset);
    }
        

    private:
    /// @brief Top right point of the plot
    const Point position;
    /// @brief Size of plot in pixels (rectangular)
    const u_int16_t size;
    /// @brief display on which stuff is drawn
    modm::ColorGraphicDisplay& display;
    /// @brief contains datapoints
    modm::LinkedList<modm::Vector2f> data;
    /// @brief  color of connecting lines
    Rgb565 color;
    /// @brief color of plot and datapoints
    Rgb565 altColor;
    /// @brief Setting to connect data or not
    bool connectData;
};

#endif //PLOT_H