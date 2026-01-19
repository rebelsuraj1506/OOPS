#include <iostream>
#include <string>

/**
 * ============================================================
 * THE DIAMOND PROBLEM: VIRTUAL RESOLUTION
 * ============================================================
 * 
 *        [ Employee ]             <-- Virtual Base (Shared)
 *         /        \
 *  [ Manager ]  [ Developer ]     <-- Virtual Inheritors
 *         \        /
 *        [ TeamLead ]             <-- Most Derived Class
 * 
 * CONCEPT: 
 * Virtual inheritance ensures that 'TeamLead' contains only 
 * ONE instance of the 'Employee' sub-object, regardless of 
 * how many inheritance paths lead back to it.
 * ============================================================
 */

class Employee {
public:
    int id;

    // Parameterized constructor to track initialization
    Employee(int _id) : id(_id) {
        std::cout << "[Step 1] Employee Sub-object Created (ID: " << id << ")\n";
    }

    // VIRTUAL DESTRUCTOR: Crucial for 2026 memory safety.
    // Ensures that deleting via a base pointer cleans up derived memory.
    virtual ~Employee() = default; 
};

/**
 * VIRTUAL PUBLIC INHERITANCE:
 * The 'virtual' keyword tells the compiler: "If someone inherits from 
 * me and another class sharing this base, share the base instance."
 */
class Manager : virtual public Employee {
public:
    Manager(int _id) : Employee(_id) {
        std::cout << "[Step 2] Manager Layer Initialized\n";
    }
};

class Developer : virtual public Employee {
public:
    Developer(int _id) : Employee(_id) {
        std::cout << "[Step 3] Developer Layer Initialized\n";
    }
};

/**
 * THE JOINT CLASS (TeamLead):
 * Inherits from both Manager and Developer.
 */
class TeamLead : public Manager, public Developer {
public:
    /**
     * RULE OF VIRTUAL INHERITANCE:
     * In 2026 C++, the 'Most Derived Class' (TeamLead) is solely 
     * responsible for calling the Virtual Base (Employee) constructor.
     * 
     * The calls to Employee(id) inside Manager and Developer are 
     * COMPLETELY IGNORED when creating a TeamLead object.
     */
    TeamLead(int _id) : Employee(_id), Manager(_id), Developer(_id) {
        std::cout << "[Step 4] TeamLead Object Fully Constructed\n";
    }

    void displayInfo() {
        std::cout << "\n--- Identity Check ---\n";
        // No ambiguity! 'id' refers to the single shared Employee instance.
        std::cout << "TeamLead Universal ID: " << id << "\n";
        std::cout << "Address of 'id': " << &id << " (Shared Location)\n";
        std::cout << "----------------------\n";
    }
};

int main() {
    std::cout << "Starting TeamLead allocation...\n\n";

    // Instantiate TeamLead. 
    // Watch the console: 'Employee' will only be constructed ONCE.
    TeamLead tl(999);
    
    tl.displayInfo();

    /**
     * ADVANTAGE SUMMARY:
     * 1. No Data Redundancy: Memory is optimized.
     * 2. No Ambiguity: tl.id is clear and distinct.
     * 3. Consistency: Every parent sees the same data values.
     */
    
    return 0;
}
