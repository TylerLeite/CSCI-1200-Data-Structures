#ifndef priority_queue_h_
#define priority_queue_h_

#include <iostream>
#include <vector>
#include <cassert>


template <class T>
class priority_queue {
private:
  std::vector<T> m_heap;

public:
    priority_queue()
    {}

    priority_queue(std::vector<T> const& values){
        for (int i = 0; i < values.size(); i++){
            push(values[i]);
        }
    }

    void percolate_up(int node){
        int parent = std::floor((node-1)/2);
        while (parent >= 0){
            if (m_heap[node] < m_heap[parent]){
                T tmp = m_heap[parent];
                m_heap[parent] = m_heap[node];
                m_heap[node] = tmp;
                node = parent;
                parent = std::floor((parent-1)/2);
            } else {
                break;
            }
        }
    }

    void percolate_down(int node){
        int left = node*2 + 1;
        while (left < m_heap.size()){
            int child = left;
            if (left+1 < m_heap.size() && m_heap[left+1] < m_heap[left]){
                child++; //now right child
            }

            if (m_heap[child] < m_heap[node]){
                T tmp = m_heap[node];
                m_heap[node] = m_heap[child];
                m_heap[child] = tmp;

                node = child;
                left = child*2 + 1;
            } else {
                break;
            }
        }
    }

    const T& top() const {
        assert( !m_heap.empty() );
        return m_heap[0]; 
    }

    void push(const T& entry){
        int pos = m_heap.size(); //position of newly inserted item
        m_heap.push_back(entry);
        percolate_up(pos);
    }

    void pop(){
        assert(!m_heap.empty());
        
        int last_leaf = m_heap.size()-1;
        m_heap[0] = m_heap[last_leaf];
        m_heap.pop_back();//erase(m_heap.begin()+last_leaf);
        percolate_down(0);
    }

    int size()   const {return m_heap.size();}
    bool empty() const {return m_heap.empty();}


    //  The following three functions are used for debugging.

    //Check to see that internally the heap property is realized.
    bool check_heap(){
        return this->check_heap(this->m_heap);
    }

    //Check an external vector to see that the heap property is realized.
    bool check_heap(const std::vector<T>& heap){
        for (int i = 0; i < heap.size(); i++){
            if (2*i + 1 < heap.size()){
                if (heap[i] > heap[2*i + 1]) return false;
            }

            if (2*i + 2 < heap.size()){
                if (heap[i] > heap[2*i + 2]) return false;
            }
        }

        return true;
    }

    //A utility to print the contents of the heap.  Use it for debugging.
    void print_heap( std::ostream & ostr ){
        for (unsigned int i=0; i<m_heap.size(); ++i){
            ostr << i << ": " << m_heap[i] << std::endl;
        }
    }
  
};


template <class T>
void heap_sort( std::vector<T> & v )
{
    priority_queue<T> heap(v);
    v.clear();

    while (heap.size() != 0){
        v.push_back(heap.top());
        heap.pop();
    }
}

#endif
