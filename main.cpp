#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "instructor.h"
#include "student.h"
#include "announcement_view.cpp"
using namespace std;

class User {
public:
    string username;
    string password;
    string userType;
};

void displayMenu() {
    cout << "\n--- Admin Menu ---" << endl;
    cout << "1. Add a user" << endl;
    cout << "2. Remove a user" << endl;
    cout << "3. Add a course" << endl;
    cout << "4. Remove a course" << endl;
    cout << "5. Display user accounts" << endl;
    cout << "6. Display course listings" << endl;
    cout << "7. Exit" << endl;
}

void saveUsers(const User users[], int userCount) {
    ofstream outFile("users.txt");
    if (outFile.is_open()) {
        outFile << userCount << endl;
        for (int i = 0; i < userCount; ++i) {
            outFile << users[i].username << endl;
            outFile << users[i].password << endl;
            outFile << users[i].userType << endl;
        }
        outFile.close();
    }
}

void loadUsers(User users[], int &userCount) {
    ifstream inFile("users.txt");
    if (inFile.is_open()) {
        inFile >> userCount;
        inFile.ignore();
        for (int i = 0; i < userCount; ++i) {
            getline(inFile, users[i].username);
            getline(inFile, users[i].password);
            getline(inFile, users[i].userType);
        }
        inFile.close();
    }
}

void saveCourses(const vector<Course>& courses) {
    ofstream outFile("courses.txt");
    if (outFile.is_open()) {
        outFile << courses.size() << endl;
        for (const auto& course : courses) {
            outFile << course.title << endl;
            outFile << course.instructor << endl;
            outFile << course.capacity << endl;
            outFile << course.enrolled << endl;
            outFile << course.students.size() << endl;
            for (const auto& student : course.students) {
                outFile << student.name << endl;
                outFile << student.rollNumber << endl;
                outFile << student.grade << endl;
            }
        }
        outFile.close();
    }
}

void loadCourses(vector<Course>& courses) {
    ifstream inFile("courses.txt");
    if (inFile.is_open()) {
        int courseCount;
        inFile >> courseCount;
        inFile.ignore();
        for (int i = 0; i < courseCount; ++i) {
            Course course;
            getline(inFile, course.title);
            getline(inFile, course.instructor);
            inFile >> course.capacity >> course.enrolled;
            int studentCount;
            inFile >> studentCount;
            inFile.ignore();
            for (int j = 0; j < studentCount; ++j) {
                Student student;
                getline(inFile, student.name);
                getline(inFile, student.rollNumber);
                inFile >> student.grade;
                inFile.ignore();
                course.students.push_back(student);
            }
            courses.push_back(course);
        }
        inFile.close();
    }
}

void addUser(User users[], int &userCount) {
    if (userCount >= 10) {
        cout << "Cannot add more users. Limit reached." << endl;
        return;
    }

    string newUsername;
    cout << "Enter username: ";
    getline(cin, newUsername);

    // Check if username already exists
    for (int i = 0; i < userCount; ++i) {
        if (users[i].username == newUsername) {
            cout << "❌ Username already exists. Try another.\n";
            return;
        }
    }

    string password, userType;
    cout << "Enter password: ";
    getline(cin, password);

    cout << "Enter user type (Instructor/Student): ";
    getline(cin, userType);

    if (userType != "Instructor" && userType != "Student") {
        cout << "❌ Only 'Instructor' or 'Student' signups allowed.\n";
        return;
    }

    User newUser{newUsername, password, userType};
    users[userCount++] = newUser;
    saveUsers(users, userCount);

    cout << "✅ " << userType << " registered successfully.\n";
}



void removeUser(User users[], int &userCount) {
    string username;
    cout << "Enter username to remove: ";
    getline(cin, username);
    for (int i = 0; i < userCount; ++i) {
        if (users[i].username == username) {
            for (int j = i; j < userCount - 1; ++j) users[j] = users[j + 1];
            userCount--;
            saveUsers(users, userCount);
            cout << "User removed successfully." << endl;
            return;
        }
    }
    cout << "User not found." << endl;
}

void addCourse(vector<Course>& courses, const User users[], int userCount) {
    Course newCourse;
    cout << "Enter course title: ";
    getline(cin, newCourse.title);

    string instructorUsername;
    bool validInstructor = false;

    // Ask for instructor username and validate
    do {
        cout << "Enter instructor username: ";
        getline(cin, instructorUsername);

        for (int i = 0; i < userCount; ++i) {
            if (users[i].username == instructorUsername && users[i].userType == "Instructor") {
                validInstructor = true;
                break;
            }
        }

        if (!validInstructor) {
            cout << "❌ Instructor not found. Please enter a valid instructor username from the system.\n";
        }

    } while (!validInstructor);

    newCourse.instructor = instructorUsername;

    cout << "Enter capacity: ";
    cin >> newCourse.capacity;
    cin.ignore();
    newCourse.enrolled = 0;

    courses.push_back(newCourse);
    saveCourses(courses);

    cout << "✅ Course added successfully with instructor: " << instructorUsername << "\n";
}


void removeCourse(vector<Course>& courses) {
    string title;
    cout << "Enter course title to remove: ";
    getline(cin, title);
    for (auto it = courses.begin(); it != courses.end(); ++it) {
        if (it->title == title) {
            courses.erase(it);
            saveCourses(courses);
            cout << "Course removed." << endl;
            return;
        }
    }
    cout << "Course not found." << endl;
}

void displayUsers(const User users[], int userCount) {
    for (int i = 0; i < userCount; ++i) {
        cout << users[i].username << " (" << users[i].userType << ")" << endl;
    }
}

void displayCourses(const vector<Course>& courses) {
    for (const auto& course : courses) {
        cout << course.title << " - " << course.instructor << endl;
    }
}

int main() {
    const int max_users = 10;
    User users[max_users];
    vector<Course> courses;
    int userCount = 0;

    loadUsers(users, userCount);
    loadCourses(courses);

    while (true) {
        cout << "Sign up? (y/n): ";
        char signup;
        cin >> signup;
        cin.ignore();

        if (signup == 'y' || signup == 'Y') {
            addUser(users, userCount);
        }

        string username, password;
        cout << "Enter username: ";
        getline(cin, username);
        cout << "Enter password: ";
        getline(cin, password);

        bool loggedIn = false;

        for (int i = 0; i < userCount; ++i) {
            if (users[i].username == username && users[i].password == password) {
                loggedIn = true;

                if (users[i].userType == "Admin") {
                    cout << "Welcome Admin!" << endl;
                    int choice;
                    do {
                        displayMenu();
                        cout << "Enter choice: ";
                        cin >> choice;
                        cin.ignore();
                        switch (choice) {
                            case 1: addUser(users, userCount); break;
                            case 2: removeUser(users, userCount); break;
                            case 3: addCourse(courses, users, userCount); break;
                            case 4: removeCourse(courses); break;
                            case 5: displayUsers(users, userCount); break;
                            case 6: displayCourses(courses); break;
                            case 7: cout << "Logging out...\n"; break;
                            default: cout << "Invalid choice.\n";
                        }
                    } while (choice != 7);

                } else if (users[i].userType == "Instructor") {
                    cout << "Welcome Instructor!" << endl;
                    instructorPanel(courses, username);
                    cout << "Logging out...\n";

                } else if (users[i].userType == "Student") {
                    cout << "Welcome Student!" << endl << endl;
                    viewAnnouncements(courses, username);
                    cout << endl;
                    studentPanel(courses, username);
                    cout << "Logging out...\n";

                } else {
                    cout << "User type not supported." << endl;
                }

                saveUsers(users, userCount);
                saveCourses(courses);
                break; 
            }
        }

        if (!loggedIn) {
            cout << "Invalid credentials.\n";
        }

        cout << "Returning to login screen...\n\n";
    }

    return 0;
}
