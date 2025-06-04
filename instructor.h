// instructor.h
#ifndef INSTRUCTOR_H
#define INSTRUCTOR_H

#include <string>
#include <vector>
using namespace std;

struct Student {
    string name;
    string rollNumber;
    string grade;
};

struct Course {
    string title;
    string instructor;
    int capacity;
    int enrolled;
    vector<Student> students;
};

void instructorPanel(vector<Course>& courses, const string &username);
void viewInstructorCourses(const vector<Course>& courses, const string &instructor);
void addGrades(vector<Course>& courses, const string &instructor);
void viewEnrolledStudents(const vector<Course>& courses, const string &instructor);
void updateCourseInformation(vector<Course>& courses, const string &instructor);
void viewSendAnnouncements(const vector<Course>& courses, const string& instructorUsername);

#endif // INSTRUCTOR_H
