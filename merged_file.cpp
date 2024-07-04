#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

class User
{
public:
    string username;
    string password;
    string userType;
};

class Student
{
public:
    string name;
    string rollNumber;
    string grade;
};

class Course
{
public:
    string title;
    string instructor;
    int capacity;
    int enrolled;
    vector<string> announcements;
    vector<Student> students;
    vector<string> articles;
    vector<string> assignments;
    vector<string> practiceQuizzes;
    vector<string> quizzes;
};

// Function to display the main menu
void displayMainMenu()
{
    cout << "\n--- Main Menu ---" << endl;
    cout << "1. Sign Up" << endl;
    cout << "2. Log In" << endl;
    cout << "3. Exit" << endl;
    cout << "Enter choice: ";
}

// Function to display the admin menu
void displayAdminMenu()
{
    cout << "\n--- Admin Menu ---" << endl;
    cout << "1. Add a user" << endl;
    cout << "2. Remove a user" << endl;
    cout << "3. Create a course" << endl;
    cout << "4. Assign instructor to course" << endl;
    cout << "5. Change course capacity" << endl;
    cout << "6. Display user accounts" << endl;
    cout << "7. Display course listings" << endl;
    cout << "8. Manage instructor salaries" << endl;
    cout << "9. Exit to main menu" << endl;
    cout << "Enter choice: ";
}

// Function to display the instructor menu
void displayInstructorMenu()
{
    cout << "\n--- Instructor Menu ---" << endl;
    cout << "1. View your courses" << endl;
    cout << "2. Add grades for students" << endl;
    cout << "3. View enrolled students" << endl;
    cout << "4. Update course information" << endl;
    cout << "5. View and send announcements" << endl;
    cout << "6. Exit to main menu" << endl;
    cout << "Enter choice: ";
}

// Function to save users to a file
void saveUsers(const User users[], int userCount)
{
    ofstream file("users.txt");
    for (int i = 0; i < userCount; ++i)
    {
        file << users[i].username << "," << users[i].password << "," << users[i].userType << endl;
    }
    file.close();
}

// Function to load users from a file
void loadUsers(User users[], int &userCount)
{
    ifstream file("users.txt");
    if (!file.is_open())
    {
        cout << "Error opening users file." << endl;
        return;
    }

    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        getline(ss, users[userCount].username, ',');
        getline(ss, users[userCount].password, ',');
        getline(ss, users[userCount].userType, ',');
        ++userCount;
    }
    file.close();
}

// Function to save courses to a file
void saveCourses(const Course courses[], int courseCount)
{
    ofstream file("courses.txt");
    for (int i = 0; i < courseCount; ++i)
    {
        file << courses[i].title << "," << courses[i].instructor << "," << courses[i].capacity << "," << courses[i].enrolled << endl;
        for (const auto &announcement : courses[i].announcements)
        {
            file << "announcement:" << announcement << endl;
        }
        for (const auto &student : courses[i].students)
        {
            file << "student:" << student.name << "," << student.rollNumber << "," << student.grade << endl;
        }
        for (const auto &article : courses[i].articles)
        {
            file << "article:" << article << endl;
        }
        for (const auto &assignment : courses[i].assignments)
        {
            file << "assignment:" << assignment << endl;
        }
        for (const auto &quiz : courses[i].quizzes)
        {
            file << "quiz:" << quiz << endl;
        }
        for (const auto &practiceQuiz : courses[i].practiceQuizzes)
        {
            file << "practiceQuiz:" << practiceQuiz << endl;
        }
    }
    file.close();
}

// Function to load courses from a file
void loadCourses(Course courses[], int &courseCount)
{
    ifstream file("courses.txt");
    if (!file.is_open())
    {
        cout << "Error opening courses file." << endl;
        return;
    }

    string line;
    while (getline(file, line))
    {
        if (line.find("announcement:") == 0)
        {
            courses[courseCount - 1].announcements.push_back(line.substr(13));
        }
        else if (line.find("student:") == 0)
        {
            Student student;
            stringstream ss(line.substr(8));
            getline(ss, student.name, ',');
            getline(ss, student.rollNumber, ',');
            getline(ss, student.grade, ',');
            courses[courseCount - 1].students.push_back(student);
        }
        else if (line.find("article:") == 0)
        {
            courses[courseCount - 1].articles.push_back(line.substr(8));
        }
        else if (line.find("assignment:") == 0)
        {
            courses[courseCount - 1].assignments.push_back(line.substr(11));
        }
        else if (line.find("quiz:") == 0)
        {
            courses[courseCount - 1].quizzes.push_back(line.substr(5));
        }
        else if (line.find("practiceQuiz:") == 0)
        {
            courses[courseCount - 1].practiceQuizzes.push_back(line.substr(13));
        }
        else
        {
            stringstream ss(line);
            getline(ss, courses[courseCount].title, ',');
            getline(ss, courses[courseCount].instructor, ',');
            ss >> courses[courseCount].capacity;
            ss.ignore();
            ss >> courses[courseCount].enrolled;
            ++courseCount;
        }
    }
    file.close();
}

// Function to add a user
void addUser(User users[], int &userCount)
{
    if (userCount >= 10)
    {
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
void removeUser(User users[], int &userCount)
{
    string username;
    cout << "Enter username of the user to remove: ";
    getline(cin, username);
    for (int i = 0; i < userCount; ++i)
    {
        if (users[i].username == username)
        {
            for (int j = i; j < userCount - 1; ++j)
            {
                users[j] = users[j + 1];
            }
            --userCount;
            saveUsers(users, userCount); // Save users to file
            cout << "User " << username << " removed successfully." << endl;
            return;
        }
    }
    cout << "User not found." << endl;
}

// Function to create a course
void createCourse(Course courses[], int &courseCount)
{
    if (courseCount >= 10)
    {
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
    saveCourses(courses, courseCount); // Save courses to file
    cout << "Course created successfully." << endl;
    cin.ignore(); // Clear the input buffer
}

// Function to assign a course to an instructor
void assignCourseToInstructor(Course courses[], int courseCount, User users[], int userCount)
{
    string courseTitle, instructorUsername;
    cout << "Enter course title: ";
    getline(cin, courseTitle);
    cout << "Enter instructor username: ";
    getline(cin, instructorUsername);

    for (int i = 0; i < courseCount; ++i)
    {
        if (courses[i].title == courseTitle)
        {
            bool instructorFound = false;
            for (int j = 0; j < userCount; ++j)
            {
                if (users[j].username == instructorUsername && users[j].userType == "instructor")
                {
                    courses[i].instructor = instructorUsername;
                    instructorFound = true;
                    break;
                }
            }
            if (!instructorFound)
            {
                cout << "Instructor not found or invalid instructor username." << endl;
                return;
            }

            saveCourses(courses, courseCount); // Save courses to file
            cout << "Instructor assigned to course successfully." << endl;
            return;
        }
    }
    cout << "Course not found." << endl;
}

// Function to change course capacity
void changeCourseCapacity(Course courses[], int courseCount)
{
    string courseTitle;
    int newCapacity;
    cout << "Enter course title: ";
    getline(cin, courseTitle);
    cout << "Enter new capacity: ";
    cin >> newCapacity;

    for (int i = 0; i < courseCount; ++i)
    {
        if (courses[i].title == courseTitle)
        {
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
void displayUsers(const User users[], int userCount)
{
    cout << "\n--- User Accounts ---" << endl;
    if (userCount == 0)
    {
        cout << "No user accounts found." << endl;
    }
    else
    {
        for (int i = 0; i < userCount; ++i)
        {
            cout << "Username: " << users[i].username << ", Password: " << users[i].password << ", Type: " << users[i].userType << endl;
        }
    }
}

// Function to display course listings
void displayCourses(const Course courses[], int courseCount)
{
    cout << "\n--- Course Listings ---" << endl;
    if (courseCount == 0)
    {
        cout << "No courses available." << endl;
    }
    else
    {
        for (int i = 0; i < courseCount; ++i)
        {
            cout << "Title: " << courses[i].title << ", Instructor: " << courses[i].instructor << ", Capacity: " << courses[i].capacity << ", Enrolled: " << courses[i].enrolled << endl;
        }
    }
}

// Function to manage instructor salaries
void manageSalaries()
{
    cout << "This feature is not yet implemented." << endl;
}

// Function for instructor to view courses
void viewCourses(const Course courses[], int courseCount, const string &instructorUsername)
{
    cout << "\n--- Your Courses ---" << endl;
    for (int i = 0; i < courseCount; ++i)
    {
        if (courses[i].instructor == instructorUsername)
        {
            cout << "Title: " << courses[i].title << ", Capacity: " << courses[i].capacity << ", Enrolled: " << courses[i].enrolled << endl;
        }
    }
}

// Function for instructor to add grades
void addGrades(Course courses[], int courseCount, const string &instructorUsername)
{
    string courseTitle;
    cout << "Enter course title: ";
    getline(cin, courseTitle);

    for (int i = 0; i < courseCount; ++i)
    {
        if (courses[i].title == courseTitle && courses[i].instructor == instructorUsername)
        {
            string rollNumber, grade;
            cout << "Enter student roll number: ";
            getline(cin, rollNumber);
            cout << "Enter grade: ";
            getline(cin, grade);

            for (auto &student : courses[i].students)
            {
                if (student.rollNumber == rollNumber)
                {
                    student.grade = grade;
                    saveCourses(courses, courseCount); // Save courses to file
                    cout << "Grade added successfully." << endl;
                    return;
                }
            }
            cout << "Student not found." << endl;
            return;
        }
    }
    cout << "Course not found or you are not the instructor of this course." << endl;
}

// Function for instructor to view enrolled students
void viewEnrolledStudents(const Course courses[], int courseCount, const string &instructorUsername)
{
    string courseTitle;
    cout << "Enter course title: ";
    getline(cin, courseTitle);

    for (int i = 0; i < courseCount; ++i)
    {
        if (courses[i].title == courseTitle && courses[i].instructor == instructorUsername)
        {
            cout << "\n--- Enrolled Students ---" << endl;
            for (const auto &student : courses[i].students)
            {
                cout << "Name: " << student.name << ", Roll Number: " << student.rollNumber << ", Grade: " << student.grade << endl;
            }
            return;
        }
    }
    cout << "Course not found or you are not the instructor of this course." << endl;
}

// Function for instructor to update course information
void updateCourseInfo(Course courses[], int courseCount, const string &instructorUsername)
{
    string courseTitle;
    cout << "Enter course title: ";
    getline(cin, courseTitle);

    for (int i = 0; i < courseCount; ++i)
    {
        if (courses[i].title == courseTitle && courses[i].instructor == instructorUsername)
        {
            int choice;
            cout << "1. Add an article" << endl;
            cout << "2. Add an assignment" << endl;
            cout << "3. Add a practice quiz" << endl;
            cout << "4. Add a quiz" << endl;
            cout << "Enter your choice: ";
            cin >> choice;
            cin.ignore(); // Clear the input buffer

            string content;
            cout << "Enter content: ";
            getline(cin, content);

            switch (choice)
            {
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
    cout << "Course not found or you are not the instructor of this course." << endl;
}

// Function for instructor to view and send announcements
void manageAnnouncements(Course courses[], int courseCount, const string &instructorUsername)
{
    string courseTitle;
    cout << "Enter course title: ";
    getline(cin, courseTitle);

    for (int i = 0; i < courseCount; ++i)
    {
        if (courses[i].title == courseTitle && courses[i].instructor == instructorUsername)
        {
            cout << "\n--- Announcements ---" << endl;
            for (const auto &announcement : courses[i].announcements)
            {
                cout << "- " << announcement << endl;
            }

            string newAnnouncement;
            cout << "Enter new announcement: ";
            getline(cin, newAnnouncement);

            courses[i].announcements.push_back(newAnnouncement);
            saveCourses(courses, courseCount); // Save courses to file
            cout << "Announcement added successfully." << endl;
            return;
        }
    }
    cout << "Course not found or you are not the instructor of this course." << endl;
}

int main()
{
    const int maxUsers = 10;
    const int maxCourses = 10;
    User users[maxUsers];
    Course courses[maxCourses];
    int userCount = 0;
    int courseCount = 0;

    loadUsers(users, userCount);
    loadCourses(courses, courseCount);

    int mainChoice;
    do
    {
        displayMainMenu();
        cin >> mainChoice;
        cin.ignore(); // Clear the input buffer

        if (mainChoice == 1)
        {
            // Sign Up
            addUser(users, userCount);
        }
        else if (mainChoice == 2)
        {
            // Log In
            string username, password;
            cout << "Enter username: ";
            getline(cin, username);
            cout << "Enter password: ";
            getline(cin, password);

            bool userFound = false;
            for (int i = 0; i < userCount; ++i)
            {
                if (users[i].username == username && users[i].password == password)
                {
                    userFound = true;
                    if (users[i].userType == "administrator")
                    {
                        int adminChoice;
                        do
                        {
                            displayAdminMenu();
                            cin >> adminChoice;
                            cin.ignore(); // Clear the input buffer

                            switch (adminChoice)
                            {
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
                                cout << "Returning to main menu." << endl;
                                break;
                            default:
                                cout << "Invalid choice. Please enter a number between 1 and 9." << endl;
                            }
                        } while (adminChoice != 9);
                    }
                    else if (users[i].userType == "instructor")
                    {
                        int instructorChoice;
                        do
                        {
                            displayInstructorMenu();
                            cin >> instructorChoice;
                            cin.ignore(); // Clear the input buffer

                            switch (instructorChoice)
                            {
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
                                cout << "Returning to main menu." << endl;
                                break;
                            default:
                                cout << "Invalid choice. Please enter a number between 1 and 6." << endl;
                            }
                        } while (instructorChoice != 6);
                    }
                    else
                    {
                        cout << "Invalid user type." << endl;
                    }
                    break;
                }
            }

            if (!userFound)
            {
                cout << "Invalid username or password. Please try again." << endl;
            }
        }
        else if (mainChoice != 3)
        {
            cout << "Invalid choice. Please enter 1, 2, or 3." << endl;
        }
    } while (mainChoice != 3);

    cout << "Exiting program. Goodbye!" << endl;
    return 0;
}
