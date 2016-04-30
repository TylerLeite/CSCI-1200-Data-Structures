/*
    HOMEWORK 1: MOIRE STRINGS
    NAME:  Tyler Leite
*/

#include <cstdlib>
#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

bool writeVectorToFile(std::vector<std::string>& output, std::string& filename);
std::vector<std::string> drawSquare(std::string& text, int height);
std::vector<std::string> drawRightTriangle(std::string& text, int height);
std::vector<std::string> drawisoscelesTriangle(std::string& text, int height);
std::vector<std::string> drawRandom(std::string& text, int height);
std::vector<std::string> drawHourglass(std::string& text, int height);

int main(int argc, char** argv){
    srand(time(NULL));

    //sanity check
    if (argc != 5){ 
        std::cerr << "Error: Invalid number of arguments \"" << argc << "\"!" 
                  << std::endl
                  << "Usage: moire text height type out_file" 
                  << std::endl;
        return 0;
    }

    //input
    std::string input_text = argv[1];
    std::string type = argv[3];
    std::string output_filename = argv[4];
    int height = atoi(argv[2]);

    //more sanity checking
    if (height <= 0){ 
        std::cerr << "Error: Height must be a positive number!" << std::endl;
        return 0;
    }

    //use the correct function based on input
    std::vector<std::string> moire_pattern;
    if (type == "square"){
        moire_pattern = drawSquare(input_text, height);
    } else if (type == "right_triangle"){
        moire_pattern = drawRightTriangle(input_text, height);
    } else if (type == "isosceles_triangle"){
        moire_pattern = drawisoscelesTriangle(input_text, height);
    } else if (type == "random"){
        moire_pattern = drawRandom(input_text, height);
    } else if (type == "hourglass"){
        moire_pattern = drawHourglass(input_text, height);
    } else { 
        //if a pattern isnt found, let the user know
        std::cerr << "Error: Invalid shape \"" << type << "\"!" << std::endl;
        return 0;
    }

    //output
    if (writeVectorToFile(moire_pattern, output_filename)){
        std::cout << "Success! Wrote to \"" << output_filename << "\"" 
                  << std::endl; //success
    }

    return 0;
}

/** open or create the specified file and print the pattern to it */
bool writeVectorToFile(std::vector<std::string>& output, std::string& filename){
    //open the output file
    std::ofstream filestream(filename.c_str());
    
    if (!filestream.is_open()){
        std::cerr << "Error: Failed to create file \"" << filename << "\" \n";
        return false; //error
    } else {
        for (int line = 0; line < output.size(); line++){
            //std::cout << output[line] << std::endl; //debug only
            //write the pattern line-by-line
            filestream << output[line] << std::endl;
        }
        
        filestream.close();
        return true; //success
    }
}

/** draw a height*height square and fill it with text
      for each spot in the grid that the square will be drawn on, check if it is
      an edge. if it is, print a "*", else print the next character from text
*/
std::vector<std::string> drawSquare(std::string& text, int height){
    std::vector<std::string> moire_pattern; //the output
    int position_in_text = 0; //track which character in the string is next
    
    for (int y = 0; y < height; y++){
        std::string current_line = "";
        for (int x = 0; x < height; x++){
            if (y == 0 || y == height-1 || x == 0 || x == height-1){ 
                //edges are asterisks
                current_line += "*";
            } else { 
                //everything else is the text
                current_line += text[position_in_text];
                if (position_in_text == text.size()-1){
                    position_in_text = 0;
                } else {
                    position_in_text++;
                }
            }
        }

        //add the finished line to the output vector
        moire_pattern.push_back(current_line); 
    }
    
    return moire_pattern;
}

/** draw a right triangle with height "height" and fill it with text
      same idea as with the square, but x only goes to y+1 instead of height 
*/
std::vector<std::string> drawRightTriangle(std::string& text, int height){
    std::vector<std::string> moire_pattern; //the output
    int position_in_text = 0; //track which character in the string is next
    
    for (int y = 0; y < height; y++){
        std::string current_line = "";
        for (int x = 0; x < y+1; x++){
            if (y == 0 || y == height-1 || x == 0 || x == y){ 
                //edges are asterisks
                current_line += "*";
            } else { 
                //everthing else is text
                current_line += text[position_in_text];
                if (position_in_text == text.size()-1){
                    position_in_text = 0;
                } else {
                    position_in_text++;
                }
            }
        }

        //add the finished line to the output vector
        moire_pattern.push_back(current_line);
    }
    
    return moire_pattern;
}

/** draw an isosceles triangle with height "height" and fill it with text
      similar to square and isosceles, but the way the edges are determined is more
      complicated. for each line, the edge is at plus or minus (height-x-1), so
      that absolute value is checked to see if the current position in the loop is
      on an edge, outside the shape, or inside it. 
*/
std::vector<std::string> drawisoscelesTriangle(std::string& text, int height){
    std::vector<std::string> moire_pattern; //the output
    int position_in_text = 0; //track which character in the string is next
    
    for (int y = 0; y < height; y++){
        std::string current_line = "";
        for (int x = 0; x < height*2-1; x++){
            if (abs(height-x-1) - y == 0 || y == height-1){
                //edges are asterisks
                current_line += "*";
            } else if (abs(height-x-1) - y > 0){
                //everything outside the edges is whitespace
                current_line += " ";
            } else { 
                //everything else is text
                current_line += text[position_in_text];
                if (position_in_text == text.size()-1){
                    position_in_text = 0;
                } else {
                    position_in_text++;
                }
            }
        }

        //trim the whitespace so that the homework server accepts it
        for (int i = current_line.size()-1; i > 0; i--){
            if (current_line[i] != ' '){
                current_line.erase(i+1);
                break;
            }
        }

        //add the finished line to the output vector
        moire_pattern.push_back(current_line);
    }
    
    return moire_pattern;
}

/** draw a shape with variable width and fill it with text
      each line can be 1 char longer, 1 char shorter, or the same length as the
      previous line. the shape is centered at the end for aesthetic purposes
*/
std::vector<std::string> drawRandom(std::string& text, int height){
//20 mins
    std::vector<std::string> moire_pattern; //the output
    int position_in_text = 0; //track which character in the string is next
    int width = rand()%(height-1)+2; //initial width is between 2 and height
    
    for (int y = 0; y < height; y++){
        std::string current_line = "";

        //change the length by 0, 1, or -1
        width += rand()%3-1;
        if (width < 2){
            width = 2; //minimum width of 2
        } else if (width > height){
            width = height; //maximumm width of "height"
        }
        
        for (int x = 0; x < width; x++){
            if (y == 0 || y == height-1 || x == 0 || x == width-1){ 
                //edges are asterisks
                current_line += "*";
            } else {
                //everything else is the text
                current_line += text[position_in_text];
                if (position_in_text == text.size()-1){
                    position_in_text = 0;
                } else {
                    position_in_text++;
                }
            }
        }

        //center the shape
        int whitespace_needed = height-width;
        //half the whitespace on either side
        std::string whitespace = std::string(whitespace_needed/2, ' ');

        //finalize the centering
        current_line = whitespace + current_line;//+ whitespace;
        //current_line = current_line.substr(0, height-1);
        //add the finished line to the output vector
        moire_pattern.push_back(current_line);
    }
    
    return moire_pattern;
}


/** draw an hourglass shape and fill it with text 
      the hourglass is made by stacking two semi-circles edge-to-edge on top of
      each other. simple math was used to find the length of the circle at a
      given height and that equation is used to determine how much whitespace
      there should be inside the hourglass. with that value, finding how much
      space should be outside the circle is trivial. those values are used to 
      construct the hourglass line-by-line
*/
std::vector<std::string> drawHourglass(std::string& text, int height){
    std::vector<std::string> moire_pattern; //the output
    int position_in_text = 0; //track which character in the string is next

    int radius = height/2;
    bool repeat = false;

    //compensate for truncation when odd heights are halved
    int oddHeight = height%2 != 0;
    for (int y = -radius; y < radius + oddHeight; y++){
        std::string current_line = "";
        int r2 = radius*radius; //radius squared shorthand
        //dy: height of the current line relative to the center
        int dy = (radius - abs(y))*(radius - abs(y));
        //in_circ: whitespace in the semi-circle
        int in_circ = ceil(2*sqrt(r2 - dy)); 
        //out_circ: whitespace on either side of the semi-circle
        int out_circ = floor((2*radius - in_circ)/2);
        int width = in_circ + out_circ + 2; //2 spaces for the outline
        
        //construct the current line
        for (int x = 0; x < width+1; x++){
            if (x < out_circ+1){
                //outside the circle is whitespace
                current_line += " ";
            } else if (x == out_circ + 1 || x == width 
                    || y == -radius || y == radius-1+oddHeight){
                //the edges
                current_line += "*";
            } else { 
                //everything else is text
                current_line += text[position_in_text];
                if (position_in_text == text.size()-1){
                    position_in_text = 0;
                } else {
                    position_in_text++;
                }
            }
        }
        
        moire_pattern.push_back(current_line);
    }
    
    return moire_pattern;
}

