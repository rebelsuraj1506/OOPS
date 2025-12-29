#include<iostream>
#include<string>
using namespace std;

// CLASS 1: IMPLEMENTING SHALLOW COPY
class ShallowStudent {
public:
    string name;
    double* cgpaPtr;

    ShallowStudent(string name, double cgpa) {
        this->name = name;
        this->cgpaPtr = new double;
        *cgpaPtr = cgpa;
    }

    // Explicit Shallow Copy Constructor (Same as default compiler behavior)
    ShallowStudent(ShallowStudent &obj) {
        this->name = obj.name;
        this->cgpaPtr = obj.cgpaPtr; // Copies the ADDRESS (Both point to same heap memory)
    }

    // Destructor commented out for Shallow class to prevent program crash (Double Free)
    // ~ShallowStudent() { delete cgpaPtr; } 

    void getInfo() {
        cout << "Name: " << name << ", CGPA: " << *cgpaPtr << " (at Address: " << cgpaPtr << ")" << endl;
    }
};

// CLASS 2: IMPLEMENTING DEEP COPY
class DeepStudent {
public:
    string name;
    double* cgpaPtr;

    DeepStudent(string name, double cgpa) {
        this->name = name;
        this->cgpaPtr = new double;
        *cgpaPtr = cgpa;
    }

    // Deep Copy Constructor
    DeepStudent(DeepStudent &obj) {
        this->name = obj.name;
        this->cgpaPtr = new double;         // Allocate BRAND NEW memory on heap
        *(this->cgpaPtr) = *(obj.cgpaPtr);  // Copy the VALUE to the new address
    }

    // Safe Destructor: Each object has its own memory to delete
    ~DeepStudent() {
        delete cgpaPtr;
    }

    void getInfo() {
        cout << "Name: " << name << ", CGPA: " << *cgpaPtr << " (at Address: " << cgpaPtr << ")" << endl;
    }
};

// Main function
int main() {
    // --- 1. SHALLOW COPY DEMONSTRATION ---
    cout << "--- SHALLOW COPY TEST ---" << endl;
    ShallowStudent s1("Rahul", 8.5);
    ShallowStudent s2(s1); // Shallow copy happens here

    cout << "Before Modification:" << endl;
    s1.getInfo();
    s2.getInfo();

    *(s2.cgpaPtr) = 9.9; // Changing s2's CGPA also changes s1!

    cout << "After modifying s2.cgpaPtr to 9.9:" << endl;
    s1.getInfo(); // s1 is now 9.9
    s2.getInfo(); // s2 is now 9.9
    cout << "Observation: Both share the same memory address." << endl;


    // --- 2. DEEP COPY DEMONSTRATION ---
    cout << "\n--- DEEP COPY TEST ---" << endl;
    DeepStudent d1("Anjali", 9.0);
    DeepStudent d2(d1); // Deep copy happens here

    cout << "Before Modification:" << endl;
    d1.getInfo();
    d2.getInfo();

    *(d2.cgpaPtr) = 9.5; // Changing d2's CGPA does NOT affect d1

    cout << "After modifying d2.cgpaPtr to 9.5:" << endl;
    d1.getInfo(); // d1 stays 9.0
    d2.getInfo(); // d2 becomes 9.5
    cout << "Observation: Both have unique, independent memory addresses." << endl;

    return 0;
}
