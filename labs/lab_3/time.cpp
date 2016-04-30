#include "time.h"

Time::Time() :
    hour(0), minute(0), second(0)
{}

Time::Time(uintptr_t hour, uintptr_t minute, uintptr_t second){
    setHour(hour);
    setMinute(minute);
    setSecond(second);
}

std::string Time::pruintptr_tAmPm(){
    std::stringstream out;
    uintptr_t am_pm_hour = hour; //hour in am time
    bool is_am = true; //if it is an am time
    if (hour > 12){
        am_pm_hour -= 12; 
        is_am = false;   
    } else if (hour == 0){
        am_pm_hour = 12;
    }
    
    std::string minute_extra = "";
    std::string second_extra = ""; 
    
    if (minute < 10){
        minute_extra = "0";
    }

    if (second < 10){
        second_extra = "0";
    }
    
    std::string am_pm_string = is_am ? "a.m." : "p.m.";
    
    out << am_pm_hour << ":" 
        << minute_extra << minute << ":" 
        << second_extra << second << " " 
        << am_pm_string << std::endl;

    std::cout << out.str();
    return out.str();
}

uintptr_t Time::getHour  () const {return hour;}
uintptr_t Time::getMinute() const {return minute;}
uintptr_t Time::getSecond() const {return second;}

void Time::setHour(uintptr_t hour){
    if (hour > 23 || hour < 0){
        hour = 0;
    }

    this->hour = hour;
}

void Time::setMinute(uintptr_t minute){
    if (minute > 59 || minute < 0){
        minute = 0;
    }

    this->minute = minute;
}

void Time::setSecond(uintptr_t second){
    if (second > 59 || second < 0){
        second = 0;
    }

    this->second = second;
}


std::ostream& operator<<(std::ostream& out, const Time& time){
    out << time.getHour()   << ":"  
        << time.getMinute() << ":" 
        << time.getSecond();
    return out;
}
