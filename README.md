# CS112 LMS Project (OOP-based)

A basic console-based Learning Management System (LMS) written in C++ for the CS112 Object-Oriented Programming course.  
It features a role-based login system for Admins, Instructors, and Students with persistent file handling.

> GUI not implemented yet — purely CLI-based.

---

## Versions

### v1.0 – Legacy Version
- Located at: `./legacy/lms.cpp`
- Single `.cpp` file with everything hardcoded
- Good for understanding the evolution of the project

### v2.0 – Modular Version (**Current**)
- Modularized into multiple `.cpp` and `.h` files:
  - `main.cpp`, `instructor.cpp`, `student.cpp`, etc.
- File-based storage using `users.txt`, `courses.txt`, and `announcements.txt`

---

## Features

- OOP-based architecture (classes + inheritance)
- Login & Sign-up system (Admin / Instructor / Student)
- Course creation and enrollment
- Instructors can:
  - Add grades
  - View students in their courses
  - Make announcements
- Students can:
  - Enroll in available courses
  - Submit assignments
  - View only their relevant course announcements
- Persistent storage via `.txt` files

---

## Running the Project

### For v2.0:
Run CodeRunner.bat
