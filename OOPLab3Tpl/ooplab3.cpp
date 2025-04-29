#include <iostream>
#include <cmath>
#include <string>

using namespace std;

class Triangle {
private:
    double a, b, c; // sides
    string color;

    bool isValidTriangle(double a, double b, double c) {
        return (a > 0 && b > 0 && c > 0 &&
            a + b > c && a + c > b && b + c > a);
    }

public:
    // Default constructor
    Triangle() : a(1), b(1), c(1), color("White") {}

    // Parameterized constructor
    Triangle(double a, double b, double c, string color) {
        if (isValidTriangle(a, b, c)) {
            this->a = a;
            this->b = b;
            this->c = c;
        }
        else {
            cout << "Invalid sides. Setting to default (1,1,1)." << endl;
            this->a = this->b = this->c = 1;
        }
        this->color = color;
    }

    // Setters
    void setSides(double a, double b, double c) {
        if (isValidTriangle(a, b, c)) {
            this->a = a;
            this->b = b;
            this->c = c;
        }
        else {
            cout << "Invalid sides. No changes made." << endl;
        }
    }

    void setColor(string color) {
        this->color = color;
    }

    // Getters
    double getA() const { return a; }
    double getB() const { return b; }
    double getC() const { return c; }
    string getColor() const { return color; }

    // Calculate perimeter
    double perimeter() const {
        return a + b + c;
    }

    // Calculate area using Heron's formula
    double area() const {
        double s = perimeter() / 2;
        return sqrt(s * (s - a) * (s - b) * (s - c));
    }

    // Print function
    void print() const {
        cout << "Triangle sides: a = " << a << ", b = " << b << ", c = " << c << endl;
        cout << "Color: " << color << endl;
        cout << "Perimeter: " << perimeter() << endl;
        cout << "Area: " << area() << endl;
    }
};

int main() {
    // Test default constructor
    cout << "Testing default constructor:" << endl;
    Triangle t1;
    t1.print();
    cout << endl;

    // Test parameterized constructor with valid sides
    cout << "Testing parameterized constructor (valid sides):" << endl;
    Triangle t2(3, 4, 5, "Blue");
    t2.print();
    cout << endl;

    // Test parameterized constructor with invalid sides
    cout << "Testing parameterized constructor (invalid sides):" << endl;
    Triangle t3(1, 2, 3, "Red"); // Should default to (1,1,1)
    t3.print();
    cout << endl;

    // Test setters
    cout << "Testing setters:" << endl;
    t1.setSides(5, 5, 6);
    t1.setColor("Green");
    t1.print();
    cout << endl;

    // Test setting invalid sides
    cout << "Testing setting invalid sides:" << endl;
    t1.setSides(1, 2, 3); // Should not change
    t1.print();
    cout << endl;

    return 0;
}
