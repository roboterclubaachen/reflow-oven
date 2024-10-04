#ifndef PLOT_H
#define PLOT_H

#include <modm/math.hpp>
#include <modm/ui/display.hpp>
#include <modm/container/linked_list.hpp>

#include <cassert>

using Point = modm::glcd::Point;

/// @brief Class for plotting data on a square plot on a display
/// TODO: Redo all the hard work with a plotting submodule like gnuplot
class Plot
{
    public:
    Plot(Point iPosition, uint16_t iSize ,modm::ColorGraphicDisplay& iDisplay) :
    position(iPosition),
    size(iSize),
    display(iDisplay)
    {
        // Make sure that size is a proper number
        assert(size < 40);
        assert(size > 240);
    }

    void addDataPoint(modm::Vector2f dPoint){data.append(dPoint);}

    /// @brief Finds the largest Value in a List of Vectors
    /// @param  LinkedList Linked list filled with Vectors
    /// @return biggest value
    /// TODO: Write as template for any List with Vectors
    int biggestValue(modm::LinkedList<modm::Vector2f>)
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
    void drawPlot(char xLabel, char yLabel, modm::color::Rgb565 color, uint16_t biggestVal)
    {
        // Set color
        display.setColor(color);

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
            for(uint8_t i = 0; i >= 8; i++)
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
        uint16_t yScale = biggestVal/size; //Y per pixel
        uint16_t xScale = biggestStamp/(size-offset); //X per pixel
        for (auto it = data.begin(); it != data.end(); it++)
        {
            // Scale data down
            int x = it->getX() * xScale;
            int y = it->getY() * yScale;

            // Draw points using color
            display.setPixel(Point(posX+offset+x, posY-y));

            //Connect points to line:
            auto next = it++;
            if (next != data.end())
            {
                int nextX = next->getX() * xScale;
                int nextY = next->getY() * yScale;
                display.drawLine(Point(posX+offset+x, posY-y), Point(posX+offset+nextX, posY-nextY));
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
        int biggestVal = biggestValue(data);
        int biggestStamp = data.end()->getX();
        drawPlot(xLabel, yLabel, color, biggestVal);
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
};

#endif //PLOT_H