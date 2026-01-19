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
- **Definition:** Expose *what* an object does via abstract interfaces (pure virtual functions) while hiding *how*.
- **What it shows:** 
  - `Abstraction.cpp`: abstract `PaymentMethod::processPayment`, concrete `CreditCard`/`PayPal`, `dynamic_cast` to reach derived-only behavior, virtual destructor.
  - `Abstraction_child_parent.cpp`: abstract base `Parent`, derived `Child`, virtual destructor cleanup via base pointer.
- **Diagram (interface to concrete types):**
  ```
     PaymentMethod (abstract)
         /          \
  CreditCard      PayPal
         ^           ^
         |           | dynamic_cast to PayPal-only API

     Parent (abstract)
         |
       Child
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
    - remainingBalance(total, used)

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
  Abstraction.cpp main()
    PaymentMethod* myPayment
      |-- new CreditCard -> processPayment -> showReceipt -> delete
      \-- new PayPal     -> processPayment -> showReceipt
                      -> dynamic_cast<PayPal*>(myPayment)
                      -> remainingBalance -> delete

  Abstraction_child_parent.cpp main()
    Parent* ptr = new Child
      -> set name -> print name -> ptr->hello()
      -> delete ptr  (Child dtor then Parent dtor)
  ```
- **Sample output — `Abstraction.cpp`:**
  ```
  Processing $150 via Credit Card Secure Gateway...
  Receipt generated for: $150
  --------------------------
  Redirecting to PayPal... Processing $45.5
  Receipt generated for: $45.5
  Your remaining balance is $104.5
  ```
- **Sample output — `Abstraction_child_parent.cpp`:**
  ```
  Name: Rahul
  Hello from Child.
  Child Destructor.
  Parent Destructor.
  ```
- **💡 Interview Takeaway:**
  - **Abstract Class:** Contains at least one pure virtual function (`= 0`). Cannot be instantiated; serves as a contract.
  - **Virtual Destructor:** Always use `virtual ~Base()` when deleting via base pointer. Ensures derived destructor runs.
  - **dynamic_cast:** Safely downcast to access derived-only members. Returns `nullptr` if cast fails.

## Composition vs. aggregation (`Aggregation.cpp`)
- **Definition:** “Has-a” composition assembles objects; lifetimes owned by the container. Aggregation is a weaker, shareable link.
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

## Single & multilevel inheritance (`Inheritance.cpp`)
- **Definition:** Derived classes reuse and extend base class state/behavior across levels.
- **What it shows:** `Person -> Student -> GradStudent`, `using Person::Person`, overridden `getInfo`.
- **Diagram (multilevel chain):**
  ```
  Person
    |
  Student
    |
  GradStudent
  ```
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
- **💡 Interview Takeaway:**
  - **Inheritance Chain:** Person → Student → GradStudent. Each level adds new members and can override base methods.
  - **Constructor Order:** Base constructors run first (top to bottom), then derived. Destructors run in reverse.
  - **Access Specifiers:** `public` inheritance preserves access; `private`/`protected` restrict it.

## Multiple inheritance (`Multiple_inheritance.cpp`)
- **Definition:** A class derives from more than one base, combining their interfaces/data.
- **What it shows:** `TA` inherits from `Student` and `Teacher`, uses members from both.
- **Diagram (two parents):**
  ```
   Student        Teacher
        \        /
         \      /
            TA
  ```
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
- **💡 Interview Takeaway:**
  - **Multiple Inheritance:** Class inherits from two or more bases. Combines interfaces/data from all parents.
  - **Ambiguity Risk:** If both bases have same member name, use scope resolution (`obj.Base1::member`).
  - **Constructor Order:** All base constructors run before derived. Order follows inheritance list.

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
  - **Solution:** Use `virtual` inheritance (`class Manager : virtual public Employee`) to share single base instance.
  - **Memory Cost:** Without virtual, base is duplicated. With virtual, only one copy exists (but adds indirection overhead).

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

## Hybrid inheritance (`Hybrid.cpp`)
- **Definition:** Mix of hierarchical + multiple inheritance while virtually sharing a common base to avoid duplicates.
- **Diagram:**
  ```
        Person (shared)
        /           \
    Student       Teacher   [both virtual]
         \         /
            TA
  ```
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
- **💡 Interview Takeaway:**
  - **Hybrid Inheritance:** Combines hierarchical (one base, multiple derived) + multiple inheritance (one derived, multiple bases).
  - **Virtual Base Required:** When diamond forms, use `virtual` inheritance to share common ancestor.
  - **No Ambiguity:** With virtual inheritance, `t1.name` refers to single shared Person instance, not ambiguous.

## Composition/aggregation vs inheritance diagram
- Composition (preferred here): `TeamLead` --> {`Employee`, `ManagerRole`, `DeveloperRole`} (owned subobjects, no ambiguity).
- Multiple inheritance alternative would form a diamond and need scope resolution; see sections above.

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