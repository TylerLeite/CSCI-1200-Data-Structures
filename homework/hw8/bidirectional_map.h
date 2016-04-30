#ifndef BDMAP_H
#define BDMAP_H

#include <iostream>

template <typename KEY_T, typename VAL_T>
class bidirectional_map_node {
    public:
        bidirectional_map_node() : 
            link(NULL), left(NULL), right(NULL), parent(NULL) 
        {}
        
        bidirectional_map_node(const KEY_T& key) : 
            data(key), link(NULL), left(NULL), right(NULL), parent(NULL)
        {}

        KEY_T data;

        const KEY_T key  () const {return data;}
        const VAL_T value() const {return link->data;}

        const std::pair<KEY_T, VAL_T> getPair() const {
            return std::pair<KEY_T, VAL_T>(data, link->data);
        }
        
        bidirectional_map_node<VAL_T, KEY_T>* link;
        bidirectional_map_node<KEY_T, VAL_T>* left, *right, *parent;
};

template <typename KEY_T, typename VAL_T>
class bidirectional_map_iterator {
    public:
        template <typename F_KEY_T, typename F_VAL_T> 
        friend class bidirectional_map;
        
        //needs node, not key_t
        bidirectional_map_iterator() : ptr(NULL), end(false) {}
        bidirectional_map_iterator(bidirectional_map_node<KEY_T, VAL_T>* key) : 
            ptr(key), end(false) 
        {}
        bidirectional_map_iterator(const bidirectional_map_iterator<KEY_T, VAL_T>& rhs) : 
            ptr(rhs.ptr), end(rhs.end) 
        {}
    
        const std::pair<KEY_T, VAL_T> operator*(){return ptr->getPair();}

        bidirectional_map_iterator<KEY_T, VAL_T>& operator++(){
            if (end) return *this;

            if (ptr->right == NULL){
                if (ptr->parent == NULL){
                    end = true;
                } else {      
                    if (ptr == ptr->parent->right){
                        //find the next "left" child
                        //in case this is the end, save the pointer
                        bidirectional_map_node<KEY_T, VAL_T>* save = ptr;
                        //if ptr->parent == NULL, at end
                        while (ptr != ptr->parent->left){
                            ptr = ptr->parent;
                            if (ptr->parent == NULL){
                                ptr = save;
                                end = true;
                                return *this;
                            }
                        }
                        
                        ptr = ptr->parent;
                    } else {
                        ptr = ptr->parent;
                    }
                }
            } else {
                ptr = ptr->right;
                if (ptr->left != NULL){
                    while (ptr->left != NULL){ //move to the end of this branch
                        ptr = ptr->left;
                    }
                }
            }

            return *this;
        }

        bidirectional_map_iterator<KEY_T, VAL_T> operator++(int){
            bidirectional_map_iterator<KEY_T, VAL_T> temp = *this;
            operator++();
            return temp;
        }
        
        bidirectional_map_iterator<KEY_T, VAL_T>& operator--(){ //reverse operator++
            if (end){
                end = false;
                return *this;
            }

            if (ptr->left == NULL){
                if (ptr->parent == NULL){
                    return *this;
                } else {      
                    if (ptr == ptr->parent->left){
                        bidirectional_map_node<KEY_T, VAL_T>* save = ptr;
                        //TODO: make sure this workd
                        while (ptr != ptr->parent->right){
                            ptr = ptr->parent;
                            if (ptr->parent == NULL){
                                ptr = save;
                                return *this;
                            }
                        }
                        
                        ptr = ptr->parent;
                    } else {
                        ptr = ptr->parent;
                    }
                }
            } else {
                ptr = ptr->left;
                if (ptr->right != NULL){
                    while (ptr->right != NULL){
                        ptr = ptr->right;
                    }
                }
            }

            return *this;
        }

        bidirectional_map_iterator<KEY_T, VAL_T> operator--(int){
            bidirectional_map_iterator<KEY_T, VAL_T> temp = *this;
            operator--();
            return temp;
        }
        
        bidirectional_map_iterator<VAL_T, KEY_T> follow_link(){
            return bidirectional_map_iterator<VAL_T, KEY_T>(ptr->link);
        }

        bool operator==(const bidirectional_map_iterator<KEY_T, VAL_T>& rhs){
            return ptr == rhs.ptr && end == rhs.end;
        }
        
        bool operator!=(const bidirectional_map_iterator<KEY_T, VAL_T>& rhs){
            return ptr != rhs.ptr || end != rhs.end;
        }
            
        bidirectional_map_iterator& operator=(
                           const bidirectional_map_iterator<KEY_T, VAL_T>& rhs){
            ptr = rhs.ptr;
            end = rhs.end;
        }
        
    protected:
        bool end;
        bidirectional_map_node<KEY_T, VAL_T>* ptr;
};

template <typename KEY_T, typename VAL_T>
class bidirectional_map {
    public:
        bidirectional_map() : size_(0), key_root(NULL), val_root(NULL) {};
        bidirectional_map(const bidirectional_map<KEY_T, VAL_T>& rhs) {copy_tree(rhs);}
        ~bidirectional_map(){delete_tree();}

        void delete_tree();
        bidirectional_map<KEY_T, VAL_T> copy_tree(const bidirectional_map& rhs);
    
        int size() const {return size_;}
        void print(std::ostream& out);

        typedef bidirectional_map_iterator<KEY_T, VAL_T> key_iterator;
        typedef bidirectional_map_iterator<VAL_T, KEY_T> value_iterator;
        typedef bidirectional_map_node<KEY_T, VAL_T>  keynode;
        typedef bidirectional_map_node<VAL_T, KEY_T>  valnode;

        key_iterator begin();
        key_iterator key_begin(){return begin();}
        value_iterator value_begin();
        
        key_iterator end();
        key_iterator key_end(){return end();}
        value_iterator value_end();
        
        const VAL_T at(const KEY_T& key);
        const KEY_T at(const VAL_T& val);

        const VAL_T operator[](const KEY_T& key){return at(key);}
        const KEY_T operator[](const VAL_T& val){return at(val);}

        key_iterator find(const KEY_T& key);
        value_iterator find(const VAL_T& val);

        std::pair<key_iterator, bool> insert(const KEY_T& key, const VAL_T& value);
        std::pair<key_iterator, bool> insert(const std::pair<KEY_T, VAL_T>& toInsert){
            insert(toInsert.first, toInsert.second);
        }

        key_iterator erase(const KEY_T& to_erase); //by key
        //value_iterator erase(const VAL_T& to_erase); //by value
        //key_iterator erase(key_iterator& at); //by key iterator
        //value_iterator erase(value_iterator& at); //by value iterator
        
    protected:
      //print_recursive, delete_from, and insert_node need 2 versions because the 
      // compiler got mad at me when there was only 1 each.
      //recursive copy is never called on valnodes, so it only needs 1 version
        void print_recursive(std::ostream& out, keynode* node, int depth);
        void print_recursive(std::ostream& out, valnode* node, int depth);
        
        void delete_from(keynode* root);
        void delete_from(valnode* root);
        
        keynode* recursive_copy(keynode* copy);
        
        bool insert_node(keynode* node, keynode* root);
        bool insert_node(valnode* node, valnode* root);
    
        bidirectional_map_node<KEY_T, VAL_T>* key_root;
        bidirectional_map_node<VAL_T, KEY_T>* val_root;
        int size_;
};

template <typename KEY_T, typename VAL_T>
void bidirectional_map<KEY_T, VAL_T>::delete_tree(){
    //recursively erase the whole tree
    delete_from(key_root);
    delete_from(val_root);

    key_root = NULL;
    val_root = NULL;
}

template <typename KEY_T, typename VAL_T>
void bidirectional_map<KEY_T, VAL_T>::delete_from(
                                    bidirectional_map_node<KEY_T, VAL_T>* root){
    if (root == NULL) return;
    
    delete_from(root->left);
    delete_from(root->right);

    delete root;
}

template <typename KEY_T, typename VAL_T>
void bidirectional_map<KEY_T, VAL_T>::delete_from(
                                    bidirectional_map_node<VAL_T, KEY_T>* root){
    if (root == NULL) return;
    
    delete_from(root->left);
    delete_from(root->right);

    delete root;
}

template <typename KEY_T, typename VAL_T>
bidirectional_map<KEY_T, VAL_T> bidirectional_map<KEY_T, VAL_T>::copy_tree(
                                                  const bidirectional_map& rhs){
    delete_tree(); //delete old tree

    key_root = recursive_copy(rhs.key_root); //copy keys
    val_root = recursive_copy(rhs.val_root); //copy values

    //repair the links (probably not a very efficient way of doing it)
    bidirectional_map_iterator<KEY_T, VAL_T> key_it;
    for (key_it = rhs.begin(); key_it != rhs.end(); key_it++){
        bidirectional_map_node<KEY_T, VAL_T>* key_fix = key_root;
        bidirectional_map_node<VAL_T, KEY_T>* val_fix = val_root;

        while (key_fix->key() != (*key_it).first){
            if (key_fix->key() < (*key_it).first){
                key_fix = key_fix->left;
            } else {
                key_fix = key_fix->right;
            }
        }

        while (val_fix->val() != key_it.ptr->link->key()){
            if (val_fix->key() < key_it.ptr->link->key()){
                val_fix = val_fix->left;
            } else {
                val_fix = val_fix->right;
            }
        }

        key_fix->link = val_fix;
        val_fix->link = key_fix;
    }

    size_ = rhs.size();
    
    return *this;
}

template <typename KEY_T, typename VAL_T>
bidirectional_map_node<KEY_T, VAL_T>* bidirectional_map<KEY_T, VAL_T>::recursive_copy(
                                    bidirectional_map_node<KEY_T, VAL_T>* copy){
    bidirectional_map_node<KEY_T, VAL_T>* root = 
                           new bidirectional_map_node<KEY_T, VAL_T>(copy->data);
    root->left = recursive_copy(copy->left);
    root->right = recursive_copy(copy->right);

    root->left->parent = root;
    root->right->parent = root;

    return root;
}

template <typename KEY_T, typename VAL_T>
void bidirectional_map<KEY_T, VAL_T>::print(std::ostream& out){
    std::cout << "=================================================" << std::endl 
              << "KEYS:" << std::endl;
    print_recursive(out, key_root, 0);
    std::cout << "-------------------------------------------------" << std::endl 
              << "VALUES:" << std::endl;
    print_recursive(out, val_root, 0);
    std::cout << "=================================================" << std::endl;
}

template <typename KEY_T, typename VAL_T>
void bidirectional_map<KEY_T, VAL_T>::print_recursive(
                                     std::ostream& out,
                                     bidirectional_map_node<KEY_T, VAL_T>* node, 
                                     int depth){
    if (node == NULL) return;
    print_recursive(out, node->right, depth+1);
    
    for (int i = 0; i < depth; ++i){
        out << "    ";
    }
    
    out << node->key()<< " [" << node->value() << "]" << std::endl;
    print_recursive(out, node->left, depth+1);
}

template <typename KEY_T, typename VAL_T>
void bidirectional_map<KEY_T, VAL_T>::print_recursive(
                                     std::ostream& out, 
                                     bidirectional_map_node<VAL_T, KEY_T>* node, 
                                     int depth){
    if (node == NULL) return;
    print_recursive(out, node->right, depth+1);
    
    for (int i = 0; i < depth; ++i){
        out << "    ";
    }
    
    out << node->key()<< " [" << node->value() << "]" << std::endl;
    print_recursive(out, node->left, depth+1);
}

template <typename KEY_T, typename VAL_T>
bidirectional_map_iterator<KEY_T, VAL_T> bidirectional_map<KEY_T, VAL_T>::begin(){
    bidirectional_map_node<KEY_T, VAL_T>* foot = key_root;
    if (foot != NULL){
        while (foot->left != NULL){
            foot = foot->left; //get least element
        }
    }

    bidirectional_map_iterator<KEY_T, VAL_T> out = 
                                 bidirectional_map_iterator<KEY_T, VAL_T>(foot);
    return out;
}

template <typename KEY_T, typename VAL_T>
bidirectional_map_iterator<KEY_T, VAL_T> bidirectional_map<KEY_T, VAL_T>::end(){
    bidirectional_map_node<KEY_T, VAL_T>* foot = key_root;
    if (foot != NULL){
        while (foot->right != NULL){
            foot = foot->right; //get greatest element
        }
    }

    bidirectional_map_iterator<KEY_T, VAL_T> out = 
                                 bidirectional_map_iterator<KEY_T, VAL_T>(foot);
    out.end = true;
    return out;
}

template <typename KEY_T, typename VAL_T>
bidirectional_map_iterator<VAL_T, KEY_T> 
 bidirectional_map<KEY_T, VAL_T>::value_begin(){
    bidirectional_map_node<VAL_T, KEY_T>* foot = val_root;
    if (foot != NULL){
        while (foot->left != NULL){
            foot = foot->left;
        }
    }

    bidirectional_map_iterator<VAL_T, KEY_T> out = 
                                 bidirectional_map_iterator<VAL_T, KEY_T>(foot);
    return out;
}

template <typename KEY_T, typename VAL_T>
bidirectional_map_iterator<VAL_T, KEY_T> bidirectional_map<KEY_T, VAL_T>::value_end(){
    bidirectional_map_node<VAL_T, KEY_T>* foot = val_root;
    if (foot != NULL){
        while (foot->right != NULL){
            foot = foot->right;
        }
    }

    bidirectional_map_iterator<VAL_T, KEY_T> out = 
                                 bidirectional_map_iterator<VAL_T, KEY_T>(foot);
    out.end = true;
    return out;
}

template <typename KEY_T, typename VAL_T>
const VAL_T bidirectional_map<KEY_T, VAL_T>::at(const KEY_T& find_key){
    bidirectional_map_node<KEY_T, VAL_T>* out = key_root;
    //traverse the tree as normal
    while (find_key != out->key()){
        if (find_key > out->key()){
            out = out->right;
        } else if (find_key < out->key()){
            out = out->left;
        }

        if (out == NULL) return VAL_T();
    }

    return out->value();
}

template <typename KEY_T, typename VAL_T>
const KEY_T bidirectional_map<KEY_T, VAL_T>::at(const VAL_T& val){
    bidirectional_map_node<VAL_T, KEY_T>* out = val_root;
    while (val != out->key()){
        if (val > out->key()){
            out = out->right;
        } else if (val < out->key()){
            out = out->left;
        }

        if (out == NULL) return KEY_T();
    }

    return out->value(); //in this case, the key
}

template <typename KEY_T, typename VAL_T>
bidirectional_map_iterator<KEY_T, VAL_T> bidirectional_map<KEY_T, VAL_T>::find(
                                                              const KEY_T& key){
    if (key_root == NULL) return end();

    //pretty much the same as at()
    bidirectional_map_node<KEY_T, VAL_T>* out = key_root;
    while (out != NULL && key != out->key()){
        //if right and left are null, at a leaf and still no match -> not in tree 
        if (out->right == NULL && out->left == NULL) return end();
    
        if (key > out->key()){
            out = out->right;
        } else if (key < out->key()){
            out = out->left;
        } 
    }

    if (out == NULL) return end();

    return bidirectional_map_iterator<KEY_T, VAL_T>(out);
}

template <typename KEY_T, typename VAL_T>
bidirectional_map_iterator<VAL_T, KEY_T> bidirectional_map<KEY_T, VAL_T>::find(const VAL_T& val){
    if (val_root == NULL) return value_end();
    
    bidirectional_map_node<VAL_T, KEY_T>* out = val_root;
    while (out != NULL && val != out->key()){
        if (out->right == NULL && out->left == NULL) return value_end();
        
        if (val > out->key()){
            out = out->right;
        } else if (val < out->key()){
            out = out->left;
        }

    }

    if (out == NULL) return value_end();

    return bidirectional_map_iterator<VAL_T, KEY_T>(out);
}

template <typename KEY_T, typename VAL_T>
std::pair<bidirectional_map_iterator<KEY_T, VAL_T>, bool> 
 bidirectional_map<KEY_T, VAL_T>::insert(const KEY_T& key, const VAL_T& value){
    bidirectional_map_node<KEY_T, VAL_T>* key_node = 
                                  new bidirectional_map_node<KEY_T, VAL_T>(key);
    bidirectional_map_node<VAL_T, KEY_T>* val_node = 
                                  new bidirectional_map_node<VAL_T, KEY_T>(value);

    key_node->link = val_node;
    val_node->link = key_node;

    bool success = true;

    if (key_root == NULL){
        key_node->parent = NULL;
        val_node->parent = NULL;

        key_root = key_node;
        val_root = val_node;

        size_++;
    } else {
        //note: should probably check if both will work first, since otherwise
        // there would be a key inserted with no matching value, but when I tried
        // that, I was getting false positives for "value exists"
        if (insert_node(key_node, key_root) && insert_node(val_node, val_root)){
            size_++;
        } else {
            success = false;
        }
    }

    bidirectional_map_iterator<KEY_T, VAL_T> out(key_node);
    if (!success){out = end();}

    return std::pair<bidirectional_map_iterator<KEY_T, VAL_T>, bool>(out, success);
}

template <typename KEY_T, typename VAL_T>
bool bidirectional_map<KEY_T, VAL_T>::insert_node(bidirectional_map_node<KEY_T, VAL_T>* 
                              node, bidirectional_map_node<KEY_T, VAL_T>* root){
    if (root == NULL){return false;}

    //find the correct spot, then handle all of the links appropriately
    if (node->key() > root->key()){
        if (root->right == NULL){
            root->right = node;
            node->parent = root;
            return true;
        } else {
            insert_node(node, root->right);
            return true;
        }
    } else if (node->key() < root->key()){
        if (root->left == NULL){
            root->left = node;
            node->parent = root;
            return true;
        } else {
            insert_node(node, root->left);
            return true;
        }
    } else {
        //std::cerr << "cannot insert value, already exitst" << std::endl;
        return false;
    }
}

template <typename KEY_T, typename VAL_T>
bool bidirectional_map<KEY_T, VAL_T>::insert_node(
                                     bidirectional_map_node<VAL_T, KEY_T>* node, 
                                     bidirectional_map_node<VAL_T, KEY_T>* root){
    if (root == NULL){return false;}
    if (node->key() > root->key()){
        if (root->right == NULL){
            root->right = node;
            node->parent = root;
            return true;
        } else {
            insert_node(node, root->right);
            return true;
        }
    } else if (node->key() < root->key()){
        if (root->left == NULL){
            root->left = node;
            node->parent = root;
            return true;
        } else {
            insert_node(node, root->left);
            return true;
        }
    } else {
        //std::cerr << "cannot insert value, already exitst" << std::endl;
        return false;
    }
}

template <typename KEY_T, typename VAL_T>
bidirectional_map_iterator<KEY_T, VAL_T> bidirectional_map<KEY_T, VAL_T>::erase(
                                                         const KEY_T& to_erase){
    bidirectional_map_iterator<KEY_T, VAL_T> out = find(to_erase);
    if (out == end()) return out;

    size--;
    out--;
     
    bidirectional_map_node<KEY_T, VAL_T>* key = find(to_erase).ptr;
    bidirectional_map_node<VAL_T, KEY_T>* val = key->link;

    //delete the key
    if (key->left != NULL && key->right != NULL){ //key has 2 children
        //find least element in the right tree
        bidirectional_map_node<KEY_T, VAL_T>* lowest = key->right;
        while (lowest->left != NULL){
            lowest = lowest->left;
        }

        //replace the deleted node with the least element
        lowest->parent->left = NULL;
        lowest->right = key->right;
        lowest->parent = key->parent;

        if (key->parent != NULL){ //not the root
            //update the parent
            if (key == key->parent->left){
                key->parent->right = lowest;
            } else {
                key->parent->left = lowest;
            }
        }
    } else if (key->left != NULL){ //key is replaced by left
        if (key->parent != NULL){ //not the root
            //update the parent
            if (key == key->parent->right){
                key->parent->right = key->left;
            } else {
                key->parent->left = key->left;
            }
        } else {
            key_root = key->left;
        }
        
        key->left->parent = key->parent;
    } else if (key->right != NULL){ //key is replaced by right
        if (key->parent != NULL){ //not the root
            //update the parent
            if (key == key->parent->right){
                key->parent->right = key->right;
            } else {
                key->parent->left = key->right;
            }
        } else {
            key_root = key->right;
        }

        key->right->parent = key->parent;
    } else { //key doesn't need to be replaced (0 children)
        if (key->parent != NULL){
            if (key == key->parent->right){
                key->parent->right = NULL;
            } else {
                key->parent->left = NULL;
            }
        } else {
            key_root = NULL;
        }
    }

    //do the same for values
    if (val->left != NULL && val->right != NULL){
        //find least element in the right tree
        bidirectional_map_node<VAL_T, KEY_T>* lowest = val;
        while (lowest->left != NULL){
            lowest = lowest->left;
        }

        lowest->parent->left = NULL;
        lowest->right = val->right;
        lowest->parent = val->parent;

        if (val->parent != NULL){
            if (val == val->parent->left){
                val->parent->right = lowest;
            } else {
                val->parent->left = lowest;
            }
        }
    } else if (val->left != NULL){
        if (val->parent != NULL){
            if (val == val->parent->right){
                val->parent->right = val->left;
            } else {
                val->parent->left = val->left;
            }
        } else {
            val_root = val->left;
        }
        
        val->left->parent = val->parent;
    } else if (val->right != NULL){
        if (val->parent != NULL){
            if (val == val->parent->right){
                val->parent->right = val->right;
            } else {
                val->parent->left = val->right;
            }
        } else {
            val_root = val->right;
        }

        val->right->parent = val->parent;
    } else {
        if (val->parent != NULL){
            if (val == val->parent->right){
                val->parent->right = NULL;
            } else {
                val->parent->left = NULL;
            }
        } else {
            val_root = NULL;
        }
    }

    //delete key and value
    delete key;
    delete val;

    out++;
    return out;
}

#endif
