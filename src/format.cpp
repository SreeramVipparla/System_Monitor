#include <string>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) { 
    long int time = seconds;
    long int hour = time / 3600;
    time%= 3600;
    long int minutes = time / 60;
    time %= 60;
    long int sec = time;

    return std::to_string(hour) + ":" + std::to_string(minutes) + ":" + std::to_string(sec);
}