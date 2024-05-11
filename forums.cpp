#include <iostream>
#include <string>

using namespace std;

class Course; // Forward declaration of the Course class

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

    void submitAssignment(const string& assignmentName, Course& course);
    void viewGrades(Course& course);
    void postToForum(const string& message, Course& course);
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

    void conductVirtualClass() {
        cout << "Starting virtual class..." << endl;
        // Implement virtual classroom logic here
    }

    void accessMaterials() {
        cout << "Accessing course materials..." << endl;
        // Implement logic to access course materials here
    }

    void conductQuiz() {
        cout << "Conducting quiz..." << endl;
        // Implement quiz logic here
    }

    void submitAssignment(const string& assignmentName, const string& studentUsername) {
        cout << "Submitting assignment \"" << assignmentName << "\" by student: " << studentUsername << endl;
        // Implement assignment submission logic here
    }

    void viewGrades(const string& studentUsername) {
        cout << "Viewing grades for student: " << studentUsername << endl;
        // Implement grade viewing logic here
    }

    void postToForum(const string& message, const string& studentUsername) {
        cout << "Posting to forum by student " << studentUsername << ": " << message << endl;
        // Implement forum posting logic here
    }
};

void Student::submitAssignment(const string& assignmentName, Course& course) {
    course.submitAssignment(assignmentName, getUsername());
}

void Student::viewGrades(Course& course) {
    course.viewGrades(getUsername());
}

void Student::postToForum(const string& message, Course& course) {
    course.postToForum(message, getUsername());
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
    Course* chosenCourse = &courses[0]; // Choosing the first course for demonstration
    if (chosenCourse != nullptr) {
        chosenCourse->displayDetails();
        chosenCourse->conductVirtualClass();
        chosenCourse->accessMaterials();
        chosenCourse->conductQuiz();

        student.submitAssignment("Assignment 1", *chosenCourse);
        student.viewGrades(*chosenCourse);
        student.postToForum("Hello everyone! How are you doing?", *chosenCourse);
    }

    return 0;
}
