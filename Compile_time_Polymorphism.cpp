#include<iostream>   // Header file for input-output stream.
#include<string>     // Header file for using string class.
using namespace std; // To avoid prefixing std:: with standard library entities.

// Class representing a student entity.
class Student {
public:
    string name;  // Data member for storing student's name.
    int age;      // Data member for storing student's age.
    int rollno;   // Data member for storing student's roll number.

    /**
     * POLYMORPHISM:
     * Polymorphism is an OOP concept where the same function, operator, or name
     * can behave differently based on the context or the data it operates on.
     * In this code, constructor overloading and function overloading are examples
     * of compile-time (static) polymorphism.
     */
    /**
     * POLYMORPHISM (Static/Compile-time): Constructor Overloading
     * Multiple constructors exist with different parameter lists.
     * The compiler decides which one to use at compile-time based on arguments.
     */

    // 1. Non-parameterized (Default) Constructor
    Student() {
        cout << "Non-parameterized Constructor" << endl;
        /**
         * When object of Student is created without parameters,
         * this constructor is automatically called.
         */
    }

    // 2. Parameterized Constructor (Function Overloading Example)
    Student(string name, int age, int rollno) {
        cout << "Parameterized Constructor" << endl;

        /**
         * THE 'this' POINTER:
         * 'this' is an implicit pointer available inside all non-static class functions.
         * It points to the current object that invoked the function.
         * Here, 'this->name' refers to the class member,
         * whereas 'name' refers to the local (parameter) variable.
         */
        this->name = name;
        this->age = age;
        this->rollno = rollno;
    }

    // Destructor (called automatically when object goes out of scope)
    ~Student() {
        // Can be used for cleanup or releasing dynamic memory if allocated.
    }

    /**
     * Member function to print student details.
     * Return type: void (does not return any value)
     */
    void getInfo() {
        cout << "Name : " << name << endl;
        cout << "Age : " << age << endl;
        cout << "Rollno : " << rollno << endl;
    }
};

// Another class to demonstrate Function Overloading.
class Print {
public:
    // Function with int parameter
    void show(int x) {
        cout << "Integer x = " << x << endl;
    }
    
    // Overloaded function with string parameter
    void show(string x) {
        cout << "Name = " << x << endl;
    }
};

// Class to demonstrate Operator Overloading.
class Number {
    public:
        int value;
    
        Number(int v) {
            value = v;
        }
        
        /**
        * OPERATOR OVERLOADING:
        * Operator overloading allows redefining how operators (like +, -, ==)
        * work with user-defined types (classes/structs). It is also a form
        * of compile-time polymorphism in C++.[web:11][web:12]
        */
        // Overload + operator to return a new Number object directly
        Number operator+(const Number& other) const {
            // Use the existing parameterized constructor to return the sum
            return Number(value + other.value);
        }
    
        void display() {
            cout << "Function Overloading. " << endl;
            cout << "Number sum = " << value << endl;
        }
    };
    
int main() {

    /**
     * Polymorphism in action (Compile-time/Static Binding)
     * The compiler determines which constructor to invoke based on the arguments.
     */

    Student s1;  // Calls Non-parameterized constructor.

    Student s2("Rahul", 25, 31);  // Calls Parameterized constructor.

    // Calling member function to display student information.
    s2.getInfo();

    // Demonstration of Function Overloading:
    Print p1;  // Object of Print class.

    // Compiler selects correct function based on argument type.
    p1.show(25);      // Calls show(int)
    p1.show("Rahul"); // Calls show(string)

    // Demonstration of Operator Overloading:
    Number n1(10);
    Number n2(20);
    Number n3 = n1 + n2;  // Uses overloaded + operator.

    n3.display(); // Outputs: Number sum = 30

    return 0; // Successful program termination.
}
