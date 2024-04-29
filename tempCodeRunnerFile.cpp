#include <iostream>
#include <string>

using namespace std;

class User {
protected:
    string username;
    string password;

public:
    User(const string& username, const string& password) : username(username), password(password) {}

    virtual void login() {
        cout << "Logging in as " << username << endl;
    }

    string getUsername() const { return username; } // Add a public getter for username
};

class Student : public User {
public:
    Student(const string& username, const string& password) : User(username, password) {}

    void enrollCourse(const string& courseName) {
        cout << getUsername() << " enrolled in course: " << courseName << endl; // Use getUsername() to access username
    }

    // Other functionalities specific to student can be added here
};

class Instructor : public User {
public:
    Instructor(const string& username, const string& password) : User(username, password) {}

    void createCourse(const string& courseName) {
        cout << getUsername() << " created course: " << courseName << endl;
    }

    // Other functionalities specific to instructor can be added here
};

class Administrator : public User {
public:
    Administrator(const string& username, const string& password) : User(username, password) {}

    void manageAccounts() {
        cout << "Administrator managing accounts" << endl;
    }

    // Other functionalities specific to administrator can be added here
};

class Course {
private:
    string courseName;
    string instructor;
    string description;
    string enrolledStudents[100]; // Array to store enrolled student usernames (assuming maximum 100 students)

public:
    Course(const string& courseName, const string& instructor, const string& description)
        : courseName(courseName), instructor(instructor), description(description) {}

    void displayDetails() const {
        cout << "Course: " << courseName << endl;
        cout << "Instructor: " << instructor << endl;
        cout << "Description: " << description << endl;
    }

    void enrollStudent(Student& student) {
        for (int i = 0; i < 100; ++i) {
            if (enrolledStudents[i].empty()) {
                enrolledStudents[i] = student.getUsername(); // Store the username of the enrolled student
                cout << student.getUsername() << " enrolled in course: " << courseName << endl;
                return;
            }
        }
        cout << "Course is full. Cannot enroll student." << endl;
    }

    // Add methods for managing enrollment, accessing materials, etc. as needed
};

int main() {
    // Example usage
    Student student("student123", "password123");
    student.login();

    Course c1("Introduction to Programming", "Dr. Smith", "Learn the basics of programming");
    c1.displayDetails();

    c1.enrollStudent(student);

    return 0;
}
