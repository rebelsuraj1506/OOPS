#include<iostream>
#include<string>
using namespace std;

// Base Class 1: Contains student-specific data
class Student {
public:
    int age;
    string name;
    int rollno;
    ~Student() {
        // Destructor for Student
    }
};

// Base Class 2: Contains teacher-specific data
class Teacher {
public:
    string subject;
    double salary;
};

/**
 * MULTIPLE INHERITANCE:
 * The class 'TA' inherits from both 'Student' and 'Teacher'.
 * It combines all members from both classes into one.
 */
class TA : public Student, public Teacher {
public:
    void getInfo() {
        /**
         * THE 'this' POINTER:
         * Implicitly used here. 'name' is 'this->name' (from Student)
         * and 'subject' is 'this->subject' (from Teacher).
         */
        cout << "Name : " << name << endl;    // Inherited from Student
        cout << "Age : " << age << endl;      // Inherited from Student
        cout << "Rollno : " << rollno << endl; // Inherited from Student
        cout << "Subject : " << subject << endl; // Inherited from Teacher
        cout << "Salary : " << salary << endl;   // Inherited from Teacher
    }
};

int main() {
    // 1. Create instance of TA. 
    // Constructors called in order: Student -> Teacher -> TA
    TA t1;
    
    // 2. Assign values to inherited public members
    t1.name = "Suraj";
    t1.subject = "OOPS";
    t1.salary = 150000;
    
    // 3. Display information
    t1.getInfo();
    
    // 4. Accessing members directly via public inheritance
    cout << t1.name << " " << t1.subject << endl;

    return 0;
    // 5. Destructors called in reverse order: TA -> Teacher -> Student
}
