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
    void search();
    void update();
    void del();
    void display1();
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
    if (cin.fail())
    {
        cout << "Invalid input! Please enter an integer.";
    }
    cout << "Enter student name :\n";
    cin.ignore();
    cin.getline(name, 50);
    cout << "Enter class name :\n";
    cin.ignore();
    cin.getline(classsname, 20);
    cout << "Enter section :\n";
    cin.ignore();
    cin.getline(section, 5);
    cout << "Enter father's name :\n";
    cin.ignore();
    cin.getline(fathername, 30);
    cout << "Enter contact number :\n";
    cin.ignore();
    cin.getline(contactno, 15);
    cout << "Enter total fee paid :\n";
    cin >> totalfee;
    if (cin.fail())
    {
        cout << "Invalid input! Please enter a float value.";
    }
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
        cout << "\nStudent not found" << endl;
    }
    fs.close();
}
void student::update()
{
    fstream fu;
    fu.open("student.dat", ios::in | ios::out | ios::binary);
    if (!fu)
    {
        cout << "File not found";
        exit(0);
    }
    cout << "Enter student id to update : ";
    int sid;
    cin >> sid;
    bool found = false;
    int choice;
    while (fu.read((char *)this, sizeof(student)))
    {
        if (stu_id == sid)
        {
            cout << "-----------------------------" << endl;
            cout << "1. Update name \n";
            cout << "2. Update class name \n";
            cout << "3. Update section \n";
            cout << "4. Update father's name \n";
            cout << "5. Update contact number" << endl;
            cout << "6. Update total fee paid" << endl;
            cout << "------------------------------" << endl;
            cin >> choice;
            switch (choice)
            {
            case 1:
                cout << "Enter new name: ";
                cin.ignore();
                cin.getline(name, 50);
                break;

            case 2:
                cout << "Enter new class name: ";
                cin.ignore();
                cin.getline(classsname, 20);
                break;

            case 3:
                cout << "Enter new section: ";
                cin.ignore();
                cin.getline(section, 5);
                break;

            case 4:
                cout << "Enter new father's name: ";
                cin.ignore();
                cin.getline(fathername, 30);
                break;

            case 5:
                cout << "Enter new contact number: ";
                cin.ignore();
                cin.getline(contactno, 15);
                break;
            case 6:
                cout << "Enter new total fee paid: ";
                cin >> totalfee;
                if (cin.fail())
                {
                    cout << "Invalid input! Please enter a float value.";
                }
                break;
            default:
                cout << "Invalid choice!" << endl;
            }
            bool wantToUpdate;
            cout << "Do you want to make this change? (y/n): ";
            cin >> wantToUpdate;
            if (wantToUpdate)
            {

                fu.seekp(fu.tellg(),ios::cur);
                fu.write((char *)this, sizeof(student));
                cout << "UPDATE SUCCESSFUL" << endl;
                cout << "-----------------------------" << endl;
            }
            else
            {
                cout << "Update cancelled." << endl;
            }

            found = true;
        }
    }
    if (!found)
    {
        cout << "Student not found" << endl;
    }
    fu.close();
}
void student::del()
{
    fstream fd;
    fstream ft;

    fd.open("student.dat", ios::in | ios::binary);

    if (!fd)
    {
        cout << "File Not Found" << endl;
        return;
    }

    ft.open("temp.dat", ios::out | ios::binary);

    if (!ft)
    {
        cout << "Temporary file could not be opened" << endl;
        fd.close();
        return;
    }

    cout << "Enter student id to delete: ";
    int sid;
    cin >> sid;

    bool found = false;

    while (fd.read((char *)this, sizeof(student)))
    {
        if (stu_id == sid)
        {
            bool wantToDelete;
            cout << "Are you sure you want to delete this record? (y/n): ";
            cin >> wantToDelete;
            if (wantToDelete)
            {
                found = true;
                cout << "Student record deleted successfully!" << endl;
            }
        }
        else
        {
            ft.write((char *)this, sizeof(student));
        }
    }

    fd.close();
    ft.close();

    if (!found)
    {
        cout << "Invalid choice" << endl;
        remove("temp.dat");
        return;
    }

    remove("student.dat");
    rename("temp.dat", "student.dat");
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
            cout << "-----------------------------" << endl;
            found = true;
            break;
        }
    }
    if (!found)
    {
        cout << "\nStudent not found" << endl;
    }
    fs.close();
}
void Admin()
{
    student s;
    int choice;
    cout << "-----------------------------" << endl;
    int code;
    cout << "if you are Admin, Enter code: ";
    cin >> code;
    if (code == 1357)
    {
        do
        {
            cout << "-----------------------------" << endl;
            cout << "1. Add student ";
            cout << "\n2. Display all student ";
            cout << "\n3. Search student ";
            cout << "\n4. Update student ";
            cout << "\n5. Delete student ";
            cout << "\n6. Exit" << endl;
            cout << "MAKE CHOICE : ";
            cin >> choice;
            switch (choice)
            {
            case 1:
                s.add();
                break;
            case 2:
                s.display();
                break;
            case 3:
                s.search();
                break;
            case 4:
                s.update();
                break;
            case 5:
                s.del();
                break;
            case 6:
                exit(0);
                break;
            default:
                cout << " Invalid Choice ";
            }
        } while (choice != 6);
    }
    else
    {
        cout << "Invalid code" << endl;
    }
}
void stu()
{
    int choice;
    student s;
    do
    {
        cout << "-----------------------------" << endl;
        cout << "\n1. Display single student ";
        cout << "\n2. Search student ";
        cout << "\n3. Exit" << endl;
        cout << "MAKE CHOICE : ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            s.display1();
            break;
        case 2:
            s.search();
            break;
        case 3:
            exit(0);
        default:
            cout << "Invalid Choice" << endl;
        }
    } while (choice != 3);
}

int main()
{
    system("cls");
    cout << " ---STUDENT MANAGEMENT SYSTEM---" << endl;
    int position;
    cout << "\n1. Admin \n2. Student" << endl;
    cout << "Enter your position : ";
    cin >> position;
    int ch;
    if (position == 1)
    {
        Admin();
    }
    if (position == 2)
    {
        stu();
    }
}
