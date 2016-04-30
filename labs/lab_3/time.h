#ifndef TIME_H
#define TIME_H

#include <stdint.h>
#include <iostream>
#include <sstream>
#include <string>

class Time {
    public:
        Time();
        Time(uintptr_t hour, uintptr_t minute, uintptr_t second);

        uintptr_t getHour() const;
        uintptr_t getMinute() const;
        uintptr_t getSecond() const;

        std::string pruintptr_tAmPm();

        void setHour(uintptr_t hour);
        void setMinute(uintptr_t minute);
        void setSecond(uintptr_t second);

        bool operator<(Time& rhs);

        friend std::ostream& operator<<(std::ostream& out, const Time& time);
        
    protected:
        uintptr_t hour, minute, second;
};

#endif
