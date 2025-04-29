#include <iostream>

class Vector {
private:
    long* data;
    size_t size;
    int state; // 0 - OK, 1 - Memory error, 2 - Out of bounds
    static int objectCount;

public:
    // Default constructor
    Vector() : size(1), state(0) {
        data = new(std::nothrow) long[1];
        if (!data) {
            state = 1;
        }
        else {
            data[0] = 0;
        }
        objectCount++;
    }

    // Constructor with size
    Vector(size_t sz) : size(sz), state(0) {
        data = new(std::nothrow) long[size];
        if (!data) {
            state = 1;
        }
        else {
            for (size_t i = 0; i < size; ++i) {
                data[i] = 0;
            }
        }
        objectCount++;
    }

    // Constructor with size and initial value
    Vector(size_t sz, long value) : size(sz), state(0) {
        data = new(std::nothrow) long[size];
        if (!data) {
            state = 1;
        }
        else {
            for (size_t i = 0; i < size; ++i) {
                data[i] = value;
            }
        }
        objectCount++;
    }

    // Copy constructor
    Vector(const Vector& other) : size(other.size), state(other.state) {
        data = new(std::nothrow) long[size];
        if (!data) {
            state = 1;
        }
        else {
            for (size_t i = 0; i < size; ++i) {
                data[i] = other.data[i];
            }
        }
        objectCount++;
    }

    // Assignment operator
    Vector& operator=(const Vector& other) {
        if (this != &other) {
            delete[] data;

            size = other.size;
            state = other.state;
            data = new(std::nothrow) long[size];
            if (!data) {
                state = 1;
            }
            else {
                for (size_t i = 0; i < size; ++i) {
                    data[i] = other.data[i];
                }
            }
        }
        return *this;
    }

    // Destructor
    ~Vector() {
        delete[] data;
        objectCount--;
    }

    // Set element value with default parameter
    void set(size_t index, long value = 0) {
        if (index >= size) {
            state = 2;
        }
        else {
            data[index] = value;
            state = 0;
        }
    }

    // Get element value
    long get(size_t index) const {
        if (index >= size) {
            return 0; // or throw exception
        }
        else {
            return data[index];
        }
    }

    // Print vector
    void print() const {
        for (size_t i = 0; i < size; ++i) {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }

    // Add two vectors
    Vector add(const Vector& other) const {
        size_t minSize = (size < other.size) ? size : other.size;
        Vector result(minSize);
        for (size_t i = 0; i < minSize; ++i) {
            result.data[i] = data[i] + other.data[i];
        }
        return result;
    }

    // Subtract two vectors
    Vector subtract(const Vector& other) const {
        size_t minSize = (size < other.size) ? size : other.size;
        Vector result(minSize);
        for (size_t i = 0; i < minSize; ++i) {
            result.data[i] = data[i] - other.data[i];
        }
        return result;
    }

    // Multiply vector by unsigned int
    Vector multiply(unsigned int multiplier) const {
        Vector result(size);
        for (size_t i = 0; i < size; ++i) {
            result.data[i] = data[i] * multiplier;
        }
        return result;
    }

    // Comparison functions
    bool isEqual(const Vector& other) const {
        if (size != other.size) return false;
        for (size_t i = 0; i < size; ++i) {
            if (data[i] != other.data[i]) return false;
        }
        return true;
    }

    bool isNotEqual(const Vector& other) const {
        return !isEqual(other);
    }

    bool isLessThan(const Vector& other) const {
        size_t minSize = (size < other.size) ? size : other.size;
        for (size_t i = 0; i < minSize; ++i) {
            if (data[i] < other.data[i]) return true;
            else if (data[i] > other.data[i]) return false;
        }
        return size < other.size;
    }

    // Getter for object count
    static int getObjectCount() {
        return objectCount;
    }

    // Getter for state
    int getState() const {
        return state;
    }
};

int Vector::objectCount = 0;

// Testing program
int main() {
    Vector v1;
    v1.set(0, 5);
    std::cout << "v1: ";
    v1.print();

    Vector v2(5);
    for (size_t i = 0; i < 5; ++i) {
        v2.set(i, i * 2);
    }
    std::cout << "v2: ";
    v2.print();

    Vector v3(5, 7);
    std::cout << "v3: ";
    v3.print();

    Vector v4 = v2.add(v3);
    std::cout << "v2 + v3 = v4: ";
    v4.print();

    Vector v5 = v2.subtract(v3);
    std::cout << "v2 - v3 = v5: ";
    v5.print();

    Vector v6 = v2.multiply(3);
    std::cout << "v2 * 3 = v6: ";
    v6.print();

    std::cout << "v2 == v3? " << (v2.isEqual(v3) ? "Yes" : "No") << std::endl;
    std::cout << "v2 != v3? " << (v2.isNotEqual(v3) ? "Yes" : "No") << std::endl;
    std::cout << "v2 < v3? " << (v2.isLessThan(v3) ? "Yes" : "No") << std::endl;

    std::cout << "Current number of Vector objects: " << Vector::getObjectCount() << std::endl;

    return 0;
}