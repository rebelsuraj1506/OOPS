#include <iostream>
#include <string>
using namespace std;

class Employee {
public:
    int id;
    // Parameterized constructor
    Employee(int emp_id) : id(emp_id) { 
        cout << "Employee initialized with ID: " << id << endl; 
    }
};

class Manager : virtual public Employee {
public:
    // Manager calls Employee(id), but this is ignored when part of TeamLead
    Manager(int id) : Employee(id) { 
        cout << "Manager Constructor" << endl; 
    }
};

class Developer : virtual public Employee {
public:
    // Developer calls Employee(id), but this is ignored when part of TeamLead
    Developer(int id) : Employee(id) { 
        cout << "Developer Constructor" << endl; 
    }
};

class TeamLead : public Manager, public Developer {
public:
    /**
     * IMPORTANT: The most derived class (TeamLead) MUST 
     * explicitly initialize the virtual base (Employee).
     */
    TeamLead(int id) : Employee(id), Manager(id), Developer(id) { 
        cout << "TeamLead Constructor" << endl; 
    }
};

int main() {
    // TeamLead directly passes the ID to Employee
    TeamLead tl(500); 
    tl.Manager::id = 102;
    tl.Developer::id = 103;
    tl.Employee::id = 104;
    cout << "Manager ID: " << tl.Manager::id << endl;
    cout << "Developer ID: " << tl.Developer::id << endl;
    cout << "Employee ID: " << tl.Employee::id << endl;
    cout << "Final TeamLead ID: " << tl.id << endl;
    return 0;
}
