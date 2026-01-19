#include <iostream>
#include <string>
#include <typeinfo> // Required for dynamic_cast to work
using namespace std;

/**
 * ABSTRACTION:
 * Abstraction is the process of hiding internal implementation details 
 * and showing only the essential features of an object to the user.
 * It reduces complexity and allows focusing on "what" an object does 
 * rather than "how" it does it.
 */

/**
 * ABSTRACT CLASS PROPERTIES:
 * 1. An abstract class is a class that contains at least one "Pure Virtual Function".
 * 2. You cannot create an object (instantiate) of an abstract class.
 * 3. It serves as a blueprint or "contract" for derived classes.
 * 4. Derived classes MUST override all pure virtual functions to be instantiated.
 */

// 1. ABSTRACT CLASS (The Abstraction) - Must have at least one virtual function
class PaymentMethod {
public:
    // Pure Virtual Function: Defines the interface but no implementation.
    /**
     * PURE VIRTUAL FUNCTION:
     * Declared by assigning 0 to the declaration. 
     * It has no body here and forces derived classes to implement it.
     */
    virtual void processPayment(double amount) = 0;

    // A regular function can still exist in an abstract class.
    void showReceipt(double amount) {
        cout << "Receipt generated for: $" << amount << endl;
    }

    // A virtual destructor is good practice when using polymorphism/dynamic allocation
    virtual ~PaymentMethod() = default; 
};

// 2. CONCRETE CLASS: Credit Card
class CreditCard : public PaymentMethod {
public:
    void processPayment(double amount) override {
        cout << "Processing $" << amount << " via Credit Card Secure Gateway..." << endl;
        // Complex encryption and bank communication logic happens here (hidden).
    }
};

// 3. CONCRETE CLASS: PayPal
class PayPal : public PaymentMethod {
public:
    void processPayment(double amount) override {
        cout << "Redirecting to PayPal... Processing $" << amount << endl;
        // API calls and wallet verification logic happens here (hidden).
    }
    
    // This function is specific to PayPal, not part of the base interface.
    void remainingBalance(double amount, double used){
        cout << "Your remaining balance is $" << amount - used << endl;
    }
};

int main() {
    // PaymentMethod p; // ERROR: Cannot instantiate an abstract class.

    // Using pointers to the Abstract class (Abstraction in action)
    PaymentMethod* myPayment;

    // --- Credit Card Example ---
    myPayment = new CreditCard();
    myPayment->processPayment(150.00); 
    myPayment->showReceipt(150.00);
    delete myPayment; // Clean up memory

    cout << "--------------------------" << endl;

    // --- PayPal Example ---
    myPayment = new PayPal();
    myPayment->processPayment(45.50);
    myPayment->showReceipt(45.50);

    /**
     * DYNAMIC CASTING:
     * Used to convert the base class pointer (PaymentMethod*) back to 
     * the derived class pointer (PayPal*) to access specific functionality.
     */
    PayPal* paypalPtr = dynamic_cast<PayPal*>(myPayment);
    if (paypalPtr != nullptr) {
        paypalPtr->remainingBalance(150, 45.50);
    } else {
        cout << "Error casting pointer to PayPal type." << endl;
    }

    delete myPayment; // Clean up memory
    return 0;
}
