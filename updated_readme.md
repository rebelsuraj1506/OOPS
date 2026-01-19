# C++ OOP Examples (Placement/OOPS)

Self-contained C++ programs that demonstrate core OOP topics. Each file has its own `main()`; compile individually with `g++ -std=c++17 <file>.cpp -o demo && ./demo`.

## Encapsulation & constructor patterns (`oops.cpp`)
- **Definition:** Encapsulation hides data behind an interface; constructors set up state, and custom copy constructors control copy semantics.
- **What it shows:** private salary with getters/setters; default, parameterized, and custom copy constructor; deep-copy of heap `cgpaPtr`; destructor cleanup.
- **Classes/functions (diagram):**
  ```
  Teacher
    - name, dept, subject
    - salary (private)
    - Teacher()                    // default
    - Teacher(name, dept, subject, salary)
    - Teacher(Teacher&)            // custom copy
    - changeDept(), setSalary(), getSalary(), getInfo()

  Account
    - balance (private), password (private)
    - accountID, userName

  Student
    - name
    - cgpaPtr  (double*, heap)
    - Student(name, cgpa)
    - Student(Student&)            // deep copy
    - ~Student()
    - getInfo()
  ```
- **Main flow (diagram):**
  ```
  main()
   |
   |-- Teacher t1 (default ctor) -> setSalary(100000) -> getInfo()
   |-- Teacher t2 (param ctor)   -> changeDept("ECE"/"Civil") -> setSalary(150000) -> getInfo()
   |-- Teacher t3 = Teacher(t1)  (copy ctor: name+"Kumar", salary*1.15) -> setSalary(120000) -> getInfo()
   |-- Teacher t4 = Teacher(t1)  (copy ctor: name+"Kumar", salary*1.15) -> setSalary(110000) -> getInfo()
   |
   |-- Student s1("Shyam", 7.6) -> getInfo()
   |-- Student s2(s1)  (deep copy) -> *s2.cgpaPtr=8.3, s2.name="Ghanshyam"
   |-- print s1 (unchanged) and s2 (changed)
   \-- end of scope -> ~Student frees heap
  ```
- **Diagram (objects and heap copy):**
  ```
  Teacher t1 -----> {name, subject, salary}
               \
                \__ Teacher t3 (copy-ctor tweaks fields)

  Student s1 ----> cgpaPtr: [7.6]   (heap)
  Student s2 ----> cgpaPtr: [8.3]   (deep-copied heap block)
  ```
- **Sample output (abridged):**
  ```
  Printing Teacher1 Info : Name : Suraj
  Teacher2 old salary : 200000
  Printing Teacher2 Info : Name : Avnish
  Teacher3 old salary : 115000
  Teacher4 old salary : 115000
  --- Student Deep Copy Test ---
  Student 1 (Original):
  Name : Shyam
  CGPA : 7.6
  Student 2 Info (Should be 8.3 and Ghanshyam):
  Name : Ghanshyam
  CGPA : 8.3
  ```
- **💡 Interview Takeaway:**
  - **Encapsulation:** Use `private` members + getters/setters to control access. Prevents unauthorized modification.
  - **Copy Constructor:** Default copy is shallow (dangerous for pointers). Always implement deep copy for heap-allocated resources.
  - **Rule of Three:** If you define copy-ctor, also define assignment operator and destructor.

## Abstraction (`Abstraction.cpp`, `Abstraction_child_parent.cpp`)

### `Abstraction.cpp` - Multiple Implementations Pattern
- **Definition:** Expose *what* an object does via abstract interfaces (pure virtual functions) while hiding *how*. Demonstrates multiple concrete implementations of same interface.
- **What it shows:** abstract `PaymentMethod::processPayment`, concrete `CreditCard`/`PayPal`, `dynamic_cast` to reach derived-only behavior, virtual destructor.
- **Use Case:** Payment processing system with different providers, plugin systems, strategy pattern.
- **Diagram (interface to concrete types):**
  ```
     PaymentMethod (abstract)
         /          \
  CreditCard      PayPal
         ^           ^
         |           | dynamic_cast to PayPal-only API
  ```
- **Classes/functions (diagram):**
  ```
  PaymentMethod   (abstract)
    - processPayment(amount) = 0      // pure virtual
    - showReceipt(amount)
    - virtual ~PaymentMethod()

  CreditCard : public PaymentMethod
    - processPayment(amount) override

  PayPal : public PaymentMethod
    - processPayment(amount) override
    - remainingBalance(total, used)   // PayPal-specific method
  ```
- **Main flow (diagram):**
  ```
  main()
    PaymentMethod* myPayment
      |-- new CreditCard -> processPayment -> showReceipt -> delete
      \-- new PayPal     -> processPayment -> showReceipt
                      -> dynamic_cast<PayPal*>(myPayment)
                      -> remainingBalance -> delete
  ```
- **Sample output:**
  ```
  Processing $150 via Credit Card Secure Gateway...
  Receipt generated for: $150
  --------------------------
  Redirecting to PayPal... Processing $45.5
  Receipt generated for: $45.5
  Your remaining balance is $104.5
  ```

### `Abstraction_child_parent.cpp` - Simple Contract Pattern
- **Definition:** Basic abstract base class pattern to enforce mandatory behavior in derived classes.
- **What it shows:** abstract base `Parent`, derived `Child`, virtual destructor cleanup via base pointer.
- **Use Case:** Template method pattern, enforcing interface contracts, simple parent-child relationships.
- **Diagram:**
  ```
     Parent (abstract)
         |
       Child
  ```
- **Classes/functions (diagram):**
  ```
  Parent   (abstract)
    - name
    - show()
    - hello() = 0                     // pure virtual
    - virtual ~Parent()

  Child : public Parent
    - show() override
    - hello() override
    - ~Child()
  ```
- **Main flow (diagram):**
  ```
  main()
    Parent* ptr = new Child
      -> set name -> print name -> ptr->hello()
      -> delete ptr  (Child dtor then Parent dtor)
  ```
- **Sample output:**
  ```
  Name: Rahul
  Hello from Child.
  Child Destructor.
  Parent Destructor.
  ```

### Difference Between Two Abstraction Examples

| Aspect | `Abstraction.cpp` | `Abstraction_child_parent.cpp` |
|--------|-------------------|--------------------------------|
| **Complexity** | Multiple derived classes (CreditCard, PayPal) | Single parent-child relationship |
| **Use Case** | Real-world system with multiple providers | Basic contract/template enforcement |
| **Features** | Uses `dynamic_cast` for type-specific behavior | Simple virtual function override |
| **Polymorphism** | Multiple implementations of same interface | One base, one derived |
| **When to Use** | Plugin architecture, strategy pattern, multiple service providers | Simple inheritance chains, enforcing base contracts |

### 💡 Interview Takeaway - Abstraction
  - **Abstract Class:** Contains at least one pure virtual function (`= 0`). Cannot be instantiated; serves as a contract.
  - **Virtual Destructor:** Always use `virtual ~Base()` when deleting via base pointer. Ensures derived destructor runs.
  - **dynamic_cast:** Safely downcast to access derived-only members. Returns `nullptr` if cast fails.
  - **Multiple Implementations:** `Abstraction.cpp` shows how different classes implement same interface differently.
  - **Contract Enforcement:** `Abstraction_child_parent.cpp` shows how base class enforces derived classes to implement certain methods.

## Composition vs. aggregation (`Aggregation.cpp`)
- **Definition:** "Has-a" composition assembles objects; lifetimes owned by the container. Aggregation is a weaker, shareable link.
- **What it shows:** `TeamLead` contains `Employee`, `ManagerRole`, `DeveloperRole` instead of inheriting.
- **Diagram (has-a composition):**
  ```
  TeamLead
    |-- Employee (id)
    |-- ManagerRole (managementLevel)
    |-- DeveloperRole (primaryLanguage)
  ```
- **Classes/functions (diagram):**
  ```
  Employee
    - id
    - Employee(id)

  ManagerRole
    - managementLevel
    - ManagerRole(level)

  DeveloperRole
    - primaryLanguage
    - DeveloperRole(lang)

  TeamLead
    - generalProfile : Employee
    - mgtRole       : ManagerRole
    - devRole       : DeveloperRole
    - TeamLead(id, level, lang)
    - showInfo()
  ```
- **Main flow (diagram):**
  ```
  main()
    -> TeamLead tl(101, 5, "C++26 Standards")
         (builds Employee + ManagerRole + DeveloperRole)
    -> print tl.generalProfile.id / tl.mgtRole.managementLevel / tl.devRole.primaryLanguage
    -> tl.showInfo()
  ```
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
- **💡 Interview Takeaway:**
  - **Composition over Inheritance:** "Has-a" relationship avoids diamond problem and ambiguity. More flexible and maintainable.
  - **Single Responsibility:** Each component (Employee, ManagerRole, DeveloperRole) manages one concern. Easier to test and modify.
  - **Lifetime Management:** Composition means container owns parts. When TeamLead dies, its components die too.

## Compile-time polymorphism (`Compile_time_Polymorphism.cpp`)
- **Definition:** Binding decided by the compiler via overload resolution (functions/operators/constructors).
- **What it shows:** constructor overloading, `Print::show` overloads, `Number::operator+`.
- **Diagram (overload set chosen at compile time):**
  ```
        show(int)      show(string)
             \            /
              \          /
              call site (argument type picks overload)

  Number + Number  --> operator+(const Number&)
  ```
- **Classes/functions (diagram):**
  ```
  Student
    - name, age, rollno
    - Student()                      // non-parameterized
    - Student(name, age, rollno)     // parameterized
    - ~Student()
    - getInfo()

  Print
    - show(int x)
    - show(string x)                 // overloaded by parameter type

  Number
    - value
    - Number(int v)
    - operator+(const Number&) const // returns new Number
    - display()
  ```
- **Main flow (diagram):**
  ```
  main()
    -> Student s1;                  // picks Student()
    -> Student s2("Rahul",25,31);   // picks Student(string,int,int)
    -> s2.getInfo()
    -> Print p1;  p1.show(25); p1.show("Rahul")   // overload chosen by arg type
    -> Number n1(10), n2(20);  n3 = n1 + n2;      // operator+ selected
    -> n3.display()
  ```
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
- **💡 Interview Takeaway:**
  - **Function Overloading:** Same name, different parameters. Compiler picks based on argument types/signature at compile-time.
  - **Operator Overloading:** Redefine operators (`+`, `-`, `==`) for user-defined types. Must be a member function or friend.
  - **Static Binding:** Resolution happens at compile-time. Faster but less flexible than runtime polymorphism.

## Run-time polymorphism (`Run_time_Polymorphism.cpp`)
- **Definition:** Virtual functions enable dynamic dispatch based on the actual object at runtime.
- **What it shows:** `Parent::hello` virtual, overridden in `Child`; static vs dynamic binding; explicit base calls.
- **Diagram (vtable dispatch):**
  ```
  Parent* ptr --> [Child object]
                     |
                   vptr --> vtable --> hello() resolves to Child

  ptr->hello();          // late-bound
  ptr->Parent::hello();  // forced base
  ```
- **Classes/functions (diagram):**
  ```
  Parent
    - name
    - show()                // non-virtual
    - virtual hello()

  Child : public Parent
    - show() override       // hides Parent::show
    - hello() override
  ```
- **Main flow (diagram):**
  ```
  main()
    -> Child c1
    -> c1.show()         // Child::show (static call)
    -> c1.name="Rahul"   // inherited field
    -> c1.hello()        // Child::hello
    -> Parent* ptr=&c1
         -> ptr->hello()         // virtual => Child::hello
         -> ptr->Parent::hello() // force Parent version
         -> c1.Parent::hello()   // force Parent version
  ```
- **Sample output:**
  ```
  Child Class.
  Rahul
  Hello from Child.
  Hello from Child.
  Hello from Parent.
  Hello from Parent.
  ```
- **💡 Interview Takeaway:**
  - **Virtual Functions:** Enable runtime polymorphism. Base pointer calls derived implementation via vtable.
  - **Static vs Dynamic Binding:** Non-virtual functions bind at compile-time; virtual functions bind at runtime.
  - **Scope Resolution:** Use `ptr->Base::func()` to force base version even if overridden.

## Inheritance Types - Complete Overview

### Single Inheritance (`Inheritance.cpp`)
- **Definition:** One derived class inherits from one base class (A → B). Simplest form with direct parent-child relationship.
- **What it shows:** `Person -> Student -> GradStudent`, `using Person::Person`, overridden `getInfo`.
- **Diagram:**
  ```
  Person
    |
  Student
    |
  GradStudent
  ```
- **Key Characteristics:**
  - No ambiguity, straightforward inheritance
  - Constructor order: Base → Derived
  - Destructor order: Derived → Base
  - Clear IS-A relationship
- **Classes/functions (diagram):**
  ```
  Person
    - name, age
    - Person(name, age)
    - virtual ~Person()

  Student : public Person
    - rollno
    - using Person::Person         // inherit ctors
    - Student(name, age, rollno)
    - string getName(), int getAge()
    - changeRollno(newRoll)
    - getInfo()
    - ~Student()

  GradStudent : public Student
    - researchArea
    - GradStudent(name, age, rollno, researchArea)
    - getName() override
    - getInfo() override
  ```
- **Main flow (diagram):**
  ```
  main()
    -> Student s2("Neha",25,35)
         -> s2.getInfo() -> s2.getName()
         -> s2.changeRollno(46) -> s2.getInfo()
    -> GradStudent s3("Avnish",28,1,"AI")
         construction: Person -> Student -> GradStudent
         -> s3.getInfo() -> print s3.name
  ```
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
- **💡 Interview Takeaway - Single Inheritance:**
  - **Simplest Pattern:** One parent, one child. No complexity or ambiguity.
  - **Constructor Chain:** Base constructor runs first, then derived.
  - **Access Specifiers:** `public` inheritance preserves access; `private`/`protected` restrict it.
  - **When to Use:** Clear IS-A relationship (Student IS-A Person).

### Multilevel Inheritance (`Inheritance.cpp`)
- **Definition:** Chain of inheritance where derived class becomes base for next level (A → B → C). Each level adds specialization.
- **What it shows:** Person → Student → GradStudent chain, progressive refinement.
- **Diagram:**
  ```
  Person
    ↓
  Student
    ↓
  GradStudent
  ```
- **Key Characteristics:**
  - Each level adds new functionality
  - Constructors called top-to-bottom
  - Destructors called bottom-to-top
  - All public members propagate down the chain
  - Each class can override parent methods
- **Constructor/Destructor Order:**
  ```
  Construction: Person() → Student() → GradStudent()
  Destruction:  ~GradStudent() → ~Student() → ~Person()
  ```
- **💡 Interview Takeaway - Multilevel Inheritance:**
  - **Progressive Specialization:** Each level refines the abstraction (Person → Student → GradStudent).
  - **Transitive IS-A:** GradStudent IS-A Student IS-A Person (all relationships hold).
  - **Constructor Delegation:** Each level calls immediate parent constructor.
  - **Method Resolution:** Most derived version called if virtual.
  - **When to Use:** Natural hierarchies (Animal → Mammal → Dog), specialization chains.

### Multiple Inheritance (`Multiple_inheritance.cpp`)
- **Definition:** A class derives from more than one base, combining their interfaces/data (B, C → D).
- **What it shows:** `TA` inherits from `Student` and `Teacher`, uses members from both.
- **Diagram (two parents):**
  ```
   Student        Teacher
        \        /
         \      /
            TA
  ```
- **Key Characteristics:**
  - Combines features from multiple sources
  - Potential name collision/ambiguity
  - Constructor order follows declaration order (left-to-right)
  - Can lead to diamond problem if bases share common ancestor
- **Classes/functions (diagram):**
  ```
  Student
    - age, name, rollno
    - ~Student()

  Teacher
    - subject, salary
    - ~Teacher()

  TA : public Student, public Teacher
    - getInfo()       // prints all inherited fields
    - ~TA()
  ```
- **Main flow (diagram):**
  ```
  main()
    -> TA t1
         -> set t1.name, t1.subject, t1.salary
         -> t1.getInfo()
         -> print t1.name and t1.subject
  ```
- **Sample output:**
  ```
  Name : Suraj
  Age : 0
  Rollno : 1
  Subject : OOPS
  Salary : 150000
  Suraj OOPS
  ```
- **💡 Interview Takeaway - Multiple Inheritance:**
  - **Multiple Parents:** Class inherits from two or more bases. Combines interfaces/data from all.
  - **Ambiguity Risk:** If both bases have same member name, use scope resolution (`obj.Base1::member`).
  - **Constructor Order:** All base constructors run before derived, left-to-right in inheritance list.
  - **Design Consideration:** Often indicates poor design; prefer composition. Can lead to diamond problem.
  - **When to Use:** Only when genuinely needed (TA IS-A Student AND IS-A Teacher). Consider interfaces instead.

### Hierarchical Inheritance
- **Definition:** Multiple classes inherit from one base class (A → B, A → C, A → D). One parent, many children.
- **Diagram:**
  ```
      Person
     /  |  \
Student Teacher Employee
  ```
- **Key Characteristics:**
  - Code reuse from common base
  - Each derived class is independent
  - No diamond problem (single base, multiple unrelated children)
  - Base pointer can hold any derived object (polymorphism)
- **💡 Interview Takeaway - Hierarchical Inheritance:**
  - **Code Reuse:** Common functionality (name, age) in Person base, specialized behavior in derived classes.
  - **Independence:** Student, Teacher, Employee don't interact with each other.
  - **Polymorphism:** `Person* ptr` can point to Student, Teacher, or Employee.
  - **When to Use:** Shape → Circle, Rectangle, Triangle; Vehicle → Car, Bike, Truck.

### Hybrid Inheritance (`Hybrid.cpp`)
- **Definition:** Combination of two or more inheritance types. Typically hierarchical + multiple inheritance.
- **What it shows:** Mix of hierarchical + multiple while virtually sharing a common base to avoid duplicates.
- **Diagram:**
  ```
        Person (shared via virtual)
        /           \
    Student       Teacher   [both virtual]
         \         /
            TA
  ```
- **Key Characteristics:**
  - Most complex inheritance pattern
  - Requires virtual inheritance to avoid diamond problem
  - Single shared base instance
  - Real-world scenarios often need this pattern
- **Classes/functions (diagram):**
  ```
  Person
    - name, age

  Student : virtual public Person
    - rollno
    - ~Student()

  Teacher : virtual public Person
    - subject, salary
    - ~Teacher()

  TA : public Student, public Teacher
    - getInfo()   // uses shared Person + role fields
  ```
- **Main flow (diagram):**
  ```
  main()
    -> TA t1
    -> set shared base fields: t1.name (Person), plus t1.subject/salary (Teacher)
    -> t1.getInfo() prints: Person::name/age + Student::rollno + Teacher::subject/salary
    -> print t1.name and t1.subject
  ```
- **Sample output:**
  ```
  Name : Suraj
  Age : <uninitialized>  // garbage value (not set in code)
  Rollno : <uninitialized>  // garbage value (not set in code)
  Subject : OOPS
  Salary : 150000
  Suraj OOPS
  ```
- **💡 Interview Takeaway - Hybrid Inheritance:**
  - **Mixed Pattern:** Combines hierarchical (Person → Student, Teacher) + multiple (Student, Teacher → TA).
  - **Virtual Base Required:** Without virtual inheritance, TA would have two Person copies (diamond problem).
  - **No Ambiguity:** With virtual inheritance, `t1.name` unambiguously refers to single shared Person.
  - **Most Derived Constructor:** TA constructor must call Person constructor directly (virtual base rule).
  - **When to Use:** Complex real-world scenarios where object genuinely needs multiple roles with shared base.

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
- **Memory Layout:**
  ```
  TeamLead object contains:
  ├── Manager part
  │   └── Employee part (copy 1)
  ├── Developer part
  │   └── Employee part (copy 2)
  └── TeamLead-specific data
  ```
- **Classes/functions (diagram):**
  ```
  Employee
    - id
    - Employee()

  Manager : public Employee
    - Manager()

  Developer : public Employee
    - Developer()

  TeamLead : public Manager, public Developer
    - id    // own id, hides base ids
    - TeamLead()
  ```
- **Main flow (diagram):**
  ```
  main()
    -> TeamLead t1
        (construct order: Employee(A)->Manager->Employee(B)->Developer->TeamLead)
    -> t1.Manager::id   = 101   // left Employee
    -> t1.Developer::id = 102   // right Employee
    -> t1.id            = 103   // TeamLead's own id
    -> print all three ids
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
- **💡 Interview Takeaway:**
  - **Diamond Problem:** Common base inherited twice creates ambiguity. `TeamLead` has two `Employee` copies.
  - **Ambiguity:** `t1.id` is ambiguous - compiler doesn't know which Employee::id (Manager's or Developer's).
  - **Solution:** Use `virtual` inheritance (`class Manager : virtual public Employee`) to share single base instance.
  - **Memory Cost:** Without virtual, base is duplicated. With virtual, only one copy exists (but adds indirection overhead).
  - **Scope Resolution:** Must use `t1.Manager::id` or `t1.Developer::id` to disambiguate.

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
- **Memory Layout:**
  ```
  TeamLead object contains:
  ├── Employee part (ONE shared copy)
  ├── Manager part (vbase pointer to Employee)
  ├── Developer part (vbase pointer to Employee)
  └── TeamLead-specific data
  ```
- **Classes/functions (diagram):**
  ```
  Employee
    - id
    - Employee()

  Manager : virtual public Employee
    - Manager()

  Developer : virtual public Employee
    - Developer()

  TeamLead : public Manager, public Developer
    - TeamLead()
  ```
- **Main flow (diagram):**
  ```
  main()
    -> TeamLead t1
       (virtual base Employee constructed once)
    -> set id via t1.id, t1.Manager::id, t1.Developer::id (all refer to same shared Employee::id)
    -> print IDs
  ```
- **Sample output:**
  ```
  Employee Constructor called
  Manager Constructor called
  Developer Constructor called
  TeamLead Constructor called
  Manager ID: 103
  Developer ID: 103
  TeamLead ID: 103
  Employee ID: 103
  ```
- **💡 Interview Takeaway:**
  - **Virtual Inheritance:** `virtual public Base` ensures only one shared instance of base in diamond hierarchy.
  - **Most Derived Constructor:** Only the most derived class calls virtual base constructor. Intermediate calls are ignored.
  - **Memory Efficiency:** Single base instance saves memory and eliminates ambiguity. Trade-off: slight performance overhead.
  - **No Ambiguity:** `t1.id` directly accesses shared Employee::id without scope resolution.

## Virtual parameterized inheritance (`Virtual_parameterized_Inheritance.cpp`)
- **Definition:** Virtual inheritance with parameterized constructors. Demonstrates that the most derived class must call the virtual base constructor directly.
- **Diagram:**
  ```
        Employee  (shared, parameterized)
         /    \
    Manager   Developer   [both virtual]
         \    /
        TeamLead
  ```
- **Classes/functions (diagram):**
  ```
  Employee
    - id
    - Employee(int _id)              // parameterized constructor
    - virtual ~Employee()

  Manager : virtual public Employee
    - Manager(int _id) : Employee(_id)   // Employee call IGNORED when TeamLead created
    - Manager()

  Developer : virtual public Employee
    - Developer(int _id) : Employee(_id) // Employee call IGNORED when TeamLead created
    - Developer()

  TeamLead : public Manager, public Developer
    - TeamLead(int _id) : Employee(_id), Manager(_id), Developer(_id)
      // Most derived class MUST call Employee constructor directly
    - displayInfo()
  ```
- **Main flow (diagram):**
  ```
  main()
    -> TeamLead tl(999)
       (Employee constructed ONCE with id=999, despite Manager/Developer ctors)
       (Manager and Developer ctors run, but their Employee(_id) calls are ignored)
    -> tl.displayInfo()  // shows single shared id
  ```
- **Sample output:**
  ```
  Starting TeamLead allocation...

  [Step 1] Employee Sub-object Created (ID: 999)
  [Step 2] Manager Layer Initialized
  [Step 3] Developer Layer Initialized
  [Step 4] TeamLead Object Fully Constructed

  --- Identity Check ---
  TeamLead Universal ID: 999
  Address of 'id': 0x... (Shared Location)
  ----------------------
  ```
- **💡 Interview Takeaway:**
  - **Most Derived Constructor Rule:** In virtual inheritance, only the most derived class calls the virtual base constructor. Intermediate class calls are ignored.
  - **Parameterized Virtual Base:** When virtual base has parameters, most derived class must provide them explicitly: `TeamLead(int id) : Employee(id), Manager(id), Developer(id)`
  - **Single Instance:** Employee is constructed only once, proving virtual inheritance works correctly.
  - **Why This Rule:** Prevents multiple initialization attempts of the shared base object.

## Inheritance Types Comparison Table

| Type | Structure | Example | Diamond Risk | When to Use |
|------|-----------|---------|--------------|-------------|
| **Single** | A → B | Person → Student | No | Clear IS-A relationship, simple hierarchy |
| **Multilevel** | A → B → C | Person → Student → GradStudent | No | Progressive specialization, refinement chain |
| **Multiple** | B,C → D | Student, Teacher → TA | Yes (if bases share ancestor) | Object genuinely needs multiple roles |
| **Hierarchical** | A → B,C,D | Person → Student, Teacher, Employee | No | Code reuse, independent derived classes |
| **Hybrid** | Mixed patterns | Person → Student, Teacher → TA (virtual) | Yes (requires virtual inheritance) | Complex real-world scenarios |

**Constructor Order Rules:**
- **Single/Multilevel:** Base → Derived (top to bottom)
- **Multiple:** Left-to-right in inheritance list, then derived
- **Virtual Base:** Virtual base first (by most derived class), then non-virtual bases, then derived

**Key Interview Points:**
1. **Prefer Composition over Multiple Inheritance** - avoids complexity and diamond problem
2. **Always use virtual destructor in base classes** - ensures proper cleanup via base pointer
3. **Virtual inheritance solves diamond problem** - but adds memory/performance overhead
4. **Most derived class calls virtual base constructor** - critical for parameterized virtual bases

## Static storage duration (`static.cpp`)
- **Definition:** `static` locals persist across function calls; instance members are per-object.
- **Diagram (lifetime vs instance):**
  ```
  fun():
    static x (data segment, one copy, retains value)

  A obj1 --> x (unique per object)
  A obj2 --> x (unique per object)
  ```
- **Classes/functions (diagram):**
  ```
  fun()
    - static int x = 0   // initialized once, value kept between calls

  class A
    - int x              // per-object
    - incX()             // x = x + 1
  ```
- **Main flow (diagram):**
  ```
  main()
    -> fun() -> prints x=0, increments to 1
    -> fun() -> prints x=1, increments to 2
    -> fun() -> prints x=2, increments to 3
    -> A obj1, obj2
         obj1.x=100 -> incX() -> 101
         obj2.x=200 -> incX() -> 201
  ```
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
- **💡 Interview Takeaway:**
  - **Static Local:** Initialized once, persists across function calls. Lives in data segment, not stack.
  - **Instance Members:** Each object has its own copy. Changes to one object don't affect others.
  - **Lifetime:** Static variables live for program duration; instance members live with object lifetime.

## Copy semantics (`shallow_vs_deep_copy.cpp`)
- **Definition:** Shallow copy shares pointers (risking double-free/aliasing); deep copy duplicates owned resources.
- **Diagram (alias vs owned memory):**
  ```
  ShallowStudent s1 cgpaPtr --> [8.5] (heap A)
                 s2 cgpaPtr --> [8.5] (same A)

  DeepStudent d1 cgpaPtr --> [9.0] (heap B)
             d2 cgpaPtr --> [9.0] (heap C, separate)
  ```
- **Classes/functions (diagram):**
  ```
  ShallowStudent
    - name
    - cgpaPtr (double*)
    - ShallowStudent(name, cgpa)
    - ShallowStudent(ShallowStudent&)   // shallow: copy pointer
    - getInfo()

  DeepStudent
    - name
    - cgpaPtr (double*)
    - DeepStudent(name, cgpa)
    - DeepStudent(DeepStudent&)         // deep: allocate + copy value
    - ~DeepStudent()                    // delete cgpaPtr
    - getInfo()
  ```
- **Main flow (diagram):**
  ```
  main()
    Shallow:
      -> ShallowStudent s1("Rahul",8.5)
      -> ShallowStudent s2(s1)  // copies pointer (same heap)
      -> *s2.cgpaPtr = 9.9      // affects s1 + s2

    Deep:
      -> DeepStudent d1("Anjali",9.0)
      -> DeepStudent d2(d1)     // allocates new heap + copies value
      -> *d2.cgpaPtr = 9.5      // affects only d2
  ```
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
- **💡 Interview Takeaway:**
  - **Shallow Copy:** Copies pointer value. Both objects point to same memory. Dangerous: double-free, data races.
  - **Deep Copy:** Allocates new memory and copies content. Objects are independent. Required for heap-allocated resources.
  - **Rule of Three/Five:** If you manage resources, implement copy-ctor, assignment operator, and destructor (or use smart pointers).

---

## 🎯 Common Interview Questions & Answers

### **Encapsulation Questions**

**Q1: What is encapsulation? Why is it important?**
**A:** Encapsulation is bundling data (attributes) and methods (functions) that operate on the data into a single unit (class), while hiding internal implementation details. It's important because:
- **Data Hiding:** Private members prevent unauthorized access
- **Modularity:** Changes to internal implementation don't affect external code
- **Maintainability:** Easy to modify without breaking dependent code
- **Security:** Controlled access through getters/setters with validation

**Example from `oops.cpp`:**
```cpp
class Teacher {
    string name;
    double salary;  // private - cannot be accessed directly
public:
    void setSalary(double s) {
        if(s > 0) salary = s;  // validation
    }
    double getSalary() { return salary; }
};
```

---

**Q2: What is the difference between default, parameterized, and copy constructor?**
**A:**
- **Default Constructor:** No parameters, initializes with default values. Called when `Teacher t1;`
- **Parameterized Constructor:** Takes arguments to initialize specific values. Called when `Teacher t2("Ram", "CS", "OOPS", 50000);`
- **Copy Constructor:** Creates new object as copy of existing object. Called when `Teacher t3(t1);`

**Key Point:** If you don't define copy constructor, compiler provides shallow copy (dangerous for pointers).

---

**Q3: What is the Rule of Three/Five?**
**A:** If a class manages resources (heap memory, file handles, etc.), you should define:

**Rule of Three (C++98):**
1. Copy Constructor
2. Copy Assignment Operator
3. Destructor

**Rule of Five (C++11):**
4. Move Constructor
5. Move Assignment Operator

**From `oops.cpp` Student class:**
```cpp
class Student {
    double* cgpaPtr;  // manages heap memory
public:
    Student(Student& obj) {  // Copy constructor
        cgpaPtr = new double;
        *cgpaPtr = *obj.cgpaPtr;  // deep copy
    }
    ~Student() { delete cgpaPtr; }  // Destructor
    // Should also define assignment operator
};
```

---

### **Abstraction Questions**

**Q4: What is abstraction? How is it different from encapsulation?**
**A:**
- **Abstraction:** Showing only essential features while hiding implementation details. Achieved using abstract classes and interfaces.
- **Encapsulation:** Bundling data and methods together with access control.

**Difference:**
| Abstraction | Encapsulation |
|-------------|---------------|
| Focuses on "what" object does | Focuses on "how" it does |
| Design level concept | Implementation level concept |
| Uses abstract classes/interfaces | Uses access modifiers (private/public) |
| Hides complexity | Hides data |

**Example:** `PaymentMethod` (abstraction) defines what payment processing means, while actual implementation in `CreditCard` class is encapsulated.

---

**Q5: What is a pure virtual function? Can we instantiate an abstract class?**
**A:** 
- **Pure Virtual Function:** Function with `= 0`, no implementation in base class. Forces derived classes to provide implementation.
```cpp
virtual void processPayment(double amount) = 0;  // pure virtual
```
- **Abstract Class:** Class with at least one pure virtual function. **Cannot be instantiated**.
```cpp
PaymentMethod pm;  // ❌ ERROR - cannot create object
PaymentMethod* ptr = new CreditCard();  // ✅ OK - pointer allowed
```

---

**Q6: Why do we need virtual destructor in abstract classes?**
**A:** Without virtual destructor, deleting via base pointer only calls base destructor, causing memory leaks.

```cpp
// Without virtual destructor
Parent* ptr = new Child();
delete ptr;  // ❌ Only ~Parent() called, ~Child() skipped!

// With virtual destructor
class Parent {
    virtual ~Parent() {}  // ✅ Ensures Child destructor runs
};
```

**From `Abstraction_child_parent.cpp`:** Always use `virtual ~Parent()` when using polymorphism.

---

### **Inheritance Questions**

**Q7: What are different types of inheritance? Explain each.**
**A:**
1. **Single:** A → B (Person → Student)
2. **Multilevel:** A → B → C (Person → Student → GradStudent)
3. **Multiple:** B,C → D (Student, Teacher → TA)
4. **Hierarchical:** A → B,C,D (Person → Student, Teacher, Employee)
5. **Hybrid:** Mix of above patterns (requires virtual inheritance)

**See detailed sections above for examples and diagrams.**

---

**Q8: What is the diamond problem? How do you solve it?**
**A:** Diamond problem occurs when a class inherits from two classes that share a common base, creating two copies of the base class.

**Problem (`Diamond_problem.cpp`):**
```cpp
    Employee        Employee
        ↓              ↓
    Manager        Developer
         ↘          ↙
          TeamLead
// TeamLead has TWO Employee copies!
```

**Solution (`Virtual_inheritance.cpp`):**
```cpp
class Manager : virtual public Employee {};
class Developer : virtual public Employee {};
class TeamLead : public Manager, public Developer {};
// TeamLead has ONE shared Employee
```

**Key Point:** Most derived class (TeamLead) must call virtual base constructor directly.

---

**Q9: What is the constructor calling order in inheritance?**
**A:**
- **Single/Multilevel:** Base → Derived (top to bottom)
- **Multiple:** Left-to-right in inheritance list, then derived
- **Virtual Inheritance:** Virtual base first (by most derived), then non-virtual bases, then derived

**Example from `Virtual_parameterized_Inheritance.cpp`:**
```cpp
TeamLead tl(999);
// Order: Employee(999) → Manager() → Developer() → TeamLead()
```

**Destructor order:** Reverse of construction (bottom to top).

---

**Q10: When to use inheritance vs composition?**
**A:**

**Use Inheritance (IS-A):**
- Clear "is-a" relationship (GradStudent IS-A Student)
- Need polymorphic behavior
- Want to override base class methods

**Use Composition (HAS-A) - Preferred:**
- "Has-a" relationship (Car HAS-A Engine)
- Need flexibility to change components
- Want to avoid diamond problem
- Better testability and maintainability

**From `Aggregation.cpp`:** TeamLead HAS-A Employee, ManagerRole, DeveloperRole (composition).

---

### **Polymorphism Questions**

**Q11: What is the difference between compile-time and runtime polymorphism?**
**A:**

| Compile-Time (Static) | Runtime (Dynamic) |
|----------------------|-------------------|
| Function/operator overloading | Virtual functions |
| Resolved at compile time | Resolved at runtime using vtable |
| Faster (no overhead) | Slight overhead (vtable lookup) |
| Early binding | Late binding |
| `show(int)` vs `show(string)` | `virtual void hello()` |

**Compile-time (`Compile_time_Polymorphism.cpp`):**
```cpp
Print p;
p.show(25);      // Calls show(int)
p.show("Ram");   // Calls show(string)
// Compiler decides which function at compile time
```

**Runtime (`Run_time_Polymorphism.cpp`):**
```cpp
Parent* ptr = new Child();
ptr->hello();  // Calls Child::hello() - decided at runtime
```

---

**Q12: What is a vtable? How does virtual function work internally?**
**A:** 
- **vtable (Virtual Table):** Static array of function pointers, one per class with virtual functions
- **vptr (Virtual Pointer):** Hidden pointer in each object pointing to its class's vtable

**Mechanism:**
1. Compiler creates vtable for each class with virtual functions
2. Each object gets a vptr pointing to its class's vtable
3. When calling `ptr->virtualFunc()`, follows vptr → vtable → actual function

**Example:**
```cpp
class Parent {
    virtual void hello() { cout << "Parent"; }
};
class Child : public Parent {
    void hello() override { cout << "Child"; }
};

Parent* ptr = new Child();
ptr->hello();  // vptr → Child's vtable → Child::hello()
```

---

**Q13: Can we overload or override static functions?**
**A:**
- **Overloading:** ✅ Yes, same name different parameters
- **Overriding:** ❌ No, static functions don't participate in polymorphism. They belong to class, not objects.

```cpp
class Parent {
    static void fun() { cout << "Parent"; }
};
class Child : public Parent {
    static void fun() { cout << "Child"; }  // Hides, not overrides
};

Parent* ptr = new Child();
ptr->fun();  // ❌ ERROR - cannot call static via pointer
Parent::fun();  // Calls Parent::fun
Child::fun();   // Calls Child::fun
```

---

### **Copy Constructor & Memory Management**

**Q14: What is shallow copy vs deep copy?**
**A:** 

**Shallow Copy (`shallow_vs_deep_copy.cpp`):**
- Copies pointer value (address)
- Both objects point to same memory
- **Problem:** Double-free, data corruption

```cpp
ShallowStudent s1("Ram", 8.5);
ShallowStudent s2(s1);  // s1.cgpaPtr == s2.cgpaPtr (same address)
*s2.cgpaPtr = 9.9;      // Also changes s1's CGPA!
```

**Deep Copy:**
- Allocates new memory
- Copies actual data
- Objects are independent

```cpp
DeepStudent(DeepStudent& obj) {
    cgpaPtr = new double;        // New memory
    *cgpaPtr = *obj.cgpaPtr;     // Copy value
}
```

---

**Q15: What happens if we don't write a destructor for a class with dynamic memory?**
**A:** **Memory leak!** Dynamically allocated memory is not freed automatically.

```cpp
class Student {
    double* cgpaPtr;
public:
    Student() { cgpaPtr = new double; }
    // No destructor - MEMORY LEAK!
};

void test() {
    Student s1;
}  // s1 destroyed, but heap memory not freed!
```

**Solution:** Always define destructor to free resources:
```cpp
~Student() { delete cgpaPtr; }
```

---

### **Static & Storage**

**Q16: What is the difference between static local variable and instance variable?**
**A:**

**From `static.cpp`:**

| Static Local Variable | Instance Variable |
|----------------------|-------------------|
| Initialized once | Initialized for each object |
| Retains value across calls | Independent per object |
| Lives in data segment | Lives with object (stack/heap) |
| Shared across all calls | Unique to each object |

```cpp
void fun() {
    static int x = 0;  // Initialized once
    x++;
}
fun();  // x = 1
fun();  // x = 2 (retains previous value)

class A {
    int x;  // Each object has own x
};
A obj1; obj1.x = 10;
A obj2; obj2.x = 20;  // Independent
```

---

### **Advanced Questions**

**Q17: What is the "most derived constructor calls virtual base" rule?**
**A:** In virtual inheritance, intermediate classes' calls to virtual base constructor are **ignored**. Only the most derived class calls it.

**From `Virtual_parameterized_Inheritance.cpp`:**
```cpp
class Employee { Employee(int id); };
class Manager : virtual public Employee {
    Manager(int id) : Employee(id) {}  // IGNORED when TeamLead created
};
class Developer : virtual public Employee {
    Developer(int id) : Employee(id) {}  // IGNORED when TeamLead created
};
class TeamLead : public Manager, public Developer {
    TeamLead(int id) : Employee(id),  // MUST call Employee directly
                       Manager(id), Developer(id) {}
};
```

**Why?** To prevent multiple initialization of the shared virtual base.

---

**Q18: Can we have private virtual functions? Will they be overridden?**
**A:** ✅ Yes, private virtual functions can be overridden!

```cpp
class Parent {
    virtual void fun() { cout << "Parent"; }  // private virtual
public:
    void call() { fun(); }  // Calls polymorphically
};
class Child : public Parent {
    void fun() override { cout << "Child"; }  // Can override
};

Parent* ptr = new Child();
ptr->call();  // Prints "Child" - polymorphism works!
// ptr->fun(); // ❌ ERROR - private, cannot access
```

**Key Point:** Access specifiers control accessibility, not polymorphism.

---

**Q19: What is function hiding in inheritance?**
**A:** When derived class defines function with same name as base class (but different signature), base function is hidden.

**From `Run_time_Polymorphism.cpp`:**
```cpp
class Parent {
public:
    void show() { cout << "Parent"; }
};
class Child : public Parent {
public:
    void show() { cout << "Child"; }  // Hides Parent::show
};

Child c;
c.show();          // Calls Child::show
c.Parent::show();  // Must use scope resolution for Parent version
```

**Solution:** Use `using Parent::show;` in Child to bring base function into scope.

---

**Q20: What is the difference between public, protected, and private inheritance?**
**A:**

| Base Access | public Inheritance | protected Inheritance | private Inheritance |
|-------------|-------------------|----------------------|---------------------|
| public → | public | protected | private |
| protected → | protected | protected | private |
| private → | Not accessible | Not accessible | Not accessible |

**From `Inheritance.cpp`:**
```cpp
class Student : public Person {};      // IS-A relationship (most common)
class Student : protected Person {};   // Rare use
class Student : private Person {};     // HAS-A (use composition instead)
```

**Best Practice:** Use `public` inheritance for IS-A relationships. Private/protected inheritance are rare and confusing.

---

## 🔥 Quick Interview Tips

1. **Always mention virtual destructor** when discussing polymorphism/inheritance
2. **Rule of Three/Five** is critical for classes managing resources
3. **Prefer composition over inheritance** - modern C++ guideline
4. **Virtual inheritance** solves diamond problem but adds overhead
5. **Deep copy** is essential for classes with pointers
6. **Constructor order:** Base → Derived; **Destructor order:** Reverse
7. **vtable/vptr** mechanism for runtime polymorphism
8. **Pure virtual function** makes class abstract
9. **Function hiding** vs **function overriding** - know the difference
10. **Static functions** cannot be virtual

---

## 📝 Practice Questions to Ask Yourself

1. Draw memory layout for diamond inheritance (with and without virtual)
2. Trace constructor/destructor order for multilevel inheritance
3. Explain when shallow copy causes bugs (with example)
4. Write code showing function hiding vs overriding
5. Implement deep copy constructor for a class with multiple pointers
6. Explain why `delete ptr` needs virtual destructor
7. Show ambiguity problem in multiple inheritance and fix it
8. Demonstrate compile-time vs runtime polymorphism with code
9. Write a class following Rule of Five
10. Explain how vtable works with diagram