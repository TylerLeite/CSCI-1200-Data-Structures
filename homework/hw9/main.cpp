#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <vector>

#include "image.h"

// ===================================================================================================
// ===================================================================================================

//contains info used in creating the offset image
struct OffsetInfo {
    OffsetInfo(int x, int y, const Color& color) :
        x(x), y(y), color(color)
    {}

    int x, y; //x and y in original image
    Color color;
};

//removes the need for a map and list to sort keys of the map
struct OffsetInfoVec {
    OffsetInfoVec(int key) : key(key) {}

    void push_back(const OffsetInfo& inf){offsets.push_back(inf);}
    unsigned size() const {return offsets.size();}
    
    bool operator<(const OffsetInfoVec& rhs) const {
        return offsets.size() > rhs.offsets.size(); //biggest vecs first
    }
    OffsetInfo operator[](int pos) {return offsets[pos];}

    int key;
    std::vector<OffsetInfo> offsets;
};

void Compress(const Image<Color> &input, 
              Image<bool> &occupancy, Image<Color> &hash_data, Image<Offset> &offset){

    int width = input.Width();
    int height = input.Height();
    
    //get number of non-white pixels and fill the occupancy image
    int p = 0;
    occupancy = Image<bool>(width, height);
    for (int x = 0; x < width; x++){
        for (int y = 0; y < height; y++){
            if (!input.GetPixel(x, y).isWhite()){
                p++;
                occupancy.SetPixel(x, y, true);
            }
        }
    }
    
    //pick size for hash_data and offset
    int s_hash = std::ceil(std::sqrt(1.01f*p));
    int s_off  = std::ceil(std::sqrt(p/4.0f));

    while (true){
        //iniialize other output images
        offset = Image<Offset>(s_off, s_off);
        hash_data = Image<Color>(s_hash, s_hash);
        
        //find how many collisions there are per pixel in the offset image
        std::vector<OffsetInfoVec> offsets; 
        for (int x = 0; x < width; x++){
            for (int y = 0; y < height; y++){
                if (!input.GetPixel(x, y).isWhite()){
                    int off_x = x%s_off;
                    int off_y = y%s_off;
                    
                    int key = off_x + off_y*s_off; //for infovec
                    OffsetInfo info(x, y, input.GetPixel(x, y));

                    bool already = false; //already have a pixel with that offset
                    for (int i = 0; i < offsets.size(); i++){
                        if (offsets[i].key == key){
                            offsets[i].push_back(info);
                            already = true;
                        }
                    }
                    
                    if (!already){ //first pixel with that offset
                        OffsetInfoVec infovec(key);
                        infovec.push_back(info);
                        offsets.push_back(infovec);
                    }
                }
            }
        }
        
        std::sort(offsets.begin(), offsets.end());
        
        for (int i = 0; i < offsets.size(); i++){
            Offset next_off;
            
            //loop through all possible offsets and try the offset on all colors at 
            // that location. if there is a collision, go to next offset
            for (int dx = 0; dx < 16; dx++){ //have size limits
                next_off.dx = dx;
                for (int dy = 0; dy < 16; dy++){
                    bool works = true;
                    next_off.dy = dy;
                    
                    std::vector<int> tried; //make sure there are no collisions 
                                            // within the offset pixel
                    for (int j = 0; j < offsets[i].size(); j++){
                        OffsetInfo info = offsets[i][j];
                        
                        //find position in hash_data to be placed
                        int hash_x = (info.x+dx)%s_hash;
                        int hash_y = (info.y+dy)%s_hash;
                        
                        int key = hash_x + hash_y*s_hash; //position as one number
                        
                        if (!hash_data.GetPixel(hash_x, hash_y).isWhite()){
                            works = false; //taken by another offset's pixel
                        } else {
                            for (int k = 0; k < tried.size(); k++){
                                if (tried[k] == key){ //taken by this offset's pixel
                                    works = false;
                                    break;
                                }
                            }
                        }
                        
                        if (!works) {
                            break;
                        } else {
                            tried.push_back(key);
                        }
                    }
                    
                    if (works){
                        //mark changes in offset
                        int off_x = offsets[i].key%s_off;
                        int off_y = (offsets[i].key-off_x)/s_off;
                        offset.SetPixel(off_x, off_y, next_off);
                        
                        //mark changes in hash_data
                        for (int j = 0; j < offsets[i].size(); j++){
                            OffsetInfo info = offsets[i][j];
                            int hash_x = (info.x+dx)%s_hash;
                            int hash_y = (info.y+dy)%s_hash;
                            
                            hash_data.SetPixel(hash_x, hash_y, info.color);
                        }
                       
                        goto next_itr; //only using goto to avoid bools and several
                                       // if statements
                    } else {
                        continue;
                    }
                }
            }
            
            //found no solution
            s_hash++;
            s_off++;
            goto start_over;
            
            next_itr: //move to next infovec
                continue;
        }
        
        break; //found a solution
        
        start_over:
            continue; //try again
    }
}

void UnCompress(const Image<bool> &occupancy, const Image<Color> &hash_data, 
                const Image<Offset> &offset,  Image<Color> &output){
                
    int width = occupancy.Width();
    int height = occupancy.Height();
    
    output = Image<Color>(width, height);
    
    for (int x = 0; x < width; x++){
        for (int y = 0; y < height; y++){
            if (occupancy.GetPixel(x, y)){ //colored pixels
                //get pixel in offset
                int off_x = x%offset.Width();
                int off_y = y%offset.Height();
                
                Offset cur_off = offset.GetPixel(off_x, off_y);
                
                //find the offset
                unsigned char dx = cur_off.dx;
                unsigned char dy = cur_off.dy;
                
                //get the color from hash_data
                int hash_x = (x+dx)%hash_data.Width();
                int hash_y = (y+dy)%hash_data.Height();
                
                Color next_color = hash_data.GetPixel(hash_x, hash_y);
                
                //set the output's pixel to the color
                output.SetPixel(x, y, next_color);
            } else { //white pixels
                output.SetPixel(x, y, Color()); //pixel should already be white
            }
        }
    }
}


// ===================================================================================================
// ===================================================================================================

// Takes in two 24-bit color images as input and creates a b&w output
// image (black where images are the same, white where different)
void Compare(const Image<Color> &input1, const Image<Color> &input2, Image<bool> &output) {

  // confirm that the files are the same size
  if (input1.Width() != input2.Width() ||
      input1.Height() != input2.Height()) {
    std::cerr << "Error: can't compare images of different dimensions: " 
         << input1.Width() << "x" << input1.Height() << " vs " 
         << input2.Width() << "x" << input2.Height() << std::endl;
  } else {
    // make sure that the output images is the right size to store the
    // pixel by pixel differences
    output.Allocate(input1.Width(),input1.Height());
    int count = 0;
    for (int i = 0; i < input1.Width(); i++) {
      for (int j = 0; j < input1.Height(); j++) {
        Color c1 = input1.GetPixel(i,j);
        Color c2 = input2.GetPixel(i,j);
        if (c1.r == c2.r && c1.g == c2.g && c1.b == c2.b)
          output.SetPixel(i,j,true);
        else {
          count++;
          output.SetPixel(i,j,false);
        }
      }      
    }     

    // confirm that the files are the same size
    if (count == 0) {
      std::cout << "The images are identical." << std::endl;
    } else {
      std::cout << "The images differ at " << count << " pixel(s)." << std::endl;
    }
  }
}

// ===================================================================================================
// ===================================================================================================

// to allow visualization of the custom offset image format
void ConvertOffsetToColor(const Image<Offset> &input, Image<Color> &output) {
  // prepare the output image to be the same size as the input image
  output.Allocate(input.Width(),input.Height());
  for (int i = 0; i < output.Width(); i++) {
    for (int j = 0; j < output.Height(); j++) {
      // grab the offset value for this pixel in the image
      Offset off = input.GetPixel(i,j);
      // set the pixel in the output image
      int dx = off.dx;
      int dy = off.dy;
      assert (dx >= 0 && dx <= 15);
      assert (dy >= 0 && dy <= 15);
      // to make a pretty image with purple, cyan, blue, & white pixels:
      int red = dx * 16;
      int green = dy *= 16;
      int blue = 255;
      assert (red >= 0 && red <= 255);
      assert (green >= 0 && green <= 255);
      output.SetPixel(i,j,Color(red,green,blue));
    }
  }
}

// ===================================================================================================
// ===================================================================================================

void usage(char* executable) {
  std::cerr << "Usage:  4 options" << std::endl;
  std::cerr << "  1)  " << executable << " compress input.ppm occupancy.pbm data.ppm offset.offset" << std::endl;
  std::cerr << "  2)  " << executable << " uncompress occupancy.pbm data.ppm offset.offset output.ppm" << std::endl;
  std::cerr << "  3)  " << executable << " compare input1.ppm input2.ppm output.pbm" << std::endl;
  std::cerr << "  4)  " << executable << " visualize_offset input.offset output.ppm" << std::endl;
}

// ===================================================================================================
// ===================================================================================================

int main(int argc, char* argv[]) {
  if (argc < 2) { usage(argv[0]); exit(1); }

  if (argv[1] == std::string("compress")) {
    if (argc != 6) { usage(argv[0]); exit(1); }
    // the original image:
    Image<Color> input;
    // 3 files form the compressed representation:
    Image<bool> occupancy;
    Image<Color> hash_data;
    Image<Offset> offset;
    input.Load(argv[2]);
    Compress(input,occupancy,hash_data,offset);
    // save the compressed representation
    occupancy.Save(argv[3]);
    hash_data.Save(argv[4]);
    offset.Save(argv[5]);

  } else if (argv[1] == std::string("uncompress")) {
    if (argc != 6) { usage(argv[0]); exit(1); }
    // the compressed representation:
    Image<bool> occupancy;
    Image<Color> hash_data;
    Image<Offset> offset;
    occupancy.Load(argv[2]);
    hash_data.Load(argv[3]);
    offset.Load(argv[4]);
    // the reconstructed image
    Image<Color> output;
    UnCompress(occupancy,hash_data,offset,output);
    // save the reconstruction
    output.Save(argv[5]);
  
  } else if (argv[1] == std::string("compare")) {
    if (argc != 5) { usage(argv[0]); exit(1); }
    // the original images
    Image<Color> input1;
    Image<Color> input2;    
    input1.Load(argv[2]);
    input2.Load(argv[3]);
    // the difference image
    Image<bool> output;
    Compare(input1,input2,output);
    // save the difference
    output.Save(argv[4]);

  } else if (argv[1] == std::string("visualize_offset")) {
    if (argc != 4) { usage(argv[0]); exit(1); }
    // the 8-bit offset image (custom format)
    Image<Offset> input;
    input.Load(argv[2]);
    // a 24-bit color version of the image
    Image<Color> output;
    ConvertOffsetToColor(input,output);
    output.Save(argv[3]);

  } else {
    usage(argv[0]);
    exit(1);
  }
}

// ===================================================================================================
// ===================================================================================================
