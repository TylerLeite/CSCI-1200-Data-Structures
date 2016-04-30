#ifndef NODE_H
#define NODE_H

#ifndef NUM_ELEMENTS_PER_NODE
#define NUM_ELEMENTS_PER_NODE (int)6
#endif

template <typename T>
class Node {
    public:
        Node(Node<T>* next, Node<T>* prev);
        ~Node();

        Node<T>* prev(){return m_prev;}
        Node<T>* next(){return m_next;}

        int size() const {return m_num_elements;}

        void erase(int pos);
        void insert(int pos, T* value);

        T** m_values;
        
    //private:
        Node<T>* m_next;
        Node<T>* m_prev;
        int m_num_elements;
        
    private:
        Node();
        const int k_size;
};

template <typename T>
Node<T>::Node(Node<T>* next, Node<T>* prev) : 
    m_next(next), m_prev(prev), k_size(NUM_ELEMENTS_PER_NODE), m_num_elements(0)
{
    m_values = new T*[k_size];

    for (int i = 0; i < k_size; i++){
        m_values[i] = NULL;
    }
}

template <typename T>
Node<T>::~Node(){
    for (int i = 0; i < size(); i++){
        delete m_values[i];
    }

    delete[] m_values;
}


template <typename T>
void Node<T>::erase(int pos){
    if (pos == size()) pos--;
    m_num_elements--;
    delete m_values[pos];
    m_values[pos] = NULL;

    //shift elements to the side
    for (int i = pos; i < size(); i++){
        m_values[i] = m_values[i+1];
    }

    m_values[size()] = NULL; //leave no duplicates at end
}

template <typename T>
void Node<T>::insert(int pos, T* value){
    m_num_elements++;

    if (m_values[pos] != NULL){
        //move values over in the list until you can fit the new value
        for (int i = k_size-2; i >= pos; --i){ //doesn't work if called on a full node
            if (m_values[i] == NULL){
                continue;
            } else {
                m_values[i+1] = m_values[i];
                m_values[i] = NULL;
            }
        }
    }
    
    //insert the value in the specified position
    m_values[pos] = value;
}

#endif
