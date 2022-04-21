# 💻 Assignment 05
## Requirements

- You will be given one of the problems below to solve using feature-driven development
- The program must provide a menu-driven console user interface.
- Use classes to represent the following:
    - The domain entity (`complex`,  `expense`,  `student`, `book`)
    - A services class that implements the required functionalities
    - The ui class which implements the user interface
- Have 10 programmatically generated entries in the application at start-up.
- Unit tests and specifications for non-UI functions related to the first functionality.

## Problem Statements
### 1. Complex numbers
Manage a list of complex numbers in `a+bi` form and provide the user the following features:
1. Add a number. The number is read from the console.
2. Display the list of numbers.
3. Filter the list so that it contains only the numbers between indices `start` and `end`, where these values are read from the console.
4. Undo the last operation that modified program data. This step can be repeated.

---
### 2. Expenses
Manage a list of expenses. Each expense has a `day` (integer between 1 and 30), `amount` of money (positive integer) and expense `type` (string). Provide the following features:
1. Add an expense. Expense data is read from the console.
2. Display the list of expenses.
3. Filter the list so that it contains only expenses above a certain value read from the console.
4. Undo the last operation that modified program data. This step can be repeated.

---
### 3. Students
Manage a list of students. Each student has an `id` (integer, unique), a `name` (string) and a `group` (positive integer). Provide the following features:
1. Add a student. Student data is read from the console.
2. Display the list of students.
3. Filter the list so that students in a given group (read from the console) are deleted from the list.
4. Undo the last operation that modified program data. This step can be repeated.

---
### 4. Books
Manage a list of books. Each book has an `isbn` (string, unique), an `author` and a `title` (strings). Provide the following features:
1. Add a book. Book data is read from the console.
2. Display the list of books.
3. Filter the list so that book titles starting with a given word are deleted from the list.
4. Undo the last operation that modified program data. This step can be repeated.
