#include <iostream>
#include <string>

using namespace std;

// Struct to represent a user
struct User
{
    string username;
    string password;
};

// Struct to represent a course
struct Course
{
    string title;
    string instructor;
    int capacity;
    int enrolled;
};

// Function prototypes
void displayMenu();
void addUser(User users[], int &userCount);
void removeUser(User users[], int &userCount);
void addCourse(Course courses[], int &courseCount);
void removeCourse(Course courses[], int &courseCount);
void displayUsers(const User users[], int userCount);
void displayCourses(const Course courses[], int courseCount);

int mainadmin()
{
    const int max_users = 10;
    const int max_courses = 10;
    User users[max_users];
    Course courses[max_courses];
    int userCount = 0;
    int courseCount = 0;

    // Initialize some users
    users[userCount++] = {"Faheem Ahmad", "Giki@123"};
    users[userCount++] = {"Sabahat Hussaain", "Admin@123"};

    // Initialize some courses
    courses[courseCount++] = {"MT102", "Fahad", 50, 47};
    courses[courseCount++] = {"CS112", "Qasim", 40, 35};
    courses[courseCount++] = {"HM102", "Hira", 45, 40};
    courses[courseCount++] = {"MM101", "Shanza", 85, 40};

    int choice;

    cout << "Welcome, Administrator!" << endl;

    do
    {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Clear the input buffer

        switch (choice)
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
            cout << "Invalid choice. Please enter a number between 1 and 7." << endl;
        }
    } while (choice != 7);

    return 0;
}

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

// Function to add a user
void addUser(User users[], int &userCount)
{
    if (userCount >= 10)
    {
        cout << "Cannot add more users. Maximum limit reached." << endl;
        return;
    }

    User newUser;
    cout << "Enter username: ";
    getline(cin, newUser.username);
    cout << "Enter password: ";
    getline(cin, newUser.password);
    users[userCount++] = newUser;
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
            userCount--;
            cout << "User " << username << " removed successfully." << endl;
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
            cout << "Username: " << users[i].username << ", Password: " << users[i].password << endl;
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

//***********
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class CourseInstructor
{
private:
    string courseName;
    string subTopic;

public:
    void setCourseName(string name)
    {
        courseName = name;
    }
    string getCourseName()
    {
        return courseName;
    }
    void setSubTopic(string topic)
    {
        subTopic = topic;
    }
    string getSubTopic()
    {
        return subTopic;
    }
    void addContent()
    {
        cout << "Content added to " << courseName << " - " << subTopic << endl;
    }
};

class StudentInstructor
{
private:
    string name;
    vector<string> assignments;
    vector<string> grades;

public:
    StudentInstructor(string studentName) : name(studentName) {}

    string getName()
    {
        return name;
    }

    void submitAssignment(string assignment)
    {
        assignments.push_back(assignment);
    }

    void receiveGrade(string assignment, string grade)
    {
        grades.push_back(grade);
        cout << "Received grade " << grade << " for assignment " << assignment << endl;
    }

    vector<string> getAssignments()
    {
        return assignments;
    }

    vector<string> getGrades()
    {
        return grades;
    }
};

class Instructor
{
private:
    string name;
    CourseInstructor course;
    vector<StudentInstructor> students;

public:
    Instructor()
    {
        name = "";
    }
    void setName(string instructorName)
    {
        name = instructorName;
    }
    string getName()
    {
        return name;
    }
    void createCourseContent()
    {
        string courseChoices[8] = {"Basic Computer Science", "Object-Oriented Programming", "English", "Communications", "Calculus 1", "Calculus 2", "Chemistry", "Health"};
        string subTopicChoices[5];
        int choice;

        cout << "Choose a course: " << endl;
        for (int i = 0; i < 8; i++)
        {
            cout << i + 1 << ". " << courseChoices[i] << endl;
        }
        cin >> choice;
        choice--;

        if (choice < 0 || choice >= 8)
        {
            cout << "Invalid choice. Please choose a number between 1 and 8." << endl;
            return;
        }

        course.setCourseName(courseChoices[choice]);

        cout << "Enter subtopics (up to 5): " << endl;
        if (course.getCourseName() == "Basic Computer Science")
        {
            subTopicChoices[0] = "Introduction to Programming";
            subTopicChoices[1] = "Data Structures";
            subTopicChoices[2] = "Algorithms";
            subTopicChoices[3] = "Operating Systems";
            subTopicChoices[4] = "Computer Networks";
        }
        else if (course.getCourseName() == "Object-Oriented Programming")
        {
            subTopicChoices[0] = "Introduction to Object-Oriented Programming";
            subTopicChoices[1] = "Inheritance and Polymorphism";
            subTopicChoices[2] = "Exception Handling";
            subTopicChoices[3] = "Templates and STL";
            subTopicChoices[4] = "Design Patterns";
        }
        else if (course.getCourseName() == "English")
        {
            subTopicChoices[0] = "Grammar and Punctuation";
            subTopicChoices[1] = "Reading Comprehension";
            subTopicChoices[2] = "Writing Skills";
            subTopicChoices[3] = "Literature Analysis";
            subTopicChoices[4] = "Vocabulary and Spelling";
        }
        else if (course.getCourseName() == "Communications")
        {
            subTopicChoices[0] = "Interpersonal Communication";
            subTopicChoices[1] = "Group Communication";
            subTopicChoices[2] = "Nonverbal Communication";
            subTopicChoices[3] = "Conflict Resolution";
            subTopicChoices[4] = "Public Speaking";
        }
        else if (course.getCourseName() == "Calculus 1")
        {
            subTopicChoices[0] = "Limits and Continuity";
            subTopicChoices[1] = "Differentiation";
            subTopicChoices[2] = "Applications of Differentiation";
            subTopicChoices[3] = "Integration";
            subTopicChoices[4] = "Applications of Integration";
        }
        else if (course.getCourseName() == "Calculus 2")
        {
            subTopicChoices[0] = "Techniques of Integration";
            subTopicChoices[1] = "Applications of Integration";
            subTopicChoices[2] = "Infinite Series";
            subTopicChoices[3] = "Power Series";
            subTopicChoices[4] = "Parametric Equations and Polar Coordinates";
        }
        else if (course.getCourseName() == "Chemistry")
        {
            subTopicChoices[0] = "Introduction to Chemistry";
            subTopicChoices[1] = "Organic Chemistry";
            subTopicChoices[2] = "Physical Chemistry";
            subTopicChoices[3] = "Analytical Chemistry";
            subTopicChoices[4] = "Inorganic Chemistry";
        }
        else if (course.getCourseName() == "Health")
        {
            subTopicChoices[0] = "Anatomy and Physiology";
            subTopicChoices[1] = "Health Education";
            subTopicChoices[2] = "Nutrition";
            subTopicChoices[3] = "First Aid and CPR";
            subTopicChoices[4] = "Fitness and Exercise";
        }

        for (int i = 0; i < 5; i++)
        {
            cout << i + 1 << ". " << subTopicChoices[i] << endl;
        }

        int subChoice;
        cin >> subChoice;
        subChoice--;

        if (subChoice < 0 || subChoice >= 5)
        {
            cout << "Invalid choice. Please choose a number between 1 and 5." << endl;
            return;
        }

        course.setSubTopic(subTopicChoices[subChoice]);
        course.addContent();
    }

    void enrollStudent()
    {
        string studentName;
        cout << "Enter the name of the student: ";
        cin >> studentName;
        students.push_back(StudentInstructor(studentName));
        cout << "Enrolled student " << studentName << " in course " << course.getCourseName() << endl;
    }

    void assignAssignment()
    {
        string assignment;
        cout << "Enter the assignment to assign: ";
        cin.ignore();
        getline(cin, assignment);
        for (auto &student : students)
        {
            student.submitAssignment(assignment);
            cout << "Assigned " << assignment << " to student " << student.getName() << endl;
        }
    }

    void gradeAssignment()
    {
        string assignment;
        string studentName;
        string grade;
        cout << "Enter the name of the student: ";
        cin >> studentName;
        cout << "Enter the assignment to grade: ";
        cin.ignore();
        getline(cin, assignment);
        cout << "Enter the grade for " << assignment << ": ";
        cin >> grade;

        for (auto &student : students)
        {
            if (student.getName() == studentName)
            {
                student.receiveGrade(assignment, grade);
                return;
            }
        }
        cout << "Student not found." << endl;
    }

    void viewStudentProgress()
    {
        cout << "Course: " << course.getCourseName() << " - " << course.getSubTopic() << endl;
        for (auto &student : students)
        {
            cout << "Student: " << student.getName() << endl;
            cout << "Assignments submitted: " << endl;
            for (size_t i = 0; i < student.getAssignments().size(); ++i)
            {
                cout << " - " << student.getAssignments()[i] << " - Grade: " << student.getGrades()[i] << endl;
            }
            cout << endl;
        }
    }
};

int mainInstructor()
{
    Instructor instructor;
    string instructorName;
    cout << "Enter your name: ";
    cin >> instructorName;
    instructor.setName(instructorName);

    while (true)
    {
        cout << "\nChoose an option:\n";
        cout << "1. Create Course Content\n";
        cout << "2. Enroll Student\n";
        cout << "3. Assign Assignment\n";
        cout << "4. Grade Assignment\n";
        cout << "5. View Student Progress\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        switch (choice)
        {
        case 1:
            instructor.createCourseContent();
            break;
        case 2:
            instructor.enrollStudent();
            break;
        case 3:
            instructor.assignAssignment();
            break;
        case 4:
            instructor.gradeAssignment();
            break;
        case 5:
            instructor.viewStudentProgress();
            break;
        case 6:
            cout << "Exiting program.\n";
            return 0;
        default:
            cout << "Invalid choice. Please enter a number between 1 and 6.\n";
        }
    }

    return 0;
}
/////////////////////////
//////////////////////
///////////////////
///////////////
///////////
///////
///

#include <iostream>
#include <string>

using namespace std;

int choicequiz;
// Forward declaration of the CourseStudent class
class CourseStudent;
class UserStudent
{
protected:
    string username;
    string password;

public:
    UserStudent() {}

    UserStudent(const string &username, const string &password) : username(username), password(password) {}

    void setUsername(const string &username)
    {
        this->username = username;
    }

    string getUsername() const
    {
        return username;
    }

    void setPassword(const string &password)
    {
        this->password = password;
    }

    string getPassword() const
    {
        return password;
    }

    virtual void login()
    {
        cout << "Logging in as " << username << endl;
    }
};

// Forward declarations
struct CourseMaterial;
struct CourseSession;

class Student : public UserStudent
{
private:
    string name;
    int quizzes;
    int assignments;
    int exams;
    bool certified;

public:
    Student() {}

    Student(const string &username, const string &password, const string &name)
        : UserStudent(username, password), name(name), quizzes(0), assignments(0), exams(0), certified(false) {}

    void submitAssignment()
    {
        // cout << "assignment has been submitted" << endl;

        string studentName, assignment, subject;
    int choice;

    // Predefined subjects
    string subjects[] = {
        "Basic Computer Science", "OOP", "English", "Communications",
        "Calculus 1", "Calculus 2", "Chemistry", "Health", "Stats"
    };

    // Get student's name
    cout << "Enter your name: ";
    getline(cin, studentName);

    // Choose subject for assignment submission
    cout << "Choose the subject for assignment submission:" << endl;
    for (int i = 0; i < 9; ++i) {
        cout << i + 1 << ". " << subjects[i] << endl;
    }
    cout << "Enter your choice (1-9): ";
    cin >> choice;
    cin.ignore(); // Ignore newline character from previous input

    // Check for valid choice
    if (choice >= 1 && choice <= 9) {
        subject = subjects[choice - 1];

        // Get assignment from student
        cout << "Enter your assignment for " << subject << ": ";
        getline(cin, assignment);

        // Submit assignment
        cout << "Student " << studentName << " submitted assignment for " << subject << ": " << assignment << endl;
        
    } else {
        cout << "Invalid choice. Please choose a number between 1 and 9." << endl;
    }


        assignments++;
        // checkCertification();
        
    }

    void takeExam()
    {
        cout << "exam has been taken." << endl;
        exams++;
        checkCertification();
    }
    void takeQuiz(int choicequiz);

    void checkCertification();

    void displayProgress();

    void browseCourses(const CourseStudent courses[], int numCourses);

    void enrollCourse(const CourseStudent &course);

    void accessCourseMaterial(const CourseMaterial materials[], int numMaterials);

    void participateInSession(const CourseSession sessions[], int numSessions);
};

class InstructorStudent : public UserStudent
{
public:
    InstructorStudent() {}

    InstructorStudent(const string &username, const string &password) : UserStudent(username, password) {}

    void createCourse(const string &courseName)
    {
        cout << getUsername() << " created course: " << courseName << endl;
    }
};

class AdministratorStudent : public UserStudent
{
public:
    AdministratorStudent() {}

    AdministratorStudent(const string &username, const string &password) : UserStudent(username, password) {}

    void manageAccounts()
    {
        cout << "Administrator managing accounts" << endl;
    }
};

// Structure to represent a course material item
struct CourseMaterial
{
    string title;
    string content;
    string description;
};

// Structure to represent a class session
struct CourseSession
{
    string topic;
    string instructor;
};

class CourseStudent
{
private:
    string courseName;
    string instructor;
    string description;
    string enrolledStudents[100]; // Array to store enrolled student usernames (assuming maximum 100 students)

public:
    CourseStudent() {}

    CourseStudent(const string &courseName, const string &instructor, const string &description)
        : courseName(courseName), instructor(instructor), description(description) {}

    void setCourseName(const string &courseName)
    {
        this->courseName = courseName;
    }

    string getCourseName() const
    {
        return courseName;
    }

    void setInstructor(const string &instructor)
    {
        this->instructor = instructor;
    }

    string getInstructor() const
    {
        return instructor;
    }

    void setDescription(const string &description)
    {
        this->description = description;
    }

    string getDescription() const
    {
        return description;
    }

    void displayDetails() const
    {
        cout << "Course: " << courseName << endl;
        cout << "Instructor: " << instructor << endl;
        cout << "Description: " << description << endl;
    }

    void enrollStudent(Student &student)
    {
        for (int i = 0; i < 100; ++i)
        {
            if (enrolledStudents[i].empty())
            {
                enrolledStudents[i] = student.getUsername(); // Store the username of the enrolled student
                cout << student.getUsername() << " enrolled in course: " << courseName << endl;
                return;
            }
        }
        cout << "Course is full. Cannot enroll student." << endl;
    }
};

void promptUser(UserStudent &user, const string &role)
{
    string username, password;

    cout << role << " Login:" << endl;
    cout << "Enter username: ";
    cin >> username;
    user.setUsername(username);

    cout << "Enter password: ";
    cin >> password;
    user.setPassword(password);
}

int mainStudent()
{
    
    // Define some imaginary course materials
    CourseMaterial materials[] = {
        {"Introduction to OOP Concepts", "This material covers the basics of object-oriented programming..."},
        {"Classes and Objects", "This material explains classes, objects, and their relationships..."},
        {"Basic Computer Science", "This material covers the fundamentals of computer science..."},
        {"English", "This material covers English language and literature..."},
        {"Communication", "This material covers communication skills..."},
        {"Calculus 1", "This material covers differential calculus..."},
        {"Calculus 2", "This material covers integral calculus..."},
        {"Chemistry", "This material covers basic principles of chemistry..."},
        {"Health", "This material covers topics related to health and wellness..."},
        {"Statistics", "This material covers statistical analysis..."}
    };

    const int numMaterials = sizeof(materials) / sizeof(materials[0]); // Calculate number of materials

    // Define some imaginary class sessions
    CourseSession sessions[] = {
        {"Session on Introduction to OOP Concepts", "This material covers the basics of object-oriented programming..."},
        {"Session on Classes and Objects", "This material explains classes, objects, and their relationships..."},
        {"Session on Basic Computer Science", "This material covers the fundamentals of computer science..."},
        {"Session on English", "This material covers English language and literature..."},
        {"Session on Communication", "This material covers communication skills..."},
        {"Session on Calculus 1", "This material covers differential calculus..."},
        {"Session on Calculus 2", "This material covers integral calculus..."},
        {"Session on Chemistry", "This material covers basic principles of chemistry..."},
        {"Session on Health", "This material covers topics related to health and wellness..."},
        {"Session on Statistics", "This material covers statistical analysis..."}
    };
    const int numSessions = sizeof(sessions) / sizeof(sessions[0]); // Calculate number of sessions
    CourseStudent courses[] = {
        CourseStudent("CS101", "Mr. Talha Ashfaq", "Introduction to Computer Science"),
        CourseStudent("CS112", "Mr Qasim Riaz", "Data Structures and Algorithms"),
        CourseStudent("HM101", "Mr Abrar", "Introduction to History"),
        CourseStudent("HM102", "Ms Hira Ahad", "World History"),
        CourseStudent("MT101", "Mr Fahad Zulfiqar", "Introduction to Mathematics"),
        CourseStudent("MT102", "Mr Asif", "Calculus"),
        CourseStudent("CH101", "Ms Nida", "Introduction to Chemistry"),
        CourseStudent("CH161", "Ms Ramesha Tariq", "Organic Chemistry"),
        CourseStudent("ES111", "Mr Fahad Zulfiqar", "Introduction to Environmental Science")};
    string choice;
    do
    {
        cout << "For student verification press 1 :" << endl;
        
        cin >> choice;
    } while (choice != "1");

    if (choice == "1")
    {
        Student student;
        promptUser(student, "Student");
        student.login();

        // Define the courses
        student.browseCourses(courses, 9);

        // Prompt for actions
        do
        {
            cout << "\nChoose action:" << endl;
            cout << "1. Access Course Material" << endl;
            cout << "2. Participate in Class Session" << endl;
            cout << "3. Take a Quiz" << endl;
            cout << "4. Submit an assignment" << endl;
            cout << "5. Take an Exam" << endl;
            cout << "6. Exit" << endl;
            cout << "Enter choice (1/2/3/4/5/6): ";
            cin >> choice;

            switch (choice[0])
            {
            case '1':
                student.accessCourseMaterial(materials, numMaterials);
                break;
            case '2':
                student.participateInSession(sessions, numSessions);
                break;
            case '3':
                student.takeQuiz(choicequiz);
                break;
            case '4':
                student.submitAssignment();
                break;
            case '5':
                student.takeExam();
                break;
            case '6':
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
            }
        } while (choice != "6");
    }
return 0;
}
// final 3

void Student::browseCourses(const CourseStudent courses[], int numCourses)
{
    cout << "Available Courses:" << endl;
    for (int i = 0; i < numCourses; ++i)
    {
        cout << i + 1 << ". ";
        courses[i].displayDetails();
    }

    cout << "Enter the number of the course you want to enroll in: ";
    cin >> choicequiz;
    if (choicequiz >= 1 && choicequiz <= numCourses)
    {
        enrollCourse(courses[choicequiz - 1]);
    }
    else
    {
        cout << "Invalid choice. Please try again." << endl;
    }
}

void Student::enrollCourse(const CourseStudent &course)
{
    cout << getUsername() << " enrolled in course: " << course.getCourseName() << endl;
}

void Student::accessCourseMaterial(const CourseMaterial materials[], int numMaterials)
{
    cout << "Available Course Materials:" << endl;
    for (int i = 0; i < numMaterials; ++i)
    {
        cout << i + 1 << ". " << materials[i].title << endl;
    }

    int choice;
    cout << "Enter the number of the material you want to access: ";
    cin >> choice;

    if (choice >= 1 && choice <= numMaterials)
    {
        cout << "\n** " << materials[choice - 1].title << " **" << endl;
        cout << materials[choice - 1].content << endl;
    }
    else
    {
        cout << "Invalid choice. Please try again." << endl;
    }
}

void Student::participateInSession(const CourseSession sessions[], int numSessions)
{
    cout << "Available Class Sessions:" << endl;
    for (int i = 0; i < numSessions; ++i)
    {
        cout << i + 1 << ". " << sessions[i].topic << " - " << sessions[i].instructor << endl;
    }

    int choice;
    cout << "Enter the number of the session you want to attend: ";
    cin >> choice;

    if (choice >= 1 && choice <= numSessions)
    {
        cout << "\n** Participating in class session: " << sessions[choice - 1].topic << " **" << endl;
        cout << "Instructor: " << sessions[choice - 1].instructor << endl;
        cout << "(Simulate class participation here, e.g., asking questions, taking notes)" << endl;
    }
    else
    {
        cout << "Invalid choice. Please try again." << endl;
    }
}

void Student::takeQuiz(int choicequiz)
{
    // Function prototypes
    // void quizselection(int choice);
    void cs101quiz();
    void cs112quiz();
    void mt101quiz();
    void mt102quiz();
    void hm101quiz();
    void hm102quiz();
    void ch101quiz();
    void ch161quiz();
    void es111quiz();

    // Function definitions
    // void quizselection(int option) {
    switch (choicequiz)
    {
    case 1:
        cs101quiz();
        break;
    case 2:
        cs112quiz();
        break;
    case 3:
        mt101quiz();
        break;
    case 4:
        mt102quiz();
        break;
    case 5:
        hm101quiz();
        break;
    case 6:
        hm102quiz();
        break;
    case 7:
        ch101quiz();
        break;
    case 8:
        ch161quiz();
        break;
    case 9:
        es111quiz();
        break;
    default:
        cout << "Invalid choice!" << endl;
        break;
    }
    quizzes++;
    checkCertification();
}
void Student::displayProgress()
{
    cout << "Progress of " << name << ":" << endl;
    cout << "Exams taken: " << quizzes << endl;
    cout << "Assignments submitted: " << assignments << endl;
    // cout << "Exams taken: " << exams << endl;
    if (certified)
        cout << "Certified: Yes" << endl;
    else
        cout << "Certified: No" << endl;
}
void cs101quiz()
{
    string answer1, answer2;

    cout << "\n--- Basic Computer Science Quiz ---" << endl;
    cout << "Q1. What is a compiler?" << endl;
    cout << "a) Program that translates source code into machine language" << endl;
    cout << "b) Program that executes machine language instructions" << endl;
    cout << "c) Program that optimizes code for better performance" << endl;
    cout << "Your answer: ";
    cin.ignore();
    getline(cin, answer1);

    cout << "Q2. What is a variable?" << endl;
    cout << "a) Container that holds a value" << endl;
    cout << "b) Control structure" << endl;
    cout << "c) Loop statement" << endl;
    cout << "Your answer: ";
    getline(cin, answer2);

    // Check answers
    if (answer1 == "a" && answer2 == "a")
    {
        cout << "Correct answers! Well done!" << endl;
    }
    else
    {
        cout << "Incorrect answers! Better luck next time!" << endl;
    }
}

void Student::checkCertification()
{
    if (quizzes >= 3 && assignments >= 5 && exams >= 1)
    {
        certified = true;
        cout << "Congratulations, " << name << "! You are certified." << endl;
    }
}

void cs112quiz()
{
    string answer1, answer2;

    cout << "\n--- Object-Oriented Programming (OOP) Quiz ---" << endl;
    cout << "Q1. What is encapsulation?" << endl;
    cout << "a) Combining data and methods that operate on the data into a single unit" << endl;
    cout << "b) Ability of an object to take many forms" << endl;
    cout << "c) Restricting access to certain parts of an object" << endl;
    cout << "Your answer: ";
    cin.ignore();
    getline(cin, answer1);

    cout << "Q2. What is inheritance?" << endl;
    cout << "a) Mechanism by which one class acquires the properties and behavior of another class" << endl;
    cout << "b) Hiding the complexity of a task by providing a simpler interface" << endl;
    cout << "c) Passing data between different objects" << endl;
    cout << "Your answer: ";
    getline(cin, answer2);

    // Check answers
    if (answer1 == "a" && answer2 == "a")
    {
        cout << "Correct answers! You passed the quiz!" << endl;
    }
    else
    {
        cout << "Incorrect answers! Better luck next time!" << endl;
    }
}

void mt101quiz()
{
    string answer1, answer2;

    cout << "\n--- Mathematics Quiz ---" << endl;
    cout << "Q1. What is the value of pi (p)?" << endl;
    cout << "a) 3.14" << endl;
    cout << "b) 3.1416" << endl;
    cout << "c) 3.14159265358979323846" << endl;
    cout << "Your answer: ";
    cin.ignore();
    getline(cin, answer1);

    cout << "Q2. What is the Pythagorean theorem?" << endl;
    cout << "a) a  = b  + c " << endl;
    cout << "b) a + b = c" << endl;
    cout << "c) a   b = c" << endl;
    cout << "Your answer: ";
    getline(cin, answer2);

    // Check answers
    if (answer1 == "c" && answer2 == "a")
    {
        cout << "Correct answers! Well done!" << endl;
    }
    else
    {
        cout << "Incorrect answers! Better luck next time!" << endl;
    }
}

void mt102quiz()
{
    string answer1, answer2;

    cout << "\n--- Calculus 2 Quiz ---" << endl;
    cout << "Q1. What is an integral?" << endl;
    cout << "a) A mathematical operation that finds the product of two numbers" << endl;
    cout << "b) A mathematical operation that finds the area under a curve" << endl;
    cout << "c) A mathematical operation that finds the slope of a curve" << endl;
    cout << "Your answer: ";
    cin.ignore();
    getline(cin, answer1);

    cout << "Q2. What is the integral of 2x with respect to x?" << endl;
    cout << "a) x^2" << endl;
    cout << "b) 2x^2" << endl;
    cout << "c) x" << endl;
    cout << "Your answer: ";
    getline(cin, answer2);

    // Check answers
    if (answer1 == "b" && answer2 == "a")
    {
        cout << "Correct answers! Well done!" << endl;
    }
    else
    {
        cout << "Incorrect answers! Better luck next time!" << endl;
    }
}

void hm101quiz()
{
    string answer1, answer2;

    cout << "\n--- English Quiz ---" << endl;
    cout << "Q1. What is a verb?" << endl;
    cout << "a) A word that describes an action, state, or occurrence" << endl;
    cout << "b) A word that names a person, place, thing, or idea" << endl;
    cout << "c) A word that describes a noun" << endl;
    cout << "Your answer: ";
    cin.ignore();
    getline(cin, answer1);

    cout << "Q2. What is a simile?" << endl;
    cout << "a) Figure of speech in which a word or phrase is applied to an object or action" << endl;
    cout << "b) Figure of speech involving the comparison of one thing with another thing of a different kind" << endl;
    cout << "c) Figure of speech in which a term or phrase is applied to something to which it is not literally applicable" << endl;
    cout << "Your answer: ";
    getline(cin, answer2);

    // Check answers
    if (answer1 == "a" && answer2 == "b")
    {
        cout << "Correct answers! Well done!" << endl;
    }
    else
    {
        cout << "Incorrect answers! Better luck next time!" << endl;
    }
}

void hm102quiz()
{
    string answer1, answer2;

    cout << "\n--- Communications Quiz ---" << endl;
    cout << "Q1. What is the primary function of communication?" << endl;
    cout << "a) To transmit information and share ideas" << endl;
    cout << "b) To entertain people" << endl;
    cout << "c) To manipulate others" << endl;
    cout << "Your answer: ";
    cin.ignore();
    getline(cin, answer1);

    cout << "Q2. What is active listening?" << endl;
    cout << "a) Listening with full attention, fully concentrating on what is being said" << endl;
    cout << "b) Listening only to respond rather than understand" << endl;
    cout << "c) Listening passively without engaging with the speaker" << endl;
    cout << "Your answer: ";
    getline(cin, answer2);

    // Check answers
    if (answer1 == "a" && answer2 == "a")
    {
        cout << "Correct answers! Well done!" << endl;
    }
    else
    {
        cout << "Incorrect answers! Better luck next time!" << endl;
    }
}

void ch101quiz()
{
    string answer1, answer2;

    cout << "\n--- Chemistry Quiz ---" << endl;
    cout << "Q1. What is an element?" << endl;
    cout << "a) Substance that cannot be broken down into simpler substances by chemical means" << endl;
    cout << "b) Substance formed by the chemical combination of two or more elements in definite proportions" << endl;
    cout << "c) Substance that has physical properties of both metals and nonmetals" << endl;
    cout << "Your answer: ";
    cin.ignore();
    getline(cin, answer1);

    cout << "Q2. What is a molecule?" << endl;
    cout << "a) Smallest unit of an element that retains the properties of that element" << endl;
    cout << "b) Smallest unit of a compound that retains the properties of that compound" << endl;
    cout << "c) Smallest unit of matter that retains the properties of that matter" << endl;
    cout << "Your answer: ";
    getline(cin, answer2);

    // Check answers
    if (answer1 == "a" && answer2 == "b")
    {
        cout << "Correct answers! Well done!" << endl;
    }
    else
    {
        cout << "Incorrect answers! Better luck next time!" << endl;
    }
}

void ch161quiz()
{
    string answer1, answer2;

    cout << "\n--- Health Quiz ---" << endl;
    cout << "Q1. What is the recommended daily intake of water for adults?" << endl;
    cout << "a) 1 liter" << endl;
    cout << "b) 2 liters" << endl;
    cout << "c) 3 liters" << endl;
    cout << "Your answer: ";
    cin.ignore();
    getline(cin, answer1);

    cout << "Q2. What is the main function of carbohydrates in the body?" << endl;
    cout << "a) Provide energy" << endl;
    cout << "b) Build muscle" << endl;
    cout << "c) Regulate body temperature" << endl;
    cout << "Your answer: ";
    getline(cin, answer2);

    // Check answers
    if (answer1 == "b" && answer2 == "a")
    {
        cout << "Correct answers! Well done!" << endl;
    }
    else
    {
        cout << "Incorrect answers! Better luck next time!" << endl;
    }
}

void es111quiz()
{
    string answer1, answer2;

    cout << "\n--- Statistics Quiz ---" << endl;
    cout << "Q1. What is the mean of a dataset?" << endl;
    cout << "a) Sum of all values / Number of values" << endl;
    cout << "b) Middle value in a dataset" << endl;
    cout << "c) Most frequent value in a dataset" << endl;
    cout << "Your answer: ";
    cin.ignore();
    getline(cin, answer1);

    cout << "Q2. What is the standard deviation?" << endl;
    cout << "a) Measure of the spread of values in a dataset" << endl;
    cout << "b) Average value in a dataset" << endl;
    cout << "c) Maximum value in a dataset" << endl;
    cout << "Your answer: ";
    getline(cin, answer2);

    // Check answers
    if (answer1 == "a" && answer2 == "a")
    {
        cout << "Correct answers! Well done!" << endl;
    }
    else
    {
        cout << "Incorrect answers! Better luck next time!" << endl;
    }
}
//******************************

int main()
{
    std::cout << "Welcome to the Learning Management System!\n";

    int choice;
    do
    {
        std::cout << "\nChoose an option:\n";
        std::cout << "1. Admin\n";
        std::cout << "2. Instructor\n";
        std::cout << "3. Student\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            // Call admin functionality
            mainadmin();
            break;
        case 2:
            // Call instructor functionality
            // instructorFunctionality();
            mainInstructor();
            break;
        case 3:
            // Call student functionality
            mainStudent();
            break;
        case 4:
            std::cout << "Exiting program.\n";
            break;
        default:
            std::cout << "Invalid choice. Please enter a number between 1 and 4.\n";
        }
    } while (choice != 4);

    return 0;
}
