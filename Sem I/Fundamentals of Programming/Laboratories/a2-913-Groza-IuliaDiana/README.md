# Assignment 02

## Requirements
- Use functions to: `read a complex number` from the console, `write a complex number` to the console, implement `each required functionality`.
- Functions communicate using input parameter(s) and the return statement (**DO NOT use global variables**)
- Use a `list`, `tuple` or `dictionary` tu represent each complex number (e.g. 1-2i as `[1, -2]`, `(1, -2)` or `{'real': 1, 'imag': -2}` respectively). To access or modify numbers, use `getter` and `setter` functions.
- Separate input/output functions (those using `print` and `input` statements) from those performing the calculations (see **program.py**)
- Provide the user with a menu-driven console-based user interface. Input data should be read from the console and the results printed to the console. At each step, the program must provide the user the context of the operation (do not display an empty prompt).
- Deadline is week 3 for maximum grade, week 5 is hard deadline.

## Problem Statement
Implement a menu-driven console application that provides the following functionalities:
1. Read a list of complex numbers (in `z = a + bi` form) from the console.
2. Display the entire list of numbers on the console.
3. Display on the console the longest sequence that observes a given property. Each student will receive 2 of the properties from the list provided below.
4. Exit the application.

**The source code will include:**
- Specifications for the functions related to point 3 above. 
- 10 complex numbers already available at program startup.

### Sequence Properties
The sequence (consists of):
1. Numbers with a strictly increasing real part.
2. Contains at most 3 distinct values.
3. Numbers having the same modulus.
4. Numbers having increasing modulus.
5. Real numbers.
6. Distinct numbers.
7. The difference between the modulus of consecutive numbers is a prime number.
8. The modulus of all elements is in the `[0, 10]` range.
9. Consecutive number pairs have equal sum. (e.g. `1+3i`, `1-i`, `1+3i`, `1-i`)
10.	Sum of its elements is `10+10i`
11.	Real part is in the form of a mountain (first the values increase, then they decrease). (e.g. `1-i, 2+6i, 4-67i, 90+3i, 80-7i, 76+i, 43-12i, 3`)
12.	Both real and imaginary parts can be written using the same base 10 digits (e.g. `1+3i, 31i, 33+i, 111, 11-313i`)
