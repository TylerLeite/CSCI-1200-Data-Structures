#include <iostream>

void compute_squares(unsigned* a, unsigned* b, unsigned n){
    for (int i = 0; i < n; i++){
        *(b+i) = *(a+i) * *(a+i);
    }
}

int main(){
    unsigned a[6] = {0, 1, 2, 3, 4, 5};
    unsigned b[6];
    unsigned n = 6;

    unsigned a2[8] = {100, 842, -5, 5, 0, 99, 13423, 94};
    unsigned b2[8];
    unsigned n2 = 8;

    compute_squares(a, b, n);
    
    for (int i = 0; i < n; i++){
        std::cout << b[i] << std::endl;  
    }

    compute_squares(a2, b2, n2);
    for (int i = 0; i < n2; i++){
        std::cout << b2[i] << std::endl;  
    }
}
