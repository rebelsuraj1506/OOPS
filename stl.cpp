#include <algorithm>
#include <deque>
#include <functional>
#include <iostream>
#include <ostream>
#include <queue>
#include <unordered_set>
#include <utility> // Required for pair
#include <vector>
#include <string>
#include <list>
#include <deque>
#include <set>
#include <map>
#include <unordered_map>

using namespace std;

/**
 * PAIR EXPLAINED:
 * A pair is a container that stores two values of different or same types.
 * Stores two values. Complexity is generally constant O(1) for standard operations.
 * Accessed via .first and .second.
 */
 void explainPair(){
    // Standard pair of integers
    // O(1) - Constant time initialization
    cout << "Pair 1 containing two integers:" << endl;
    pair<int, int> p = {1, 2};
    cout << p.first << " " << p.second << endl;
    // Output : 1 2

    // Nested pair: The second element is itself a pair
    // O(1) - Nesting does not change access complexity
    cout << "Pair 2 containing an integer and a pair of integers:" << endl;
    pair<int, pair<int, int>> p2 = {1, {2, 3}};
    cout << p2.first << " " << p2.second.first << " " << p2.second.second << endl;
    // Output : 1 2 3

    // Deeply nested pairs
    cout << "Pair 3 containing two pairs of integers:" << endl;
    pair<pair<int, int>, pair<int, int>> p3 = {{1, 2}, {3, 4}};
    cout << p3.first.first << " " << p3.first.second << " " << p3.second.first << " " << p3.second.second << endl;
    // Output : 1 2 3 4

    // Array of pairs: Useful for representing edges in a graph or coordinates
    // O(N) where N is the size of the array
    cout << "Pair 3 containing two pairs of integers and an array of pairs:" << endl;
    pair<int, int> arr[] = {{1, 2}, {3, 4}, {5, 6}};
    cout << arr[1].first << " " << arr[1].second << endl;
    // Output : 3 4
    
    // O(M) where M is string length (copying "Suraj" into the pair)
    cout<< "Pair 4 containing a string and an integer:" << endl;
    pair<string, int> p4 = {"Suraj", 1};
    cout << p4.first << " " << p4.second << endl;
    // Output : Suraj 1
    
    // Pair containing a dynamic container
    // O(V) where V is the number of elements in the vector
    cout << "Pair 5 containing a vector of integers and an integer:" << endl;
    pair<vector<int>, int> p5 = {{1, 2, 3}, 4};
    cout << p5.first[0] << " " << p5.first[1] << " " << p5.first[2] << " " << p5.second << endl;
    // Output : 1 2 3 4

    cout << "Pair 6 containing two vectors of pairs:" << endl;
    pair<vector<pair<int, int>>, vector<pair<int, int>>> p6 = {{{1, 2}, {3, 4}}, {{5, 6}, {7, 8}}};
    cout << p6.first[0].first << " " << p6.first[0].second << " " << p6.first[1].first << " " << p6.first[1].second << " " << p6.second[0].first << " " << p6.second[0].second << " " << p6.second[1].first << " " << p6.second[1].second << endl;
    // Output : 1 2 3 4 5 6 7 8
}

/**
 * VECTOR EXPLAINED:
 * A vector is a dynamic array that can resize itself automatically when an element 
 * is inserted or deleted. It is a sequence container that stores elements in 
 * contiguous memory locations.
 * 
 * Key Features:
 * 1. Dynamic Size: Unlike arrays, vectors adjust their size at runtime.
 * 2. Contiguous Storage: Elements are stored side-by-side, allowing O(1) random access.
 * 3. Amortized O(1) Push Back: Inserting at the end is constant time unless capacity is full.
 * 4. Memory Management: Automatically manages heap memory; manual deletion is not required.
 * 
 * Documentation: [cppreference.com - std::vector](https://en.cppreference.com)
 */
void explainVector(){
    vector<int> v;
    // O(1) Amortized - Constant time unless reallocation is needed
    // push_back copies the value into the vector
    v.push_back(1);
    // emplace_back constructs the value in-place (generally faster)
    v.emplace_back(2);
    v.push_back(3);
    // O(1) - Direct index access is constant time
    cout << v[0] << " " << v[1] << " " << v[2] << endl;
    // Output : 1 2 3

    cout << "Vector 2 containing two pairs of integers:" << endl;
    vector<pair<int, int>> v2;
    v2.push_back({1, 2});
    v2.emplace_back(3, 4);
    cout << v2[0].first << " " << v2[0].second << " " << v2[1].first << " " << v2[1].second << endl;
    // Output : 1 2 3 4

    // Vector initialization with size and default value
    // O(N) - Initializing N elements takes linear time
    cout << "Vector 3 containing five 100s:" << endl;
    vector<int> v3(5, 100);
    cout << v3[0] << " " << v3[1] << " " << v3[2] << " " << v3[3] << " " << v3[4] << endl;
    // Output : 100 100 100 100 100
    
    // Vector initialization with size only (defaults to zero for ints)
    cout << "Vector 4 containing five 0s and a size of 5:" << endl;
    vector<int> v4(5);
    cout << v4[0] << " " << v4[1] << " " << v4[2] << " " << v4[3] << " " << v4[4] << endl;
    // Output : 100 100 100 100 100

    // Copy constructor: v5 is a deep copy of v4
    cout << "Vector 5 containing the same elements as vector 4 copying from vector 4:" << endl;
    vector<int> v5(v4);     // Deep copy of v4

    // ITERATORS:
    // Iterators act like pointers to elements within the container
    // O(1) - Iterator operations
    vector<int>::iterator it = v.begin(); // points to the first element
    cout << *it << endl;    // Output: 1
    it++; // moves to the next element
    cout << *it << endl;    // Output: 2

    it = it + 1; // Moves forward by 1 (v.begin() + 2)  Output: 3 (v.begin() + 2)
    cout << *it << endl;
    
    vector<pair<int, int>>::iterator it5 = v2.begin();
    // Using -> operator to access members of the object the iterator points to
    cout << "it5->first access:" << endl;
    cout << it5->first << " " << it5->second << endl; 
    // Output: 1 2
    
    it5++;
    cout << it5->first << " " << it5->second << endl; 
    // Output: 3 4
    
    // it2 is the end of the vector v
    vector<int>::iterator it2 = v.end();

    // REVERSE ITERATORS:
    // rbegin() points to the last element, rend() points before the first
    vector<int>::reverse_iterator it4 = v.rbegin();
    cout << "Reverse: " << *it4 << endl;
    // Output: Reverse: 3

    // it3 is the beginning of the vector v
    vector<int>::reverse_iterator it3 = v.rend();

    it4 = it4 + 2; // it4 = it4 + 2 is equivalent to it4 = it4.rbegin() + 2
    cout << *it4 << endl;   // Output: 1 (rbegin + 2 is the first element)
    

    it4 = it4 - 1; // it4 = it4 - 1 is equivalent to it4 = it4.rbegin() - 1
    cout << *it4 << endl;   // Output: 2

    cout << v[0] << " " << v.at(0) << endl; // v[0] is equivalent to v.at(0)
    // Output: 1 1

    // ELEMENT ACCESS:
    // .back() returns a reference to the last element
    // O(1) - Accessing specific properties
    cout << "Back element: " << v.back() << endl; 
    // Output: 1 1
    // v.clear(); // v.clear() is used to clear the vector v

    
    // v.empty(); // v.empty() is used to check if the vector v is empty
    if(v.empty()){
        cout << "Vector is empty" << endl;
    }
    else{
        cout << "Vector is not empty" << endl;  // Output: Vector is not empty
    }
    // LOOPS:
    // Traditional iterator loop
    // O(N) - Iterating through the entire vector
    for(vector<int>::iterator it = v.begin(); it != v.end(); it++){
        cout << *it << " ";
    }
    cout << endl;

    for(vector<int>::reverse_iterator it = v.rbegin(); it != v.rend(); it++){
        cout << *it << " ";
    }
    cout << endl;

    for(auto it = v.begin(); it != v.end(); it++){
        cout << *it << " ";
    }
    cout << endl;

    for(auto it = v.rbegin(); it != v.rend(); it++){
        cout << *it << " ";
    }
    
    cout << endl;
    
    // Auto-typed loop (modern C++)
    for(auto it : v){
        cout << it << " ";
    }
    cout << endl;

    // DELETION:
    // v.erase() takes an iterator. O(N) complexity due to shifting elements.
    v.erase(v.begin() + 1);     // v becomes {1, 3}

    // O(N) - Erasing a range
    v.erase(v.begin(), v.begin() + 1); // (start, end)  v becomes {3}

    for(auto it : v){
        cout <<  it << " ";   // Output: 3 
    }

    cout << endl;

    // INSERTION
    // O(N + K) - Inserting K elements into a vector of size N
    vector<int> v6(2, 100);          // {100, 100}
    v6.insert(v6.begin(), 300);      // {300, 100, 100}
    v6.insert(v6.begin() + 1, 2, 10); // {300, 10, 10, 100, 100} (Inserts two 10s)

    // OTHER FUNCTIONS
    cout << "Size of v6: " << v6.size() << endl;
    // O(1) - Removing the last element is always constant
    v6.pop_back();      // Removes the last element {300, 10, 10, 100}
    cout << "Is v6 empty? " << (v6.empty() ? "Yes" : "No") << endl;
    // O(N) - clear() calls destructors for all N elements
    // v6.clear();         // Erases everything

    vector<int>copy(2,50); // 50 50

    v6.insert(v6.begin(), copy.begin(), copy.end());    // 50 50 300 10 10 100

    for(auto it : v6){
        cout <<  it << " ";
    }

    cout << endl;

    // SWAP:
    // v.swap(copy) exchanges the contents of two vectors.
    // O(1) - This is highly efficient because it only swaps internal pointers 
    // to the data, rather than copying individual elements.
    // SWAP: O(1)
    // copy becomes {3} (v was {3} after deletions), v becomes {50, 50}
    copy.swap(v);

    // copy.insert(copy.begin(), 2, 75);
    // copy was {3}, after inserting two 75s, it becomes {75, 75, 3}
    copy.insert(copy.begin(), 2, 75);

    for(auto it : copy){
        cout << it << " ";
    }
    // Output: 75 75 3
    cout << endl;
}

/**
 * LIST EXPLAINED:
 * A list is a doubly linked list. 
 * Unlike a vector, it allows for constant time insertion/deletion at both 
 * the front and the back. However, it does not support direct index access (e.g., ls[2] is invalid).
 */
 void explainList(){
    // Initialization
    list<int> ls;

    // O(1) - Constant time insertion at the end
    ls.push_back(1);    // {1}
    ls.emplace_back(3); // {1, 3}

    // O(1) - Constant time insertion at the front
    // This is the primary advantage over a vector (where push_front is O(N))
    ls.push_front(5);    // {5, 1, 3}
    ls.emplace_front(2); // {2, 5, 1, 3}

    // O(N) - Iterating through the list to print elements
    for(auto it : ls){
        cout << it << " ";
    }
    // Output: 2 5 1 3 
    
    cout << endl;

    ls.pop_front();     // 5 1 3

    ls.pop_back();      // 5 1

    cout << "Back element: " << ls.back() << endl;      // 1

    cout << "Front element: " << ls.front() << endl;        // 5

    // Additional typical list operations:
    // O(1) - Accessing front or back
    // int front = ls.front(); // 2
    // int back = ls.back();   // 3

    // O(1) - Removing from front or back
    // ls.pop_front(); 
    // ls.pop_back();

    // REDUNDANT LINE: Checking the size of the list in 2026 (O(1) operation)
    int listSize = ls.size(); 

    auto it = next(ls.begin(), 2); // Moves 2 positions from the start
    cout << *it << endl;           // Dereference to get the value

    // auto it = ls.begin();
    // advance(it, 2);      // 'it' now points to the 3rd element (index 2)
    // cout << *it << endl;

    // auto it = ls.begin();
    // for(int i = 0; i < 2; i++) {
    //     it++;
    // }
    // cout << *it << endl;
}

/**
 * DEQUE EXPLAINED:
 * A deque (double-ended queue) is a dynamic container that provides 
 * efficient insertion and deletion at both the front and the back. 
 * Unlike a list, it also supports random access using the [] operator or .at() 
 * with O(1) complexity.
 */
void explainDeque(){
    deque<int>dq;

    // O(1) - Constant time insertion at the end
    dq.push_back(5);     // {5}
    dq.emplace_back(25); // {5, 25}
    
    // O(1) - Constant time insertion at the front
    dq.push_front(9);    // {9, 5, 25}
    dq.emplace_front(290); // {290, 9, 5, 25}

    // O(N) - Iterating through the deque
    for(auto it : dq){
        cout << it << " ";
    }
    // Output : 290 9 5 25
    cout << endl;

    // O(1) - Constant time removal from the end
    dq.pop_back();       // {290, 9, 5}
    
    // O(1) - Constant time removal from the front
    dq.pop_front();      // {9, 5}

    // O(1) - Accessing the last element
    cout << "Back element: " << dq.back() << endl;
    // Output: Back element: 5

    // O(1) - Accessing the first element
    cout << "Front element: " << dq.front() << endl;
    // Output: Front element: 9

    // O(1) - Random access using index is allowed (unlike std::list)
    cout << "Element at index 1: " << dq.at(1) << " or dq[1]" << endl;
    // Output: Element at index 1: 5

    // Other standard container functions are available:
    // dq.begin(), dq.end(), dq.clear(), dq.insert(), dq.erase()
}

/**
 * STACK EXPLAINED:
 * A LIFO (Last In, First Out) data structure.
 * All operations (push, pop, top) occur at only one end.
 * Note: Stack does not have iterators; you can only see the top element.
 */
 void explainStack() {
    stack<int> st;

    // O(1) - Pushing elements
    st.push(5);       // Stack: [5]
    st.push(26);      // Stack: [26, 5] (top is 26)
    
    // O(1) - Removing the top element
    st.pop();         // Stack: [5]
    
    // O(1) - Emplace constructs in-place
    st.emplace(289);  // Stack: [289, 5] (top is 289)

    cout << st.top() << endl;  
    // Output: 289

    cout << st.size() << endl; 
    // Output: 2

    cout << st.empty() << endl; 
    // Output: 0 (represents false, stack is not empty)

    stack<int> st2;
    // O(1) - Swap pointers of st and st2
    st2.swap(st);     // st is now empty, st2 is [289, 5]

    // O(1) - Pushing to the swapped stack
    st2.push(23);     // Stack st2: [23, 289, 5] (top is 23)

    cout << st2.top() << endl;
    // Output: 23

}

 /**
 * QUEUE EXPLAINED:
 * A FIFO (First In, First Out) data structure.
 * Elements are pushed at the back and popped from the front.
 */
void explainQueue() {
    queue<int> q;

    // O(1) - Pushes element to the back
    q.push(5);           // {5}
    q.push(28);          // {5, 28}
    
    // O(1) - Constructs element at the back
    q.emplace(23231);    // {5, 28, 23231}

    // O(1) - Removes the element from the FRONT
    q.pop();             // {28, 23231}

    // O(1) - Accessing and modifying the back element
    q.back() += 9;       // 23231 + 9 = 23240. Queue is now {28, 23240}

    cout << q.back() << endl;   
    // Output: 23240

    cout << q.front() << endl;  
    // Output: 28

    cout << q.size() << endl;   
    // Output: 2

    queue<int> q2;
    // O(1) - Swaps internal data pointers between q and q2
    q2.swap(q);          // q is now empty, q2 is {28, 23240}

    // O(1) - Adding to q2
    q2.emplace(23);      // q2 is now {28, 23240, 23}

    // REDUNDANT/DANGEROUS LINE: Accessing q.back() after it was swapped (q is empty)
    // In a real scenario, this would cause Undefined Behavior.
    // Assuming the user meant q2.back():
    cout << q2.back() << endl;
    // Output: 23
}

/**
 * PRIORITY QUEUE EXPLAINED:
 * A priority_queue is a container adaptor that provides constant time O(1) lookup 
 * of the element with the highest priority (the largest by default).
 * It is internally implemented as a heap (typically a binary max-heap).
 * 
 * Key Features:
 * 1. Default Behavior (Max-Heap): The largest element is always at the top.
 * 2. Min-Heap Implementation: Using `greater<T>`, the smallest element stays at the top.
 * 3. Logarithmic Efficiency: Insertion and deletion take O(log N) to maintain heap order.
 * 4. Restricted Access: Only the `top()` element is accessible; it does not support iteration.
 * 
 * Documentation: [cppreference.com - std::priority_queue](https://en.cppreference.com)
 */
 void explainPQ() {
    // MAX-HEAP (Default)
    priority_queue<int> pq;
    pq.push(5);     // {5}
    pq.push(2);     // {5, 2}
    pq.push(7);     // {7, 5, 2}
    pq.emplace(1);  // {7, 5, 2, 1}
    pq.emplace(2);  // State: {7, 5, 2, 2, 1}
    

    // O(1) - Access largest element
    cout << pq.top() << endl; // Output: 7

    // O(log N) - Removes top (7) and re-heaps
    pq.pop(); 
    cout << pq.top() << endl; // Output: 5

    // MIN-HEAP
    // Syntax: priority_queue<Type, Container, Comparator>
    priority_queue<int, vector<int>, greater<int>> pq2;
    
    // Note: Calling pop() on an empty PQ is Undefined Behavior!
    // Always check !pq2.empty() before access.
    pq2.push(2);    // {2}
    pq2.push(1);    // {1, 2}
    pq2.emplace(53); // {1, 2, 53}

    cout << pq2.top() << endl; // Output: 1
    pq2.pop();
    cout << pq2.top() << endl;  // Output: 2

    // Internal swap logic
    priority_queue<int, vector<int>, greater<int>> pq3;
    pq3.push(10);

    // O(1) - Swap is constant time as it swaps internal container references
    pq2.swap(pq3); 

    cout << pq2.top() << endl; // Output: 10 (from pq3)

    // Note: You cannot swap 'pq' (Max-Heap) with 'pq2' (Min-Heap) 
    // because they are considered different data types in C++.

}

/**
 * SET EXPLAINED:
 * Stores unique elements in a sorted order (default: ascending).
 * Implementation: Balanced Binary Search Tree (Red-Black Tree).
 * Time Complexity: O(log N) for Search, Insert, and Delete.
 */
void explainSet() {
    set<int> st;

    // Insertion
    st.insert(25);    // {25}
    st.insert(4);     // {4, 25}
    st.emplace(27);   // {4, 25, 27} - emplace is generally more efficient than insert
    st.insert(43);    // {4, 25, 27, 43}
    st.insert(4);     // {4, 25, 27, 43} - Duplicate '4' is ignored; sets only store unique values

    // Finding Elements
    auto it = st.find(3);   // Searches for 3. Not found, so it returns st.end()
    if (it != st.end()) {
        cout << *it << endl; 
    } else {
        cout << "Element not found" << endl;
    }

    auto it1 = st.find(4);  // Searches for 4. Returns an iterator pointing to 4
    if (it1 != st.end()) {
        cout << *it1 << endl; 
    } else {
        cout << "Element not found" << endl;
    }

    // Erasing by Value
    st.erase(6);      // Searches for 6. Not found, set remains unchanged
    st.erase(4);      // Removes 4 from the set. Set is now {25, 27, 43}

    auto it_to_erase = st.find(27);
    if (it_to_erase != st.end()) {
        st.erase(it_to_erase); // Safe because we just found it and haven't modified the set yet
    }

    for(auto it : st){
        cout << it << " ";
    }
    cout << endl;

    // Counting Elements
    int cnt = st.count(4);  // Returns 0 because 4 was just erased
    int cnt2 = st.count(2); // Returns 0 because 2 was never in the set
    int cnt3 = st.count(25);    // Returns 1 because 25 is in the set

    cout << "Count of 4: " << cnt << " Count of 2: " << cnt2 << " Count of 25: " << cnt3 << endl;

    // Repopulating the set for range erase example
    st.insert(29);
    st.insert(47);
    st.insert(1);
    st.emplace(4);
    st.emplace(3);
    // Set is now: {1, 3, 4, 25, 29, 43, 47}

    // Range Erase: st.erase(start_iterator, end_iterator)
    auto it2 = st.find(3);   // Pointer to 3
    auto it3 = st.find(29);  // Pointer to 29
    
    // Erases elements in range [it2, it3) -> removes 3, 4, 25. 
    // it3 (29) is NOT included in the deletion.
    st.erase(it2, it3);

    // Final Print: {1, 29, 43, 47}
    for(auto it : st){
        cout << it << " ";
    }
    cout << endl;

    // Erasing by Iterator (DANGER ZONE)
    // 1. st.erase(it);  
    // WARNING: 'it' is st.end(). Erasing st.end() causes UNDEFINED BEHAVIOR/CRASH.

    // 2. st.erase(it1); 
    // WARNING: 'it1' pointed to 4, which was already erased by value above.
    // Using an invalidated iterator causes UNDEFINED BEHAVIOR/CRASH.
}

/**
 * MULTISET EXPLAINED:
 * Stores sorted elements but allows DUPLICATES.
 * Implementation: Similar to set, but tracks equivalent keys.
 * Time Complexity: O(log N) average.
 */
void explainMultiSet() {
    // Stores sorted elements but allows DUPLICATES
    multiset<int> ms;
    ms.insert(1); // {1}
    ms.insert(1); // {1, 1}
    ms.insert(1); // {1, 1, 1}

    // ERASING BY VALUE: removes ALL instances of that value
    ms.erase(1); // Set becomes empty {}

    ms.insert(1); 
    ms.insert(1); // {1, 1}
    
    // ERASING BY ITERATOR: removes ONLY the single element pointed to
    // ms.find(1) returns an iterator to the first instance of 1 it finds
    ms.erase(ms.find(1)); // Set becomes {1}

    ms.emplace(25);
    ms.emplace(25);
    ms.emplace(26);

    // Final multiset: {1, 25, 25, 26}
    cout << "Size of Multiset: " << ms.size() << endl; // Output: 4

    for(auto it : ms){
        cout << it << " "; // Output: 1 25 25 26 
    }
    
    cout << endl;

    // Accessing Raw Memory Addresses (2026 Best Practice)
    auto it1 = ms.find(1);   // Iterator to 1
    auto it2 = ms.find(26);  // Iterator to 26
    
    if(it1 != ms.end()) cout << "it1 addr: " << std::addressof(*it1) << endl;
    cout << "Address of element at it1: " << &(*it1) << endl;
    cout << "Address of element at it2: " << &(*it2) << endl;
    
    // Erases everything from it1 (inclusive) to it2 (exclusive)
    // Removed: 1, 25, 25
    // RANGE ERASE
    ms.erase(it1, it2);

    for(auto it : ms){
        cout << it << " "; // Output: 26
    }
    cout << endl;

    ms.insert(27); ms.insert(27); ms.insert(27);
    ms.insert(29); ms.insert(29);
    ms.insert(1);
    ms.insert(2);
    ms.emplace(2);
    ms.emplace(1);

    // // CORRECT ITERATOR LOOP:
    // // initialization; condition; increment
    // for(auto it = ms.begin(); it != ms.end(); it++){
    //     cout << *it << " "; // Dereference iterator to get the value
    // }
    // cout << endl;

    // SIMPLER MODERN C++ ALTERNATIVE (Range-based for loop):
    for(auto val : ms) {
        cout << val << " ";
    }
    cout << endl;

    int cnt_1= ms.count(1); // 2
    int cnt_2 = ms.count(2);    // 2
    int cnt_27 = ms.count(27);  // 3

    cout << "Count of 1: " << cnt_1 << " Count of 2: " << cnt_2 << " Count of 27: " << cnt_27 << " Count of 29: " << ms.count(29) << endl;
}

/**
 * UNORDERED SET EXPLAINED:
 * Stores unique elements in no specific order.
 * Implementation: Hash Table (Buckets).
 * Time Complexity: Average O(1), Worst case O(N) due to collisions.
 */
void explainUnorderedSet(){
    unordered_set<int> us;
    
    // Average O(1) - Inserts elements into the hash table
    us.insert(2);
    us.insert(5);
    us.insert(27);
    
    // constructs element in-place (efficient)
    us.emplace(29);
    
    us.insert(1);
    us.insert(-27);

    // Duplicate insertion: silently ignored
    us.insert(27);
    
    // Iterating: order is randomized/unpredictable
    for(auto it : us){
        cout << it << " "; 
    }
    cout << endl;

    // C++20/C++26 member function for cleaner membership checks
    if (us.find(27) != us.end()) {
        cout << "27 exists!" << endl;
    }

    // Since unordered_set has unique elements, count will be 1 or 0
    if (us.count(27) > 0) {
        cout << "27 exists!" << endl;
    }

    // Size check
    cout << "Total unique elements: " << us.size() << endl;
}

/**
 * MAP EXPLAINED:
 * Stores key-value pairs with unique keys in a sorted order.
 * 
 * IMPLEMENTATION:
 * Self-balancing Binary Search Tree (usually a Red-Black Tree).
 * 
 * TIME COMPLEXITY:
 * - Search:    O(log N)
 * - Insertion: O(log N)
 * - Deletion:  O(log N)
 * - Access:    O(log N) (using [] or .at())
 * 
 * KEY CHARACTERISTICS (2026 Standards):
 * 1. Unique Keys: Cannot have duplicate keys; inserting an existing key overwrites the value.
 * 2. Sorted Order: Elements are always sorted by key (default: ascending).
 * 3. Bidirectional Iterators: Can be traversed in both directions (forward/backward).
 * 4. Stability: References and pointers to elements remain valid even after insertions/deletions.
 */
void explainMap() {
    // Standard map: Key is int, Value is string
    map<int, string> mpp;

    // Nested Map: Key is int, Value is a pair of two ints
    // Useful for storing 2D coordinates, (score, priority), etc.
    map<int, pair<int, int>> mpp2;

    // Map with pair as KEY (Composite Key)
    // Useful for 2D coordinates mapping to a value
    map<pair<int, int>, int> mpp3;

    // 1. Insertion into mpp
    mpp[1] = "Suraj";
    mpp.emplace(3, "C++");
    mpp.insert({2, "Java"});

    // DELETION - O(log N)
    mpp.erase(2);             // Erase by key
    // mpp.erase(mpp.begin()); // Erase by iterator

    // ITERATION - O(N)
    // Elements are printed in sorted order of keys
    for(auto const& it : mpp) {
        cout << it.first << " -> " << it.second << endl;
    }

    cout << mpp[1] << endl; // It prints the value for key 1
    cout << mpp[2] << endl; // It prints the value for key 2 means nothing because we have already erased it above.
    cout << mpp[3] << endl; // It prints the value for key 3

    // 5. SIZE & CLEAR - O(1)
    cout << "Map size: " << mpp.size() << endl;
    mpp.clear(); // Removes all elements
    cout << "Map size after mpp.clear() which removes all the elements: " << mpp.size() << endl;

    // 2. Insertion into mpp2
    // Method A: Square brackets (inserts or updates)
    // INSERTION - O(log N)
    mpp2[1] = {10, 20}; 

    // Method B: emplace (more efficient, constructs in-place)
    // Note: You must pass the key and then the pair constructor arguments
    mpp2.emplace(2, make_pair(30, 40)); 

    // Method C: insert with curly braces
    mpp2.insert({3, {50, 60}});

    mpp3[{1, 2}] = 100;         // Key: (1, 2), Value: 100
    mpp3.insert({{2, 3}, 200}); // Key: (2, 3), Value: 200
    mpp3.emplace(make_pair(1, 1), 50); // Key: (1, 1), Value: 50

    // 3. Accessing Elements
    // To access nested pair values, use .first and .second on the value
    cout << "mpp2 Key 1: (" << mpp2[1].first << ", " << mpp2[1].second << ")" << endl;
    // Output: mpp2 Key 1: (10, 20)

    // 4. Iteration (Sorted by Key)
    cout << "Iterating mpp2:" << endl;
    for(auto it : mpp2) {
        // it.first is the Key (int)
        // it.second is the Value (pair<int, int>)
        cout << it.first << " -> [" << it.second.first << ", " << it.second.second << "]" << endl;
    }

    // 5. Searching in mpp2
    // SEARCHING - O(log N)
    auto it = mpp2.find(2);
    if(it != mpp2.end()) {
        // Accessing via iterator requires -> for the map element, 
        // then .first/.second for the pair itself
        cout << "Key 2 found with values: " << it->second.first << " " << it->second.second << endl;
    }

    // 6. Membership Check (2026 Practice)
    // find() works in all versions; contains() requires -std=c++20
    if (mpp2.find(3) != mpp2.end()) {
        cout << "Key 3 exists in mpp2!" << endl;
    }

    cout << "\n--- Map 3 (Pair -> Int) ---" << endl;
    for(auto it : mpp3) {
        // it.first is a pair, so we use .first and .second on it
        cout << "(" << it.first.first << ", " << it.first.second << ") -> " << it.second << endl;
    }
    /* Output:
       (1, 1) -> 50
       (1, 2) -> 100
       (2, 3) -> 200
       Note: Sorted first by pair.first, then by pair.second.
    */

    // --- ACCESSING mpp3 ---
    // Direct access using a temporary pair as the key
    cout << "\nValue at (1, 2) in mpp3: " << mpp3[{1, 2}] << endl;

    // Searching in mpp3
    auto it_mpp3 = mpp3.find({2, 3});
    if(it_mpp3 != mpp3.end()) {
        cout << "Key (2, 3) exists with value: " << it_mpp3->second << endl;
    }
}

/**
 * MULTIMAP EXPLAINED:
 * Stores key-value pairs sorted by key, allowing multiple entries with the same key.
 * Implementation: Self-balancing Binary Search Tree (usually Red-Black Tree).
 * 
 * TIME COMPLEXITY:
 * - Insertion: O(log N)
 * - Deletion: O(log N)
 * - Search: O(log N)
 * 
 * KEY CHARACTERISTICS:
 * 1. Allows duplicate keys (unlike std::map).
 * 2. Elements are always sorted by key.
 * 3. Does NOT support operator[] (e.g., m[key]) because a key could map to many values.
 */
 void explainMultiMap() {
    // Declaration: <KeyType, ValueType>
    multimap<int, string> mm;

    // 1. INSERTION
    // Must use insert() or emplace(); operator[] is not available.
    mm.insert({1, "Apple"});
    mm.insert({1, "Alpha"}); // Duplicate key allowed
    mm.insert({3, "Gamma"});
    mm.insert({2, "Beta"});

    // 2. ITERATION
    // Elements will be printed in ascending order of keys.
    // For identical keys, they appear in order of insertion.
    cout << "Multimap contents:" << endl;
    for (auto it : mm) {
        cout << it.first << " -> " << it.second << endl;
    }

    // 3. SEARCHING
    // find() returns an iterator to the FIRST instance of the key.
    auto it = mm.find(1);
    
    // count() returns the number of elements associated with a specific key.
    cout << "Count of key 1: " << mm.count(1) << endl;

    // 4. EQUAL RANGE (Handy for Multimaps)
    // Returns a pair of iterators representing the range [first, last) of a key.
    auto range = mm.equal_range(1);
    cout << "Values for key 1: ";
    for (auto i = range.first; i != range.second; ++i) {
        cout << i->second << " ";
    }
    cout << endl;

    // 5. DELETION
    // mm.erase(1) deletes ALL instances of key 1.
    // To delete only one specific instance, pass the iterator:
    // mm.erase(mm.find(1));
    mm.erase(2); // Removes {2, "Beta"}
}

/**
 * UNORDERED MAP EXPLAINED:
 * Stores key-value pairs with unique keys in no specific order.
 * Implementation: Hash Table.
 * 
 * TIME COMPLEXITY:
 * - Insertion/Search/Deletion (Average): O(1)
 * - Insertion/Search/Deletion (Worst Case): O(N) (due to hash collisions)
 * 
 * KEY CHARACTERISTICS:
 * 1. Faster than std::map for large datasets (on average).
 * 2. Order of elements is unpredictable.
 */
void explainUnorderedMap() {
    unordered_map<int, string> um;

    // 1. INSERTION (Average O(1))
    um[1] = "Data";
    um.insert({5, "Structure"});
    um.emplace(3, "Fast");

    // 2. MEMBERSHIP (C++20/C++26 style)
    // contains() is the most readable way to check existence in modern C++.
    if (um.find(1) != um.end()) { // Requires -std=c++20
        cout << "Key 1 exists with value: " << um[1] << endl;
    }

    // 3. SIZE & CAPACITY
    cout << "Unique keys: " << um.size() << endl;
    cout << "Bucket count: " << um.bucket_count() << endl;
}

// Example: Sort pairs by the SECOND element in descending order
// If second elements are equal, sort by FIRST element in ascending order
bool comp(const pair<int, int>& a, const pair<int, int>& b) {
    if (a.second != b.second) {
        return a.second > b.second; // Descending by second
    }
    return a.first < b.first; // Ascending by first
}

int main(){
    cout << "Pair:" << endl;
    explainPair();
    cout << "Vector:" << endl;
    explainVector();
    cout << "List:" << endl;
    explainList();
    cout << "Deque:" << endl;
    explainDeque();
    cout << "Stack:" << endl;
    explainStack();
    cout << "Queue:" << endl;
    explainQueue();
    cout << "Priority Queue:" << endl;
    explainPQ();
    cout << "Set:" << endl;
    explainSet();
    cout << "Multiset:" << endl;
    explainMultiSet();
    cout << "Unordered Set:" << endl;
    explainUnorderedSet();
    cout << "Map:" << endl;
    explainMap();
    cout << "MultiMap:" << endl;
    explainMultiMap();
    cout << "Unordered Map:" << endl;
    explainUnorderedMap();
    // 1. Pair and Sorting with Custom Comparator
    cout << "\n--- Custom Sort for Pair ---" << endl;
    vector<pair<int, int>> pairVec = {{1, 2}, {2, 2}, {4, 1}, {3, 5}};
    
    // Sort using custom logic: {{3, 5}, {1, 2}, {2, 2}, {4, 1}}
    sort(pairVec.begin(), pairVec.end(), comp);
    
    // Overwrite with Lexicographical Descending: {{4, 1}, {3, 5}, {2, 2}, {1, 2}}
    sort(pairVec.begin(), pairVec.end(), greater<>{}); 
    
    for (auto const& p : pairVec) cout << "{" << p.first << "," << p.second << "} ";
    cout << "\n" << endl;

    // 2. Bit Counting (Popcount)
    int num = 7; // Binary: 111
    cout << "Set bits in 7: " << __builtin_popcount(num) << endl; 

    // Use __builtin_popcountll for 64-bit numbers (long long)
    long long num1 = 165786578687LL; 
    cout << "Set bits in large num: " << __builtin_popcountll(num1) << endl; 
    
    // 3. String Permutations
    // Note: To get ALL permutations, the string must be SORTED first.
    string s = "Suraj"; 
    sort(s.begin(), s.end());   // After sorting the count of permutation is the factorial of length of the string.
    int cnt3 = 0;
    cout << "Permutations of 'Suraj':" << endl;
    do {
        cout << s << " ";
        cnt3++;
    } while (next_permutation(s.begin(), s.end()));
    cout << "\nTotal permutations: " << cnt3 << endl;

    // 4. Finding Maximum Element
    // max_element returns an iterator to the largest pair (lexicographically)
    auto it = max_element(pairVec.begin(), pairVec.end());
    if (it != pairVec.end()) {
        cout << "Max Pair: {" << it->first << ", " << it->second << "}" << endl;
    }

    return 0;
}
