#ifndef UNROLLED_IT_H
#define UNROLLED_IT_H

#include "node.h"

#ifndef MAX
#define MAX(a, b) a > b ? a : b
#endif

template <typename T>
class list_iterator {
    public:
        list_iterator() : 
            node(NULL), k_size(NUM_ELEMENTS_PER_NODE),
            m_pos(0), end(false)
        {}
    
        list_iterator(Node<T>* node, bool end=false) : 
            node(node), k_size(NUM_ELEMENTS_PER_NODE),
            m_pos(0), end(end)
        {
            if (end){
                m_pos = node->size();
            }
        }

        T operator*(){return *(node->m_values[m_pos]);}
        T* operator->(){return node->m_values[m_pos];}

        list_iterator<T>& operator++();
        list_iterator<T>  operator++(int);
        
        list_iterator<T>& operator--();
        list_iterator<T>  operator--(int);
        
        list_iterator<T>& operator=(const list_iterator<T>& copy){
            node = copy.node; 
            end = copy.end;
            m_pos = copy.m_pos;

            return *this;
        }

        bool operator==(const list_iterator<T>& lhs) const {
            return node == lhs.node && m_pos == lhs.m_pos;// && end == lhs.end;
        }
        
        bool operator!=(const list_iterator<T>& lhs) const {
            return !(*this == lhs);
        }

        bool moveToNextNode();

        int pos() const {return m_pos;}
        
        Node<T>* node;
        bool end;
        
    //private:
        const int k_size;
        int m_pos;
};

template <typename T>
bool list_iterator<T>::moveToNextNode(){
    if (node->next() == NULL){
        return false;
    } else {
        node = node->next();
        m_pos = 0;
        return true;
    }
}

template <typename T>
list_iterator<T>& list_iterator<T>::operator++(){
    m_pos++;
    if (m_pos >= k_size || node->m_values[m_pos] == NULL){
        if (node->next() == NULL){
            end = true;
            m_pos = node->size();
        } else {
            m_pos = 0;
            node = node->next();
        }
    }

   return *this;
}

template <typename T>
list_iterator<T> list_iterator<T>::operator++(int){
    list_iterator<T> temp = *this;
    
    m_pos++;
    if (m_pos >= k_size || node->m_values[m_pos] == NULL){
        if (node->next() == NULL){
            end = true;
            m_pos = node->size();
        } else {
            m_pos = 0;
            node = node->next();
        }
    }

    return temp;
}

template <typename T>
list_iterator<T>& list_iterator<T>::operator--(){
    if (end){
        end = false;
    }
    
    m_pos--;
    if (m_pos < 0){
        m_pos = k_size-1;
        node = node->prev();
        for (int i = m_pos; i >= 0; i--){
          //reset the position to the last non-null element
            if (node->m_values[i] != NULL){
                m_pos = i;
                break;
            }
        }
    }
    
    return *this;
}

template <typename T>
list_iterator<T> list_iterator<T>::operator--(int){
    list_iterator<T> temp = *this;

    if (end){
        end = false;
    }
    
    m_pos--;
    if (m_pos < 0){
        m_pos = k_size-1;
        node = node->prev();
        for (int i = m_pos; i >= 0; i--){
          //reset the position to the last non-null element
            if (node->m_values[i] != NULL){
                m_pos = i;
                break;
            }
        }
    }

    return temp;
}

#endif
