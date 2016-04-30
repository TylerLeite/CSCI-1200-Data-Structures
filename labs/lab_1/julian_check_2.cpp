#include <iostream>

//const array associating month number to days in that month
const int DaysInMonth[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

//return whether a leap day should be added
bool is_leap_year(int year){
    return (year % 4 == 0) && ((year % 100 != 0 || year % 400 == 0));
}

//convert month, day, and year to julian day
int julian_day(int month, int day, int year){
    int jday = 0;

    for (unsigned int m=1; m < month; m++){
        jday += DaysInMonth[m];
        if (m == 2 && is_leap_year(year)){
            jday++; //leap day
        }
    }

    jday += day;
    return jday;
}

int main(){
    int in_months[10]   = {0}; //input months
    int in_days[10]     = {0}; //input days
    int julian_days[10] = {0}; //output
    const int year = 2014;

    for (int i = 0; i < 10; i++){
        std::cout << "Please enter month-day combo number " << i+1 << ": ";
        std::cin >> in_months[i] >> in_days[i];

        julian_days[i] = julian_day(in_months[i], in_days[i], year);
    }

    std::cout << "Julian days: " << std::endl;
    for (int i = 0; i < 10; i++){
        std::cout << "\t" << in_months[i] << "/" << in_days[i] << " -> " << julian_days[i] << std::endl;
    }
    
    return 0;
}
