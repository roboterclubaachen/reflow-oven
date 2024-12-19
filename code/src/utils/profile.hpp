#ifndef PROFILE_HPP
#define PROFILE_HPP

#include <modm/container/dynamic_array.hpp>

class Profile {
private:
    modm::DynamicArray<float> p_tempCurve;
    uint16_t p_Time;
    std::string p_name;

public:
    // Constructor for when the curve is already known
    Profile(std::initializer_list<float> list, std::string name, uint16_t time) :
        p_tempCurve(list),
        p_Time(time),
        p_name(name)
        {};

    // Constructor for when the curve is unknown. Size limited to 100 or set manually
    Profile(std::string name, size_t size = 100) :
        p_tempCurve(size),
        p_Time(time),
        p_name(name)
        {};

    ~Profile() = default;

};

#endif // PROFILE_HPP