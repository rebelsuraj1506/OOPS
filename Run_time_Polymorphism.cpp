#include<iostream>   // Header file for input-output stream.
#include<string>     // Header file for using string class.
using namespace std; // To avoid prefixing std:: with standard library entities.

// Base Class (Parent)
class Parent {
public:
    string name;

    /**
     * NORMAL MEMBER FUNCTION:
     * This function uses static binding. If called via a Parent pointer 
     * pointing to a Child object, the Parent version would still execute.
     */
    void show() {
        cout << "Parent Class." << endl;
    }

    /**
     * VIRTUAL FUNCTION:
     * 1. Defined by the 'virtual' keyword inside a base class.
     * 2. Always declared in a base class and overridden in a derived class.
     * 3. Called during runtime (Dynamic Binding / Late Binding).
     * 4. Dynamic in nature: The exact function to call is decided based on the 
     *    actual object type, not the pointer type.
     */
    virtual void hello(){
        cout << "Hello from Parent.\n";
    }
};

/**
 * INHERITANCE:
 * The Child class inherits from the Parent class.
 * It gains access to all public members, such as the 'name' variable.
 */
class Child : public Parent {
public:
    /**
     * FUNCTION OVERRIDING (Static):
     * The Child class provides its own implementation of show().
     * This "hides" the Parent's version when called by a Child object.
     */
     // Overriding the non-virtual show() function
    void show() {
        cout << "Child Class." << endl;
    }

    /**
     * FUNCTION OVERRIDING (Dynamic):
     * This overrides the virtual hello() from the Parent class.
     * Note: The 'virtual' keyword is inherited, so hello() is also virtual here.
     */
    void hello(){
        cout << "Hello from Child.\n";
    }
};

int main() {
    // 1. Creating a Child object
    Child c1;

    /**
     * 2. Static Binding / Early Binding:
     * The compiler calls Child::show() because c1 is explicitly a Child object.
     */
    c1.show(); // Output: Child Class.

    /**
     * 3. Inheritance in Action:
     * Accessing the 'name' data member inherited from the Parent class.
     */
    c1.name = "Rahul";
    cout << c1.name << endl; // Output: Rahul

    /**
     * 4. Dynamic Binding / Late Binding:
     * Since hello() is virtual in the base class, the program ensures 
     * the most specific version (Child::hello) is executed.
     */
    c1.hello(); // Output: Hello from Child.

    // Dynamic nature: even via a Parent pointer, the Child version is called.
    Parent* ptr = &c1; 
    ptr->hello(); // Output: Hello from Child. (Runtime resolution)
    ptr->Parent::hello(); // Output: Hello from Parent.
    c1.Parent::hello(); // Output: Hello from Parent.

    return 0; // Successful program termination.
}
