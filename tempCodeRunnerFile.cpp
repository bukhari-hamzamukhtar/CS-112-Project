#include <iostream>
#include <fstream>
#include <string>
#include <vector>

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
    float grade;
};

class Course
{
    public:
    string title;
    string instructor;
    int capacity;
    int enrolled;
    vector<Student> students;
};

// Function to display the menu for instructors
void displayInstructorMenu()
{
    cout << "\n--- Instructor Menu ---" << endl;
    cout << "1. View your courses" << endl;
    cout << "2. Add grades for students" << endl;
    cout << "3. View enrolled students" << endl;
    cout << "4. Update course information" << endl;
    cout << "5. View/Send announcements" << endl;
    cout << "6. Exit" << endl;
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
            outFile << courses[i].students.size() << endl;
            for (const auto& student : courses[i].students)
            {
                outFile << student.name << endl;
                outFile << student.rollNumber << endl;
                outFile << student.grade << endl;
            }
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
            int studentCount;
            inFile >> studentCount;
            inFile.ignore();
            for (int j = 0; j < studentCount; ++j)
            {
                Student student;
                getline(inFile, student.name);
                getline(inFile, student.rollNumber);
                inFile >> student.grade;
                inFile.ignore();
                courses[i].students.push_back(student);
            }
        }
        inFile.close();
    }
    else
    {
        cout << "Unable to open file to load courses." << endl;
    }
}

// Function to view instructor's courses
void viewInstructorCourses(const Course courses[], int courseCount, const string& instructor)
{
    cout << "\n--- Your Courses ---" << endl;
    bool found = false;
    for (int i = 0; i < courseCount; ++i)
    {
        if (courses[i].instructor == instructor)
        {
            cout << "Title: " << courses[i].title << ", Capacity: " << courses[i].capacity << ", Enrolled: " << courses[i].enrolled << endl;
            found = true;
        }
    }
    if (!found)
    {
        cout << "No courses found for you." << endl;
    }
}

// Function to add grades for students
void addGrades(Course courses[], int courseCount, const string& instructor)
{
    string courseTitle;
    cout << "Enter the title of the course to add grades: ";
    getline(cin, courseTitle);
    for (int i = 0; i < courseCount; ++i)
    {
        if (courses[i].title == courseTitle && courses[i].instructor == instructor)
        {
            for (auto& student : courses[i].students)
            {
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
void viewEnrolledStudents(const Course courses[], int courseCount, const string& instructor)
{
    string courseTitle;
    cout << "Enter the title of the course to view enrolled students: ";
    getline(cin, courseTitle);
    for (int i = 0; i < courseCount; ++i)
    {
        if (courses[i].title == courseTitle && courses[i].instructor == instructor)
        {
            cout << "\n--- Enrolled Students ---" << endl;
            for (const auto& student : courses[i].students)
            {
                cout << "Name: " << student.name << ", Roll Number: " << student.rollNumber << ", Grade: " << student.grade << endl;
            }
            return;
        }
    }
    cout << "Course not found or you are not the instructor of this course." << endl;
}

// Function to update course information
void updateCourseInformation(Course courses[], int courseCount, const string& instructor)
{
    string courseTitle;
    cout << "Enter the title of the course to update: ";
    getline(cin, courseTitle);
    for (int i = 0; i < courseCount; ++i)
    {
        if (courses[i].title == courseTitle && courses[i].instructor == instructor)
        {
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
void viewSendAnnouncements()
{
    // This function can be implemented as needed.
    cout << "\n--- Announcements ---" << endl;
    cout << "This feature is not yet implemented." << endl;
}

int main()
{
    const int max_courses = 10;
    Course courses[max_courses];
    int courseCount = 0;
    string instructorUsername = "example_instructor"; // Set the instructor's username here

    // Load courses from file
    loadCourses(courses, courseCount);

    int choice_instructor;

    cout << "Welcome, Instructor!" << endl;
    do
    {
        displayInstructorMenu();
        cout << "Enter your choice: ";
        cin >> choice_instructor;
        cin.ignore(); // Clear the input buffer

        switch (choice_instructor)
        {
        case 1:
            viewInstructorCourses(courses, courseCount, instructorUsername);
            break;
        case 2:
            addGrades(courses, courseCount, instructorUsername);
            break;
        case 3:
            viewEnrolledStudents(courses, courseCount, instructorUsername);
            break;
        case 4:
            updateCourseInformation(courses, courseCount, instructorUsername);
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

    // Save courses to file before exiting
    saveCourses(courses, courseCount);

    return 0;
}
