#include <iostream>

using namespace std;

template <typename T> class Vector {
private:
  // Stores the elements of the vector
  T *storage;
  // Current number of elements in the vector
  unsigned int sz;
  // Maximum number of elements that storage can hold
  unsigned int capacity;
  // Policy for resizing the vector
  double policy;

public:
// --- Constructores ---------------------------------------

  // Constructor por defecto
  Vector() {
    storage = new T[5];
    sz = 0;
    capacity = 5;
    policy = 1.5;
  }

  // Constructor con capacidad inicial y factor de crecimiento opcional 
  Vector(unsigned int c, double p = 1.5) {
    storage = new T[c];
    sz = 0;
    capacity = c;
    policy = p;
  }

  // Constructor copia
  Vector(const Vector<T> &other) {
    sz = other.size();
    capacity = other.capacity;
    policy = other.policy;
    storage = new T[capacity];
    for (unsigned int i = 0; i < sz; i++) {
      storage[i] = other.storage[i];
    }
  }
  
 //Destructor
  ~Vector() { delete[] storage; }

// --- Métodos de acceso (getters) ---------------------------------------

 unsigned int size() const { return sz; }


 
// --- Métodos de modificación ---------------------------------------

  void push_back(const Vector<T> &other) {
    reserve(sz + other.size());
    for (unsigned int i = 0; i < other.size(); i++) {
      push_back(other.storage[i]);
    }
  }

   void push_back(const T &elem) {
    if (sz == capacity) {
      resize();
    }
    storage[sz] = elem;
    sz++;
  }

  void pop_back() {
    if (sz > 0) sz--;
}

  void shrink_to_fit() {
    if (sz < capacity) {
      T *new_storage = new T[sz];
      for (unsigned int i = 0; i < sz; i++) {
        new_storage[i] = storage[i];
      }
      delete[] storage;
      storage = new_storage;
      capacity = sz;
    }
  }
// --- Acceso por índice ---------------------------------------

  const T &operator[](unsigned int index) const { return storage[index]; }

  T &at(unsigned int index) {
    if (index >= sz) {
      throw out_of_range("Index out of range");
    }
    return storage[index];
  }

  const T &at(unsigned int index) const {
    if (index >= sz) {
      throw out_of_range("Index out of range");
    }
    return storage[index];
  }


private:
  void resize() {
    capacity *= policy;
    T *new_storage = new T[capacity];
    for (unsigned int i = 0; i < sz; i++) {
      new_storage[i] = storage[i];
    }
    delete[] storage;
    storage = new_storage;
  }

  void reserve(unsigned int new_capacity) {
    if (new_capacity > capacity) {
      capacity = new_capacity;
      T *new_storage = new T[capacity];
      for (unsigned int i = 0; i < sz; i++) {
        new_storage[i] = storage[i];
      }
      delete[] storage;
      storage = new_storage;
    }
  }
};

// Vector Practice Exercises-------------------------------------------------------------------------------

// 1. **Sum of Elements**
// Write a function that takes a `Vector<int>` and returns the sum of all elements. 

int sumVector(const Vector<int>& v){
    int sum = 0;
    for(unsigned int i = 0; i< v.size(); i++){
        sum += v[i];
    }
    return sum;
}

void printVector(const Vector<int>& v){
    for(unsigned int i = 0; i< v.size(); i++){
        cout << v[i] << " ";
    }
    cout << endl;
}


int main(){ 

    Vector<int> v;

    for (int i = 1; i <= 10; i++) {
        v.push_back(i);
    }

    printVector(v);

    cout << "Sum of elements: " << sumVector(v) << endl;

    return 0;
}
