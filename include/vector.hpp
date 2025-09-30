#pragma once

#include <algorithm>  // std::max
#include <utility>    // std::move
#include <stdexcept>  // std::out_of_range

namespace dsa{

template <typename T>
class Vector {

private:
    int cap{0};       // capacity of the array
    int sz{0};        // number of actual entries
    T* data{nullptr}; // pointer to array of elements

public:
    // empty - O(1)
    Vector() = default;
    
    //capacity - O(1)
    int capacity() const {
        // ToDo return sz
    }

    //elements stored
    int size() const {
        // ToDo
    }
    
    //return (sz == 0)
    //O(1)
    bool empty() const {
        // ToDo 
    }
    
    //element at index when vector is const (unchecked)
    //return data[i] // no bounds check
    //O(1)
    const T& operator[](int i) const { 
        // ToDo
    }
    
    //element at index when vector is non-const (unchecked)
    //return data[i] // no bounds check
    //O(1)
    T& operator[](int i) { 
        // ToDo
    }
    
    // at function for const (checked)
    //if invalid index 
    //throw std::out_of_range("Invalid Index");
    //return data[i] after checking bounds
    const T& at(int i) const{
        // ToDo
    }
    
    // at function for non const (checked)
    //if invalid index 
    //throw std::out_of_range("Invalid Index");
    //return data[i] after checking bounds
    T& at(int i){
        // ToDo
    }
    
    // first element
    //throw std::out_of_range("front on empty Vector");
    //return data[0]
    const T& front() const { 
        // ToDo
    }

    // first element
    //throw std::out_of_range("front on empty Vector");
    //return data[0]
    T& front() {
        // ToDo
    }
    
    // last element
    //throw std::out_of_range("back on empty Vector");
    //return data[sz-1]
    const T& back() const { 
        // ToDo
    }

    // last element
    //throw std::out_of_range("back on empty Vector");
    //return data[sz-1]
    T& back() {
        // ToDo
    }
    
    // insert at end
    // double array size
    //   if sz==cap: reserve(max(1, 2*cap))
    //   data[sz] = elem
    //   sz++
    //Amortized O(1); worst-case O(n)
    void push_back(const T& elem){
        // ToDo
    }

    // remove from end
    //   if sz==0 -> throw
    //   sz--
    //   shrink()
    // O(1) (shrink can be O(n) when it triggers)
    void pop_back() { 
        // ToDo
    }

    // insert at index
    //   if i<0 or i>sz -> throw
    //   if sz==cap: reserve(max(1, 2*cap))
    //   shift right
    //   data[i] = elem
    //   sz++
    // Complexity: O(n-i) moves + possible O(n) reallocation
    void insert(int i, const T& elem){
        // ToDo
    }

    // removes at index
    //   if i<0 or i>=sz -> throw
    //  shift left
    //   sz--
    //   shrink()
    // Complexity: O(n-i) moves; shrink may reallocate O(n)
    void erase(int i){
        // ToDo
    }

    //capacity >= minimum
    //if cap < minimum:
    // create new array and move elements
    // O(n) when reallocation else O(1)
    void reserve(int minimum){
        // ToDo
    }

    // nested iterator class
    class iterator {
        // needed by Vector's insert and erase
        friend class Vector;
        
        private:
            Vector* vec;
            int ind;   // index within the vector
        public:
            // constructor
            iterator(Vector* v=nullptr, int i=-1){ 
                vec=v; ind=i; 
            }

            //return this->vec->[this->ind];
            T& operator*() const {
                // ToDo
            }

            // return address of this->vec->[this->ind];
            T* operator->() const { 
                // ToDo
            }

            //pre increment overloaded without param
            //ind++; return *this
            iterator& operator++(){
                // ToDo
            }

            //post increment overloaded with parameter
            //old=*this; ind++; return old
            iterator operator++(int){ 
                // ToDo
            }

            //pre decrementr overloaded without param
            //ind--; return *this
            iterator& operator--(){
                // ToDo
            }
            
            //post decrement overloaded with parameter
            //old=*this; ind--; return old
            iterator operator--(int){
                // ToDo
            }

            //return vec==rhs.vec && ind==rhs.ind
            bool operator==(iterator rhs) const{
                // ToDo
            }

            //return !(*this == rhs)
            bool operator!=(iterator rhs) const{
                // ToDo
            }
    };

    // nested const_iterator class
    class const_iterator {
        private:
            const Vector* vec;
            int ind;   // index within the vector
        
        public:
            const_iterator(const Vector* v=nullptr, int i=-1){
                vec = v; ind=i;
            }

            //return vec->data[ind]
            const T& operator*() const { 
                // ToDo
            }
            
            //return &vec->data[ind]
            const T* operator->() const { 
                // ToDo
            }

            //pre
            //ind++; return *this
            const_iterator& operator++(){
                // ToDo
            }

            //post
            //old=*this; ind++; return old
            const_iterator operator++(int){
                // ToDo
            }

            //pre
            //ind--; return *this
            const_iterator& operator--(){
                // ToDo
            }

            //post
            //old=*this; ind--; return old
            const_iterator operator--(int){
                // ToDo
            }

            //return vec==rhs.vec && ind==rhs.ind
            bool operator==(const_iterator rhs) const{
                // ToDo
            }

            //return !(*this == rhs)
            bool operator!=(const_iterator rhs) const{
                // ToDo
            }
    };
public:
    // additional functions of Vector class
    
    //return iterator(this, 0)
    iterator begin(){
        // ToDo
    }

    //return iterator(this, sz)
    iterator end(){
        // ToDo
    }

    //return const_iterator(this, 0)
    const_iterator begin() const{
        // ToDo
    }

    //return const_iterator(this, sz)
    const_iterator end() const{
        // ToDo
    }

    // Inserts an element immediately before iterator position
    //insert(it.ind, elem); return it;
    iterator insert(iterator it, const T& elem){
        // ToDo
    }

    // Removes the element at the given iterator position
    //erase(it.ind); return it;
    iterator erase(iterator it){
        // ToDo
    }
    

    // Rule of Five
    private:
        //sz=other.sz; cap=other.cap
        //if cap==0: data=nullptr
        //else: data=new T[cap]; copy [0..sz)
        void clone(const Vector& other){
            // ToDo
        }

        // move other's pointers/sizes into this
        // reset other to empty state
        void transfer(Vector& other){
            // ToDo
        }

    public:
        // Copy constructor
        Vector(const Vector& other){ 
            clone(other); 
        }

        // Copy assignment
        Vector& operator=(const Vector& other){
            // nothing to be done if self-assignment
            // else deallocate previous and clone
            return *this;
        }

        // Move constructor
        Vector(Vector&& other){ 
            transfer(other); 
        }

        // Move assignment
        Vector& operator=(Vector&& other){
            // nothing to be done if self-assignment
            // else deallocate previous and transfer
            return *this;
        }

        // deallocate
        ~Vector(){
            delete[] this->data; 
        }

    // additional assignment functions
    // Reallocate storage to exactly new_cap (>= sz), moving elements.
    void reallocate(int new_cap){ // optional helper
        // ToDo
    }

    void shrink(){
        // ToDo
    }
    
    // explicitly reduce the cap to sz and keep at least 1 slot
    void shrink_to_fit(){
        // ToDo
    }

}; //end class Vector
}//end namespace dsa