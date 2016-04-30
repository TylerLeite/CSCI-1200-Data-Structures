#include <vector>
#include <map>
#include <string>
#include <iostream>

int main(){
    std::map<std::string, std::vector<std::string> > my_map;
    if (my_map["this"].size() == 0){
        std::cout << "works" << std::endl;
    } else {
        std::cout << "#not" << std::endl;
    }

    return 0;
}
