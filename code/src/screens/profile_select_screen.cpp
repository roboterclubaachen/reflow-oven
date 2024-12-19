#include "profile_select_screen.h"

profile_select_screen::profile_select_screen() :
    p_profiles(std::size_t(3))
{
    // Temperature profile for RSS No Pb. 15 second intervalls
    // https://www.compuphase.com/electronics/reflowsolderprofiles.htm
    std::initializer_list<float> rss_no_pb = {
        0,  // 0s
        37.5,  // 15s
        75,  // 30s
        112.5,  // 45s
        150,  // 60s
        152.5,  // 75s
        155,  // 90s
        157.5,  // 105s
        160,  // 120s
        162.5,  // 135s
        165,  // 150s
        167.5,  // 165s
        170,  // 180s
        172.5,  // 195s
        175,  // 210s
        177.5,  // 225s
        180,  // 240s
        201.7,  // 255s
        223.3,  // 270s
        245,  // 285s
        180,  // 300s
        0,  // 315s
        0  // 330s
    };
    Profile(rss_no_pb, "RSS No Pb", 300);    
    
    // Temperature profile for RSS Pb. 15 second intervalls
    // https://www.compuphase.com/electronics/reflowsolderprofiles.htm
    std::initializer_list<float> rss_pb = {
        0,  // 0s
        37.5,  // 15s
        75,  // 30s
        112.5,  // 45s
        150,  // 60s
        152.5,  // 75s
        155,  // 90s
        157.5,  // 105s
        160,  // 120s
        162.5,  // 135s
        165,  // 150s
        167.5,  // 165s
        170,  // 180s
        172.5,  // 195s
        175,  // 210s
        177.5,  // 225s
        180,  // 240s
        183.3,  // 255s
        186.7,  // 270s
        190,  // 285s
        193.3,  // 300s
        196.7,  // 315s
        200,  // 330s
        203.3,  // 345s
        206.7,  // 360s
        210,  // 375s
        213.3,  // 390s
        216.7,  // 405s
        220,  // 420s
        223.3,  // 435s
        226.7,  // 450s
        230,  // 465s
        233.3,  // 480s
        236.7,  // 495s
        240,  // 510s
        243.3,  // 525s
        246.7,  // 540s
        250,  // 555s
        253.3,  // 570s
        256.7,  // 585s
        260,  // 600s
        240,  // 615s
        220,  // 630s
        200,  // 645s
        180,  // 660s
        160,  // 675s
        140,  // 690s
        120,  // 705s
        100,  // 720s
        80,  // 735s
        60,  // 750s
        40,  // 765s
        20,  // 780s
        0  // 795s
    };
    Profile(rss_pb, "RSS No Pb", 300);
}

profile_select_screen::profile_select_screen(size_t size) :
    p_profiles(std::size_t(size))
{

}

profile_select_screen::~profile_select_screen()
{

}