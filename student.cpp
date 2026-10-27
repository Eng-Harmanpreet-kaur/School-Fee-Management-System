#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;
class student
{
private:
    int stu_id;
    char name[50];
    char section[5];
    char classname[20];
    char fathername[30];
    char contactno[15];
    float totalfee;

public:
    void add();
    void display();
    void search();
    void update();
    void del();
    void displaystu();
};

void student::add()
{
    ofstream f("student.dat", ios::app | ios::binary);
    if (!f)
    {
        cout << "< Error with file opening >";
        return;
    }
    cout << "---------------------------\n";
    cout << "ADD STUDENT INFO \n";
    cout << "Enter student id : ";
    cin >> stu_id;
    if (cin.fail() || stu_id <= 0)
    {
        cout << "\n< ERROR: Student ID must be a positive number >" << endl;
        cin.clear();
        cin.ignore(1000, '\n');
        return;
    }
    cin.ignore();
    cout << "Enter student name : ";
    cin.getline(name, 50);
    cout << "Enter class name : ";
    cin.getline(classname, 20);
    cout << "Enter section : ";
    cin.getline(section, 5);
    cout << "Enter father's name : ";
    cin.getline(fathername, 30);
    cout << "Enter contact number : ";
    cin.getline(contactno, 15);
    if (cin.fail() || strlen(contactno) != 10)
    {
        cout << "< ERROR: Contact Number must contain 10 digits >\n";
        cin.clear();
        cin.ignore(1000, '\n');
        return;
    }
    cout << "Enter total fee paid : ";
    cin >> totalfee;
    if (cin.fail() || totalfee < 0)
    {
        cout << "< ERROR: Fee must be a non-negative number >\n";
        cin.clear();
        cin.ignore(1000, '\n');
        return;
    }
    cout << "---------------------------\n";
    cout << " Are you sure to add this info (Y/N): \n";
    char confirm;
    cin >> confirm;
    if (confirm == 'Y' || confirm == 'y')
    {
        f.write((char *)this, sizeof(student));
        f.close();
        cout << "< Record added Successfully >\n";
    }
    else if (confirm == 'N' || confirm == 'n')
    {
        cout << "< Record addition cancelled >\n";
        f.close();
    }
    else
        cout << "< Invalid Action >";
}

void student::display()
{
    fstream fl;
    fl.open("student.dat", ios::in | ios::binary);
    if (!fl)
    {
        cout << "< file not found >";
        return;
    }
    while (fl.read((char *)this, sizeof(student)))
    {
        cout << "-----------------------------" << endl;
        cout << "Student id: " << stu_id << endl;
        cout << "Student name: " << name << endl;
        cout << "Class name: " << classname << endl;
        cout << "Section: " << section << endl;
        cout << "Father's name: " << fathername << endl;
        cout << "Contact number: " << contactno << endl;
        cout << "Total fee paid: " << totalfee << endl;
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
        cout << "< file not found >";
        return;
    }
    cout << "Enter student id to search : ";
    cin >> sid;
    if (cin.fail() || sid <= 0)
    {
        cout << "\n< ERROR: Student ID must be a positive number >" << endl;
        cin.clear();
        cin.ignore(1000, '\n');
        return;
    }
    bool found = 0;
    while (fs.read((char *)this, sizeof(student)))
    {
        if (stu_id == sid)
        {
            cout << "-----------------------------" << endl;
            cout << "Student id: " << stu_id << endl;
            cout << "Student name: " << name << endl;
            cout << "Class name: " << classname << endl;
            cout << "Section: " << section << endl;
            cout << "Father's name: " << fathername << endl;
            cout << "Contact number: " << contactno << endl;
            cout << "Total fee paid: " << totalfee << endl;
            cout << "-----------------------------" << endl;
            found = 1;
            break;
        }
    }
    if (!found)
    {
        cout << "\n< Student record not found! >" << endl;
    }
    fs.close();
}

void student::update()
{
    fstream fu("student.dat", ios::in | ios::binary);
    ofstream temp("temp.dat", ios::binary);
    if (!fu || !temp)
    {
        cout << "< File not found >";
        return;
    }
    int sid, ch;
    bool found = 0;
    student s;
    bool cancelledUpdate = false;
    cout << "Enter student id to update: ";
    cin >> sid;
    if (cin.fail() || sid <= 0)
    {
        cout << "< Student ID must be a positive integer >" << endl;
        cin.clear();
        cin.ignore(1000, '\n');
        fu.close();
        temp.close();
        remove("temp.dat");
        return;
    }
    while (fu.read((char *)&s, sizeof(student)))
    {
        if (s.stu_id == sid)
        {
            cout << "---------------------------\n";
            found = 1;
            cout << "student record u searched for UPDATE: " << endl;
            cout << "Student ID: " << s.stu_id << endl;
            cout << "Name: " << s.name << endl;
            cout << "Class: " << s.classname << endl;
            cout << "Section : " << s.section << endl;
            cout << "Father's Name: " << s.fathername << endl;
            cout << "Contact No: " << s.contactno << endl;
            cout << "Total Fee Paid: " << s.totalfee << endl;
            cout << "Record Found\n";
            student original = s;
            do
            {
                cout << "----------Update Menu----------\n";
                cout << "1. Update name\n";
                cout << "2. Update class name\n";
                cout << "3. Update section\n";
                cout << "4. Update father's name\n";
                cout << "5. Update contact number\n";
                cout << "6. Update total fee paid\n";
                cout << "7. Cancel changes\n";
                cout << "8. Finish updating\n";
                cout << "---------------------------\n";
                cout << "Enter choice: ";
                cin >> ch;
                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "< Enter a valid integer >\n";
                    continue;
                }
                cin.ignore();
                switch (ch)
                {
                case 1:
                    cout << "Enter new name: ";
                    cin.getline(s.name, 50);
                    break;
                case 2:
                    cout << "Enter new class name: ";
                    cin.getline(s.classname, 20);
                    break;
                case 3:
                    cout << "Enter new section: ";
                    cin.getline(s.section, 5);
                    break;
                case 4:
                    cout << "Enter new father's name: ";
                    cin.getline(s.fathername, 30);
                    break;
                case 5:
                    cout << "Enter new contact number: ";
                    cin.getline(s.contactno, 15);
                    if (cin.fail() || strlen(s.contactno) != 10)
                    {
                        cout << "< ERROR: Contact Number must contain 10 digits >\n";
                        cin.clear();
                        cin.ignore(1000, '\n');
                        return;
                    }
                    break;
                case 6:
                    cout << "Enter new total fee paid: ";
                    cin >> s.totalfee;
                    if (cin.fail() || s.totalfee < 0)
                    {
                        cout << "< ERROR: Fee must be a non-negative number >\n";
                        cin.clear();
                        cin.ignore(1000, '\n');
                        return;
                    }
                    break;
                case 7:
                    s = original;
                    cancelledUpdate = true;
                    ch = 8;
                    cout << "< Changes cancelled >" << endl;
                    break;
                case 8:
                    cout << "Finishing update.....\n";
                    break;
                default:
                    cout << "< Invalid choice >\n";
                }
            } while (ch != 8);
        }
        temp.write((char *)&s, sizeof(student));
    }
    if (found)
    {
        if (cancelledUpdate)
        {
            remove("temp.dat");
        }
        else
        {
            remove("student.dat");
            rename("temp.dat", "student.dat");
            cout << "< Record updated successfully >" << endl;
        }
    }
    else
    {
        remove("temp.dat");
        cout << "< Student record not found >" << endl;
    }
}

void student::del()
{
    fstream fd;
    ofstream ft;
    int sid, choice;
    cout << "1. Delete By ID : " << endl;
    cout << "2. Delete All " << endl;
    cout << "Make decision : ";
    cin >> choice;
    if (choice == 1)
    {
        fd.open("student.dat", ios::in | ios::binary);
        if (!fd)
        {
            cout << "< File Not Found >" << endl;
            return;
        }
        cout << "Enter student id to delete: ";
        cin >> sid;
        if (cin.fail() || sid <= 0)
        {
            cout << "< Invalid student id >" << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            fd.close();
            return;
        }
        ft.open("temp.dat", ios::out | ios::binary);
        if (!ft)
        {
            cout << "< Temporary file could not be opened >" << endl;
            fd.close();
            return;
        }
        bool found = false;
        bool deleted = false;
        bool cancelled = false;
        while (fd.read((char *)this, sizeof(student)))
        {
            if (stu_id == sid)
            {
                found = true;
                cout << "---------------------------\n";
                cout << "Student record searched for DELETE:\n";
                cout << "Student ID: " << stu_id << endl;
                cout << "Name: " << name << endl;
                cout << "Class: " << classname << endl;
                cout << "Section: " << section << endl;
                cout << "Father's Name: " << fathername << endl;
                cout << "Contact No: " << contactno << endl;
                cout << "Total Fee Paid: " << totalfee << endl;
                cout << "---------------------------\n";
                char sure;
                cout << "Are you sure you want to delete this record? (Y/N): ";
                cin >> sure;
                if (sure == 'Y' || sure == 'y')
                {
                    deleted = true;
                    cout << "< Student record deleted successfully! >" << endl;
                }
                else if (sure == 'N' || sure == 'n')
                {
                    cancelled = true;
                    ft.write((char *)this, sizeof(student));
                    cout << "< Delete cancelled >" << endl;
                }
                else
                {
                    cancelled = true;
                    ft.write((char *)this, sizeof(student));
                    cout << "< Invalid choice. Delete cancelled >" << endl;
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
            remove("temp.dat");
            cout << "< Student record not found! >" << endl;
        }
        else if (cancelled)
        {
            remove("temp.dat");
        }
        else if (deleted)
        {
            remove("student.dat");
            rename("temp.dat", "student.dat");
        }
    }
    else if (choice == 2)
    {
        fd.open("student.dat", ios::out | ios::binary | ios::trunc);
        if (!fd)
        {
            cout << "< File could not be opened >" << endl;
            return;
        }
        fd.close();
        cout << "< All records deleted >" << endl;
    }
    else
    {
        cout << "< Invalid Choice >" << endl;
    }
}

void student::displaystu()
{
    fstream fs;
    fs.open("student.dat", ios::in | ios::binary);
    if (!fs)
    {
        cout << "< file not found >";
        return;
    }
    int sid;
    cout << "Enter student id to display : ";
    cin >> sid;
    bool found = false;
    while (fs.read((char *)this, sizeof(student)))
    {
        if (stu_id == sid)
        {
            cout << "---------------------------\n";
            cout << "STUDENT DETAILS" << endl;
            cout << "---------------------------\n";
            cout << "Student id: " << stu_id << endl;
            cout << "Student name: " << name << endl;
            cout << "Class name: " << classname << endl;
            cout << "Section: " << section << endl;
            cout << "Father's name: " << fathername << endl;
            cout << "Contact number: " << contactno << endl;
            cout << "Total fee paid: " << totalfee << endl;
            cout << "-----------------------------" << endl;
            found = true;
            break;
        }
    }
    if (!found)
    {
        cout << "\n< Student record not found! >" << endl;
    }
    fs.close();
}

void Admin()
{
    student s;
    int choice;
    int code;
    cout << "---------------------------\n";
    cout << "if you are Admin, Enter code: ";
    cin >> code;
    if (code == 1357)
    {
        do
        {
            cout << endl;
            cout << "------Admin Menu------" << endl;
            cout << "1. Add student ";
            cout << "\n2. Display all student ";
            cout << "\n3. Search student ";
            cout << "\n4. Update student ";
            cout << "\n5. Delete student ";
            cout << "\n6. Exit" << endl;
            cout << "---------------------------\n";
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
                cout << "EXITING..." << endl;
                exit(0);
                break;
            default:
                cout << " \n < ERROR: Invalid Choice > \n ";
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
        cout << "------Student Menu------" << endl;
        cout << "\n1. Display single student ";
        cout << "\n2. Search student ";
        cout << "\n3. Exit" << endl;
        cout << "---------------------------\n";
        cout << "MAKE CHOICE : ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            s.displaystu();
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
    do
    {
        cout << "\n1. Admin \n2. Student\n3. Exit" << endl;
        cout << "Enter your position: ";
        cin >> position;
        cout << "---------------------------\n";
        if (cin.fail())
        {
            cout << "\n< ERROR: Position must be an integer >" << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            return -1;
        }
        if (position == 1)
        {
            Admin();
        }
        else if (position == 2)
        {
            stu();
        }
        else if (position == 3)
        {
            cout << "Exiting..." << endl;
        }
        else
        {
            cout << "Invalid position" << endl;
            continue;
        }
    } while (position != 3);
    return 0;
}
