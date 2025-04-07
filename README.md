# 📚 Assignment Management System using AVL Tree

This project is a data-structure-based **Assignment Management System** implemented using **AVL Trees**. It efficiently manages student records and assignment data while handling various operations like insertions, updates, and complex queries related to assignment status and student performance.

---

## 🚀 Features

The system supports the following operations:

1. **Insert Student Record**
   - Add a new student to the system.
   - Automatically updates relevant assignment lists after insertion.

2. **Insert Assignment Record**
   - Add a new assignment.
   - Allocate it to multiple student groups at once, triggering updates in student lists.

3. **Change Assignment & Student Status**
   - Update status on:
     - Submission by a student group.
     - Evaluation of a particular assignment for a student group.
     - Full evaluation of an assignment across all assigned groups.

4. **Display Unevaluated Assignments**
   - Print a list of all assignments that have been declared but not yet evaluated.

5. **Late Submissions**
   - List student groups who haven't submitted their assignments even after the due date.

6. **Pending Evaluations**
   - Show student groups whose submitted assignments are yet to be evaluated.
   - If viva is pending, it's explicitly indicated.

7. **Ranking by Assignment**
   - For a given assignment ID, display student groups in decreasing order of marks received.

8. **Top Performers**
   - Display student groups receiving top marks in each assignment.

---

## 🧠 Tech Stack

- **Language**: C++
- **Data Structure**: AVL Tree (Self-Balancing Binary Search Tree)

---

## 📁 Project Structure

This project uses the AVL Tree to keep all operations like insertions, deletions, and lookups efficient and balanced. It simulates a real-world academic assignment management scenario using advanced data structures.

---

## 💡 Use Case

This project is ideal for understanding how self-balancing binary search trees like AVL Trees can be applied in practical applications like academic management systems.

---


## 📌 How to Run

```bash
# Compile
g++ -o assignment_system main.cpp

# Run
./assignment_system
