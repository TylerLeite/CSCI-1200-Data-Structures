#ifndef SCORE_H
#define SCORE_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class Frame {
    public:
        Frame() :
            framenum(-1),
            throw_1(-1), throw_2(-1)
        {}

        Frame(int framenum, int throw_1, int throw_2) :
            framenum(framenum),
            throw_1(throw_1), throw_2(throw_2)
        {}
    
        int getFramenum() const {return framenum;}
        
        int getThrow1() const {return throw_1;}
        int getThrow2() const {return throw_2;}

        bool isStrike() const {return throw_1 == 10;}
        bool isSpare() const {return !isStrike() && throw_2 + throw_1 == 10;}

        bool operator==(const Frame& rhs){
            return throw_1 == rhs.throw_1 && throw_2 == rhs.throw_2;
        }

        Frame& operator=(const Frame& rhs){
            framenum = rhs.framenum;
            throw_1 = rhs.throw_1;
            throw_2 = rhs.throw_2;

            return *this;
        }

        
    protected:    
        int framenum; // frame number, 0 - 10
        int throw_1, throw_2; //throw_3 is only used if framenum == 10
};

class Score {
    public:
        std::string name;
        std::string last_name;
        
        int getFlatScoreFor(int framenum) const { //spares and strikes return 10
            Frame frame = frames[framenum];
            return frame.getThrow1() + frame.getThrow2();
        }
        
        int getScoreFor(int framenum) const;

        bool operator<(const Score& rhs) const {
            return getScoreFor(9) < rhs.getScoreFor(9);
        }

        Frame frames[11]; //treat the last frame as two frames
};

#endif
