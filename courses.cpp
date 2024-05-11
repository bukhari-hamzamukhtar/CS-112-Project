#include <iostream>
#include <string>

using namespace std;

// Forward declaration of the Course class
class Course;

class User {
protected:
    string username;
    string password;

public:
    User(const string& username, const string& password) : username(username), password(password) {}

    virtual void login() {
        cout << "Logging in as " << username << endl;
    }

    string getUsername() const { return username; }
};

class Student : public User {
public:
    Student(const string& username, const string& password) : User(username, password) {}

    void submitAssignment(const string& assignmentName) {
        cout << "Submitting assignment: " << assignmentName << endl;
        // Implement assignment submission logic here
    }

    void viewGrades() {
        cout << "Viewing grades..." << endl;
        // Implement grade viewing logic here
    }

    void postToForum(const string& message) {
        cout << "Posting to forum: " << message << endl;
        // Implement forum posting logic here
    }

    Course* browseCourses(const Course courses[], int numCourses);
};

class Course {
private:
    string courseName;
    string instructor;
    string description;

public:
    Course(const string& courseName, const string& instructor, const string& description)
        : courseName(courseName), instructor(instructor), description(description) {}

    void displayDetails() const {
        cout << "Course: " << courseName << endl;
        cout << "Instructor: " << instructor << endl;
        cout << "Description: " << description << endl;
    }
};

Course* Student::browseCourses(const Course courses[], int numCourses) {
    cout << "Available Courses:" << endl;
    for (int i = 0; i < numCourses; ++i) {
        cout << i + 1 << ". ";
        courses[i].displayDetails();
    }

    int choice;
    cout << "Enter the number of the course you want to enroll in: ";
    cin >> choice;
    if (choice >= 1 && choice <= numCourses) {
        return const_cast<Course*>(&courses[choice - 1]);
    } else {
        cout << "Invalid choice. Please try again." << endl;
        return nullptr;
    }
}

int main() {
    // Define the courses
    Course courses[] = {
        Course("CS101", "Mr. Talha Ashfaq", "Introduction to Computer Science"),
        Course("CS112", "Mr Qasim Riaz", "Data Structures and Algorithms"),
        Course("HM101", "Mr Abrar", "Introduction to History"),
        Course("HM102", "Ms Hira Ahad", "World History"),
        Course("MT101", "Mr Fahad Zulfiqar", "Introduction to Mathematics"),
        Course("MT102", "Mr Asif", "Calculus"),
        Course("CH101", "Ms Nida", "Introduction to Chemistry"),
        Course("CH161", "Ms Ramesha Tariq", "Organic Chemistry"),
        Course("ES111", "Mr Fahad Zulfiqar", "Introduction to Environmental Science")
    };

    Student student("student123", "password123");
    student.login();
    Course* chosenCourse = student.browseCourses(courses, 9);
    if (chosenCourse != nullptr) {
        chosenCourse->displayDetails();
    }

    return 0;
}
