#ifndef READ_WRITE_SCORE_H
#define READ_WRITE_SCORE_H

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>

#include "score.h"

bool lastNameComp(const Score& lhs, const Score& rhs);

class ReadWriteScore {
    public:
        ReadWriteScore(std::string in_filename, std::string out_filename) :
            in_filename(in_filename), out_filename(out_filename),
            longest_name(0)
        {}
    
        void input();
        void output();

        //helper functions
        void outputFirstLine(int cur_score, std::ofstream& file);
        void outputSecondLine(int cur_score, std::ofstream& file);
        void outputFinalScores(std::ofstream& file);
        void outputCustomStat(std::ofstream& file);
    
    protected:
        std::vector<Score> scores;
        int longest_name;
        std::string in_filename, out_filename;
};

#endif
