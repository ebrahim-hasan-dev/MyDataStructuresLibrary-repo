# My Data Structures Library (C++)

A comprehensive, high-performance C++ library implementing a wide range of data structures and algorithms. This project is built with a focus on Object-Oriented Programming (OOP), manual memory management and advanced **Pointer Manipulation** for optimal memory management, and generic programming using templates.

## 🚀 Overview

This library is designed to provide robust implementations of linear and non-linear data structures. Every structure is crafted from scratch, demonstrating advanced pointer manipulation and efficient memory allocation on the heap.

## 🛠 Key Technical Features

- **Generic Programming:** All classes are implemented using **C++ Templates**, making the library type-independent and flexible.
- **Efficiency:** Logic implemented with focus on time and space complexity.
- **Manual Memory Management:** High-level mastery of pointers with explicit memory allocation in the heap and guaranteed cleanup using **Destructors** to prevent memory leaks.
- **OOP Architecture:** Strict adherence to Object-Oriented principles, including encapsulation, inheritance, and modular design.
- **Utility Integration:** The project relies on a custom-built utility layer (`clsString`, `clsDate`, `clsInput`, `clsValidate`, `clsUtil`) for seamless data handling.
- **Internal Dependencies:** Intelligent reuse of structures (e.g., using a custom `Queue` for `AVL Tree` Level-Order traversal).

---

## 📚 Library Components & Complexity Analysis

### 1. Linear Data Structures
Includes various implementations focusing on performance and different access patterns:
- **Lists:** Array-based Lists, Singly Linked Lists, Doubly Linked Lists.
- **Stacks & Queues:** Stack, Queue, and **Priority Queue** (utilizing **Heap Sort** algorithm internally).
- **Advanced Operations:** Custom `reverse` logic, deep copying, dynamic resizing, and efficient search/deletion using pointer traversal.

| Data Structure | Access | Search | Insertion | Deletion |
| :--- | :---: | :---: | :---: | :---: |
| **Array-based List** | O(1) | O(n) | O(n) | O(n) |
| **Singly Linked List** | O(n) | O(n) | O(1) | O(1) |
| **Doubly Linked List** | O(n) | O(n) | O(1) | O(1) |
| **Stack / Queue** | - | - | O(1) | O(1) |
| **Priority Queue (Heap Sort)** | - | - | O(log n) | O(log n) |

### ⚠️ Important Note 
In a linked list or a double-linked list, Time complexity of insertion and deletion are `o(1)` if they occur at the beginning or end of the list, because we have a pointer pointing to the first node and another pointer pointing to the last node. However, if the insertion or deletion occurs before or after a specific element, the time complexity will be in the worst case `o(n)`.


### 2. Tree Structures (Hierarchical Structures)
A deep dive into hierarchical data management with recursion-based logic:
-   **Self-Balancing & Search Trees:** BST, AVL Tree, Red-Black Tree.
-   **Disk-Optimized Trees:** B-Tree and **B+ Tree**.
-   **Huffman Tree:** for file compression and decompression algorithms.
- **Traversals:** In-order, Pre-order, Post-order, and **Level-order** (The AVL implementation utilizes a custom-built Queue for Level-order traversal).

| Tree Type | Average Search | Worst Search | Insertion | Deletion |
| :--- | :---: | :---: | :---: | :---: |
| **BST (Unbalanced)** | O(log n) | O(n) | O(log n) | O(log n) |
| **AVL Tree / Red-Black** | O(log n) | O(log n) | O(log n) | O(log n) |
| **B-Tree / B+ Tree** | O(log n) | O(log n) | O(log n) | O(log n) |

> **Note on Databases:** This section highlights the relationship between **B+ Trees** and **SQL Server Indexing**. Understanding these structures provides a deep insight into how database engines handle internal data storage and binary search optimization.


### 3. Hash Tables
Highly configurable hashing mechanisms with various collision resolution strategies:
- **Hash Functions:** Supports Division, Multiplication, and Folding methods (configurable via `Enums` in the constructor).
-   **Collision Handling:**
    -   Open Hashing (Close Addressing, Chaining).
    -   Closed Hashing (Open Addressing) With the ability to specify the type of probing at the constructor.
    -   Cuckoo Hashing, Robin Hood Hashing, Coalesced Hashing, and Perfect Hashing.


| Operation | Average Case | Worst Case (Collision) |
| :--- | :---: | :---: |
| **Search / Insert / Delete** | O(1) | O(n) |

**Note:**  Each collision handling method has advantages and disadvantages in terms of speed and performance of searching, adding, and deleting.


### 4. Graphs
A robust classes for representing complex networks and Comprehensive graph theory implementation:
- **Representations:** Adjacency List, Adjacency Matrix, and Incidence Matrix.
- **Types Supported:** Directed/Undirected, Weighted/Unweighted, and Pseudo-weighted graphs.
- **Algorithms:**
  - **Traversal:** Breadth-First Search (BFS), Depth-First Search (DFS).
  - **Shortest Path:** Dijkstra’s Algorithm (It cannot handle negative weights), Bellman-Ford Algorithm (It can handle negative weights).
- **Features:** Edge management (Add/Delete), shortest path calculation, and neighbor discovery.

| Algorithm | Time Complexity |
| :--- | :---: |
| **BFS / DFS** | O(V + E) |
| **Dijkstra (Shortest Path)** | O(V + E log V) |
| **Bellman-Ford** | O(V × E) |


### 5. Practical On Stack
- This folder contains the most common uses of the Stack data structure in solving certain problems, such as undo and redo process, balanced parentheses and converting infix notation to prefix or postfix notation, enabling the compiler to calculate complex mathematical equations quickly and efficiently. (And Expression Evaluation)

- This is an example of how to use the functions located within the (PracticalOnStack) folder.

```cpp
using namespace std;
#include <iostream>

#include "../MyDataStructuresLibrary/PracticalOnStack/BalancedParentheses.h";
#include "../MyDataStructuresLibrary/PracticalOnStack/ConvertInfixToPrefixAndExpressionEvaluation.h";
#include "../MyDataStructuresLibrary/PracticalOnStack/ConvertInfixToPostfixAndExpressionEvaluation.h";
using namespace PracticalOnStack;

int main() 
{
    cout << AreBalanced("()[{}") << "\n";
    cout << AreBalanced("(){()}") << "\n";

    // =====================================================================================

	string Expression = "(5+8)*9+((8/4)*55-99)*7";

	cout << "Expression befor convert to prefix: " << Expression << "\n";
	cout << "Expression after convert to prefix: " << ConvertInfixToPrefix(Expression) << "\n";

	cout << "Expression Result Prefix : " << PerformExpressionEvaluationPrefix(Expression) << "\n\n";

	cout << "=====================================================================================\n\n";

	cout << "Expression befor convert to postfix: " << Expression << "\n";
	cout << "Expression after convert to postfix: " << ConvertInfixToPostfix(Expression) << "\n";
	cout << "Expression after convert to postfix better: " << ConvertInfixToPostfixBetter(Expression) << "\n";

	cout << "Expression Result Postfix : " << PerformExpressionEvaluationPostfix(Expression) << "\n\n";
}
```


### 6. Practical On Queue
- This folder contains the class that simulates a first-come, first-served ticket booking process, similar to a queue data structure logic.


---

## 🏗 Project Structure & Dependencies

The project is modularly structured, where advanced structures leverage simpler ones.
- **Internal Dependencies:** The `AVL Tree` depends on the custom `Queue` class There are other data structures that also depend on custom data structures.
- **Utility Classes:**
  - `clsDate`: For date-related operations.
  - `clsString`: Custom string manipulation logic.
  - `clsInput`: Validated user input handling.
  - `clsUtil`: General purpose helper functions.
  - `clsValidate`: Data validation logic.

---
## ⚠️ Important Execution Notes

1- Do not change any folder names within the main project folder, and do not change the project folder structure, to avoid any errors.

2- A console app project has been added to test any class.

---

## 💻 How to Use

Since the library is template-based, you can simply include the required header files in your project:

```cpp
#include "clsLinkedList.h"
#include "clsAVLTree.h"

int main() {
    LinkedList<int> myList;
    myList.InsertInFirst(10);
    myList.Display();

    return 0;
}
```

## 👤 About the Author

**Ebrahim Hasan**
A passionate Software Developer with a solid foundation in Computer Science. My journey started with learning the basics of the C++ language (Functional programming), then mastering **Algorithms, Object Oriented Programming and Data Structures** in C++, then learning C#, .NET and SQL Server Database, which paved the way for building complex systems using **C# and .NET**.

* **Expertise:** Desktop Applications (WinForms), SQL Server Database Design, and Logic Automation.
* **Key Projects:** Driver License Management System, Code Generator Tool.
* **Current Goal:** Transitioning into Web Full-stack Development (C#/.NET Backend).

---
📫 **Connect with me:**
* 📧 **Email:** [ebrahim-hasan-dev@gmail.com](mailto:ebrahim-hasan-dev@gmail.com)
* 💼 **LinkedIn:** [Your Profile Name](https://linkedin.com/in/ebrahim-hasan-dev)
