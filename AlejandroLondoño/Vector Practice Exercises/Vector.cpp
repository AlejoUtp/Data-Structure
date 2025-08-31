#include <iostream>
#include <stdexcept>

using namespace std;

template <typename T> 
class Vector {
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
 unsigned int getCapacity() const { return capacity; }
 double getPolicy() const { return policy; }

 
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

// ----------------Vector Practice Exercises------------------------------------------------------------------------------------------------------------------------------------------

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

//### 2. Reverse a Vector
//Write a function that takes a Vector<int> and returns a new Vector<int> with elements in reverse order.

//Vector<int>: es el tipo de valor que la función devuelve, es decir, retorna un vector de enteros.

Vector<int> reverseVector(const Vector<int>& v){ // "(const Vector<int>& v)" : es el parámetro de entrada: una referencia constante a un Vector<int> (para no hacer copia y no modificar el original).
  Vector<int> reversed;
  for(int i = v.size() - 1; i >= 0; i--){ //En bucles hacia atrás: se usa (int i = v.size() - 1; i >= 0; i--) ya que va de 0 a v.size() - 1.
    reversed.push_back(v[i]);
  }
  return reversed;
}

//### 3. **Filter Even Numbers**
//Write a function that takes a `Vector<int>` and returns a new vector containing only the even numbers.

Vector<int> filterEven(const Vector<int>& v){
  Vector<int> evens;
  for(int i = 0; i < v.size(); i++){
    if(v[i] % 2 == 0){
      evens.push_back(v[i]);
    }
  }
  return evens;
}

/*### 4. Dynamic Growth Test

Write a program that:

Creates an empty `Vector<int> u;`

Inserts numbers from 1 up to 1000 using `push_back`.

Every time the capacity changes, print the size and capacity.

Example Output (truncated):
```
Size: 6, Capacity: 7
Size: 8, Capacity: 10
Size: 11, Capacity: 15
*/

void DynamicGrowthTest(){
  Vector<int> u;
  int lastCapacity = u.getCapacity();
  for(int i = 0; i < 1000; i++){
    u.push_back(i);
    if(lastCapacity != u.getCapacity()){
       lastCapacity = u.getCapacity();
      cout << "Size: " << u.size() << ", Capacity: " << u.getCapacity() << endl;
    }
  }
}

//### 5. Merge Two Sorted Vectors
//Implement a function that merges two sorted Vector<int> into one sorted vector (like the merge step of MergeSort).

Vector<int> mergeSorted(const Vector<int>& a, const Vector<int>& b);

int main() {
    int op = 0;
    Vector<int> v;
    for (int i = 1; i <= 5; i++) {
        v.push_back(i);  // Vector: 1 2 3 4 5
    }
    
    Vector<int> u;

    Vector<int> evens;
    Vector<int> reversed;
    
    while (op != 4) {
        cout << "\nIngrese una opción:\n";
        cout << "1. Sumar los elementos de un vector\n";
        cout << "2. Invertir un vector\n";
        cout << "3. Filtrar números pares de un vector\n";
        cout << "4. Salir\n";
        cout << "Opción: ";
        cin >> op;

        switch (op) {
        case 1:
            cout << "Vector original: ";
            printVector(v);
            cout << "La suma de los elementos del vector es: " << sumVector(v) << endl;
            break;

        case 2: {
            cout << "Vector original: ";
            printVector(v);
            Vector<int> reversed = reverseVector(v);
            cout << "Vector invertido: ";
            printVector(reversed);
            break;
        }

        case 3: {
            cout << "Vector original: ";
            printVector(v);
            Vector<int> evens = filterEven(v);  // Asegúrate de definir esta función
            cout << "Números pares en el vector: ";
            printVector(evens);
            break;
        }

        case 4:
            DynamicGrowthTest();
            break;

        case 5:
            cout << "Saliendo del programa..." << endl;
            break;

        default:
            cout << "Opción no válida. Intente de nuevo." << endl;
            break;
        }
    }

    return 0;
}