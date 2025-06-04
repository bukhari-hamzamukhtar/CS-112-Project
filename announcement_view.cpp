#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "instructor.h"
using namespace std;

void viewAnnouncements(const vector<Course>& courses, const string& studentUsername) {
    cout << "\n===== Relevant Announcements =====\n";

    ifstream file("announcements.txt");
    if (!file) {
        cout << "No announcements available.\n";
        return;
    }

    string line, instructor, course, date, content;
    bool show = false;

    while (getline(file, line)) {
        if (line.rfind("Instructor:", 0) == 0) {
            instructor = line.substr(11);
        } else if (line.rfind("Course:", 0) == 0) {
            course = line.substr(8);
            show = false;

            // check if student is enrolled in this course
            for (const auto& c : courses) {
                if (c.title == course) {
                    for (const auto& s : c.students) {
                        if (s.name == studentUsername) {
                            show = true;
                            break;
                        }
                    }
                }
                if (show) break;
            }

            content.clear();
        } else if (line.rfind("Date:", 0) == 0) {
            date = line.substr(6); // capture date string
        } else if (line == "===") {
            if (show) {
                cout << "From: " << instructor << " | Course: " << course << "\n";
                cout << "Date: " << date << "\n";
                cout << content;
                cout << "-----------------------------\n";
            }
        } else {
            content += line + "\n";
        }
    }

    cout << "===============================\n\n";
}
