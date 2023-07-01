#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;
class user;
vector<string> users;

namespace training
{
    int login, no_months;
    fstream new_file;
    string course, username, cname;
    void login1();
}

class user
{
public:
    int id;
    string name;
    string courseo;
    int duration;
    user(string username, string cname, int dur)
    {
        users.push_back(username);
        name = username;
        id = users.size();
        courseo = cname;
        duration = dur;
    }
};

typedef struct userdetails
{
    int id;
    string name;
    vector<string> usercourses;
    int months;
} udet;

class manager
{
    string response;

public:
    friend void displayreport(vector<udet> report);
    static vector<user> waiting_list;
    static vector<udet> report;
    manager(vector<user> &Userobjects)
    {
        if (Userobjects.size() == 0)
        {
            cout << "No requests..\n";
            return;
        }
        cout << "Requests:\n";
        for (user i : Userobjects)
        {
            cout << i.name << endl;
        q:
            cin >> response;
            bool alreadypresent = false;
            if (response == "Y" || response == "y")
            {
                for (udet &approvedperson : report)
                {
                    // cout<<approvedperson.name<<endl;
                    if (approvedperson.name == i.name)
                    {
                        if (approvedperson.months + i.duration > 12)
                        {
                            cout << i.name << " rejected\n";
                            alreadypresent = true;
                            break;
                        }
                        else
                        {
                            cout << i.name << " approved\n";
                            approvedperson.usercourses.push_back(i.courseo);
                            approvedperson.months += i.duration;
                            alreadypresent = true;
                            break;
                        }
                    }
                }

                if (alreadypresent)
                    continue;

                udet approvedperson;
                approvedperson.id = i.id;
                approvedperson.name = i.name;
                approvedperson.usercourses.push_back(i.courseo);
                approvedperson.months = i.duration;
                report.push_back(approvedperson);
            }
            else if (response == "n" || response == "N")
                waiting_list.push_back(i);
            else
            {
                cout << "Enter a valid choice\n";
                goto q;
            }
        }
    }

    void approvewaiting(vector<user> &waiters)
    {
        for (user i : waiters)
        {
            cout << i.name << endl;
            cin >> response;
            bool alreadypresent = false;
            if (response == "Y" || response == "y")
            {
                for (udet &approvedperson : report)
                {
                    if (approvedperson.name == i.name)
                    {
                        if (approvedperson.months + i.duration > 12)
                        {
                            cout << i.name << " rejected\n";
                            alreadypresent = true;
                            break;
                        }
                        else
                        {
                            cout << i.name << " approved\n";
                            approvedperson.usercourses.push_back(i.courseo);
                            approvedperson.months += i.duration;
                            alreadypresent = true;

                            break;
                        }
                    }
                }

                if (alreadypresent)
                    continue;

                udet approvedperson;
                approvedperson.id = i.id;
                approvedperson.name = i.name;
                approvedperson.usercourses.push_back(i.courseo);
                approvedperson.months = i.duration;
                report.push_back(approvedperson);
            }
        }
        waiters.clear();
    }
};

void displayreport(vector<udet> &report)
{
    cout << "Annual status: \n";
    for (udet final : report)
    {
        cout << "-----------------------------\n";
        cout << "ID: " << final.id << "\n"
             << "Name: " << final.name << "\n"
             << "Duration: " << final.months << "\n";
        for (string skill : final.usercourses)
            cout << skill << ' ';
        cout << '\n';
    }
    cout << "\n";
}

vector<user> manager::waiting_list;
vector<udet> manager::report;
void training::login1()
{
    vector<user> userObjects;

    while (1)
    {
    label:
        cout << "Enter the login mode." << endl;
        cout << "1. Admin" << endl
             << "2. User" << endl
             << "3.Manager" << endl
             << "4.Exit" << endl;
        try // exception handling
        {
            cin >> login;
            if (login != 1 && login != 2 && login != 3 && login != 4)
            {
                throw(login);
            }
        }
        catch (int login)
        {
            cout << "Enter either 1/2/3/4\n";
            cin.clear();
            cin.ignore();
            goto label;
        }

        switch (login)
        {
        case 1:
        
            {
    int monthss;
string line;
bool courseExists = false;
cout << "Admin mode:" << endl;
l:
cin.ignore();
cout << "What course has to be added to the training programme" << endl;
cout << "Enter the course to be added" << endl;
getline(cin, course);
cin.ignore();
cout << "Enter the number of months of the training programme:" << endl;
cin >> no_months;
new_file.open("courses.txt", ios::in);
string courseName;
while (new_file >> courseName >> monthss)
{
        if (courseName == course && monthss == no_months)
    {
        cout << "The course already exists!\n";
        courseExists = true;
        break;
    }
}
new_file.close();

if (!courseExists)
{
    new_file.open("courses.txt", ios::app);
    new_file << endl
             << course << ' ' << no_months;
    new_file.close();
    cout << "Course has been added successfully!!!" << endl;
}
else
{
    goto l;
}

    break;
}
        

        case 2:
        {
            cout << "User mode:" << endl;
            cout << "Enter your name:" << endl;
            cin.ignore();
            getline(cin, username);
            cout << "Enter the number corresponding to the course you want to opt for:" << endl;
            cout << "Available choices:(in the format Course    No.of months)" << endl;
            new_file.open("courses.txt", ios::in);
            string line;
            int courseNumber = 1;
            while (getline(new_file, line))
            {
                cout << courseNumber << ". " << line << endl;
                courseNumber++;
            }
            new_file.close();

            int selectedCourseNumber;
        k:
            cin >> selectedCourseNumber;
            cin.ignore();
            if (selectedCourseNumber >= courseNumber || selectedCourseNumber <= 0)
            {
                cout << "Please enter a valid training programme code!" << endl;
                goto k;
            }
            new_file.open("courses.txt", ios::in);
            string selectedCourse;
            int currentCourseNumber = 1;
            while (getline(new_file, line))
            {
                if (currentCourseNumber == selectedCourseNumber)
                {
                    selectedCourse = line;
                    break;
                }
                currentCourseNumber++;
            }
            new_file.close();

            // Extracting course and duration from selectedCourse
            stringstream ss(selectedCourse);
            string courseName;
            ss >> courseName >> no_months;

            user name(username, courseName, no_months);
            userObjects.push_back(name);

            // cout << name.id << ' ' << name.name << endl;

            cout << "User Objects:" << endl;
            for (auto userObj : userObjects)
            {
                cout << "ID: " << userObj.id << ", Name: " << userObj.name << ", Course: " << userObj.courseo << ", Duration: " << userObj.duration << " months" << endl;
            }

            break;
        }
        case 3:
        {
            manager man(userObjects);
            string response;
            if (manager::waiting_list.size() != 0)
            {
                cout << "Approve waiters? (y/n)   ";
                cin >> response;
                if (response == "Y" || response == "y")
                {
                    man.approvewaiting(manager::waiting_list);
                }
                else if (response == "N" || response == "n")
                {
                }
                else
                {
                    cout << "Please enter a valid choice\n";
                }
            }
            displayreport(manager::report);
            userObjects.clear();
            break;
        }
        case 4:
            exit(0);
        }
    }
}
int main()
{
    training::login1();
}
