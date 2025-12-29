#include<iostream> 
#include<string>
using namespace std; 

class Teacher{
private:
    double salary; // Private data: Access restricted (Encapsulation)
public:
    // properties / attributes
    // Constructor doesn't have a return type and has same name as class.
    // 1. Non-parameterized (Default) Constructor
    string name;
    string dept;
    string subject;
    Teacher(){ // Constructor is always declared public because main function can't directly access private modifiers.
        // cout << "Hi, I am constructor.\n";
        dept = "Computer Science";
    }

    // 2. Parameterized Constructor
    // Teacher(string n, string d, string s, double sal){ 
    //     name  = n;
    //     dept = d;
    //     subject = s;
    //     salary = sal;
    // }

    Teacher(string name, string dept, string subject, double salary){ 
        // this is a special pointer in C++ that points to current object
        // this->property is same as *(this).prop because *this points to obj and normally how we call obj.prop in main function.
        // 'this' pointer differentiates between class members and parameters
        this->name  = name;
        this->dept = dept;
        this->subject = subject;
        this->salary = salary;
    }

    // 3. Custom Copy Constructor (Pass by reference)
    Teacher(Teacher &orgObj){  //pass by reference
        cout << "I am custom copy constructor.\n";
        this->name = orgObj.name + " Kumar";
        this->dept = orgObj.dept;
        this->subject = orgObj.subject;
        this->salary = orgObj.salary * 1.15;
    }

    //methods / member functions(known as member functions because the functions becomes members inside the class)
    // Methods (Member Functions)
    void changeDept(string newDept){
        dept = newDept;
    }

    // Setter: To modify private data
    void setSalary(double s){
        salary = s;
    }
    
    // Getter: To read private data
    double getSalary(){
        return salary;
    }

    void getInfo(){
        cout << "Name : " << name << endl;
        cout << "Subject: " << subject << endl;
        cout << "Dept: " << dept << endl;
        cout << "Salary: " << getSalary() << endl;
    }
};

class Account{
private:
    double balance;
    string password; //data hiding(not accessible outside the class)
public:
    string accountID;
    string userName;
};

class Student{
public:
    string name;
    double* cgpaPtr; // Pointer for dynamic memory allocation on the Heap

    // Constructor: Allocates memory on Heap
    Student(string name, double cgpa){
        this->name = name;
        cgpaPtr = new double; // Allocate memory on HEAP
        *cgpaPtr = cgpa;
    }
    /* 
       Note on Shallow Copy:
       The default compiler constructor would do: this->cgpaPtr = obj.cgpaPtr;
       This causes both objects to share the same heap memory address.
    */
    // Student(Student &obj){
    //     this->name  = obj.name;
    //     this->cgpaPtr = obj.cgpaPtr;
    // }

    // 4. DEEP COPY CONSTRUCTOR
    // Manually implemented to create a separate copy of heap-allocated memory
    Student(Student &obj){
        this->name  = obj.name;
        cgpaPtr = new double; // Allocate NEW independent memory on HEAP
        *(this->cgpaPtr) = *(obj.cgpaPtr); // Copy the VALUE from the old address to new address
    }

    // 5. DESTRUCTOR
    // Required to release Heap memory when object goes out of scope (prevents Memory Leaks)
    ~Student(){
        delete cgpaPtr;
    }

    void getInfo(){
        cout << "Name : " << name << endl;
        cout << "CGPA : " << *cgpaPtr << endl;
    }
};


int main(){
    // --- Teacher Initialization ---
    Teacher t1; //constructor call, Memory allocation happens when constructor is called.
    t1.name = "Suraj";
    t1.subject = "OOPS";
    t1.setSalary(100000);

    Teacher t2("Avnish", "CSE", "OOPS", 200000);

    // Invoking custom copy constructors
    Teacher t3(t1); 
    Teacher t4(t1); 
    // t1.dept = "CSE";
    // string newDept = "ECE";
    cout << "Printing Teacher1 Info : ";
    // cout << "Teacher1 name : " << t1.name << endl;
    // cout << "Teacher1 dept : " << t1.dept << endl;
    // cout << t1.getSalary()<< endl;
    t1.getInfo();

    t2.changeDept("ECE");
    cout << t2.dept << endl;

    t2.changeDept("Civil");
    cout << "Teacher2 old salary : " << t2.getSalary() << endl;
    t2.setSalary(150000);
    cout << "Printing Teacher2 Info : ";
    t2.getInfo();

    cout << "Teacher3 old salary : " << t3.getSalary() << endl;
    t3.setSalary(120000);
    cout<< "Printing Teacher3 Info : ";
    t3.getInfo();

    cout << "Teacher4 old salary : " << t4.getSalary() << endl;
    t4.setSalary(110000);
    cout<< "Printing Teacher4 Info : ";
    t4.getInfo();

    // --- Student Logic (Deep Copy Verification) ---
    cout << "\n--- Student Deep Copy Test ---" << endl;
    Student s1("Shyam", 7.6);
    cout << "Student 1 (Original):" << endl;
    s1.getInfo();

    // Create s2 as a Deep Copy of s1
    Student s2(s1); // Deep copy happens here
    *(s2.cgpaPtr) = 8.3; // Changing s2's CGPA does NOT affect s1
    s2.name = "Ghanshyam";

    cout << "\nStudent 1 Info after s2 modification (Should stay 7.6):" << endl;
    s1.getInfo();

    cout << "\nStudent 2 Info (Should be 8.3 and Ghanshyam):" << endl;
    s2.getInfo();

    return 0;
}
