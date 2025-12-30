#include<iostream>
#include<string>
using namespace std;

/**
 * 1. HIERARCHICAL INHERITANCE (Base Part)
 * 'Person' is the single base class for both 'Student' and 'Teacher'.
 */
class Person {
public:
    string name;
    int age;
};

/**
 * 2. VIRTUAL INHERITANCE (The Solution)
 * The 'virtual' keyword solves the "Diamond Problem."
 * It ensures that when a class (like TA) inherits from both Student and Teacher,
 * only ONE shared instance of 'Person' is created in memory.
 */
class Student : virtual public Person {
public:
    int rollno;
    ~Student() {
        // 'this' pointer is implicit here, pointing to the current Student instance
    }
};

class Teacher : virtual public Person {
public:
    string subject;
    double salary;
    ~Teacher() {
        // 'this' pointer can be used to distinguish between local and class members
    }
};

/**
 * 3. MULTIPLE INHERITANCE (Derived Part)
 * 'TA' inherits from both 'Student' and 'Teacher'.
 * 
 * 4. HYBRID INHERITANCE (Overall Structure)
 * This complete structure is 'Hybrid' because it combines Hierarchical and Multiple inheritance.
 */
class TA : public Student, public Teacher {
public:
    void getInfo() {
        /**
         * THE 'this' POINTER:
         * Inside getInfo(), 'this' points to the current TA object.
         * It provides access to all members inherited from the various levels:
         * - this->name (from shared Person)
         * - this->rollno (from Student)
         * - this->subject (from Teacher)
         */
        cout << "Name : " << name << endl;    // Resolves to shared Person::name
        cout << "Age : " << age << endl;      // Resolves to shared Person::age
        cout << "Rollno : " << rollno << endl;
        cout << "Subject : " << subject << endl;
        cout << "Salary : " << salary << endl;
    }
};

int main() {
    /**
     * 5. THE DIAMOND PROBLEM:
     * Without 'virtual' above, 't1' would have TWO names (Student::name and Teacher::name),
     * causing the compiler to throw an "ambiguous access" error.
     */
    TA t1;
    t1.name = "Suraj";
    t1.subject = "OOPS";
    t1.salary = 150000;

    // Call getInfo which uses the shared data members
    t1.getInfo();

    // Direct access in main() works because inheritance is public
    cout << t1.name << " " << t1.subject << endl;

    return 0;
}
