#include <iostream>

#include "read_write_score.h"

int main(int argc, char** argv){
    if (argc != 3){
        std::cerr << "Invalid number of arguments: " << argc << std::endl
                  << "Usage: main in_file out_file" << std::endl;
        return 0;
    }

    std::string in_file(argv[1]);
    std::string out_file(argv[2]);

    ReadWriteScore rws(in_file, out_file);
    rws.input();
    rws.output();

    return 0;
}
