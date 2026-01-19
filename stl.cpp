#include <deque>
#include <functional>
#include <iostream>
#include <queue>
#include <utility> // Required for pair
#include <vector>
#include <string>
#include <list>
#include <deque>

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

    // Nested pair: The second element is itself a pair
    // O(1) - Nesting does not change access complexity
    cout << "Pair 2 containing an integer and a pair of integers:" << endl;
    pair<int, pair<int, int>> p2 = {1, {2, 3}};
    cout << p2.first << " " << p2.second.first << " " << p2.second.second << endl;

    // Deeply nested pairs
    cout << "Pair 3 containing two pairs of integers:" << endl;
    pair<pair<int, int>, pair<int, int>> p3 = {{1, 2}, {3, 4}};
    cout << p3.first.first << " " << p3.first.second << " " << p3.second.first << " " << p3.second.second << endl;

    // Array of pairs: Useful for representing edges in a graph or coordinates
    // O(N) where N is the size of the array
    cout << "Pair 3 containing two pairs of integers and an array of pairs:" << endl;
    pair<int, int> arr[] = {{1, 2}, {3, 4}, {5, 6}};
    cout << arr[1].first << " " << arr[1].second << endl;
    
    // O(M) where M is string length (copying "Suraj" into the pair)
    cout<< "Pair 4 containing a string and an integer:" << endl;
    pair<string, int> p4 = {"Suraj", 1};
    cout << p4.first << " " << p4.second << endl;
    
    // Pair containing a dynamic container
    // O(V) where V is the number of elements in the vector
    cout << "Pair 5 containing a vector of integers and an integer:" << endl;
    pair<vector<int>, int> p5 = {{1, 2, 3}, 4};
    cout << p5.first[0] << " " << p5.first[1] << " " << p5.first[2] << " " << p5.second << endl;

    cout << "Pair 6 containing two vectors of pairs:" << endl;
    pair<vector<pair<int, int>>, vector<pair<int, int>>> p6 = {{{1, 2}, {3, 4}}, {{5, 6}, {7, 8}}};
    cout << p6.first[0].first << " " << p6.first[0].second << " " << p6.first[1].first << " " << p6.first[1].second << " " << p6.second[0].first << " " << p6.second[0].second << " " << p6.second[1].first << " " << p6.second[1].second << endl;
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

    cout << "Vector 2 containing two pairs of integers:" << endl;
    vector<pair<int, int>> v2;
    v2.push_back({1, 2});
    v2.emplace_back(3, 4);
    cout << v2[0].first << " " << v2[0].second << " " << v2[1].first << " " << v2[1].second << endl;

    // Vector initialization with size and default value
    // O(N) - Initializing N elements takes linear time
    cout << "Vector 3 containing five 100s:" << endl;
    vector<int> v3(5, 100);
    cout << v3[0] << " " << v3[1] << " " << v3[2] << " " << v3[3] << " " << v3[4] << endl;
    
    // Vector initialization with size only (defaults to zero for ints)
    cout << "Vector 4 containing five 0s and a size of 5:" << endl;
    vector<int> v4(5);
    cout << v4[0] << " " << v4[1] << " " << v4[2] << " " << v4[3] << " " << v4[4] << endl;

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

    vector<int>copy(2,50);

    v6.insert(v6.begin(), copy.begin(), copy.end());

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
    cout << "Element at index 1: " << dq[1] << endl;
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
    return 0;
}
