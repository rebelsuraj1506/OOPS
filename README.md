# C++ OOP Examples (Placement/OOPS)

Self-contained C++ programs that demonstrate core OOP topics. Each file has its own `main()`; compile individually with `g++ -std=c++17 <file>.cpp -o demo && ./demo`.

## Encapsulation & constructor patterns (`oops.cpp`)
- **Definition:** Encapsulation hides data behind an interface; constructors set up state, and custom copy constructors control copy semantics.
- **What it shows:** private salary with getters/setters; default, parameterized, and custom copy constructor; deep-copy of heap `cgpaPtr`; destructor cleanup.
- **Sample output (abridged):**
  ```
  Printing Teacher1 Info : Name : Suraj
  Teacher2 old salary : 200000
  Printing Teacher2 Info : Name : Avnish
  Teacher3 old salary : 100000
  Teacher4 old salary : 100000
  --- Student Deep Copy Test ---
  Student 1 (Original):
  Name : Shyam
  CGPA : 7.6
  Student 2 Info (Should be 8.3 and Ghanshyam):
  Name : Ghanshyam
  CGPA : 8.3
  ```

## Abstraction (`Abstraction.cpp`, `Abstraction_child_parent.cpp`)
- **Definition:** Expose *what* an object does via abstract interfaces (pure virtual functions) while hiding *how*.
- **What it shows:** abstract `PaymentMethod::processPayment`, concrete `CreditCard`/`PayPal`, `dynamic_cast` to reach derived-only behavior; separate example with abstract `Parent` and virtual destructor.
- **Sample output:**
  ```
  Processing $150 via Credit Card Secure Gateway...
  Receipt generated for: $150
  --------------------------
  Redirecting to PayPal... Processing $45.5
  Receipt generated for: $45.5
  Your remaining balance is $104.5
  Name: Rahul
  Hello from Child.
  Child Destructor.
  Parent Destructor.
  ```

## Composition vs. aggregation (`Aggregation.cpp`)
- **Definition:** “Has-a” composition assembles objects; lifetimes owned by the container. Aggregation is a weaker, shareable link.
- **What it shows:** `TeamLead` contains `Employee`, `ManagerRole`, `DeveloperRole` instead of inheriting.
- **Sample output:**
  ```
  [System] TeamLead assembled via Composition (2026 Architecture).
  TeamLead ID: 101
  Management Tier: 5
  Core Tech Stack: C++26 Standards
  
  --- TeamLead Unified Dashboard ---
  Unique Employee ID: 101
  Management Tier:   5
  Core Tech Stack:   C++26 Standards
  ```

## Compile-time polymorphism (`Compile_time_Polymorphism.cpp`)
- **Definition:** Binding decided by the compiler via overload resolution (functions/operators/constructors).
- **What it shows:** constructor overloading, `Print::show` overloads, `Number::operator+`.
- **Sample output:**
  ```
  Non-parameterized Constructor
  Parameterized Constructor
  Name : Rahul
  Age : 25
  Rollno : 31
  Integer x = 25
  Name = Rahul
  Function Overloading.
  Number sum = 30
  ```

## Run-time polymorphism (`Run_time_Polymorphism.cpp`)
- **Definition:** Virtual functions enable dynamic dispatch based on the actual object at runtime.
- **What it shows:** `Parent::hello` virtual, overridden in `Child`; static vs dynamic binding; explicit base calls.
- **Sample output:**
  ```
  Child Class.
  Rahul
  Hello from Child.
  Hello from Child.
  Hello from Parent.
  Hello from Parent.
  ```

## Single & multilevel inheritance (`Inheritance.cpp`)
- **Definition:** Derived classes reuse and extend base class state/behavior across levels.
- **What it shows:** `Person -> Student -> GradStudent`, `using Person::Person`, overridden `getInfo`.
- **Sample output:**
  ```
  Name : Neha
  Age : 25
  Rollno : 35
  Name from Getter: Neha
  Name : Neha
  Age : 25
  Rollno : 46
  Name : Avnish
  Age : 28
  Rollno : 1
  Research Area : AI
  Direct Access: Avnish
  ```

## Multiple inheritance (`Multiple_inheritance.cpp`)
- **Definition:** A class derives from more than one base, combining their interfaces/data.
- **What it shows:** `TA` inherits from `Student` and `Teacher`, uses members from both.
- **Sample output:**
  ```
  Name : Suraj
  Age : 0
  Rollno : 0
  Subject : OOPS
  Salary : 150000
  Suraj OOPS
  ```

## Diamond problem: replicated base (non-virtual) (`Diamond_problem.cpp`)
- **Definition:** Without virtual bases, a common ancestor is duplicated down multiple paths, causing ambiguity.
- **Diagram:**
  ```
      Employee   (copy A)   Employee (copy B)
        |                      |
      Manager               Developer
        \                    /
             TeamLead
  ```
- **Sample output:**
  ```
  --- Initializing TeamLead Object ---
  [System] Employee Base Constructor Executed
  [System] Manager Layer Created
  [System] Employee Base Constructor Executed
  [System] Developer Layer Created
  [System] TeamLead Final Layer Created

  --- Diamond Access Result ---
  Left-Side ID  : 101
  Right-Side ID : 102
  Bottom-Point ID: 103
  Manager Path ID:   101
  Developer Path ID: 102
  TeamLead Own ID:   103
  Employee (Local):  104
  ```

## Diamond solved with virtual bases (`Virtual_inheritance.cpp`)
- **Definition:** Virtual inheritance shares a single base sub-object across multiple paths, removing duplication.
- **Diagram:**
  ```
        Employee  (shared)
         /    \
    Manager   Developer   [virtual]
         \    /
        TeamLead
  ```
- **Sample output:**
  ```
  Employee Constructor called
  Manager Constructor called
  Developer Constructor called
  TeamLead Constructor called
  Manager ID: 102
  Developer ID: 103
  TeamLead ID: 103
  Employee ID: 103
  ```

## Hybrid / virtual parameterized inheritance (`Virtual_parameterized_Inheritance.cpp`, `Hybrid.cpp`)
- **Definition:** Mix of hierarchical + multiple inheritance while virtually sharing a common base to avoid duplicates.
- **Diagram:**
  ```
        Person (shared)
        /           \
    Student       Teacher   [both virtual]
         \         /
            TA
  ```
- **Sample output:**
  ```
  Name : Suraj
  Age : 0
  Rollno : 0
  Subject : OOPS
  Salary : 150000
  Suraj OOPS
  ```

## Composition/aggregation vs inheritance diagram
- Composition (preferred here): `TeamLead` --> {`Employee`, `ManagerRole`, `DeveloperRole`} (owned subobjects, no ambiguity).
- Multiple inheritance alternative would form a diamond and need scope resolution; see sections above.

## Static storage duration (`static.cpp`)
- **Definition:** `static` locals persist across function calls; instance members are per-object.
- **Sample output:**
  ```
  x in fun() : 0
  x in fun() : 1
  x in fun() : 2
  Object 1 x Original value = 100
  Object 1 x after increment = 101
  Object 2 x Original value = 200
  Object 2 x after increment = 201
  ```

## Copy semantics (`shallow_vs_deep_copy.cpp`)
- **Definition:** Shallow copy shares pointers (risking double-free/aliasing); deep copy duplicates owned resources.
- **Sample output (showing aliasing vs independence):**
  ```
  --- SHALLOW COPY TEST ---
  Name: Rahul, CGPA: 8.5 (at Address: 0x...)
  Name: Rahul, CGPA: 8.5 (at Address: 0x...)
  After modifying s2.cgpaPtr to 9.9:
  Name: Rahul, CGPA: 9.9 (at Address: 0x...)
  Name: Rahul, CGPA: 9.9 (at Address: 0x...)

  --- DEEP COPY TEST ---
  Name: Anjali, CGPA: 9 (at Address: 0x...)
  Name: Anjali, CGPA: 9 (at Address: 0x...)
  After modifying d2.cgpaPtr to 9.5:
  Name: Anjali, CGPA: 9 (at Address: 0xA)
  Name: Anjali, CGPA: 9.5 (at Address: 0xB)
  ```
