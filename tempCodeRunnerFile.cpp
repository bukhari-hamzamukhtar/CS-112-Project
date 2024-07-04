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

class Course {
public:
    string title;
    string instructor;
    int capacity;
    int enrolled;
    vector<string> announcements;
    vector<string> articles;
    vector<string> assignments;
    vector<string> practiceQuizzes;
    vector<string> quizzes;
};

// Function to display the main menu
void displayMainMenu() {
    cout << "\n--- Main Menu ---" << endl;
    cout << "1. Sign Up" << endl;
    cout << "2. Log In" << endl;
    cout << "3. Exit" << endl;
}

// Function to display the admin menu
void displayAdminMenu() {
    cout << "\n--- Admin Menu ---" << endl;
    cout << "1. Add a user" << endl;
    cout << "2. Remove a user" << endl;
    cout << "3. Create a course" << endl;
    cout << "4. Assign a course to an instructor" << endl;
    cout << "5. Change course capacity" << endl;
    cout << "6. Display user accounts" << endl;
    cout << "7. Display course listings" << endl;
    cout << "8. Manage salaries" << endl;
    cout << "9. Log Out" << endl;
}

// Function to display the instructor menu
void displayInstructorMenu() {
    cout << "\n--- Instructor Menu ---" << endl;
    cout << "1. View courses" << endl;
    cout << "2. Add grades" << endl;
    cout << "3. View enrolled students" << endl;
    cout << "4. Update course information" << endl;
    cout << "5. Manage announcements" << endl;
    cout << "6. Log Out" << endl;
}

// Function to load users from a file
void loadUsers(User users[], int &userCount) {
    ifstream file("users.txt");
    if (file.is_open()) {
        while (!file.eof() && userCount < 10) {
            file >> users[userCount].username >> users[userCount].password >> users[userCount].userType;
            userCount++;
        }
        file.close();
    }
}

// Function to save users to a file
void saveUsers(const User users[], int userCount) {
    ofstream file("users.txt");
    if (file.is_open()) {
        for (int i = 0; i < userCount; ++i) {
            file << users[i].username << " " << users[i].password << " " << users[i].userType << endl;
        }
        file.close();
    }
}

// Function to load courses from a file
void loadCourses(Course courses[], int &courseCount) {
    ifstream file("courses.txt");
    if (file.is_open()) {
        while (!file.eof() && courseCount < 10) {
            file >> courses[courseCount].title >> courses[courseCount].instructor >> courses[courseCount].capacity >> courses[courseCount].enrolled;
            courseCount++;
        }
        file.close();
    }
}

// Function to save courses to a file
void saveCourses(const Course courses[], int courseCount) {
    ofstream file("courses.txt");
    if (file.is_open()) {
        for (int i = 0; i < courseCount; ++i) {
            file << courses[i].title << " " << courses[i].instructor << " " << courses[i].capacity << " " << courses[i].enrolled << endl;
        }
        file.close();
    }
}

// Function to add a user
void addUser(User users[], int &userCount) {
    if (userCount >= 10) {
        cout << "Cannot add more users. Maximum limit of 10 users reached." << endl;
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
    saveUsers(users, userCount); // Save users to file
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
            saveUsers(users, userCount); // Save users to file
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
    cout << "Enter capacity: ";
    cin >> newCourse.capacity;
    newCourse.enrolled = 0;
    cin.ignore(); // Clear the input buffer

    courses[courseCount++] = newCourse;
    saveCourses(courses, courseCount); // Save courses to file
    cout << "Course created successfully." << endl;
}

// Function to assign a course to an instructor
void assignCourseToInstructor(Course courses[], int courseCount, User users[], int userCount) {
    string courseTitle, instructorUsername;
    cout << "Enter course title: ";
    getline(cin, courseTitle);
    cout << "Enter instructor username: ";
    getline(cin, instructorUsername);

    for (int i = 0; i < userCount; ++i) {
        if (users[i].username == instructorUsername && users[i].userType == "instructor") {
            for (int j = 0; j < courseCount; ++j) {
                if (courses[j].title == courseTitle) {
                    courses[j].instructor = instructorUsername;
                    saveCourses(courses, courseCount); // Save courses to file
                    cout << "Instructor assigned to course successfully." << endl;
                    return;
                }
            }
            cout << "Course not found." << endl;
            return;
        }
    }
    cout << "Instructor not found." << endl;
}

// Function to change course capacity
void changeCourseCapacity(Course courses[], int courseCount) {
    string courseTitle;
    int newCapacity;
    cout << "Enter course title: ";
    getline(cin, courseTitle);
    cout << "Enter new capacity: ";
    cin >> newCapacity;

    for (int i = 0; i < courseCount; ++i) {
        if (courses[i].title == courseTitle) {
            courses[i].capacity = newCapacity;
            saveCourses(courses, courseCount); // Save courses to file
            cout << "Course capacity updated successfully." << endl;
            cin.ignore(); // Clear the input buffer
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

// Function to manage instructor salaries
void manageSalaries() {
    cout << "This feature is not yet implemented." << endl;
}

// Function for instructor to view courses
void viewCourses(const Course courses[], int courseCount, const string &instructorUsername) {
    cout << "\n--- Your Courses ---" << endl;
    for (int i = 0; i < courseCount; ++i) {
        if (courses[i].instructor == instructorUsername) {
            cout << "Title: " << courses[i].title << ", Capacity: " << courses[i].capacity << ", Enrolled: " << courses[i].enrolled << endl;
        }
    }
}

// Function for instructor to add grades
void addGrades(Course courses[], int courseCount, const string &instructorUsername) {
    cout << "This feature is not yet implemented." << endl;
}

// Function for instructor to view enrolled students
void viewEnrolledStudents(const Course courses[], int courseCount, const string &instructorUsername) {
    cout << "\n--- Enrolled Students ---" << endl;
    for (int i = 0; i < courseCount; ++i) {
        if (courses[i].instructor == instructorUsername) {
            cout << "Course: " << courses[i].title << ", Enrolled: " << courses[i].enrolled << endl;
        }
    }
}

// Function for instructor to update course information
void updateCourseInfo(Course courses[], int courseCount, const string &instructorUsername) {
    string courseTitle;
    cout << "Enter course title: ";
    getline(cin, courseTitle);

    for (int i = 0; i < courseCount; ++i) {
        if (courses[i].title == courseTitle && courses[i].instructor == instructorUsername) {
            int updateChoice;
            cout << "1. Add article\n2. Add assignment\n3. Add practice quiz\n4. Add quiz\nEnter your choice: ";
            cin >> updateChoice;
            cin.ignore(); // Clear the input buffer
            string content;
            cout << "Enter content: ";
            getline(cin, content);

            switch (updateChoice) {
                case 1:
                    courses[i].articles.push_back(content);
                    break;
                case 2:
                    courses[i].assignments.push_back(content);
                    break;
                case 3:
                    courses[i].practiceQuizzes.push_back(content);
                    break;
                case 4:
                    courses[i].quizzes.push_back(content);
                    break;
                default:
                    cout << "Invalid choice." << endl;
                    return;
            }
            saveCourses(courses, courseCount); // Save courses to file
            cout << "Course information updated successfully." << endl;
            return;
        }
    }
    cout << "Course not found or you are not the instructor for this course." << endl;
}

// Function for instructor to manage announcements
void manageAnnouncements(Course courses[], int courseCount, const string &instructorUsername) {
    string courseTitle;
    cout << "Enter course title: ";
    getline(cin, courseTitle);

    for (int i = 0; i < courseCount; ++i) {
        if (courses[i].title == courseTitle && courses[i].instructor == instructorUsername) {
            string announcement;
            cout << "Enter announcement: ";
            getline(cin, announcement);
            courses[i].announcements.push_back(announcement);
            saveCourses(courses, courseCount); // Save courses to file
            cout << "Announcement added successfully." << endl;
            return;
        }
    }
    cout << "Course not found or you are not the instructor for this course." << endl;
}

int main() {
    const int max_users = 10;
    const int max_courses = 10;
    User users[max_users];
    Course courses[max_courses];
    int userCount = 0;
    int courseCount = 0;

    // Load data from files
    loadUsers(users, userCount);
    loadCourses(courses, courseCount);

    int mainChoice;

    do {
        displayMainMenu();
        cout << "Enter your choice: ";
        cin >> mainChoice;
        cin.ignore(); // Clear the input buffer

        if (mainChoice == 1) { // Sign Up
            addUser(users, userCount);
        } else if (mainChoice == 2) { // Log In
            string username, password;
            cout << "Enter username: ";
            getline(cin, username);
            cout << "Enter password: ";
            getline(cin, password);

            bool userFound = false;
            for (int i = 0; i < userCount; ++i) {
                if (users[i].username == username && users[i].password == password) {
                    userFound = true;
                    if (users[i].userType == "administrator") {
                        int adminChoice;
                        do {
                            displayAdminMenu();
                            cout << "Enter your choice: ";
                            cin >> adminChoice;
                            cin.ignore(); // Clear the input buffer

                            switch (adminChoice) {
                                case 1:
                                    addUser(users, userCount);
                                    break;
                                case 2:
                                    removeUser(users, userCount);
                                    break;
                                case 3:
                                    createCourse(courses, courseCount);
                                    break;
                                case 4:
                                    assignCourseToInstructor(courses, courseCount, users, userCount);
                                    break;
                                case 5:
                                    changeCourseCapacity(courses, courseCount);
                                    break;
                                case 6:
                                    displayUsers(users, userCount);
                                    break;
                                case 7:
                                    displayCourses(courses, courseCount);
                                    break;
                                case 8:
                                    manageSalaries();
                                    break;
                                case 9:
                                    cout << "Logging out..." << endl;
                                    break;
                                default:
                                    cout << "Invalid choice. Please enter a number between 1 and 9." << endl;
                            }
                        } while (adminChoice != 9);
                    } else if (users[i].userType == "instructor") {
                        int instructorChoice;
                        do {
                            displayInstructorMenu();
                            cout << "Enter your choice: ";
                            cin >> instructorChoice;
                            cin.ignore(); // Clear the input buffer

                            switch (instructorChoice) {
                                case 1:
                                    viewCourses(courses, courseCount, username);
                                    break;
                                case 2:
                                    addGrades(courses, courseCount, username);
                                    break;
                                case 3:
                                    viewEnrolledStudents(courses, courseCount, username);
                                    break;
                                case 4:
                                    updateCourseInfo(courses, courseCount, username);
                                    break;
                                case 5:
                                    manageAnnouncements(courses, courseCount, username);
                                    break;
                                case 6:
                                    cout << "Logging out..." << endl;
                                    break;
                                default:
                                    cout << "Invalid choice. Please enter a number between 1 and 6." << endl;
                            }
                        } while (instructorChoice != 6);
                    } else {
                        cout << "Invalid user type." << endl;
                    }
                    break;
                }
            }

            if (!userFound) {
                cout << "Invalid username or password. Please try again." << endl;
            }
        } else if (mainChoice != 3) {
            cout << "Invalid choice. Please enter 1, 2, or 3." << endl;
        }
    } while (mainChoice != 3);

    cout << "Exiting program. Goodbye!" << endl;
    return 0;
}
