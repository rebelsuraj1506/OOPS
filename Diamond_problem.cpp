#include <iostream>
#include <string>
using namespace std;

/**
 * THE DIAMOND PROBLEM DEFINITION:
 * The Diamond Problem occurs in C++ when a class (TeamLead) inherits from 
 * multiple classes (Manager, Developer) that share a common base (Employee).
 *
 * Without 'virtual' inheritance:
 * 1. AMBIGUITY: The compiler doesn't know which 'Employee' copy to use.
 * 2. REDUNDANCY: Multiple copies of 'Employee' members exist in memory.
 * 3. REPLICATED INHERITANCE: The inheritance graph forms a diamond shape 
 *    with a duplicate base subobject for every path from child to grandparent.
 */

// [ Employee ]          <-- Base Class (Top)
// /      \
// [Manager] [Developer]   <-- Derived Classes (Middle)
// \      /
// [TeamLead]            <-- Joint Derived Class (Bottom)

class Employee {
public:
    int id;
    Employee() { cout << "Employee Constructor" << endl; }
};

// Replicated Inheritance: Manager gets its own unique 'Employee' copy
class Manager : public Employee {
public:
    Manager() { cout << "Manager Constructor" << endl; }
};

// Replicated Inheritance: Developer gets its own unique 'Employee' copy
class Developer : public Employee {
public:
    Developer() { cout << "Developer Constructor" << endl; }
};

class TeamLead : public Manager, public Developer {
public:
    int id; // Specifically for TeamLead to avoid ambiguity with parents
    TeamLead() { cout << "TeamLead Constructor" << endl; }
};

int main() {
    /** 
     * In the 2026 memory layout for 't1':
     * - [Manager's Employee::id] at Address A
     * - [Developer's Employee::id] at Address B
     * - [TeamLead's id] at Address C
     */
    TeamLead t1;
    
    // RESOLVING AMBIGUITY VIA SCOPE RESOLUTION:
    // We manually point to different memory addresses.
    t1.Manager::id = 101;     
    t1.Developer::id = 102;   
    t1.id = 103;              
    
    // Final value for custom display
    int employeeVal = 104; 

    cout << "\n--- Diamond Problem Output (Replicated Path) ---" << endl;
    cout << "Manager Path ID:   " << t1.Manager::id << endl;     // Output: 101
    cout << "Developer Path ID: " << t1.Developer::id << endl; // Output: 102
    cout << "TeamLead Own ID:   " << t1.id << endl;             // Output: 103
    cout << "Employee (Local):  " << employeeVal << endl;       // Output: 104

    return 0;
}
