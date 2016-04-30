#ifndef JAGGED_ARRAY_H
#define JAGGED_ARRAY_H

#include <iostream>

template <typename T>
class JaggedArray {
    public:
        JaggedArray(int num_bins) :
            num_bins(num_bins), num_elements(0), packed(false),
            packed_values(NULL), offsets(NULL), 
            unpacked_values(NULL), counts(NULL)
        {
            unpacked_values = new T*[num_bins];
            for (int i = 0; i < num_bins; i++){
                unpacked_values[i] = NULL;
            }
            
            counts = new int[num_bins];
            for (int i = 0; i < num_bins; i++){
                counts[i] = 0;
            }
        }
        
        JaggedArray(const JaggedArray<T>& copy) :
            num_bins(0), num_elements(0), packed(false),
            packed_values(NULL), offsets(NULL), 
            unpacked_values(NULL), counts(NULL)
        {
            deepCopy(copy);
        }
        
        ~JaggedArray(){
            clear();

            if (packed){
                delete[] offsets;
                offsets = NULL;
            } else {
                delete[] counts;
                counts = NULL;
                delete[] unpacked_values;
                unpacked_values = NULL;
            }
        }
        
        void print(std::ostream& out=std::cout) const; 
    
        void pack();
        void unpack();

        void clear();

        void addElement(unsigned bin, const T& element);
        void removeElement(unsigned bin, unsigned pos);
        T    getElement(unsigned bin, unsigned pos) const;
        
        int  numBins()     const {return num_bins;}
        int  numElements() const {return num_elements;}
        bool isPacked()    const {return packed;}
        
        int  numElementsInBin(unsigned bin) const;

        void deepCopy(const JaggedArray<T>& copy);

        JaggedArray<T>& operator=(const JaggedArray<T>& copy){
            deepCopy(copy);
            return *this;
        }
        
    protected:
        bool packed;
        int  num_bins, num_elements;

        int* offsets, 
           * counts;

        T*  packed_values,
         ** unpacked_values;
};

//implementations

template <typename T>
void JaggedArray<T>::print(std::ostream& out) const {
    if (packed){
        out << "packed JaggedArray" << std::endl
            << "  num_bins: " << num_bins << std::endl
            << "  num_elements: " << num_elements << std::endl
            << "  offsets: "; //2 spaces between offsets: and first offset
        for (int i = 0; i < num_bins; i++){
            out << " " << offsets[i];
        }

        out << std::endl << "  values:  "; //3 spaces this time
        for (int i = 0; i < num_elements; i++){
            out << " " << packed_values[i];
        }

        std::cout << std::endl << std::endl;
    } else {
        out << "unpacked JaggedArray" << std::endl
            << "  num_bins: " << num_bins << std::endl
            << "  num_elements: " << num_elements << std::endl
            << "  counts: "; //2 spaces between counts: and first count
        for (int i = 0; i < num_bins; i++){
            out << " " << counts[i];
        }

        out << std::endl << "  values: "; //2 spaces again
        int cur_element = 0;
        bool done = false;
        while (!done){
            done = true;
            for (int i = 0; i < num_bins; i++){
                if (counts[i] <= cur_element){
                    out << "  ";
                } else {
                    out << " " << unpacked_values[i][cur_element];
                    done = false;
                }
            }
            cur_element++; //start at 1
            if (!done){
                std::cout << std::endl << "          ";
            } else {
                std::cout << std::endl;
            }
        }
    }
}

template <typename T>
void JaggedArray<T>::pack(){
    if (packed){
        std::cerr << "JaggedArray already packed" << std::endl;
        return;
    } else {
        packed = true;

        offsets = new int[num_bins];
        packed_values = new T[num_elements];
        int next = 0;
        int last_offset = 0;
        for (int i = 0; i < num_bins; i++){
            offsets[i] = last_offset;
            for (int j = 0; j < counts[i]; j++){
                packed_values[next] = unpacked_values[i][j];
                next++;
                last_offset++;
            }
        }

      //make unused members null
        delete[] counts;
        counts = NULL;
        for (int i = 0; i < num_bins; i++){
            delete[] unpacked_values[i];
        }
        delete[] unpacked_values;
        unpacked_values = NULL;
    }
}

template <typename T>
void JaggedArray<T>::unpack(){
    if (!packed){
        std::cerr << "JaggedArray already unpacked" << std::endl;
        return;
    } else {
        packed = false;

        int last_offset = 0;
        unpacked_values = new T*[num_bins];
        counts = new int[num_bins];
        
      //offsets
        for (int i = 0; i < num_bins; i++){
            if (i != num_bins-1){
                counts[i] = offsets[i+1] - offsets[i];
            } else {
                counts[i] = num_elements - offsets[i];
            }

            if (counts[i] == 0){
                unpacked_values[i] = NULL;
            } else {
                T* new_bin = new T[counts[i]];
                for (int j = 0; j < counts[i]; j++){
                    new_bin[j] = packed_values[offsets[i]+j];
                }
                
                unpacked_values[i] = new_bin;
            }
        }
        
      //make unused variables null
        delete[] offsets;
        offsets = NULL;
        delete[] packed_values;
        packed_values = NULL;
    }
}

template <typename T>
void JaggedArray<T>::clear(){
    num_elements = 0;
    if (packed){
        delete[] packed_values;
        packed_values = NULL;

        for (int i = 0; i < num_bins; i++){
            offsets[i] = 0;
        }
    } else {
        for (int i = 0; i < num_bins; i++){
            counts[i] = 0;
            delete[] unpacked_values[i];
            unpacked_values[i] = NULL;
        }
    }
}

template <typename T>
void JaggedArray<T>::addElement(unsigned bin, const T& element){
    if (packed){
        std::cerr << "Error: "
                  << "Trying to add an element to a packed JaggedArray" 
                  << std::endl;
        return;
    } else if (bin >= num_bins){
        std::cerr << "Error: "
                  << "Trying to add an element to a nonexistant bin (" << bin
                  << ") in JaggedArray" << std::endl;
        return;
    } else {
        counts[bin]++;
        num_elements++;
        
        T* new_bin = new T[counts[bin]];
        for (int i = 0; i < counts[bin]; i++){ //-1 because it was incremented
            if (i == counts[bin]-1){
                new_bin[counts[bin]-1] = element;
            } else {
                new_bin[i] = unpacked_values[bin][i];
            }
        }

        delete[] unpacked_values[bin];
        unpacked_values[bin] = new_bin;
    }
}

template <typename T>
void JaggedArray<T>::removeElement(unsigned bin, unsigned pos){
  //pretty much the same thing as adding
    if (packed){
        std::cerr << "Error: "
                  << "Trying to remove elements from a packed JaggedArray" 
                  << std::endl;
        return;
    } else if (bin >= num_bins){
        std::cerr << "Error: "
                  << "Trying to remove an element from a nonexistant bin ("
                  << bin << ") in JaggedArray" << std::endl;
    } else if (pos >= numElementsInBin(pos)){
        std::cerr << "Error: "
                  << "Trying to remove a nonexistant element (" << pos
                  << ") from bin " << bin << " in JaggedArray" << std::endl;
    } else {
        counts[bin]--;
        num_elements--;
        T* new_bin = new T[counts[bin]];

        int new_pos = 0; //pos in new bin
        for (int i = 0; i < counts[bin]+1; i++){
            if (i == pos){
                continue;
            } else {
                new_bin[new_pos] = unpacked_values[bin][i];
            }
            new_pos++;
        }

        delete[] unpacked_values[bin];
        unpacked_values[bin] = new_bin;
    }
}

template <typename T>
T JaggedArray<T>::getElement(unsigned bin, unsigned pos) const {
    if (bin >= num_bins){
        std::cerr << "Error: "
                  << "Trying to get an element from a bin that does not exist ("
                  << bin << ") in JaggedArray" << std::endl;
    } else if (pos >= numElementsInBin(bin)){
        std::cerr << "Error: "
                  << "Trying to get an element that does not exist ("
                  << bin << ", " << pos << ") in JaggedArray" << std::endl;
        return NULL;
    } else {
        if (packed){
            int packed_pos = offsets[bin] + pos;
            return packed_values[packed_pos];
        } else {
            return unpacked_values[bin][pos];
        }
    }
}

template <typename T>
int JaggedArray<T>::numElementsInBin(unsigned bin) const {
    if (bin >= num_bins){
        std::cerr << "Error: "
                  << "Asking for number of elements in a non-existant bin (" 
                  << bin << ") in JaggedArray" << std::endl;
        return -1;
    } else {
        if (packed){
            if (bin == num_bins-1){
                return num_elements - offsets[bin];
            } else {
                return offsets[bin+1] - offsets[bin];
            }
        } else {
            return counts[bin];
        }
    }
}

template <typename T>
void JaggedArray<T>::deepCopy(const JaggedArray<T>& copy){
    clear();

    if (packed){
        delete[] offsets;
        offsets = NULL;
    } else {
        delete[] counts;
        counts = NULL;
        delete[] unpacked_values;
        unpacked_values = NULL;
    }
    
    num_bins = copy.num_bins;
    num_elements = copy.num_elements;
    packed = copy.packed;

    if (packed){
        offsets = new int[num_bins];
        packed_values = new T[num_elements];

        for (int i = 0; i < num_bins; i++){
            offsets[i] = copy.offsets[i];
        }

        for (int i = 0; i < num_elements; i++){
            packed_values[i] = copy.packed_values[i];
        }
    } else {
        counts = new int[num_bins];
        unpacked_values = new T*[num_bins];
        
        for (int i = 0; i < num_bins; i++){
            counts[i] = copy.counts[i];
            T* new_bin = new T[counts[i]];
            for (int j = 0; j < counts[i]; j++){
                new_bin[j] = copy.unpacked_values[i][j];
            }
            unpacked_values[i] = new_bin;
        }
    }
}

#endif
