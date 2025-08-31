#include <iostream>
#include <stdexcept>
#include <cmath>

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

  // Constructor por lista de inicialización
  Vector(std::initializer_list<T> init) {
    capacity = (init.size() > 0 ? static_cast<unsigned int>(init.size()) : 5);
    storage = new T[capacity];
    sz = 0;
    policy = 1.5;
    for (const auto &val : init) {
      storage[sz++] = val;
    }
  }

// --- Operador de asignación ---------------------
Vector<T>& operator=(const Vector<T>& other) {
    if (this != &other) {
        delete[] storage;
        sz = other.sz;
        capacity = other.capacity;                            //Para LAVector
        storage = new T[capacity];
        for (unsigned int i = 0; i < sz; i++) {
            storage[i] = other.storage[i];
        }
    }
    return *this;
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

// Permite modificar el elemento
T& operator[](unsigned int index) { 
    return storage[index]; 
}

// Solo lectura cuando el Vector es const
const T& operator[](unsigned int index) const { 
    return storage[index]; 
}

T& at(unsigned int index) {
    if (index >= sz) {
      throw out_of_range("Index out of range");
    }
    return storage[index];
}

const T& at(unsigned int index) const {
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

// Suma los elementos de un Vector<int>
int sumVector(const Vector<int>& v) {
    int sum = 0; // Inicializa la suma en 0
    for (unsigned int i = 0; i < v.size(); i++) { // Recorre todos los elementos del vector
        sum += v[i]; // Suma cada elemento al acumulador
    }
    return sum; // Devuelve la suma total
}

// Imprime los elementos de un Vector<int>
void printVector(const Vector<int>& v) {
    for (unsigned int i = 0; i < v.size(); i++) { // Recorre todos los elementos del vector
        cout << v[i] << " "; // Imprime cada elemento seguido de un espacio
    }
    cout << endl; // Salto de línea al final
}

// Invierte los elementos de un Vector<int> y devuelve un nuevo Vector<int>
Vector<int> reverseVector(const Vector<int>& v) {
    Vector<int> reversed; // Crea un nuevo vector para almacenar los elementos invertidos
    for (unsigned int i = v.size(); i-- > 0; ) { // Recorre el vector desde el último elemento al primero
        reversed.push_back(v[i]); // Agrega cada elemento al nuevo vector
    }
    return reversed; // Devuelve el vector invertido
}

// Filtra los números pares de un Vector<int> y devuelve un nuevo Vector<int>
Vector<int> filterEven(const Vector<int>& v) {
    Vector<int> evens; // Crea un nuevo vector para almacenar los números pares
    for (unsigned int i = 0; i < v.size(); i++) { // Recorre todos los elementos del vector
        if (v[i] % 2 == 0) { // Verifica si el elemento es par
            evens.push_back(v[i]); // Si es par, lo agrega al nuevo vector
        }
    }
    return evens; // Devuelve el vector con los números pares
}

// Prueba de crecimiento dinámico del Vector<int>
void DynamicGrowthTest() {
    Vector<int> u; // Crea un vector vacío
    int lastCapacity = u.getCapacity(); // Obtiene la capacidad inicial del vector
    for (unsigned int i = 0; i < 1000; i++) { // Inserta 1000 elementos en el vector
        u.push_back(i); // Agrega el elemento al final del vector
        if (lastCapacity != u.getCapacity()) { // Verifica si la capacidad ha cambiado
            lastCapacity = u.getCapacity(); // Actualiza la capacidad
            cout << "Size: " << u.size() << ", Capacity: " << u.getCapacity() << endl; // Imprime el tamaño y la capacidad
        }
    }
}

// Fusiona dos vectores ordenados en uno solo, también ordenado
Vector<int> mergeSorted(const Vector<int>& a, const Vector<int>& b) {
    Vector<int> sorted; // Crea un nuevo vector para almacenar los elementos fusionados
    unsigned int i = 0, j = 0; // Inicializa los índices para recorrer ambos vectores
    while (i < a.size() && j < b.size()) { // Mientras haya elementos en ambos vectores
        if (a[i] <= b[j]) { // Si el elemento en 'a' es menor o igual al de 'b'
            sorted.push_back(a[i]); // Agrega el elemento de 'a' al nuevo vector
            i++; // Avanza al siguiente elemento en 'a'
        } else { // Si el elemento en 'b' es menor
            sorted.push_back(b[j]); // Agrega el elemento de 'b' al nuevo vector
            j++; // Avanza al siguiente elemento en 'b'
        }
    }
    while (i < a.size()) { // Si quedan elementos en 'a'
        sorted.push_back(a[i]); // Agrega los elementos restantes de 'a'
        i++;
    }
    while (j < b.size()) { // Si quedan elementos en 'b'
        sorted.push_back(b[j]); // Agrega los elementos restantes de 'b'
        j++;
    }
    return sorted; // Devuelve el vector fusionado y ordenado
  }

//! EXCERSICES WITH VECTORS IN THE CONTEXT OF 'LINEAR ALGEBRA' --------------------------------------------------------------------------

/* ##Vectors in the context of 'linear algebra'

### 1. LAVector class
Write the `LAVector` class that represents a vector in the context of linear
algebra (not a a data structure that stores elements):
- Implement a constructor, a copy constructor an a destructor if needed.
- Implement `operator+` for vector addition
- Implement `operator-` for vector subtraction  
- Implement `operator*` for scalar multiplication
- Add a `dot_product()` method to compute the dot product between two vectors
- Add a `magnitude()` method to calculate the Euclidean norm
- **Challenge**: Implement vector normalization
*/ 

class LAVector {
private:
    Vector<double> coords;  // aquí usas tu vector propio
public:
    // Constructor que recibe el tamaño del vector
    LAVector(unsigned int n) {      //Ejemplo de uso: LAVector result(coords.size());  
    for (unsigned int i = 0; i < n; i++) {
        coords.push_back(0.0);    // Inicializa con ceros
    }
} 

    // Constructor a partir de un inicializador
    LAVector(const std::initializer_list<double>& values) {
        for (auto v : values) {
            coords.push_back(v);
        }
    }

    // Suma de vectores 
    LAVector operator+(const LAVector& other) const {       //aunque solo reciba un vector, puede sumar dos vectores ya que es 
      LAVector result(coords.size());                       //como si coords[i] fuera a y other.coords[i] fuera b en c = a + b
        for (unsigned int i = 0; i < coords.size(); i++) {  // equivalente a result.coords[i] = a.coords[i] + b.coords[i];
            result.coords[i] = coords[i] + other.coords[i];
        }
        return result;
    }

    // Resta de vectores
    LAVector operator-(const LAVector& other) const {
        LAVector result(coords.size());
        for (unsigned int i = 0; i < coords.size(); i++) {
            result.coords[i] = coords[i] - other.coords[i];
        }
        return result;
    }

    // Multiplicación por escalar
    LAVector operator*(double scalar) const {
        LAVector result(coords.size());
        for (unsigned int i = 0; i < coords.size(); i++) {
            result.coords[i] = coords[i] * scalar;
        }
        return result;
    }

    // Producto punto
    double dot_product(const LAVector& other) const {
        double sum = 0.0;
        for (unsigned int i = 0; i < coords.size(); i++) {
            sum += coords[i] * other.coords[i];
        }
        return sum;
    }

    // Magnitud (norma Euclídea)
    double magnitude() const {
        double sum = 0.0;
        for (unsigned int i = 0; i < coords.size(); i++) {
            sum += coords[i] * coords[i];
        }
        return sqrt(sum);
    }

    // Normalización
    LAVector normalize() const {
        double mag = magnitude();
        LAVector result(coords.size());
        for (unsigned int i = 0; i < coords.size(); i++) {
            result.coords[i] = coords[i] / mag;
        }
        return result;
    }

    void PrintLAVector() const {
      cout << "(";
      for(unsigned int i = 0; i < coords.size(); i++){
        cout << coords[i];
        if(i < coords.size() - 1){
          cout << ", ";
        }
      }
      cout << ")" << endl;
    }
};

//?Test Case: Create two 3D vectors representing points in space and perform all operations.


int main() {
    int op = 0;
    Vector<int> v;
    for (int i = 1; i <= 5; i++) {
        v.push_back(i);  // Vector: 1 2 3 4 5
    }
    
    Vector<int> u = {1, 3, 4, 7, 11}; 
    Vector<int> s = {2, 6, 8, 9, 10};

    Vector<int> evens;
    Vector<int> reversed;
    Vector<int> merged;
    
    LAVector a = {1.0, 2.0, 3.0};
    LAVector b = {2.0, 5.0, 3.0};
    
    LAVector sum(3);
    LAVector diff(3);
    LAVector scaled(3);
    LAVector normA(3);
    double dot;
    double magA;

    while (op != 8) {
        cout << "\nIngrese una opción:\n";
        cout << "1. Sumar los elementos de un vector\n";
        cout << "2. Invertir un vector\n";
        cout << "3. Filtrar números pares de un vector\n";
        cout << "4. Prueba de crecimiento dinámico\n";
        cout << "5. Merge de dos vectores ordenados\n";
        cout << "6. Operaciones con LAVector (suma, resta, escalar, producto punto, magnitud, normalización)\n";
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
            Vector<int> evens = filterEven(v);  
            cout << "Números pares en el vector: ";
            printVector(evens);
            break;
        }

        case 4:
            DynamicGrowthTest();
            break;

        case 5:
            merged = mergeSorted(u, s); 
            cout << "Vector 1: ";
            printVector(u);
            cout << "Vector 2: ";
            printVector(s);
            cout << "Vector mergeado: ";
            printVector(merged);
            break;

        case 6:
            cout << "Vector a: ";
            a.PrintLAVector();
            cout << "Vector b: ";
            b.PrintLAVector();
            sum = a + b;
            diff = a - b;
            scaled = a * 2.0;
            dot = a.dot_product(b);
            magA = a.magnitude();
            normA = a.normalize();
            cout << "Vector a + b = ";
            sum.PrintLAVector();
            cout << "Vector a - b = ";
            diff.PrintLAVector();
            cout << "Vector a * 2.0 = ";
            scaled.PrintLAVector();
            cout << "Dot product a . b = " << dot << endl;
            cout << "Magnitude of a = " << magA << endl;
            cout << "Normalized a = ";
            normA.PrintLAVector();
            break;

        case 7: 
              
            break;

        case 8:
            
            break;

        default:
            cout << "Opción no válida. Intente de nuevo." << endl;
            break;
        }
    }
    return 0;
  }
