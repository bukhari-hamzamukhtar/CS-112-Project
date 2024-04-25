#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Base class User
class User
{
protected:
    string username;
    string password;
    string userType;

public:
    User(const string &username, const string &password, const string &userType)
    {
        this->username=username;
        this->password=password;
        this->userType=userType;
    }

    virtual void displayInfo() const
    {
        cout << "Username: " << username << "\nType: " << userType << endl;
    }

    virtual ~User() // Virtual destructor
    {

    } 

};

// Derived class Student
class Student : public User
{
public:
    Student(const string &username, const string &password)
        : User(username, password, "Student") {}

    void displayInfo() const override
    {
        cout << "Student Account\n";
        User::displayInfo();
    }
};

// Derived class Instructor
class Instructor : public User
{
public:
    Instructor(const string &username, const string &password)
        : User(username, password, "Instructor") {}

    void displayInfo() const override
    {
        cout << "Instructor Account\n";
        User::displayInfo();
    }
};

// Derived class Administrator
class Administrator : public User
{
public:
    Administrator(const string &username, const string &password)
        : User(username, password, "Administrator") {}

    void displayInfo() const override
    {
        cout << "Administrator Account\n";
        User::displayInfo();
    }
};

// Function to create a new user
User *createUser(const string &userType, const string &username, const string &password)
{
    if (userType == "Student")
    {
        return new Student(username, password);
    }
    else if (userType == "Instructor")
    {
        return new Instructor(username, password);
    }
    else if (userType == "Administrator")
    {
        return new Administrator(username, password);
    }
    else
    {
        return nullptr;
    }
}

int main()
{
    // Example usage:
    User *newUser = createUser("Administrator", "admin_user", "securepass");
    if (newUser)
    {
        newUser->displayInfo();
        delete newUser; // Remember to deallocate memory
    }

    return 0;
}
