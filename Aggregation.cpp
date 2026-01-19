#include <iostream>
#include <string>
#include <memory> 

using namespace std;
/**
 * DEFINITION: COMPOSITION vs. AGGREGATION
 * 
 * 1. COMPOSITION ("Part-of"): The lifetime of the contained objects (Employee, Roles) 
 *    is managed by the container (TeamLead). If TeamLead is destroyed, its roles die too.
 * 
 * 2. AGGREGATION ("Has-a"): A weaker relationship where the parts can exist independently.
 * 
 * 3. WHY AVOID INHERITANCE? 
 *    Composition follows the 'Single Responsibility Principle'. Each class manages 
 *    one domain (data, management, or coding) without complex branching paths.
 */

// BASE COMPONENT: Standard Employee Data
class Employee {
public:
    int id;
    /**
     * INITIALIZER LISTS: Preferred in 2026 for performance. 
     * It initializes the member directly rather than assigning it after creation.
     */
    Employee(int _id) : id(_id) {}
};

// COMPONENT: Management Functionality
class ManagerRole {
public:
    int managementLevel;
    ManagerRole(int level) : managementLevel(level) {}
};

// COMPONENT: Engineering Functionality
class DeveloperRole {
public:
    string primaryLanguage;
    DeveloperRole(string lang) : primaryLanguage(lang) {}
};

/**
 * THE CONTAINER CLASS: TeamLead
 * 
 * Instead of inheriting from three different classes (Diamond Shape), 
 * we "Compose" the TeamLead by making those classes member variables.
 * 
 * ADVANTAGE: 
 * - No Ambiguity: Each 'id' or 'property' belongs to a specific, named object.
 * - Encapsulation: Internal changes to 'DeveloperRole' won't break 'ManagerRole'.
 */
class TeamLead {
public:
    /**
     * MEMBER OBJECTS (The "Has-A" Relationship):
     * TeamLead is NOT an Employee; TeamLead HAS an Employee profile.
     */
    Employee generalProfile;   // Data component
    ManagerRole mgtRole;       // Role component A
    DeveloperRole devRole;     // Role component B

    // Constructor: Orchestrates the creation of all internal components
    TeamLead(int id, int level, string lang) 
        : generalProfile(id), mgtRole(level), devRole(lang) {
        std::cout << "[System] TeamLead assembled via Composition (2026 Architecture).\n";
    }

    /**
     * INTERFACE: showInfo
     * Accesses internal components via "Dot Notation" (obj.member.variable).
     * This is safer and more readable than multiple inheritance scope resolution (::).
     */
    void showInfo() {
        std::cout << "\n--- TeamLead Unified Dashboard ---\n";
        std::cout << "Unique Employee ID: " << generalProfile.id << "\n";
        std::cout << "Management Tier:   " << mgtRole.managementLevel << "\n";
        std::cout << "Core Tech Stack:   " << devRole.primaryLanguage << "\n";
        std::cout << "----------------------------------\n";
    }
};

int main() {
    /**
     * EXECUTION:
     * In 2026, stack allocation remains the fastest for local objects.
     * The components are initialized in the order they appear in the class declaration.
     */
    TeamLead tl(101, 5, "C++26 Standards");

    cout << "TeamLead ID: " << tl.generalProfile.id << endl;
    cout << "Management Tier: " << tl.mgtRole.managementLevel << endl;
    cout << "Core Tech Stack: " << tl.devRole.primaryLanguage << endl;
    tl.showInfo();

    return 0;
}
