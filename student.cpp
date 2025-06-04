// student.cpp
#include "student.h"
#include "instructor.h"
#include <iostream>

using namespace std;

void viewAllCourses(const vector<Course>& courses) {
    cout << "\n--- All Available Courses ---\n";
    for (const auto& course : courses) {
        cout << "Title: " << course.title << ", Instructor: " << course.instructor
             << ", Capacity: " << course.capacity << ", Enrolled: " << course.enrolled << "\n";
    }
}

void enrollInCourse(vector<Course>& courses, const string& studentUsername) {
    string title;
    cout << "Enter course title to enroll: ";
    getline(cin, title);
    for (auto& course : courses) {
        if (course.title == title) {
            for (const auto& s : course.students) {
                if (s.name == studentUsername) {
                    cout << "You are already enrolled in this course.\n";
                    return;
                }
            }
            if (course.enrolled >= course.capacity) {
                cout << "Course is full. Cannot enroll.\n";
                return;
            }
            Student newStudent;
            newStudent.name = studentUsername;
            cout << "Enter your roll number: ";
            getline(cin, newStudent.rollNumber);
            newStudent.grade = 0.0;
            course.students.push_back(newStudent);
            course.enrolled++;
            cout << "✅ Enrolled successfully in " << title << "\n";
            return;
        }
    }
    cout << "❌ Course not found.\n";
}

void viewMyCourses(const vector<Course>& courses, const string& studentUsername) {
    cout << "\n--- Your Enrolled Courses ---\n";
    bool found = false;
    for (const auto& course : courses) {
        for (const auto& s : course.students) {
            if (s.name == studentUsername) {
                cout << "Title: " << course.title << ", Instructor: " << course.instructor << "\n";
                found = true;
                break;
            }
        }
    }
    if (!found) cout << "You are not enrolled in any courses.\n";
}

void submitAssignment(const string& studentUsername) {
    string courseTitle, content;
    cout << "Enter course title for the assignment: ";
    getline(cin, courseTitle);
    cout << "Enter assignment content: ";
    getline(cin, content);
    cout << "Assignment submitted by " << studentUsername << " for " << courseTitle << "\nContent: " << content << "\n";
}

void takeExam() {
    cout << "Exam completed. Good luck with your results!\n";
}

void studentPanel(vector<Course>& courses, const string& studentUsername) {
    string choice;
    do {
        cout << "\n--- Student Menu ---\n";
        cout << "1. View All Courses\n";
        cout << "2. Enroll in a Course\n";
        cout << "3. View My Courses\n";
        cout << "4. Submit Assignment\n";
        cout << "5. Take Exam\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        getline(cin, choice);

        if (choice == "1") viewAllCourses(courses);
        else if (choice == "2") enrollInCourse(courses, studentUsername);
        else if (choice == "3") viewMyCourses(courses, studentUsername);
        else if (choice == "4") submitAssignment(studentUsername);
        else if (choice == "5") takeExam();
        else if (choice == "6") cout << "Exiting student panel...\n";
        else cout << "Invalid choice. Try again.\n";
    } while (choice != "6");
}
