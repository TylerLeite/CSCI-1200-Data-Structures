#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

#include "time.h"

bool isEarlierThan(const Time& lhs, const Time& rhs){
    if (lhs.getHour() < rhs.getHour()){
        return true;
    } else if (lhs.getHour() == rhs.getHour() && lhs.getMinute() < rhs.getMinute()){
        return true;
    } else if (lhs.getMinute() == rhs.getMinute() && lhs.getSecond() < rhs.getSecond()){
        return true;
    } else {
        return false;
    }
}

int main(int argc, char** argv){
    srand(time(NULL));

    std::vector<Time> times;

    for (int i = 0; i < 10; i++){
        int hour = rand()%24;
        int minute = rand()%60;
        int second = rand()%60;
        times.push_back(Time(hour, minute, second));
    }

    sort(times.begin(), times.end(), isEarlierThan);

    std::vector<Time>::iterator it = times.begin();
    for (; it != times.end(); it++){
        it->printAmPm();
    }
    
    return 0;
}
