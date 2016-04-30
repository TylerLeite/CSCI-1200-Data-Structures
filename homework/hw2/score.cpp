#include "score.h"

int Score::getScoreFor(int framenum) const {
    if (framenum <= -1 || framenum >= 10){
        //terminate recursion and only use the 11th frame to score a strike in
        //the 10th
        return 0;
    }
    
    Frame frame = frames[framenum];
    int score = -1;
    if (frame.isStrike()){
        if (framenum < 9){
            //score of the next two throws
            int next_two_balls = getFlatScoreFor(framenum + 1);
            if (frames[framenum+1].isStrike()){ 
                //go to the next-next frame only if the next frame was a strike
                next_two_balls += frames[framenum+2].getThrow1();
            }
            score = 10 + next_two_balls;
        } else if (framenum == 9){
            //frame 10 will only ever look to frame 11
            int next_frame = getFlatScoreFor(10); //always frame 11
            score = 10 + next_frame;
        }
    } else if (frame.isSpare()){
        //will never go out of bounds
        int next_frame_first_throw = frames[framenum+1].getThrow1();
        score = 10 + next_frame_first_throw;
    } else {
        score = frames[framenum].getThrow1() + frames[framenum].getThrow2();
    }

    return score + getScoreFor(framenum-1);
}
