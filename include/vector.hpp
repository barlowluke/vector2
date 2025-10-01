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
        return cap;
    }

    //elements stored
    int size() const {
        return sz;
    }
    
    //return (sz == 0)
    //O(1)
    bool empty() const {
        if (sz == 0) {
            return true;
        }
        return false;
    }
    
    //element at index when vector is const (unchecked)
    //return data[i] // no bounds check
    //O(1)
    const T& operator[](int i) const { 
        return data[i];
    }
    
    //element at index when vector is non-const (unchecked)
    //return data[i] // no bounds check
    //O(1)
    T& operator[](int i) { 
        return data[i];
    }
    
    // at function for const (checked)
    //if invalid index 
    //throw std::out_of_range("Invalid Index");
    //return data[i] after checking bounds
    const T& at(int i) const{
        if (i < 0 || i >= sz) {
            throw std::out_of_range("Invalid Index");
        }
        return data[i];
    }
    
    // at function for non const (checked)
    //if invalid index 
    //throw std::out_of_range("Invalid Index");
    //return data[i] after checking bounds
    T& at(int i){
        if (i < 0 || i >= sz) {
            throw std::out_of_range("Invalid Index");
        }
        return data[i];
    }
    
    // first element
    //throw std::out_of_range("front on empty Vector");
    //return data[0]
    const T& front() const { 
        if (sz == 0) {
            throw std::out_of_range("front on empty Vector");
        }
        return data[0];
    }

    // first element
    //throw std::out_of_range("front on empty Vector");
    //return data[0]
    T& front() {
        if (sz == 0) {
            throw std::out_of_range("front on empty Vector");
        }
        return data[0];
    }
    
    // last element
    //throw std::out_of_range("back on empty Vector");
    //return data[sz-1]
    const T& back() const { 
        if (sz == 0) {
            throw std::out_of_range("back on empty Vector");
        }
        return data[sz - 1];
    }

    // last element
    //throw std::out_of_range("back on empty Vector");
    //return data[sz-1]
    T& back() {
        if (sz == 0) {
            throw std::out_of_range("back on empty Vector");
        }
        return data[sz - 1];
    }
    
    // insert at end
    // double array size
    //   if sz==cap: reserve(max(1, 2*cap))
    //   data[sz] = elem
    //   sz++
    //Amortized O(1); worst-case O(n)
    void push_back(const T& elem){
        if (sz == cap) {
            reserve(std::max(1, 2 * cap));
        }
        data[sz] = elem;
        sz++;
    }

    // remove from end
    //   if sz==0 -> throw
    //   sz--
    //   shrink()
    // O(1) (shrink can be O(n) when it triggers)
    void pop_back() { 
        if (sz == 0) {
            throw std::out_of_range("remove on empty Vector");
        }
        sz--;
        shrink();
    }

    // insert at index
    //   if i<0 or i>sz -> throw
    //   if sz==cap: reserve(max(1, 2*cap))
    //   shift right
    //   data[i] = elem
    //   sz++
    // Complexity: O(n-i) moves + possible O(n) reallocation
    void insert(int i, const T& elem){
        if (i < 0 || i > sz) {
            throw std::out_of_range("Invalid index");
        }
        if (sz == cap) {
            reserve(std::max(1, 2 * cap));
        }
        for (int k = sz - 1; k >= i; k--) {
            data[k + 1] = data[k];
        }
        data[i] = elem;
        sz++;
    }

    // removes at index
    //   if i<0 or i>=sz -> throw
    //  shift left
    //   sz--
    //   shrink()
    // Complexity: O(n-i) moves; shrink may reallocate O(n)
    void erase(int i){
        if (i < 0 || i >= sz) {
            throw std::out_of_range("Invalid index");
        }
        for (int k = i + 1; k < sz; k++) {
            data[k - 1] = data[k];
        }
        sz--;
        shrink();
    }

    //capacity >= minimum
    //if cap < minimum:
    // create new array and move elements
    // O(n) when reallocation else O(1)
    void reserve(int minimum){
        if (cap < minimum) {
            T* new_array = new T[minimum];
            for (int k = 0; k < sz; k++) {
                new_array[k] = std::move(data[k]);
            }
            delete[] data;
            data = new_array;
            cap = minimum;
        }
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
                return vec->data[ind];
            }

            // return address of this->vec->[this->ind];
            T* operator->() const { 
                return &(vec->data[ind]);
            }

            //pre increment overloaded without param
            //ind++; return *this
            iterator& operator++(){
                ind++;
                return *this;
            }

            //post increment overloaded with parameter
            //old=*this; ind++; return old
            iterator operator++(int){ 
                iterator old = *this;
                ind++;
                return old;
            }

            //pre decrementr overloaded without param
            //ind--; return *this
            iterator& operator--(){
                ind--;
                return *this;
            }
            
            //post decrement overloaded with parameter
            //old=*this; ind--; return old
            iterator operator--(int){
                iterator old = *this;
                ind--;
                return old;
            }

            //return vec==rhs.vec && ind==rhs.ind
            bool operator==(iterator rhs) const{
                return (vec == rhs.vec) && (ind == rhs.ind);
            }

            //return !(*this == rhs)
            bool operator!=(iterator rhs) const{
                return !(*this == rhs);
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
                return vec->data[ind];
            }
            
            //return &vec->data[ind]
            const T* operator->() const { 
                return &(vec->data[ind]);
            }

            //pre
            //ind++; return *this
            const_iterator& operator++(){
                ind++;
                return *this;
            }

            //post
            //old=*this; ind++; return old
            const_iterator operator++(int){
                const_iterator old = *this;
                ind++;
                return old;
            }

            //pre
            //ind--; return *this
            const_iterator& operator--(){
                ind--;
                return *this;
            }

            //post
            //old=*this; ind--; return old
            const_iterator operator--(int){
                const_iterator old = *this;
                ind--;
                return old;
            }

            //return vec==rhs.vec && ind==rhs.ind
            bool operator==(const_iterator rhs) const{
                return (vec == rhs.vec) && (ind == rhs.ind);
            }

            //return !(*this == rhs)
            bool operator!=(const_iterator rhs) const{
                return !(*this == rhs);
            }
    };
public:
    // additional functions of Vector class
    
    //return iterator(this, 0)
    iterator begin(){
        return iterator(this, 0);
    }

    //return iterator(this, sz)
    iterator end(){
        return iterator(this, sz);
    }

    //return const_iterator(this, 0)
    const_iterator begin() const{
        return const_iterator(this, 0);
    }

    //return const_iterator(this, sz)
    const_iterator end() const{
        return const_iterator(this, sz);
    }

    // Inserts an element immediately before iterator position
    //insert(it.ind, elem); return it;
    iterator insert(iterator it, const T& elem){
        insert(it.ind, elem);
        return it;
    }

    // Removes the element at the given iterator position
    //erase(it.ind); return it;
    iterator erase(iterator it){
        erase(it.ind);
        return it;
    }
    

    // Rule of Five
    private:
        //sz=other.sz; cap=other.cap
        //if cap==0: data=nullptr
        //else: data=new T[cap]; copy [0..sz)
        void clone(const Vector& other){
            sz = other.sz;
            cap = other.cap;
            if (cap == 0) {
                data = nullptr;
            } else {
                data = new T[cap];
                for (int k = 0; k < sz; k++) {
                    data[k] = other.data[k];
                }
            }
        }

        // move other's pointers/sizes into this
        // reset other to empty state
        void transfer(Vector& other){
            sz = other.sz;
            cap = other.cap;
            data = other.data;

            other.sz = 0;
            other.cap = 0;
            other.data = nullptr;
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
            if (this != &other) {
                delete[] data;
                clone(other);
            }
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
            if (this != &other) {
                delete[] data;
                sz = other.sz;
                cap = other.cap;
                data = other.data;
                other.sz = 0;
                other.cap = 0;
                other.data = nullptr;
            }
            return *this;
        }

        // deallocate
        ~Vector(){
            delete[] this->data; 
        }

    // additional assignment functions
    // Reallocate storage to exactly new_cap (>= sz), moving elements.
    void reallocate(int new_cap){ // optional helper
        if (new_cap == cap) {
            return;
        }
        T* temp = new T[new_cap];
        for (int k = 0; k < sz; k++) {
            temp[k] = data[k];
        }
        delete[] data;
        data = temp;
        cap = new_cap;
    }

    void shrink(){
        if (cap > 0 && sz <= cap / 4) {
            int new_cap = std::max(1, cap / 2);
            reallocate(new_cap);
        }
    }
    
    // explicitly reduce the cap to sz and keep at least 1 slot
    void shrink_to_fit(){
        if (cap > sz) {
            int new_cap = std::max(1, sz);
            reallocate(new_cap);
        }
    }

}; //end class Vector
}//end namespace dsa
