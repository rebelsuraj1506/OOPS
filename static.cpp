#include<iostream>   // Header file for input-output stream.
#include<string>     // Header file for using string class.
using namespace std; // To avoid prefixing std:: with standard library entities.

/**
 * STATIC VARIABLES IN FUNCTIONS:
 * When a variable is declared as 'static' inside a function:
 * 1. Space is allocated for the lifetime of the program.
 * 2. It is initialized ONLY ONCE (the first time the function is called).
 * 3. It retains its value across multiple function calls.
 * 4. Allocated in the data segment of memory (not the stack).
 */
void fun(){
    // This line is executed only during the first call to fun()
    static int x = 0; 
    
    cout << "x in fun() : " << x << endl;
    
    // Incrementing x; because it is static, the new value persists
    x++;
}

/**
 * CLASS INSTANCE VARIABLES:
 * These variables are part of the object's state. 
 * Each object (instance) of class A will have its own separate copy of x.
 */
class A{
public:

    int x; // Member variable (Attribute)

    // Method to modify the instance variable
    void incX(){
        x = x + 1;
    }
};

int main(){
    /**
     * Call 1: x is initialized to 0, printed, then incremented to 1.
     */
    fun(); // Output: x : 0
    
    /**
     * Call 2: x is NOT re-initialized. It starts at 1, is printed, then incremented to 2.
     */
    fun(); // Output: x in fun() : 1
    
    /**
     * Call 3: x starts at 2, is printed, then incremented to 3.
     */
    fun(); // Output: x : 2

    /**
     * INSTANCE DEMONSTRATION:
     * 'obj' is an instance of class A. Its 'x' is unique to this object.
     */
     A obj1;
     A obj2;

     // Manual initialization of the member variable
     obj1.x = 100;
     obj2.x = 200;
     cout << "Object 1 x Original value = " << obj1.x << endl; // Output: 0
     // Modifying the state of 'obj'
     obj1.incX();
     cout << "Object 1 x after increment = " << obj1.x << endl; // Output: 1

     cout << "Object 2 x Original value = " << obj2.x << endl; // Output: 200
 
     // Modifying the state of 'obj'
     obj2.incX();
     cout << "Object 2 x after increment = " << obj2.x << endl; // Output: 1
 
     /**
      * Note: If you created another object 'A obj2;', it would have 
      * its own 'x' completely independent of 'obj.x'.
      */
     
    
    return 0; // Successful program termination.
}
