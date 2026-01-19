#include <iostream>
#include <string>
using namespace std;

// The shared "Grandparent" class
class Employee {
public:
    int id;
    Employee() { cout << "Employee Constructor called" << endl; }
};

// Use 'virtual' inheritance here to share the Employee instance
class Manager : virtual public Employee {
public:
    Manager() { cout << "Manager Constructor called" << endl; }
};

class Developer : virtual public Employee {
public:
    Developer() { cout << "Developer Constructor called" << endl; }
};

// The 'join' class at the bottom of the diamond
class TeamLead : public Manager, public Developer {
public:
    TeamLead() { cout << "TeamLead Constructor called" << endl; }
};

int main() {
    TeamLead t1;
    
    // Without virtual inheritance, this next line would be ambiguous 
    // and cause a compile error because 'id' would exist twice.
    t1.id = 101; 
    t1.Manager::id = 102;
    t1.Developer::id = 103; 
    cout << "Manager ID: " << t1.Manager::id << endl;
    cout << "Developer ID: " << t1.Developer::id << endl;
    cout << "TeamLead ID: " << t1.id << endl;
    cout << "Employee ID: " << t1.Employee::id << endl;
    return 0;
}
