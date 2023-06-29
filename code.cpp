#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

vector<string> users;



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
        duration =dur;
    }
};

typedef struct userdetails {
    int id;
    string name;
    vector <string> usercourses;
    int months;
}udet;

class manager {
    string response;

    public:
    static vector <user> waiting_list; 
    static vector <udet> report;
    manager(vector <user> &Userobjects) {
        if(Userobjects.size()==0){
            cout<<"No requests..\n";
            return;
        }
        cout<<"Requests:\n";
        for(user i:Userobjects) {
            cout<<i.name<<endl;
            cin>>response;
            bool alreadypresent=false;
            if(response=="Y") {
                for(udet &approvedperson:report) {
                    cout<<approvedperson.name<<endl;
                    if(approvedperson.name==i.name) {
                        if(approvedperson.months+i.duration>12) {
                            cout<<i.name<<" rejected\n";
                            alreadypresent=true;
                            break;
                        }
                        else {
                            cout<<i.name<<" approved\n";
                            approvedperson.usercourses.push_back(i.courseo);
                            approvedperson.months+=i.duration;
                            alreadypresent=true;
                            break;
                        }
                    }
                }

                if(alreadypresent) 
                continue;
                
                udet approvedperson;
                approvedperson.id=i.id;
                approvedperson.name=i.name;
                approvedperson.usercourses.push_back(i.courseo);
                approvedperson.months=i.duration;
                report.push_back(approvedperson);
            }
            else 
            waiting_list.push_back(i);
        }
        
    }

    void approvewaiting(vector <user> &waiters) {
        for(user i:waiters) {
            cout<<i.name<<endl;
            cin>>response;
            bool alreadypresent=false;
            if(response=="Y") {
                for(udet &approvedperson:report) {
                    cout<<approvedperson.name<<endl;
                    if(approvedperson.name==i.name) {
                        if(approvedperson.months+i.duration>12) {
                            cout<<i.name<<" rejected\n";
                            alreadypresent=true;
                            break;
                        }
                        else {
                            cout<<i.name<<" approved\n";
                            approvedperson.usercourses.push_back(i.courseo);
                            approvedperson.months+=i.duration;
                            alreadypresent=true;
                            break;
                        }
                    }
                }

                if(alreadypresent) 
                continue;
                
                udet approvedperson;
                approvedperson.id=i.id;
                approvedperson.name=i.name;
                approvedperson.usercourses.push_back(i.courseo);
                approvedperson.months=i.duration;
                report.push_back(approvedperson);
            }
        }
    }

    
};

vector <user> manager:: waiting_list; 
vector<udet> manager::report;

int main()
{
    int login, no_months;
    fstream new_file;
    string course, username, cname;
    vector<user> userObjects;

    while (1)
    {
        cout << "Enter the login mode." << endl;
        cout << "1. Admin" << endl<< "2. User" << endl<<"3.Manager"<<endl;
        cin >> login;

        switch (login)
        {
        case 1:
        {
            cout << "Admin mode:" << endl;
            cout << "What course has to be added to the training programme" << endl;
            cout << "Enter the course to be added" << endl;
            cin.ignore();
            getline(cin, course);
            cout << "Enter the number of months of the training programme:" << endl;
            cin >> no_months;
            new_file.open("courses.txt", ios::app);
            new_file << endl << course << ' ' << no_months;
            new_file.close();
            cout<<"Course has been added successfully!!!"<<endl;
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
            if(selectedCourseNumber>=courseNumber|| selectedCourseNumber<=0)
            {
                cout<<"Please enter a valid training programme code!"<<endl;
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

            //cout << name.id << ' ' << name.name << endl;

            cout << "User Objects:" << endl;
            for (auto userObj:userObjects)
            {
                cout << "ID: " << userObj.id << ", Name: " << userObj.name << ", Course: " << userObj.courseo << ", Duration: " << userObj.duration << " months" << endl;
            }

            break;
        }
        case 3: {
            manager man(userObjects);
            string response;
            if(manager::waiting_list.size()!=0) {
                cout<<"Approve waiters?    ";
                cin>>response;
                if(response=="Y") {
                    man.approvewaiting(manager::waiting_list);
                }
            }
            //man.displayreport(manager::report);
            userObjects.clear();
            break;
        }
        default:
        exit(0);
        }
    }
}
