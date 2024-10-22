#ifndef TIMER_H
#define TIMER_H

#include <modm/processing/timer/periodic_timer.hpp>
#include <modm/math/units.hpp>

// #include <chrono>

using namespace std::literals;

// TODO add protothread to up performance

/// @brief Timer class opens a timer which counts down every second
class timer
{
    public:
        // Constructor for a timer.
        timer(uint16_t iSeconds) :
        secondsTimer(1s),
        seconds(iSeconds)

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
            if(seconds > 0)
            {
                seconds--;
                return false;
            }
            else return true;
        }

        uint8_t getSeconds() const {return seconds;}



    private:
    modm::ShortPeriodicTimer secondsTimer;

    uint16_t seconds;
};
        
        /// @brief Overload of stream operator for output
        /// @param stream used IOStream
        /// @param timer Timer which should be output
        /// @return The same stream
        inline modm::IOStream& operator<<(modm::IOStream& stream, const timer& tim)
        {
            stream.printf("%u", tim.getSeconds());
            // modm::flush(stream); EXTREMELY EXPENSIVE
            return stream;
        }

#endif //TIME_H