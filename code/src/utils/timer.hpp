#ifndef TIMER_H
#define TIMER_H

#include <modm/processing/timer/periodic_timer.hpp>
#include <modm/math/units.hpp>

using namespace std::chrono_literals;

// TODO add protothread to up performance

/// @brief Timer class opens a timer which counts down every second
class Timer
{
    public:
        // Constructor for a timer.
        Timer(uint8_t iMinutes, uint8_t iSeconds) :
        secondsTimer(1s),
        minutes(iMinutes),
        seconds(iSeconds)
        {}

        ~Timer() = default;

        void restart()
        {
            secondsTimer.restart();
        }
        /// @brief Timer function using PeriodicTimer to count seconds on microcontroller
        void update()
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
                    return true;
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

        uint8_t getMinutes() const {return minutes;}
        uint8_t getSeconds() const {return seconds;}

        void setMinutes(uint8_t iMinutes) { minutes = iMinutes; }
        void setSeconds(uint8_t iSeconds) { seconds = iSeconds; }

    private:
    modm::ShortPeriodicTimer secondsTimer;

    uint8_t minutes;
    uint8_t seconds = 0;
};

#endif //TIME_H