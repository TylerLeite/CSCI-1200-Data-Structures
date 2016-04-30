#include <iostream>
#include <list>
#include <string>
#include <vector>

//reverse vector
template <typename T>
void reverse_vector(std::vector<T>& vec){
  //for lists/vectors of odd size, the middle element is never touched
    for (int i = 0; i < vec.size()/2; i++){
      //swap the nth element and the k-nth element
        T tmp = vec[i];
        vec[i] = vec[vec.size()-i-1];
        vec[vec.size()-i-1] = tmp;
    }
}

//reverse list (essentially same as reverse vector)
template <typename T>
void reverse_list(std::list<T>& list){
    typename std::list<T>::iterator f_it = list.begin();
    typename std::list<T>::reverse_iterator r_it = list.rbegin();
    for (int i = 0; i < list.size()/2; i++, f_it++, r_it++){
        T tmp = *r_it;
        *r_it = *f_it;
        *f_it = tmp;
    }
}

int main(int argc, char** argv){
{
    std::cout << "Bool vector, even number of elements (2):" << std::endl;
    std::vector<bool> bool_vec;
    bool_vec.push_back(false);
    bool_vec.push_back(true);

    reverse_vector(bool_vec);

    std::cout << "  " << bool_vec[0] << " " << bool_vec[1] << std::endl;
}
{
    std::cout << "Int vector, odd number of elements (99):" << std::endl;

    std::vector<int> int_vec;
    for (int i = 1; i < 100; i++){
        int_vec.push_back(i);
    }

    reverse_vector(int_vec);

    std::cout << "  ";
    std::vector<int>::iterator vec_it = int_vec.begin();
    int i = 0;
    for (; vec_it != int_vec.end(); vec_it++){
        if (i%26 == 0 && i != 0) std::cout << std::endl << "  ";
        std::cout << *vec_it << " ";
        i++;
    }

    std::cout << std::endl;
}
{
    std::cout << "Char list, even number of elements (26):" << std::endl;
    
    std::list<char> char_list;
    for (int i = 0; i < 26; i++){
        char_list.push_back((char)(97+i));
    }

    reverse_list(char_list);

    std::cout << "  ";
    std::list<char>::iterator list_it = char_list.begin();
    for (; list_it != char_list.end(); list_it++){
        std::cout << *list_it << " ";
    }
    
    std::cout << std::endl;
}
{
    std::cout << "String list, odd number of elements (7): " << std::endl;

    std::list<std::string> str_list;
    
    str_list.push_back("one");
    str_list.push_back("two");
    str_list.push_back("three");
    str_list.push_back("four");
    str_list.push_back("five");
    str_list.push_back("six");
    str_list.push_back("seven");
    
    reverse_list(str_list);

    std::cout << "  ";
    std::list<std::string>::iterator list_it = str_list.begin();
    for (; list_it != str_list.end(); list_it++){
        std::cout << *list_it << " ";
    }
    
    std::cout << std::endl;
}
{
    std::cout << "Null list test: " << std::endl;
    std::list<int> empty;

    reverse_list(empty);

    std::string out = "  This should be printed.";
    std::list<int>::iterator list_it = empty.begin();
    for (; list_it != empty.end(); list_it++){
        out = "  This should NOT be printed.";
    }

    std::cout << out << std::endl;
}
}
