#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include "instructor.h"

#include <chrono>
#include <ctime>
#include <iomanip>

using namespace std;

void viewSendAnnouncements(const vector<Course>& courses, const string& instructorUsername) {
    string courseTitle, line, announcementText;

    cout << "\nEnter course title this announcement is for: ";
    getline(cin, courseTitle);

    // ✅ Verify course exists and belongs to instructor
    bool found = false;
    for (const auto& c : courses) {
        if (c.title == courseTitle && c.instructor == instructorUsername) {
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "❌ You are not assigned to this course or it doesn't exist.\n";
        return;
    }


    cout << "Enter your announcement (end with a single '.' on a new line):\n";
    while (true) {
        getline(cin, line);
        if (line == ".") break;
        announcementText += line + "\n";
    }

    ofstream file("announcements.txt", ios::app);
    if (!file) {
        cout << "❌ Could not open announcements.txt\n";
        return;
    }
    // 🕒 Get current time
auto now = chrono::system_clock::now();
time_t now_time = chrono::system_clock::to_time_t(now);

file << "Instructor: " << instructorUsername << "\n";
file << "Course: " << courseTitle << "\n";
file << "Date: " << put_time(localtime(&now_time), "%B %d, %Y — %I:%M %p") << "\n";
file << announcementText;
file << "===\n";


    file.close();
    cout << "✅ Announcement added for course: " << courseTitle << "\n";
}