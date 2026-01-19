#include <iostream>
#include <string>
using namespace std;

// ABSTRACT BASE CLASS (Parent)
class Parent {
public:
    string name;

    // Virtual Destructor: Ensures derived class cleanup
    virtual ~Parent() {
        cout << "Parent Destructor." << endl;
    }

    void show() {
        cout << "Parent Class." << endl;
    }

    /**
     * PURE VIRTUAL FUNCTION:
     * Declared with '= 0'. This makes the class "Abstract".
     * Objects of 'Parent' cannot be created.
     */
    virtual void hello() = 0; 
};

// DERIVED CLASS (Child)
class Child : public Parent {
public:
    // Destructor
    ~Child() {
        cout << "Child Destructor." << endl;
    }

    void show() {
        cout << "Child Class." << endl;
    }

    // Must implement pure virtual function to be instantiable
    void hello() override {
        cout << "Hello from Child." << endl;
    }
};

int main() {
    // 1. Creating a Child object on the heap
    // This allows us to demonstrate proper destruction via a base pointer.
    Parent* ptr = new Child();

    // 2. Accessing inherited members
    ptr->name = "Rahul";
    cout << "Name: " << ptr->name << endl;

    // 3. Dynamic Binding
    ptr->hello(); // Calls Child::hello()

    /**
     * 4. Safe Memory Cleanup:
     * Because of the virtual destructor, 'delete ptr' will call 
     * Child's destructor first, then Parent's destructor.
     */
    delete ptr; 

    return 0;
}
