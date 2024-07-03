#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class User {
public:
    string username;
    string password;
    string userType; // "administrator" or "instructor"
};

class Student {
public:
    string name;
    string rollNumber;
    float grade;
};

class Course {
public:
    string title;
    string instructor;
    int capacity;
    int enrolled;
    vector<Student> students;
};

// Function to display the menu for administrators
void displayAdminMenu() {
    cout << "\n--- Administrator Menu ---" << endl;
    cout << "1. Add a user" << endl;
    cout << "2. Remove a user" << endl;
    cout << "3. Add a course" << endl;
    cout << "4. Remove a course" << endl;
    cout << "5. Display user accounts" << endl;
    cout << "6. Display course listings" << endl;
    cout << "7. Exit" << endl;
}

// Function to display the menu for instructors
void displayInstructorMenu() {
    cout << "\n--- Instructor Menu ---" << endl;
    cout << "1. View your courses" << endl;
    cout << "2. Add grades for students" << endl;
    cout << "3. View enrolled students" << endl;
    cout << "4. Update course information" << endl;
    cout << "5. View/Send announcements" << endl;
    cout << "6. Exit" << endl;
}

// Function to save users to file
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
    } else {
        cout << "Unable to open file to save users." << endl;
    }
}

// Function to load users from file
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
    } else {
        cout << "Unable to open file to load users." << endl;
    }
}

// Function to save courses to file
void saveCourses(const Course courses[], int courseCount) {
    ofstream outFile("courses.txt");
    if (outFile.is_open()) {
        outFile << courseCount << endl;
        for (int i = 0; i < courseCount; ++i) {
            outFile << courses[i].title << endl;
            outFile << courses[i].instructor << endl;
            outFile << courses[i].capacity << endl;
            outFile << courses[i].enrolled << endl;
            outFile << courses[i].students.size() << endl;
            for (const auto& student : courses[i].students) {
                outFile << student.name << endl;
                outFile << student.rollNumber << endl;
                outFile << student.grade << endl;
            }
        }
        outFile.close();
    } else {
        cout << "Unable to open file to save courses." << endl;
    }
}

// Function to load courses from file
void loadCourses(Course courses[], int &courseCount) {
    ifstream inFile("courses.txt");
    if (inFile.is_open()) {
        inFile >> courseCount;
        inFile.ignore();
        for (int i = 0; i < courseCount; ++i) {
            getline(inFile, courses[i].title);
            getline(inFile, courses[i].instructor);
            inFile >> courses[i].capacity;
            inFile >> courses[i].enrolled;
            int studentCount;
            inFile >> studentCount;
            inFile.ignore();
            for (int j = 0; j < studentCount; ++j) {
                Student student;
                getline(inFile, student.name);
                getline(inFile, student.rollNumber);
                inFile >> student.grade;
                inFile.ignore();
                courses[i].students.push_back(student);
            }
        }
        inFile.close();
    } else {
        cout << "Unable to open file to load courses." << endl;
    }
}

// Function to add a user
void addUser(User users[], int &userCount) {
    if (userCount >= 10) {
        cout << "Cannot add more users. Maximum limit of 10 users has reached." << endl;
        return;
    }

    User newUser;
    cout << "Enter username: ";
    getline(cin, newUser.username);
    cout << "Enter password: ";
    getline(cin, newUser.password);
    cout << "Enter user type (administrator/instructor): ";
    getline(cin, newUser.userType);
    users[userCount++] = newUser;
    saveUsers(users, userCount);
    cout << "User added successfully." << endl;
}

// Function to remove a user
void removeUser(User users[], int &userCount) {
    string username;
    cout << "Enter username of the user to remove: ";
    getline(cin, username);
    for (int i = 0; i < userCount; ++i) {
        if (users[i].username == username) {
            for (int j = i; j < userCount - 1; ++j) {
                users[j] = users[j + 1];
            }
            userCount--;
            saveUsers(users, userCount);
            cout << "User " << username << " removed successfully." << endl;
            return;
        }
    }
    cout << "User not found." << endl;
}

// Function to add a course
void addCourse(Course courses[], int &courseCount) {
    if (courseCount >= 10) {
        cout << "Cannot add more courses. Maximum limit reached." << endl;
        return;
    }

    Course newCourse;
    cout << "Enter course title: ";
    getline(cin, newCourse.title);
    cout << "Enter instructor: ";
    getline(cin, newCourse.instructor);
    cout << "Enter capacity: ";
    cin >> newCourse.capacity;
    newCourse.enrolled = 0;
    courses[courseCount++] = newCourse;
    saveCourses(courses, courseCount);
    cout << "Course added successfully." << endl;
    cin.ignore(); // Clear the input buffer
}

// Function to remove a course
void removeCourse(Course courses[], int &courseCount) {
    string title;
    cout << "Enter the title of the course to remove: ";
    getline(cin, title);
    for (int i = 0; i < courseCount; ++i) {
        if (courses[i].title == title) {
            for (int j = i; j < courseCount - 1; ++j) {
                courses[j] = courses[j + 1];
            }
            courseCount--;
            saveCourses(courses, courseCount);
            cout << "Course " << title << " removed successfully." << endl;
            return;
        }
    }
    cout << "Course not found." << endl;
}

// Function to display user accounts
void displayUsers(const User users[], int userCount) {
    cout << "\n--- User Accounts ---" << endl;
    if (userCount == 0) {
        cout << "No user accounts found." << endl;
    } else {
        for (int i = 0; i < userCount; ++i) {
            cout << "Username: " << users[i].username << ", Password: " << users[i].password << ", Type: " << users[i].userType << endl;
        }
    }
}

// Function to display course listings
void displayCourses(const Course courses[], int courseCount) {
    cout << "\n--- Course Listings ---" << endl;
    if (courseCount == 0) {
        cout << "No courses available." << endl;
    } else {
        for (int i = 0; i < courseCount; ++i) {
            cout << "Title: " << courses[i].title << ", Instructor: " << courses[i].instructor << ", Capacity: " << courses[i].capacity << ", Enrolled: " << courses[i].enrolled << endl;
        }
    }
}

// Function to view instructor's courses
void viewInstructorCourses(const Course courses[], int courseCount, const string& instructor) {
    cout << "\n--- Your Courses ---" << endl;
    bool found = false;
    for (int i = 0; i < courseCount; ++i) {
        if (courses[i].instructor == instructor) {
            cout << "Title: " << courses[i].title << ", Capacity: " << courses[i].capacity << ", Enrolled: " << courses[i].enrolled << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "No courses found for you." << endl;
    }
}

// Function to add grades for students
void addGrades(Course courses[], int courseCount, const string& instructor) {
    string courseTitle;
    cout << "Enter the title of the course to add grades: ";
    getline(cin, courseTitle);
    for (int i = 0; i < courseCount; ++i) {
        if (courses[i].title == courseTitle && courses[i].instructor == instructor) {
            for (auto& student : courses[i].students) {
                cout << "Enter grade for " << student.name << " (Roll No: " << student.rollNumber << "): ";
                cin >> student.grade;
            }
            saveCourses(courses, courseCount); // Save courses to file
            cout << "Grades added successfully." << endl;
            return;
        }
    }
    cout << "Course not found or you are not the instructor of this course." << endl;
}

// Function to view enrolled students
void viewEnrolledStudents(const Course courses[], int courseCount, const string& instructor) {
    string courseTitle;
    cout << "Enter the title of the course to view enrolled students: ";
    getline(cin, courseTitle);
    for (int i = 0; i < courseCount; ++i) {
        if (courses[i].title == courseTitle && courses[i].instructor == instructor) {
            cout << "\n--- Enrolled Students ---" << endl;
            for (const auto& student : courses[i].students) {
                cout << "Name: " << student.name << ", Roll Number: " << student.rollNumber << ", Grade: " << student.grade << endl;
            }
            return;
        }
    }
    cout << "Course not found or you are not the instructor of this course." << endl;
}

// Function to update course information
void updateCourseInformation(Course courses[], int courseCount, const string& instructor) {
    string courseTitle;
    cout << "Enter the title of the course to update: ";
    getline(cin, courseTitle);
    for (int i = 0; i < courseCount; ++i) {
        if (courses[i].title == courseTitle && courses[i].instructor == instructor) {
            cout << "Enter new title: ";
            getline(cin, courses[i].title);
            cout << "Enter new capacity: ";
            cin >> courses[i].capacity;
            cin.ignore();
            saveCourses(courses, courseCount); // Save courses to file
            cout << "Course information updated successfully." << endl;
            return;
        }
    }
    cout << "Course not found or you are not the instructor of this course." << endl;
}

// Function to view/send announcements
void viewSendAnnouncements() {
    // This function can be implemented as needed.
    cout << "\n--- Announcements ---" << endl;
    cout << "This feature is not yet implemented." << endl;
}

int main() {
    const int max_users = 10;
    const int max_courses = 10;
    User users[max_users];
    Course courses[max_courses];
    int userCount = 0;
    int courseCount = 0;

    // Load users and courses from files
    loadUsers(users, userCount);
    loadCourses(courses, courseCount);

    string username, password;
    cout << "Enter username: ";
    getline(cin, username);
    cout << "Enter password: ";
    getline(cin, password);

    string userType;
    bool loggedIn = false;

    for (int i = 0; i < userCount; ++i) {
        if (users[i].username == username && users[i].password == password) {
            userType = users[i].userType;
            loggedIn = true;
            break;
        }
    }

    if (!loggedIn) {
        cout << "Invalid username or password." << endl;
        return 0;
    }

    if (userType == "administrator") {
        int choice_admin;
        cout << "Welcome, Administrator!" << endl;
        do {
            displayAdminMenu();
            cout << "Enter your choice: ";
            cin >> choice_admin;
            cin.ignore(); // Clear the input buffer

            switch (choice_admin) {
            case 1:
                addUser(users, userCount);
                break;
            case 2:
                removeUser(users, userCount);
                break;
            case 3:
                addCourse(courses, courseCount);
                break;
            case 4:
                removeCourse(courses, courseCount);
                break;
            case 5:
                displayUsers(users, userCount);
                break;
            case 6:
                displayCourses(courses, courseCount);
                break;
            case 7:
                cout << "Exiting the program." << endl;
                break;
            default:
                cout << "Invalid choice. Please enter a number between 1 and 7." << endl;
            }
        } while (choice_admin != 7);
    } else if (userType == "instructor") {
        int choice_instructor;
        cout << "Welcome, Instructor!" << endl;
        do {
            displayInstructorMenu();
            cout << "Enter your choice: ";
            cin >> choice_instructor;
            cin.ignore(); // Clear the input buffer

            switch (choice_instructor) {
            case 1:
                viewInstructorCourses(courses, courseCount, username);
                break;
            case 2:
                addGrades(courses, courseCount, username);
                break;
            case 3:
                viewEnrolledStudents(courses, courseCount, username);
                break;
            case 4:
                updateCourseInformation(courses, courseCount, username);
                break;
            case 5:
                viewSendAnnouncements();
                break;
            case 6:
                cout << "Exiting the program." << endl;
                break;
            default:
                cout << "Invalid choice. Please enter a number between 1 and 6." << endl;
            }
        } while (choice_instructor != 6);
    } else {
        cout << "Invalid user type." << endl;
    }

    // Save users and courses to files before exiting
    saveUsers(users, userCount);
    saveCourses(courses, courseCount);

    return 0;
}
