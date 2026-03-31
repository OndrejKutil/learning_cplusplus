# Level 4 - OOP and File I/O

Goal: design simple classes and persist data using files.

## Exercise 1: Bank Account Class
File: `ex01_bank_account.cpp`
- Create a `BankAccount` class with:
  - owner name
  - account balance
  - `deposit` and `withdraw` methods
- Prevent invalid operations (negative deposit, overdraft).
- Print account summary.

## Exercise 2: To-Do List with File Save
File: `ex02_todo_file.cpp`
- Create a simple menu:
  - add task
  - list tasks
  - save tasks to file
  - load tasks from file
- Use a `Task` struct or class.
- Use text file storage (`tasks.txt`).

## Completion Check
- You used constructors and encapsulation.
- Methods have clear responsibilities.
- Data survives between runs via file save/load.
