#include <iostream>
#include <vector>

struct Point {
    Point(int x, int y) : x(x), y(y) {}

    int x, y;
};

std::vector<std::vector<Point> > recursive_find_all_paths(int x, int y){
    std::vector<std::vector<Point> > out;

    if (x == 0 && y == 0){
        std::vector<Point> tmp;
        tmp.push_back(Point(0, 0));
        out.push_back(tmp);
        return out;
    } else {
        if (x > 0){
            std::vector<std::vector<Point> > tmp = recursive_find_all_paths(x-1, y);
            for (int i = 0; i < tmp.size(); i++){
                out.push_back(tmp[i]);
            }
        }
        
        if (y > 0){
            std::vector<std::vector<Point> > tmp = recursive_find_all_paths(x, y-1);
            for (int i = 0; i < tmp.size(); i++){
                out.push_back(tmp[i]);
            }
        }
        
        for (int i = 0; i < out.size(); i++){
            out[i].push_back(Point(x, y));
        }
    }

    return out;
}

int main(int argc, char** argv){
    int x, y;
    std::cout << "Please enter a start x and a start y: ";
    std::cin >> x >> y;

    std::vector<std::vector<Point> > paths;
    paths = recursive_find_all_paths(x, y);
    
    std::cout << paths.size() << std::endl;

    return 0;

    for (int i = 0; i < paths.size(); i++){
        for (int j = 0; j < paths[i].size(); j++){
            std::cout << "(" << paths[i][j].x << ", " << paths[i][j].y << ") ";
        }
        std::cout << std::endl;
    }
    
}
