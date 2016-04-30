#include <iostream>
#include <list>
#include <string>

// ===========================================================================

// A SIMPLE LINKED LIST CLASS
// (note: it's ok that all the member variables are public for this tiny class)

class Node {
public:
  int value;
  Node* ptr;
};


// ===========================================================================

// a helper function to print the contents of a linked list of Nodes
void print_linked_list(const std::string &name, Node *my_linked_list) {
  // print the name of this list
  std::cout << name;
  // use a temporary pointer to walk down the list
  Node *tmp = my_linked_list;
  while (tmp != NULL) {
    // print out each element
    std::cout << " " << tmp->value;
    tmp = tmp->ptr;
  }
  std::cout << std::endl;
}


// YOU NEED TO WRITE THIS FUNCTION
Node* make_linked_list_from_STL_list(const std::list<int> &lst) {

  // create a linked list chain of Nodes, populating the structure
  // with the data in the STL list

  // NOTE: this code should work for input STL lists of arbitrary
  // length

    if (lst.size() == 0){
        return NULL;
    }

    Node* first = new Node;
    first->ptr = NULL;

    Node* last = first;
    std::list<int>::const_iterator list_it = lst.begin();
    int i = 0;
    for (; list_it != lst.end(); list_it++){
        i++;
        last->value = *list_it;
        if (i == lst.size()){
            last->ptr = NULL;
        } else {
            Node* next = new Node;
            next->ptr = NULL;
            last->ptr = next;
            last = next;
        }
    }

    return first;
}


// YOU NEED TO WRITE THIS FUNCTION
Node* reverse_nodes_in_linked_list(Node *input) {

  // rearrange the pointers in the linked list chain of Nodes,
  // so that the structure is reversed.  

  // NOTE: Do not edit the values of the Nodes.  Do not create any new
  // Node objects (don't call 'new').  Instead, change the ptrs of the
  // existing Nodes to shuffle the order.

    if (input == NULL){
        return NULL;
    } else if (input->ptr == NULL){
        return input;
    } else {
        Node* out = reverse_nodes_in_linked_list(input->ptr);
        input->ptr->ptr = input;
        input->ptr = NULL;
        return out;
    }
}
    
/*
    Node* last = input;
    int size = 0;
    //get size of list
    while (last->ptr != NULL){
        size++;
        last = last->ptr;
    }

    while (true){
        Node* cur_node = input;
        Node* prev_node = input;

        for (int i = 0; i < size; i++){
            if (i < size-1){
                prev_node = prev_node->ptr;
            }
            
            cur_node = cur_node->ptr;
        }
        
        if (size == 0){
            cur_node->ptr = NULL;
            return last;
        } else {
            cur_node->ptr = prev_node;
        }

        size--;
    }
*/


// ===========================================================================

int main() {

  // manually create a linked list of notes with 4 elements
  Node* a = new Node; 
  a->value = 6; 
  a->ptr = new Node;
  a->ptr->value = 7;
  a->ptr->ptr = new Node;
  a->ptr->ptr->value = 8;
  a->ptr->ptr->ptr = new Node;
  a->ptr->ptr->ptr->value = 9;
  a->ptr->ptr->ptr->ptr = NULL;
  // print out this list
  print_linked_list("a",a);

  // create an STL list with 4 elements
  std::list<int> b;
  b.push_back(10);
  b.push_back(11);
  b.push_back(12);
  b.push_back(13);

  // use the STL list as input to a creator function that creates
  // linked lists with the same data
  Node* c = make_linked_list_from_STL_list(b);
  // print that data
  print_linked_list("c",c);
  // 
  // WRITE A FEW MORE TEST CASES OF make_linked_list_from_STL_list
  //
  
  // reverse a linked list of nodes
  Node* d = reverse_nodes_in_linked_list(c);
  // print this data
  print_linked_list("d",d);

  // 
  // WRITE A FEW MORE TEST CASES OF reverse_nodes_in_linked_list
  //

  std::list<int> e;
  Node* z = make_linked_list_from_STL_list(e);
  Node* y = reverse_nodes_in_linked_list(z);
  print_linked_list("y", y);
  

  std::list<int> f;
  f.push_back(1);
  f.push_back(2);
  f.push_back(3);
  f.push_back(4);
  f.push_back(5);

  Node* g = make_linked_list_from_STL_list(f);
  Node* h = reverse_nodes_in_linked_list(g);
  print_linked_list("h",h);

  


  // NOTE: We are not deleting any of the Nodes we created...  so this
  //       program has some memory leaks!  More on this in future
  //       lectures & labs :)

}

// ===========================================================================
