#include <iostream>

int main(){
    int float_count = 0; //how many floats are entered
    float float_arr[100] = {0}; //array to store input

    std::cout << "How many floats do you want to enter? ";
    std::cin >> float_count;

    if (float_count > 100){\
        float_count = 100;
    }

    float average = 0; //average of the input numbers
    
    for (int i = 0; i < float_count; i++){
        std::cout << "Please enter a float (" << i << "/" << float_count << "): ";
        std::cin  >> float_arr[i];
        average += float_arr[i];
    }

    average /= float_count;

    std::cout << "The average is: " << average << std::endl
              << "The following numbers were larger than average: "
              << std::endl;
    
    for (int i = 0; i < float_count; i++){
        if (float_arr[i] > average){
            std::cout << "\t" << float_arr[i] << " ";
        }
    }

    std::cout << std::endl;
}   
