#include "read_write_score.h"

void ReadWriteScore::input(){
    std::ifstream file(in_filename.c_str());

    if (!file.good()){
        std::cerr << "Cannot find file \"" << in_filename << "\"" << std::endl;
    }
    
    std::string line; //stringstreastring
    while(getline(file, line)){
        std::stringstream file_ss(line);
        Score current_score;

        //load names from file
        std::string first_name, last_name;
        file_ss >> first_name  >> last_name;
        std::string full_name = first_name + std::string(" ") + last_name;
        std::replace(full_name.begin(), full_name.end(), '_', ' ');
        current_score.name = full_name;
        current_score.last_name = last_name;

        //name length = characters in name + 1 space on either side + 1 space 
        // between the names
        int name_length = first_name.size() + last_name.size() + 1;
        if (name_length > longest_name) {
            longest_name = name_length;
        }

        //load frames
        int frame_ct = 0; //current working frame
        while (frame_ct < 11) {
            int throw_1 = 0, throw_2 = 0;
            if (!(file_ss >> throw_1)){
                break; //stop reading if the line is finished
            }
            
            if (throw_1 != 10 || frame_ct == 10){ //11th frame can be 2 strikes
                file_ss >> throw_2;
            }

            if (throw_1 < 0 || throw_1 > 10
             || throw_2 < 0 || throw_2 > 10){
                std::cerr << "Invalid throw for " << current_score.name 
                          << "in frame " << frame_ct+1 << std::endl;
                exit(1);
            }

            Frame frame(frame_ct, throw_1, throw_2);
            current_score.frames[frame_ct] = frame;
            frame_ct++;
        }

        if (frame_ct < 10){
            std::cerr << "Not enough frames were parsed for " 
                      << current_score.name << std::endl;
            exit(1);
        }

        scores.push_back(current_score);
    }
}

bool lastNameComp(const Score& lhs, const Score& rhs) {
    bool less = lhs.last_name < rhs.last_name;
    bool great = lhs.last_name > rhs.last_name;
    
    if (!less && !great){
        return lhs.name < rhs.name;
    } else {
        return less;
    }
}

void ReadWriteScore::output(){
    std::ofstream file(out_filename.c_str());
    int len = longest_name + 66; //whole line minus the name is 66 characters
    
    std::sort(scores.begin(), scores.end(), lastNameComp);

    file << std::string(len, '-') << std::endl; //top
    for (int i = 0; i < scores.size(); i++){
        outputFirstLine(i, file); //name and individual frame scores
        outputSecondLine(i, file); //total score by each frame
        file << std::string(len, '-') << std::endl; //bottom / seperators
    }

    outputFinalScores(file);
    outputCustomStat(file);
}

//cur_score is the current place in the scores vector
void ReadWriteScore::outputFirstLine(int cur_score, std::ofstream& file){
    //name, dont forget to add padding so it lines up with the longest name
    std::string whitespace(longest_name+1-scores[cur_score].name.size(), ' ');
    file << "| " << scores[cur_score].name << whitespace;

    //scores, special cases for strikes, spares, and gutterballs
    for (int i = 0; i < 9; i++){
        if (scores[cur_score].frames[i].isStrike()){
            file << "|   X ";
        } else if (scores[cur_score].frames[i].isSpare()){
            if (scores[cur_score].frames[i].getThrow1() == 0){
                file << "| - / ";
            } else {
                file << "| " << scores[cur_score].frames[i].getThrow1()
                     << " / ";
            }
        } else if (scores[cur_score].frames[i].getThrow1() == 0){
            if (scores[cur_score].frames[i].getThrow2() == 0){
                file << "| - - ";
            } else {
                file << "| - " << scores[cur_score].frames[i].getThrow2() 
                     << " ";
            }
        } else if (scores[cur_score].frames[i].getThrow2() == 0){
            //throw_1 will be nonzero
            file << "| " << scores[cur_score].frames[i].getThrow1() << " - ";
        } else {
            file << "| " << scores[cur_score].frames[i].getThrow1() 
                 << " " << scores[cur_score].frames[i].getThrow2() << " ";
        }
    }

    //10th frame score is weird
    if (scores[cur_score].frames[9].isStrike()){
        file << "| X ";
    } else if (scores[cur_score].frames[9].isSpare()){
        if (scores[cur_score].frames[9].getThrow1() == 0){
            file << "| - / ";
        } else {
            file << "| " << scores[cur_score].frames[9].getThrow1() << " / ";
        }
    } else if (scores[cur_score].frames[9].getThrow1() == 0){
        if (scores[cur_score].frames[9].getThrow2() == 0){
            file << "| - -   |" << std::endl; 
            return;
        } else {
            file << "| - " << scores[cur_score].frames[9].getThrow2() << "   |"
                 << std::endl;
            return;
        }
    } else if (scores[cur_score].frames[9].getThrow2() == 0){
        file << "| " << scores[cur_score].frames[9].getThrow1() << " -   |"
             << std::endl;
        return;
    } else {
        file << "| " << scores[cur_score].frames[9].getThrow1() << " "
             << scores[cur_score].frames[9].getThrow2() << "   |" << std::endl; 
        return;
    }

    //this is if there was a strike or spare in the 10th frame

    //11th frame, first throw
    if (scores[cur_score].frames[10].getThrow1() == 10){
        file << "X ";
        if (!scores[cur_score].frames[9].isStrike()){
            file << "|" << std::endl;
            return;
        }
    } else if (scores[cur_score].frames[10].isSpare()){
        file << scores[cur_score].frames[10].getThrow1() << " / |" << std::endl;
        return;
    } else if (scores[cur_score].frames[10].getThrow1() == 0){
        file << "- ";
    } else {
         file << scores[cur_score].frames[10].getThrow1() << " ";
    }

    //11th frame, second throw
    if (scores[cur_score].frames[10].getThrow2() == 10){
        file << "X ";
    } else if (!scores[cur_score].frames[9].isStrike()){
        //everything after this only happens if frame 10 was a strike
        file << "|" << std::endl; 
        return;
    } else if (scores[cur_score].frames[10].getThrow2() == 0){
        file << "- ";
    } else {
        file << scores[cur_score].frames[10].getThrow2() << " ";
    }

    //end of first line
    file << "|" << std::endl; 
}

void ReadWriteScore::outputSecondLine(int cur_score, std::ofstream& file){
    //name
    std::string whitespace(longest_name - scores[cur_score].name.size(), ' ');
    file << "| " << std::string(longest_name, ' ') << " ";  
    
    //scores
    for (int i = 0; i < 9; i++){
        int score_so_far = scores[cur_score].getScoreFor(i);
        if (score_so_far > 99){ //3-digit number
            whitespace = " ";
        } else if (score_so_far > 9){ //2-digit number
            whitespace = "  ";
        } else { //single-digit number
            whitespace = "   ";
        }

        file << "|" << whitespace << score_so_far << " ";
    }

    //make it so single- and 2-digit scores dont mess with formatting
    int total_score = scores[cur_score].getScoreFor(9);
    if (total_score > 99){
        whitespace = "   ";
    } else if (total_score > 9){
        whitespace = "    ";
    } else {
        whitespace = "     ";
    }
    file << "|" << whitespace << total_score << " ";

    //end of second line
    file << "|" << std::endl;
}

void ReadWriteScore::outputFinalScores(std::ofstream& file){
    file << std::endl;

    //sort from smallest to biggest, then reverse
    std::sort(scores.begin(), scores.end());
    std::reverse(scores.begin(), scores.end());
    
    for (int cur_score = 0; cur_score < scores.size(); cur_score++){
        //whitespace is the difference between the longest and curent name + 1
        //for general padding
        std::string whitespace(longest_name+1-scores[cur_score].name.size(), 
                               ' ');
        file << scores[cur_score].name << whitespace;

        //make it so single- and 2-digit scores dont mess with formatting again
        int total_score = scores[cur_score].getScoreFor(9);
        if (total_score > 99){
            whitespace = " ";
        } else if (total_score > 9){
            whitespace = "  ";
        } else {
            whitespace = "   ";
        }

        file << whitespace << total_score << std::endl;
    }
}

//average strike rate
void ReadWriteScore::outputCustomStat(std::ofstream& file){
    std::map<std::string, float> strike_rates; //by person
    //names of the best and worst players
    std::string best_pl, worst_pl;
    //strike rates of the best and worst players
    float best_rate = 0.0f, worst_rate = 1.0f, avg_rate = 0.0f;
    float num_pl = 0.0f; //account for possible duplicate names

    //first record who got what strike rate
    for (int i = 0; i < scores.size(); i++){
        if (strike_rates.find(scores[i].name) == strike_rates.end()){
            strike_rates.insert(
                std::pair<std::string, float>(scores[i].name, -1.0f)
                );
            num_pl++;
        }

        float strike_avg = 0.0f; //how many frames were strikes
        for (int j = 0; j < 10; j++){
            if (scores[i].frames[j].isStrike()){
                strike_avg++;
            }
        }

        if (scores[i].frames[10].getThrow1() == 10){
            if (scores[i].frames[10].getThrow2() == 10){
                strike_avg += 2;
            } else {
                strike_avg ++;
            }
        }

        //count the last frame as 3 if there was a strike (even if the 11th
        // frame was like a single frame)
        if (scores[i].frames[9].isStrike()){
            if (scores[i].frames[10].isStrike()){
                //first throw of the 11th frame is a strike
                strike_avg /= 12.0f;
            } else {
                strike_avg /= 11.0f;
            }
        } else if (scores[i].frames[9].isSpare()){
            //else count the last frame as 2 if there was a spare
            strike_avg /= 11.0f;
        } else {
            //else count it as 1
            strike_avg /= 10.0f;
        }

        if (strike_rates[scores[i].name] == -1.0f){
            strike_rates[scores[i].name] = strike_avg;
        } else {
            strike_rates[scores[i].name] = (strike_rates[scores[i].name]
                                         + strike_avg)/2.0f;
        }
    }
    std::map<std::string, float>::iterator map_it = strike_rates.begin();
    for (; map_it != strike_rates.end(); map_it++){
        if (map_it->second == -1.0f){
            map_it->second = 0.0f;
        }
    }

    map_it = strike_rates.begin();
    for (; map_it != strike_rates.end(); map_it++){
        avg_rate += map_it->second;
        if (map_it->second > best_rate){
            best_rate = map_it->second;
            best_pl = "\n\t" + map_it->first;
        } else if (map_it->second == best_rate){
            best_pl += "\n\t" + map_it->first;
        }
        //no else, could be 0
        if (map_it->second < worst_rate){
            worst_rate = map_it->second;
            worst_pl = "\n\t" + map_it->first;
        } else if (map_it->second == worst_rate){
            worst_pl += "\n\t" + map_it->first;
        }
    }

    avg_rate /= num_pl;

    //truncated not rounded, % to 1 decimal
    avg_rate = floor(1000.0f*avg_rate)/10.0f;
    best_rate = floor(1000.0f*best_rate)/10.0f;
    worst_rate = floor(1000.0f*worst_rate)/10.0f;
    
    file << std::endl
         << "The average strike rate was " << avg_rate << "%"
         << std::endl << std::endl
         << "The best strike rate was " << best_rate << "%" 
            << " by: " << best_pl
         << std::endl << std::endl
         << "The worst strike rate was " << worst_rate << "%"
            << " by: " << worst_pl 
         << std::endl;
}
