#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class User
{
    public:
    string username;
    string password;
    string userType;
};

class Course
{
    public:
    string title;
    string instructor;
    int capacity;
    int enrolled;
};

// Function to display the menu
void displayMenu()
{
    cout << "\n--- Menu ---" << endl;
    cout << "1. Add a user" << endl;
    cout << "2. Remove a user" << endl;
    cout << "3. Add a course" << endl;
    cout << "4. Remove a course" << endl;
    cout << "5. Display user accounts" << endl;
    cout << "6. Display course listings" << endl;
    cout << "7. Exit" << endl;
}

// Function to save users to file
void saveUsers(const User users[], int userCount)
{
    ofstream outFile("users.txt");
    if (outFile.is_open())
    {
        outFile << userCount << endl;
        for (int i = 0; i < userCount; ++i)
        {
            outFile << users[i].username << endl;
            outFile << users[i].password << endl;
            outFile << users[i].userType << endl;
        }
        outFile.close();
    }
    else
    {
        cout << "Unable to open file to save users." << endl;
    }
}

// Function to load users from file
void loadUsers(User users[], int &userCount)
{
    ifstream inFile("users.txt");
    if (inFile.is_open())
    {
        inFile >> userCount;
        inFile.ignore();
        for (int i = 0; i < userCount; ++i)
        {
            getline(inFile, users[i].username);
            getline(inFile, users[i].password);
            getline(inFile, users[i].userType);
        }
        inFile.close();
    }
    else
    {
        cout << "Unable to open file to load users." << endl;
    }
}

// Function to save courses to file
void saveCourses(const Course courses[], int courseCount)
{
    ofstream outFile("courses.txt");
    if (outFile.is_open())
    {
        outFile << courseCount << endl;
        for (int i = 0; i < courseCount; ++i)
        {
            outFile << courses[i].title << endl;
            outFile << courses[i].instructor << endl;
            outFile << courses[i].capacity << endl;
            outFile << courses[i].enrolled << endl;
        }
        outFile.close();
    }
    else
    {
        cout << "Unable to open file to save courses." << endl;
    }
}

// Function to load courses from file
void loadCourses(Course courses[], int &courseCount)
{
    ifstream inFile("courses.txt");
    if (inFile.is_open())
    {
        inFile >> courseCount;
        inFile.ignore();
        for (int i = 0; i < courseCount; ++i)
        {
            getline(inFile, courses[i].title);
            getline(inFile, courses[i].instructor);
            inFile >> courses[i].capacity;
            inFile >> courses[i].enrolled;
            inFile.ignore();
        }
        inFile.close();
    }
    else
    {
        cout << "Unable to open file to load courses." << endl;
    }
}

// Function to add a user
void addUser(User users[], int &userCount)
{
    if (userCount >= 10)
    {
        cout << "Cannot add more users. Maximum limit of 10 users has been reached." << endl;
        return;
    }

    User newUser;
    cout << "Enter username: ";
    getline(cin, newUser.username);
    cout << "Enter password: ";
    getline(cin, newUser.password);
    cout << "Enter user type (e.g., Student, Instructor, Admin): ";
    getline(cin, newUser.userType);

    users[userCount++] = newUser;
    cout << "User added successfully." << endl;

    saveUsers(users, userCount); // Save users to file
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
            userCount--;
            cout << "User " << username << " removed successfully." << endl;
            saveUsers(users, userCount); // Save users to file
            return;
        }
    }
    cout << "User not found." << endl;
}

// Function to add a course
void addCourse(Course courses[], int &courseCount)
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
    cout << "Course added successfully." << endl;
    cin.ignore(); // Clear the input buffer

    saveCourses(courses, courseCount); // Save courses to file
}

// Function to remove a course
void removeCourse(Course courses[], int &courseCount)
{
    string title;
    cout << "Enter the title of the course to remove: ";
    getline(cin, title);
    for (int i = 0; i < courseCount; ++i)
    {
        if (courses[i].title == title)
        {
            for (int j = i; j < courseCount - 1; ++j)
            {
                courses[j] = courses[j + 1];
            }
            courseCount--;
            cout << "Course " << title << " removed successfully." << endl;
            saveCourses(courses, courseCount); // Save courses to file
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
            cout << "Username: " << users[i].username << ", Password: " << users[i].password << ", User Type: " << users[i].userType << endl;
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

int main()
{
    const int max_users = 10;
    const int max_courses = 10;
    User users[max_users];
    Course courses[max_courses];
    int userCount = 0;
    int courseCount = 0;

    // Load users and courses from files
    loadUsers(users, userCount);
    loadCourses(courses, courseCount);

    int choice_admin;

    cout << "Welcome, Administrator!" << endl;
    do
    {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice_admin;
        cin.ignore(); // Clear the input buffer

        switch (choice_admin)
        {
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
            cout << "Invalid choice_admin. Please enter a number between 1 and 7." << endl;
        }
    } while (choice_admin != 7);

    // Save users and courses to files before exiting
    saveUsers(users, userCount);
    saveCourses(courses, courseCount);

    return 0;
}
