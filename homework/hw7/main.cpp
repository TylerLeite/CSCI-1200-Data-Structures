#include <iostream>
#include <fstream>
#include <map>
#include <cassert>
#include <string>
#include <vector>
#include <list>
#include <algorithm>

#include <cstring>


// two data structures store all of the information for efficiency
typedef std::map<std::string, std::list<std::string> > LIBRARY_TYPE;
typedef std::map<std::string, std::list<std::string> > PEOPLE_TYPE;


// prototypes for the helper functions
void addItem(LIBRARY_TYPE& library);
void checkoutItem(LIBRARY_TYPE& library, PEOPLE_TYPE& people);
void returnItems(LIBRARY_TYPE& library, PEOPLE_TYPE& people);
void lookup(LIBRARY_TYPE& library);
void printPeople(PEOPLE_TYPE& people);

int main() {
    //std::string inFile = "custom_input.txt";
    //std::string outFile = "out.txt";
    //std::streambuf *cinBuf, *coutBuf;

    //std::ofstream out(outFile.c_str());
    //coutBuf = std::cout.rdbuf(); //save old buf
    //std::cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt

    //std::ifstream in(inFile.c_str());
    //cinBuf = std::cin.rdbuf(); //save old buf
    //std::cin.rdbuf(in.rdbuf()); //redirect std::cout to out.txt
    

  LIBRARY_TYPE library;
  PEOPLE_TYPE people;
  char c;
  while (std::cin >> c) {
    if (c == 'a') {
      addItem(library);
    } else if (c == 'c') {
      checkoutItem(library,people);
    } else if (c == 'r') {
      returnItems(library,people);
    } else if (c == 'l') {
      lookup(library);
    } else if (c == 'p') {
      printPeople(people);
    } else {
      std::cerr << "error unknown char " << c << std::endl;
      exit(0);
    }
  }

    //retore old bufs
}


void addItem(LIBRARY_TYPE& library) {
    std::string title;
    int num;
    std::cin >> num >> title;
 
    if (num < 1){
        std::cout << "can't add " << num << " copies of a book" << std::endl;
        return;
    } else {
        for (int i = 0; i < num; i++){
            library[title].push_back("");
        }
        
        std::cout << "added " << num << " cop";
        if (num == 1) std::cout << "y"; else std::cout << "ies";
        std::cout << " of " << title << std::endl;
    }
}


void checkoutItem(LIBRARY_TYPE& library, PEOPLE_TYPE& people) {
    std::string name;
    std::string title;
    std::cin >> name >> title;

    if (library.count(title) == 0){
        std::cout << "don't have " << title << " in library" << std::endl;
    } else {
        std::list<std::string>::iterator emptySpot = std::find(library[title].begin(), library[title].end(), "");
        if (std::find(people[name].begin(), people[name].end(), title) != people[name].end()){
                std::cout << name << " already has " << title << std::endl;
        } else if (emptySpot == library[title].end()){
          std::cout << "no copies of " << title << " available" << std::endl;
        } else {
            people[name].push_back(title);
            *emptySpot = name;
            std::cout << name << " checked out " << title << std::endl;
        }
    }
}
 

void returnItems(LIBRARY_TYPE& library, PEOPLE_TYPE& people) {
  std::string name;
  std::cin >> name;

    for (std::list<std::string>::iterator book = people[name].begin(); book != people[name].end(); book++){
        for (std::list<std::string>::iterator person = library[*book].begin(); person != library[*book].end(); person++){
            if (*person == name){
                *person = "";
            }
        }
    }

    int returned = people[name].size();
    people[name].clear(); //person has no books checked out anymore

    std::cout << name;
    if (returned > 0){
        std::cout << " returned " << returned << " item";
        if (returned > 1) std::cout << "s";
        std::cout << std::endl;
    } else {
        std::cout << " has no items checked out" << std::endl;
    }
}

bool comp(const std::string& a, const std::string& b){
    return strcmp(a.c_str(), b.c_str()) < 0;
}

void lookup(LIBRARY_TYPE& library) {
  std::string title;
  std::cin >> title;

  //check if book exists
    if (library.count(title) == 0){
        std::cout << "don't have " << title << " in library" << std::endl;
    } else {
        int available = 0;
        std::vector<std::string> checkersOut;
        for (std::list<std::string>::iterator person = library[title].begin(); person != library[title].end(); person++){
            if (*person == ""){
                available++;
            } else {
                checkersOut.push_back(*person);
            }
        }
        
        std::cout << "library info for: " << title << std::endl;
        
        if (available > 0){
            std::cout << "  " << available << " cop";
            if (available == 1) std::cout << "y"; else std::cout << "ies";
            std::cout << " available" << std::endl;
        }
        
        if (checkersOut.size() > 0){
            std::cout << "  " << checkersOut.size() << " cop";
            if (checkersOut.size() == 1) std::cout << "y"; else std::cout << "ies";
            std::cout << " checked out by:" << std::endl;
              
            //std::sort(checkersOut.begin(), checkersOut.end(), comp);
            
            for (int i = 0; i < checkersOut.size(); i++){
                std::cout << "    " << checkersOut[i] << std::endl;
            }
        }
    }
}

void printPeople(PEOPLE_TYPE& people) {
    std::list<std::string> names;
    for (PEOPLE_TYPE::iterator person = people.begin(); person != people.end(); person++){
        if (person->second.size() > 0){
            names.push_back(person->first);
        }
    }

    if (names.size() == 0){
        std::cout << "no books are currently checked out" << std::endl;
    }
    
    names.sort(comp);
    for (std::list<std::string>::iterator name = names.begin(); name != names.end(); name++){
        if (people[*name].size() > 0){ //redundant
            std::cout << *name << " has ";
            if (people[*name].size() == 1) std::cout << "this item"; else std::cout << "these items";
            std::cout << " checked out:" << std::endl;
            //print books person has (should already be in chronological order)
            for (std::list<std::string>::iterator book = people[*name].begin(); book != people[*name].end(); book++){
                std::cout << "  " << *book << std::endl;
            }
        }
    }
}
