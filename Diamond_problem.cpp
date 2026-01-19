#include <iostream>
#include <string>
using namespace std;

/**
 * ============================================================================
 * THE DIAMOND PROBLEM: REPLICATED INHERITANCE (NON-VIRTUAL)
 * ============================================================================
 * 
 *        [ Employee ] (Copy A)      [ Employee ] (Copy B)
 *             |                          |
 *        [ Manager ]                [ Developer ]
 *             \                        /
 *              \-------[ TeamLead ]---/
 * 
 * DIAGRAM EXPLANATION:
 * Because the 'virtual' keyword is NOT used, the inheritance graph splits.
 * 'TeamLead' ends up with TWO distinct 'Employee' sub-objects in its memory.
 * This is the classic "Deadly Diamond of Death" leading to ambiguity.
 * ============================================================================
 */

class Employee {
public:
    int id; // This variable exists twice inside a TeamLead object
    Employee() { 
        cout << "[System] Employee Base Constructor Executed" << endl; 
    }
};

/**
 * CLASS: Manager
 * Inherits a UNIQUE copy of Employee.
 */
class Manager : public Employee {
public:
    Manager() { 
        cout << "[System] Manager Layer Created" << endl; 
    }
};

/**
 * CLASS: Developer
 * Inherits a SECOND UNIQUE copy of Employee.
 */
class Developer : public Employee {
public:
    Developer() { 
        cout << "[System] Developer Layer Created" << endl; 
    }
};

/**
 * CLASS: TeamLead (The Joint Class)
 * Inherits from both Manager and Developer.
 */
class TeamLead : public Manager, public Developer {
public:
    int id; // Local 'id' to hide the ambiguity of the two inherited 'id's.
    
    TeamLead() { 
        cout << "[System] TeamLead Final Layer Created" << endl; 
    }
};

int main() {
    /** 
     * 2026 MEMORY LAYOUT ANALYSIS:
     * When 't1' is created, the Employee constructor runs TWICE.
     * Memory Map of t1:
     * 1. [Manager::Employee::id] -> Path A
     * 2. [Developer::Employee::id] -> Path B
     * 3. [TeamLead::id] -> Local Path
     */
     /**
     * VISUALIZING THE DIAMOND IN MEMORY:
     *        [Employee]  <-- Top
     *         /      \
     *    [Manager] [Developer]  <-- Left/Right
     *         \      /
     *        [TeamLead]  <-- Bottom
     */
    cout << "--- Initializing TeamLead Object ---" << endl;
    TeamLead t1;
    
    /**
     * RESOLVING AMBIGUITY:
     * In 2026, we use the Scope Resolution Operator (::) to tell the 
     * compiler exactly which "replicated" copy of 'id' we want to modify.
     */
     // Accessing the 'Left' side of the diamond
    t1.Manager::id = 101; 
    // Accessing the 'Right' side of the diamond
    t1.Developer::id = 102;   
    // Accessing the 'Bottom' point directly
    t1.id = 103;              // Accessing TeamLead's own local 'id'

    cout << "\n--- Diamond Access Result ---\n";
    cout << "Left-Side ID  : " << t1.Manager::id << endl;
    cout << "Right-Side ID : " << t1.Developer::id << endl;
    cout << "Bottom-Point ID: " << t1.id << endl;
    
    // A separate variable for demonstration
    int employeeVal = 104; 

    cout << "\n--- Diamond Problem Output (Replicated Path) ---" << endl;
    
    // Proves that Manager::id and Developer::id are at DIFFERENT memory addresses
    cout << "Manager Path ID:   " << t1.Manager::id << endl;     // Result: 101
    cout << "Developer Path ID: " << t1.Developer::id << endl; // Result: 102
    cout << "TeamLead Own ID:   " << t1.id << endl;             // Result: 103
    cout << "Employee (Local):  " << employeeVal << endl;       // Result: 104

    /**
     * CONCLUSION:
     * This code successfully manages the Diamond Problem by manually 
     * identifying paths. However, 't1' is carrying 3 different 'id' 
     * variables in memory, which is inefficient compared to Virtual Inheritance.
     */
    return 0;
}
