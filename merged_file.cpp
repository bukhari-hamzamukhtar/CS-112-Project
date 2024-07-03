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
    vector<string> announcements;
};

// Function to display the menu for administrators
void displayAdminMenu() {
    cout << "\n--- Administrator Menu ---" << endl;
    cout << "1. Add a user" << endl;
    cout << "2. Remove a user" << endl;
    cout << "3. Create a course" << endl;
    cout << "4. Assign a course to an instructor" << endl;
    cout << "5. Change course capacity" << endl;
    cout << "6. Display user accounts" << endl;
    cout << "7. Display course listings" << endl;
    cout << "8. Exit" << endl;
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
            outFile << courses[i].announcements.size() << endl;
            for (const auto& announcement : courses[i].announcements) {
                outFile << announcement << endl;
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
            int announcementCount;
            inFile >> announcementCount;
            inFile.ignore();
            for (int k = 0; k < announcementCount; ++k) {
                string announcement;
                getline(inFile, announcement);
                courses[i].announcements.push_back(announcement);
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

// Function to create a course
void createCourse(Course courses[], int &courseCount) {
    if (courseCount >= 10) {
        cout << "Cannot add more courses. Maximum limit reached." << endl;
        return;
    }

    Course newCourse;
    cout << "Enter course title: ";
    getline(cin, newCourse.title);
    cout << "Enter course capacity: ";
    cin >> newCourse.capacity;
    newCourse.enrolled = 0;
    newCourse.instructor = "Unassigned";
    courses[courseCount++] = newCourse;
    saveCourses(courses, courseCount);
    cout << "Course created successfully." << endl;
    cin.ignore(); // Clear the input buffer
}

// Function to assign a course to an instructor
void assignCourseToInstructor(Course courses[], int courseCount, User users[], int userCount) {
    string courseTitle, instructorUsername;
    cout << "Enter course title: ";
    getline(cin, courseTitle);
    cout << "Enter instructor username: ";
    getline(cin, instructorUsername);

    for (int i = 0; i < courseCount; ++i) {
        if (courses[i].title == courseTitle) {
            for (int j = 0; j < userCount; ++j) {
                if (users[j].username == instructorUsername && users[j].userType == "instructor") {
                    courses[i].instructor = instructorUsername;
                    saveCourses(courses, courseCount);
                    cout << "Course " << courseTitle << " assigned to instructor " << instructorUsername << " successfully." << endl;
                    return;
                }
            }
            cout << "Instructor not found or invalid user type." << endl;
            return;
        }
    }
    cout << "Course not found." << endl;
}

// Function to change course capacity
void changeCourseCapacity(Course courses[], int courseCount) {
    string courseTitle;
    cout << "Enter course title: ";
    getline(cin, courseTitle);
    for (int i = 0; i < courseCount; ++i) {
        if (courses[i].title == courseTitle) {
            cout << "Enter new capacity: ";
            cin >> courses[i].capacity;
            cin.ignore();
            saveCourses(courses, courseCount); // Save courses to file
            cout << "Course capacity updated successfully." << endl;
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
            cout << "Username: " << users[i].username << ", Password: " << users[i].password << ", User Type: " << users[i].userType << endl;
        }
    }
}

// Function to display course listings
void displayCourses(const Course courses[], int courseCount) {
    cout << "\n--- Course Listings ---" << endl;
    if (courseCount == 0) {
        cout << "No courses found." << endl;
    } else {
        for (int i = 0; i < courseCount; ++i) {
            cout << "Course Title: " << courses[i].title << ", Instructor: " << courses[i].instructor << ", Capacity: " << courses[i].capacity << ", Enrolled: " << courses[i].enrolled << endl;
            for (const auto& announcement : courses[i].announcements) {
                cout << " - Announcement: " << announcement << endl;
            }
        }
    }
}

// Function for instructor to view their courses
void viewInstructorCourses(const Course courses[], int courseCount, const string &instructorUsername) {
    cout << "\n--- Your Courses ---" << endl;
    bool found = false;
    for (int i = 0; i < courseCount; ++i) {
        if (courses[i].instructor == instructorUsername) {
            cout << "Course Title: " << courses[i].title << ", Capacity: " << courses[i].capacity << ", Enrolled: " << courses[i].enrolled << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "You are not assigned to any courses." << endl;
    }
}

// Function to add grades for students
void addGrades(Course courses[], int courseCount, const string &instructorUsername) {
    string courseTitle;
    cout << "Enter course title to add grades: ";
    getline(cin, courseTitle);
    for (int i = 0; i < courseCount; ++i) {
        if (courses[i].title == courseTitle && courses[i].instructor == instructorUsername) {
            for (auto &student : courses[i].students) {
                cout << "Enter grade for " << student.name << " (Roll Number: " << student.rollNumber << "): ";
                cin >> student.grade;
            }
            cin.ignore(); // Clear the input buffer
            saveCourses(courses, courseCount); // Save courses to file
            cout << "Grades added successfully." << endl;
            return;
        }
    }
    cout << "Course not found or you are not the instructor for this course." << endl;
}

// Function to view enrolled students
void viewEnrolledStudents(const Course courses[], int courseCount, const string &instructorUsername) {
    string courseTitle;
    cout << "Enter course title to view enrolled students: ";
    getline(cin, courseTitle);
    for (int i = 0; i < courseCount; ++i) {
        if (courses[i].title == courseTitle && courses[i].instructor == instructorUsername) {
            cout << "\n--- Enrolled Students ---" << endl;
            for (const auto &student : courses[i].students) {
                cout << "Name: " << student.name << ", Roll Number: " << student.rollNumber << ", Grade: " << student.grade << endl;
            }
            return;
        }
    }
    cout << "Course not found or you are not the instructor for this course." << endl;
}

// Function to update course information
void updateCourseInfo(Course courses[], int courseCount, const string &instructorUsername) {
    string courseTitle;
    cout << "Enter course title to update information: ";
    getline(cin, courseTitle);
    for (int i = 0; i < courseCount; ++i) {
        if (courses[i].title == courseTitle && courses[i].instructor == instructorUsername) {
            cout << "Enter new capacity: ";
            cin >> courses[i].capacity;
            cin.ignore(); // Clear the input buffer
            saveCourses(courses, courseCount); // Save courses to file
            cout << "Course information updated successfully." << endl;
            return;
        }
    }
    cout << "Course not found or you are not the instructor for this course." << endl;
}

// Function to view and send announcements
void viewSendAnnouncements(Course courses[], int courseCount, const string &instructorUsername) {
    string courseTitle;
    cout << "Enter course title to view/send announcements: ";
    getline(cin, courseTitle);
    for (int i = 0; i < courseCount; ++i) {
        if (courses[i].title == courseTitle && courses[i].instructor == instructorUsername) {
            cout << "\n--- Announcements ---" << endl;
            for (const auto &announcement : courses[i].announcements) {
                cout << "- " << announcement << endl;
            }
            cout << "Do you want to add a new announcement? (yes/no): ";
            string choice;
            getline(cin, choice);
            if (choice == "yes") {
                string newAnnouncement;
                cout << "Enter new announcement: ";
                getline(cin, newAnnouncement);
                courses[i].announcements.push_back(newAnnouncement);
                saveCourses(courses, courseCount); // Save courses to file
                cout << "Announcement added successfully." << endl;
            }
            return;
        }
    }
    cout << "Course not found or you are not the instructor for this course." << endl;
}

// Function to sign up a new user
void signUp(User users[], int &userCount, Course courses[], int courseCount) {
    addUser(users, userCount);
    cout << "Returning to main menu for login." << endl;
}

// Function to log in a user
int logIn(User users[], int userCount) {
    string username, password;
    cout << "Enter username: ";
    getline(cin, username);
    cout << "Enter password: ";
    getline(cin, password);

    for (int i = 0; i < userCount; ++i) {
        if (users[i].username == username && users[i].password == password) {
            return i; // Return the index of the logged-in user
        }
    }
    return -1; // Return -1 if login fails
}

int main() {
    User users[10];
    Course courses[10];
    int userCount = 0;
    int courseCount = 0;

    loadUsers(users, userCount);
    loadCourses(courses, courseCount);

    while (true) {
        cout << "\n--- Main Menu ---" << endl;
        cout << "1. Sign Up" << endl;
        cout << "2. Log In" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter choice: ";
        int choice;
        cin >> choice;
        cin.ignore(); // Clear the input buffer

        if (choice == 1) {
            signUp(users, userCount, courses, courseCount);
        } else if (choice == 2) {
            int userIndex = logIn(users, userCount);
            if (userIndex == -1) {
                cout << "Invalid username or password. Please try again." << endl;
            } else {
                if (users[userIndex].userType == "administrator") {
                    while (true) {
                        displayAdminMenu();
                        cout << "Enter choice: ";
                        int adminChoice;
                        cin >> adminChoice;
                        cin.ignore(); // Clear the input buffer
                        if (adminChoice == 1) {
                            addUser(users, userCount);
                        } else if (adminChoice == 2) {
                            removeUser(users, userCount);
                        } else if (adminChoice == 3) {
                            createCourse(courses, courseCount);
                        } else if (adminChoice == 4) {
                            assignCourseToInstructor(courses, courseCount, users, userCount);
                        } else if (adminChoice == 5) {
                            changeCourseCapacity(courses, courseCount);
                        } else if (adminChoice == 6) {
                            displayUsers(users, userCount);
                        } else if (adminChoice == 7) {
                            displayCourses(courses, courseCount);
                        } else if (adminChoice == 8) {
                            break;
                        } else {
                            cout << "Invalid choice. Please try again." << endl;
                        }
                    }
                } else if (users[userIndex].userType == "instructor") {
                    while (true) {
                        displayInstructorMenu();
                        cout << "Enter choice: ";
                        int instructorChoice;
                        cin >> instructorChoice;
                        cin.ignore(); // Clear the input buffer
                        if (instructorChoice == 1) {
                            viewInstructorCourses(courses, courseCount, users[userIndex].username);
                        } else if (instructorChoice == 2) {
                            addGrades(courses, courseCount, users[userIndex].username);
                        } else if (instructorChoice == 3) {
                            viewEnrolledStudents(courses, courseCount, users[userIndex].username);
                        } else if (instructorChoice == 4) {
                            updateCourseInfo(courses, courseCount, users[userIndex].username);
                        } else if (instructorChoice == 5) {
                            viewSendAnnouncements(courses, courseCount, users[userIndex].username);
                        } else if (instructorChoice == 6) {
                            break;
                        } else {
                            cout << "Invalid choice. Please try again." << endl;
                        }
                    }
                }
            }
        } else if (choice == 3) {
            break;
        } else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
