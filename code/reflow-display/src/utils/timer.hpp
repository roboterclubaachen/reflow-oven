#ifndef TIMER_H
#define TIMER_H

#include <modm/processing/timer/periodic_timer.hpp>
#include <modm/processing/protothread.hpp>


#include <chrono>
#include <string>
#include <sstream>
#include <iomanip>

// TODO add protothread to up performance

/// @brief Timer class opens a timer which counts down every second
class timer
{
    public:
        // Constructor for a timer.
        timer(uint16_t iHours, uint8_t iMinutes) :
        secondsTimer(1s),
        hours(iHours),
        minutes(iMinutes)
        {}

        ~timer() = default;

        /// @brief Timer function using PeriodicTimer to count seconds on microcontroller
        void run()
        {
            if (secondsTimer.execute())
            {
                countDown();
            }
            // Timer should be finished now.
        }
        /// @brief Function which counts down one second of the timer
        /// @return is the timer empty?
        bool countDown()
        {
            if (seconds == 0)
            {
                if (minutes == 0)
                {
                    if (hours != 0) 
                    {
                        hours--;
                        minutes = 60;
                    }
                    else return true;
                } 
                else 
                {
                    minutes--;
                    seconds = 60;
                }
            } 
            else 
            {
                seconds--;
            }
            return false;
        }

        uint16_t getHours() const {return hours;}
        uint8_t getMinutes() const {return minutes;}
        uint8_t getSeconds() const {return seconds;}

        /// @brief Overload of stream operator for output
        /// @param stream used IOStream
        /// @param timer Timer which should be output
        /// @return The same stream
        friend modm::IOStream& operator<<(modm::IOStream& stream, const timer& timer);

        /// @brief A function which gives back the timer formated as string
        /// TODO: Somehow eliminate the need of a heap
        /// @return Timer time as string
        const char* getTime()
        {
            static char buffer[15];
            std::snprintf(buffer, 15, "%02u:%02u:%02u", hours, minutes, seconds);
            return buffer;
        }



    private:
    modm::ShortPeriodicTimer secondsTimer;

    uint16_t hours;
    uint8_t minutes;
    uint8_t seconds = 0;
};

        modm::IOStream& operator<<(modm::IOStream& stream, const timer& timer)
        {
            stream.printf("%02u:%02u:%02u", timer.getHours(), timer.getMinutes(), timer.getSeconds());
            // modm::flush(stream); EXTREMELY EXPENSIVE
            return stream;
        }

#endif //TIME_H