#ifndef UNROLLED_LL_H
#define UNROLLED_LL_H

#include <iostream>
#include "unrolled_it.h"

template <typename T>
class UnrolledLL {
    public: 
        UnrolledLL();
        virtual ~UnrolledLL(){recursiveFree(m_head);}

        UnrolledLL(const UnrolledLL<T>& copy){deepCopy(copy);}

        void recursiveFree(Node<T>* node){if (node->next() != NULL) recursiveFree(node->next()); delete node;}
        void deepCopy(const UnrolledLL<T>& copy);

        void print(std::ostream& out);

        int size() const {return m_size;}

        typedef list_iterator<T> iterator;
        
        iterator insert(iterator& before, const T& value);
        iterator erase(iterator& at);

        void push_back(const T& value);
        void pop_back();

        void push_front(const T& value);
        void pop_front();

        iterator begin() const {return iterator(m_head);}
        iterator end() const {return iterator(m_tail, true);}

        T front(){return *(m_head->m_values[0]);}
        T back(){return *(m_tail->m_values[m_tail->size()-1]);}
        
        UnrolledLL<T>& operator=(const UnrolledLL<T>& copy){deepCopy(copy); return *this;}
        
    protected:
        const int k_epn; //number of elements per node
        int m_size; //total number of elements in the list
        Node<T>* m_head;
        Node<T>* m_tail;
};

template <typename T>
UnrolledLL<T>::UnrolledLL() :
    k_epn(NUM_ELEMENTS_PER_NODE), m_size(0)
{
    m_head = new Node<T>(NULL, NULL); 
    m_tail = m_head;
}

template <typename T>
void UnrolledLL<T>::deepCopy(const UnrolledLL<T>& copy){
    Node<T>* node = m_head;
    recursiveFree(m_head);

    Node<T>* prev = NULL;
    for (iterator it = copy.begin(); it != copy.end(); it++){
        if (it.pos() == 0){
            Node<T>* node = new Node<T>(NULL, NULL);
            node->m_prev = prev;
            if (prev != NULL){
                prev->m_next = node;
            } else {
                m_head = node;
            }
            prev = node;
        }

        prev->insert(it.pos(), new T(*it));
    }

    m_tail = prev;

}

template <typename T>
void UnrolledLL<T>::print(std::ostream& out){
    out << "UnrolledLL, size: " << size() << std::endl;
    Node<T>* node = m_head;
    while (node != NULL){
        out << "node:[" << node->size() << "]";
        for (int i = 0; i < node->size(); i++){
            if (node->m_values[i] == NULL) break;
            out << " " << *(node->m_values[i]);
        }

        out << std::endl;
        node = node->next();
    }
}

template <typename T>
list_iterator<T> UnrolledLL<T>::insert(iterator& before, const T& value){
    m_size++;

    if (before.node->size() == k_epn){
        if (before.pos() == 0){
            //if this is being inserted at the front of a full node, make a new node in front of the current one and insert it there instead
            Node<T>* new_node = new Node<T>(before.node, before.node->prev());

            //update the neighbors / unrolledLL
            if (before.node->prev() == NULL){
                m_head = new_node;
            } else {
                before.node->prev()->m_next = new_node;
            }

            before.node->m_prev = new_node;

            //insert the value into the new node
            new_node->insert(0, new T(value));
        } else {
            //create a new node and shift values over
            Node<T>* new_node = new Node<T>(before.node->next(), before.node);

            //update the neighbors / unrolledLL
            if (before.node->next() == NULL){
                m_tail = new_node;
            } else {
                before.node->next()->m_prev = new_node;
            }

            before.node->m_next = new_node;

            //move the last element into the new node
            new_node->insert(0, before.node->m_values[k_epn-1]);
            before.node->m_values[k_epn-1] = NULL;

            //insert the new value;
            before.node->insert(before.pos(), new T(value));
            before.node->m_num_elements -= 1;
        }
    } else {
        before.node->insert(before.pos(), new T(value));
    }
    
    return before++; //return an iterator pointing to the new element
}

template <typename T>
list_iterator<T> UnrolledLL<T>::erase(iterator& at){
    m_size--;

    Node<T>* new_node = at.node;
    int new_pos = at.pos();
    bool new_end = at.end;
    
    at.node->erase(at.pos()); //make node clean up memory

    if (at.node->size() == 0){
        //remove empty nodes
        new_node = new_node->next();
        if (at.node->prev() == NULL && at.node->next() == NULL){
            //this is the last node, don't delete it
        } else {
            if (at.node->prev() == NULL){
                //update the unrolledLL's head node
                m_head = at.node->next();
                new_node = m_head;
                new_pos = m_head->size();
            } else {
                //update the previous node so it isn't pointing to garbage
                at.node->prev()->m_next = at.node->next();
            }

            if (at.node->next() == NULL){
                m_tail = at.node->prev();
                new_node = m_tail;
                new_pos = m_tail->size();
                new_end = true;
            } else {
                //update the next node so it isn't pointng to garbage
                at.node->next()->m_prev = at.node->prev();
            }
            
            delete at.node; //free memory
        }
    }

    at.node = new_node;
    at.m_pos = new_pos;
    at.end = new_end;

    if (at.m_pos >= at.node->size()) at++;
    return at;
}

template <typename T>
void UnrolledLL<T>::push_back(const T& value){
    m_size++;

    if (m_tail->size() == k_epn){
        Node<T>* new_node = new Node<T>(NULL, m_tail);
        m_tail->m_next = new_node;

        //move the last element into the new node
        new_node->insert(0, new T(value));
        m_tail = new_node;
    } else {
        //node isn't full, put it in the first open spot
        m_tail->insert(m_tail->size(), new T(value));
    }

}

template <typename T>
void UnrolledLL<T>::pop_back(){
    iterator end_it = end();
    erase(end_it);
}

template <typename T>
void UnrolledLL<T>::push_front(const T& value){
    iterator begin_it = begin(); 
    insert(begin_it, value);
}

template <typename T>
void UnrolledLL<T>::pop_front(){
    iterator begin_it = begin();
    erase(begin_it);
}

#endif
