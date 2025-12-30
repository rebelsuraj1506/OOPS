#include<iostream>
#include<string>
using namespace std;

class Person{
public:
    string name;
    int age;
    // Parameterized constructor
    Person(string name, int age){
        this->name = name;
        this->age = age;
    }
    // Default constructor (Needed for s1)
    // Person(){
    //     cout << "This is parent constructor" << endl;
    // }
    // Virtual destructor is a 2025 best practice for inheritance
    virtual ~Person(){

    }
};

// Level 2: Derived Class (Inherits from Person)
// This is SINGLE INHERITANCE at this stage
class Student : public Person{
public:
    // // Expose name from the base class via a public method
    // Exposing base members via public methods (Getters)
    string getName(){ return name; } 
    int getAge(){ return age; }
    int rollno;
    using Person :: Person;
    // Explicitly define a constructor for Student
    // Custom constructor for Student; calls Person's constructor
    Student(string name, int age, int rno) : Person(name, age) {
        this->rollno = rno;
    }

    // // You also need to keep or define a default constructor if using s1
    // Student() : Person() {}

    void getInfo() {
        cout << "Name : " << name << endl;
        cout << "Age : " << age << endl;
        cout << "Rollno : " << rollno << endl;
    }

    void changeRollno(int rollno){
        this->rollno = rollno;
    }
    // First dervied class destructor takes place and then the base class.
    // When an object is destroyed, its destructors are called in the exact reverse order of its constructors. 
    // Constructor Order: Person (Base) → Student (Derived).
    // Destructor Order: Student (Derived) → Person (Base). 
    // Destructor for Level 2
    ~Student(){

    }
};

 // Multilevel Inheritance
 /**
 * Level 3: Derived Class (Inherits from Student)
 * This completes the MULTILEVEL INHERITANCE chain:
 * Person -> Student -> GradStudent
 */
class GradStudent : public Student{
public:
    string researchArea;

    // Function Overriding: Redefining getName() from the parent class
    string getName(){return name;}

    // Constructor for Level 3: Calls Student constructor, which calls Person constructor
    GradStudent(string name, int age, int rno, string res) : Student(name, age, rno){
        this->researchArea = res;
    }

    // Function Overriding: Redefining getInfo() for GradStudent specifics
    void getInfo(){
        cout << "Name : " << name << endl;
        cout << "Age : " << age << endl;
        cout << "Rollno : " << rollno << endl;
        cout << "Research Area : " << researchArea << endl;
    }
};

int main(){
    // Student s1;
    // s1.name = "Rahul";
    // s1.age = 21;
    // s1.rollno = 34;

    // 1. Working with Level 2 (Student)
    Student s2("Neha", 25, 35);
    s2.getInfo();
    cout << "Name from Getter: " << s2.getName() << endl;

    s2.changeRollno(46);
    s2.getInfo();

    // 2. Working with Level 3 (GradStudent)
    // Construction Order: Person -> Student -> GradStudent
    GradStudent s3("Avnish", 28, 1, "AI");
    s3.getInfo();

    // Direct access to 'name' is possible because inheritance is 'public'
    cout << "Direct Access: " << s3.name << endl;

    return 0;
    // 3. Destruction Order (Reverse): GradStudent -> Student -> Person
}