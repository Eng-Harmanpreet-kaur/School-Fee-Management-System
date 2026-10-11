#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class student
{
private:
    int stu_id;
    char name[50];
    char section[5];
    char classsname[20];
    char fathername[30];
    char contactno[15];
    float totalfee;

public:
    void add();
    void display();
    void display1();
    void search();
    void update();
    void del();
};
void student::add()
{
    ofstream f("student.dat", ios::app | ios::binary);
    if (!f)
    {
        cout << "file not found";
        exit(0);
    }
    cout << "-----------------------------" << endl;
    cout << " Enter student id : \n";
    cin >> stu_id;
    cout << "Enter student name :\n";
    cin.ignore();
    cin.getline(name, 50);
    cout << "Enter class name :\n";
    cin.getline(classsname, 20);
    cout << "Enter section :\n";
    cin.getline(section, 5);
    cout << "Enter father's name :\n";
    cin.getline(fathername, 30);
    cout << "Enter contact number :\n";
    cin.getline(contactno, 15);
    cout << "Enter total fee paid :\n";
    cin >> totalfee;
    cout << "-----------------------------" << endl;
    f.write((char *)this, sizeof(student));
    f.close();
}
void student::display()
{
    fstream fl;
    fl.open("student.dat", ios::in | ios::binary);
    if (!fl)
    {
        cout << "file not found";
        exit(0);
    }
    while (fl.read((char *)this, sizeof(student)))
    {
        cout << "-----------------------------" << endl;
        cout << "Student id " << stu_id << endl;
        cout << "Student name " << name << endl;
        cout << "Class name " << classsname << endl;
        cout << "Section " << section << endl;
        cout << "Father's name " << fathername << endl;
        cout << "Contact number " << contactno << endl;
        cout << "Total fee paid " << totalfee << endl;
        cout << "-----------------------------" << endl;
    }
    fl.close();
}
void student::search()
{
    int sid;
    fstream fs;
    fs.open("student.dat", ios::in | ios::binary);
    if (!fs)
    {
        cout << "file not found";
        exit(0);
    }
    cout << "Enter student id to search : ";
    cin >> sid;
    bool found = 0;
    while (fs.read((char *)this, sizeof(student)))
    {
        if (stu_id == sid)
        {
            cout << "-----------------------------" << endl;
            cout << "Student id " << stu_id << endl;
            cout << "Student name " << name << endl;
            cout << "Class name " << classsname << endl;
            cout << "Section " << section << endl;
            cout << "Father's name " << fathername << endl;
            cout << "Contact number " << contactno << endl;
            cout << "Total fee paid " << totalfee << endl;
            cout << "-----------------------------" << endl;
            found = 1;
            break;
        }
    }
    if (!found)
    {
        cout << " Student not found" << endl;
    }
    fs.close();
}
void student::update()
{
    ifstream fu;
    fu.open("student.dat", ios::in | ios::binary);
    if (!fu)
    {
        cout << "File not found";
        exit(0);
    }
    cout << "Enter student id to update : ";
    int sid;
    cin >> sid;
    while (fu.read((char *)this, sizeof(student)))
    {
        if (stu_id == sid)
        {
            cout << "-----------------------------" << endl;
            cout << "Enter new name : ";
            cin.ignore();
            cin.getline(name, 50);
            cout << "Enter new class name : ";
            cin.getline(classsname, 20);
            cout << "Enter new section : ";
            cin.getline(section, 5);
            cout << "Enter new father's name : ";
            cin.getline(fathername, 30);
            cout << "Enter new contact number : ";
            cin.getline(contactno, 15);
            cout << "UPDATE SUCCESSFUL" << endl;
            cout << "-----------------------------" << endl;
        }
    }
    fu.close();
}
void student::del()
{
    fstream fd;
    fd.open("student.dat", ios::in | ios::out | ios::trunc);
    if (!fd)
    {
        cout << "File Not Found ";
        exit(0);
    }
    int choice, sid;
    cout << "-----------------------------" << endl;
    cout << " 1. Delete all \n 2. Delete by id ";
    cout << "-----------------------------" << endl;
    cout << "\n Enter your choice : ";
    cin >> choice;
    if (choice == 1)
    {
        fd.close();
        remove("student.dat");
        cout << "ALL DELETED SUCCESSFULLY" << endl;
        exit(0);
    }
    else if (choice == 2)
    {
        cout << "Enter student id to delete : ";
        cin >> sid;
        fstream temp;
        temp.open("temp.dat", ios::out | ios::binary);
        if (!temp)
        {
            cout << "File not found";
            exit(0);
        }
        while (fd.read((char *)this, sizeof(student)))
        {
            if (stu_id != sid)
            {
                temp.write((char *)this, sizeof(student));
            }
        }
        fd.close();
        temp.close();
        remove("student.dat");
        rename("temp.dat", "student.dat");
        cout << "DELETED SUCCESSFULLY" << endl;
    }
    else
    {
        cout << "Invalid choice";
    }
}
void student::display1()
{
    fstream fs;
    fs.open("student.dat", ios::in | ios::binary);
    if (!fs)
    {
        cout << "file not found";
        exit(0);
    }
    int sid;
    cout << "Enter student id to display : ";
    cin >> sid;
    bool found = false;
    while (fs.read((char *)this, sizeof(student)))
    {
        if (stu_id == sid)
        {
            cout << "-----------------------------" << endl;
            cout << "Student id " << stu_id << endl;
            cout << "Student name " << name << endl;
            cout << "Class name " << classsname << endl;
            cout << "Section " << section << endl;
            cout << "Father's name " << fathername << endl;
            cout << "Contact number " << contactno << endl;
            cout << "Total fee paid " << totalfee << endl;
            cout<<"-----------------------------"<<endl;
            found = true;
            break;
        }
    }
    if (!found)
    {
        cout << " Student not found" << endl;
    }
    fs.close();
}
void stu(){
    student s;
int c;
     do
        {   
            cout<<"-----------------------------"<<endl;
            cout << "\n1. Display your info ";
            cout << "\n2. Search student ";
            cout << "\n3. Exit" << endl;
            cout<<"-----------------------------"<<endl;
            cout << "MAKE CHOICE : ";
            cin >> c;
            switch (c)
            {
            case 1:
                s.display1();
                break;
            case 2:
                s.search();
                break;
            case 3:
                break;
            default:
                cout << "Invalid Choice" << endl;
                break;
            }
        }while(c!= 3);
    }
void admin(){
    int pass;
    cout<<"Enter your passwoed to continue :";
    cin>>pass;
    int p=7513;
    if(pass==p){
    student a;
    int choice;
    cout<<"-------ACCESS GRANTED------- "<<endl;
    do{
    cout << "-----------------------------" << endl;
    cout<<" 1. Add Student "<<endl;
    cout << "2. Display single student "<<endl;
        cout << "3. Display all student "<<endl;
        cout << "4. Search student "<<endl;
        cout << "5. Update student "<<endl;
        cout << "6. Delete student "<<endl;
        cout << "7. Exit" << endl;
        cout<<"-----------------------------"<<endl;
        cout << "MAKE CHOICE : ";
        cin >> choice;
      switch (choice)
        {
        case 1:
            a.add();
            break;
        case 2:
            a.display1();
            break;
        case 3:
            a.display();
            break;
        case 4:
            a.search();
            break;
        case 5:
            a.update();
            break; 
        case 6:
            a.del();
            break;
        case 7:
            break;
            default:
            cout << " Invalid Choice ";
            break;
        }
    }while(choice!=7);
}

    else
    cout<<"-------ACCESS DENIED-------";
}

int main()
{
    cout << " ---STUDENT MANAGEMENT SYSTEM---" << endl;
    student s;
    int c;
    do
    {
        cout << "\tYour Role ? \n\t 1. Admin \n\t 2. Student \n\t 3. Exit ";
        cout << "Make choice : ";
        cin >> c;
        if(c==1){
        admin();
        }
        else if(c==2){
            stu();
        }
    }while (c!=3);
    cout<<" EXIT SUCCESSFUL ";
}
