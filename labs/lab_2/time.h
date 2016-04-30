#ifndef TIME_H
#define TIME_H

#include <iostream>
#include <sstream>
#include <string>

class Time {
    public:
        Time();
        Time(int hour, int minute, int second);

        int getHour() const;
        int getMinute() const;
        int getSecond() const;

        std::string printAmPm();

        void setHour(int hour);
        void setMinute(int minute);
        void setSecond(int second);

        bool operator<(Time& rhs);

        friend std::ostream& operator<<(std::ostream& out, const Time& time);
        
    protected:
        int hour, minute, second;
};

#endif
