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

    void conductQuiz(const string& studentUsername) {
        cout << "Conducting quiz for student: " << studentUsername << endl;
        // Implement quiz logic here
    }
};

int main() {
    // Example usage
    Student student("student123", "password123");
    student.login();

    Course c1("Introduction to Programming", "Dr. Smith", "Learn the basics of programming");
    c1.displayDetails();

    c1.enrollStudent(student);
    student.submitAssignment("Assignment 1");
    student.viewGrades();
    student.postToForum("Hello everyone! How are you doing?"); // Student posts to forum

    return 0;
}
