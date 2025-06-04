// instructor.cpp
#include <iostream>
#include <fstream>
#include "instructor.h"
#include "announcement_update.cpp"
using namespace std;

void instructorPanel(vector<Course>& courses, const string &username) {
    int choice;
    do {
        cout << "\n--- Instructor Menu ---" << endl;
        cout << "1. View your courses" << endl;
        cout << "2. Add grades for students" << endl;
        cout << "3. View enrolled students" << endl;
        cout << "4. Update course information" << endl;
        cout << "5. View/Send announcements" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                viewInstructorCourses(courses, username);
                break;
            case 2:
                addGrades(courses, username);
                break;
            case 3:
                viewEnrolledStudents(courses, username);
                break;
            case 4:
                updateCourseInformation(courses, username);
                break;
            case 5:
                viewSendAnnouncements(courses, username);
                break;
            case 6:
                cout << "Exiting Instructor Menu." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 6);
}

void viewInstructorCourses(const vector<Course>& courses, const string &instructor) {
    bool found = false;
    for (const auto& course : courses) {
        if (course.instructor == instructor) {
            cout << "Title: " << course.title << ", Capacity: " << course.capacity
                 << ", Enrolled: " << course.enrolled << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "No courses found for you." << endl;
    }
}

void addGrades(vector<Course>& courses, const string &instructor) {
    string title;
    cout << "Enter the course title to add grades: ";
    getline(cin, title);

    vector<string> validGrades = {"A", "A-", "B+", "B", "B-", "C+", "C", "C-", "D", "F"};

    for (auto& course : courses) {
        if (course.title == title && course.instructor == instructor) {
            // Display all students with numbering
            int count = 1;
            cout << "Students enrolled in " << course.title << ":\n";
            for (auto& student : course.students) {
                cout << count << ". " << student.name << "\n";
                count++;
            }

            // Now proceed to input grades for each student
            for (auto &student : course.students) {
                string grade;
                while (true) {
                    cout << "Enter grade for " << student.name << " (" << student.rollNumber << "): ";
                    cin >> grade;

                    bool isValid = false;
                    for (const string& g : validGrades) {
                        if (grade == g) {
                            isValid = true;
                            break;
                        }
                    }

                    if (isValid) {
                        student.grade = grade;
                        break;
                    } else {
                        cout << "❌ Invalid grade. Valid grades are: A, A-, B+, B, B-, C+, C, C-, D, F\n";
                    }
                }
            }
            cin.ignore();
            cout << "✅ Grades added successfully.\n";
            return;
        }
    }

    cout << "❌ Course not found or you're not authorized.\n";
}


void viewEnrolledStudents(const vector<Course>& courses, const string &instructor) {
    string title;
    cout << "Enter course title: ";
    getline(cin, title);

    for (const auto& course : courses) {
        if (course.title == title && course.instructor == instructor) {
            cout << "\n--- Enrolled Students ---" << endl;
            for (const auto &student : course.students) {
                cout << "Name: " << student.name << ", Roll Number: " << student.rollNumber
                     << ", Grade: " << student.grade << endl;
            }
            return;
        }
    }
    cout << "Course not found or you're not authorized." << endl;
}

void updateCourseInformation(vector<Course>& courses, const string &instructor) {
    string title;
    cout << "Enter course title: ";
    getline(cin, title);

    for (auto& course : courses) {
        if (course.title == title && course.instructor == instructor) {
            cout << "Enter new title: ";
            getline(cin, course.title);
            cout << "Enter new capacity: ";
            cin >> course.capacity;
            cin.ignore();
            cout << "Course updated successfully." << endl;
            return;
        }
    }
    cout << "Course not found or you're not authorized." << endl;
}

// void viewSendAnnouncements() {
//     cout << "\n--- Update Announcements ---\n";
//     cout << "Enter new announcements (end input with a single '.' on a new line):\n";

//     string line, newAnnouncement;
//     cin.ignore();  // clear input buffer before getline loop

//     while (true) {
//         getline(cin, line);
//         if (line == ".") break;
//         newAnnouncement += line + "\n";
//     }

//     if (!newAnnouncement.empty()) {
//         announcements = newAnnouncement;
//         cout << "✅ Announcements updated successfully.\n";
//     } else {
//         cout << "No changes made to announcements.\n";
//     }
// }

