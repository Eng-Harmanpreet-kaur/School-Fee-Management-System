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
    if (cin.fail())
    {
        cout << "Invalid input! Please enter an integer.";
    }
    cout << "Enter student name :\n";
    cin.ignore();
    cin.getline(name, 50);
    cout << "Enter class name :\n";
<<<<<<< HEAD
    cin.ignore();
=======
>>>>>>> b6893f23f88b5d8fe003f70cd106909baf4228c7
    cin.getline(classsname, 20);
    cout << "Enter section :\n";
    cin.getline(section, 5);
    cout << "Enter father's name :\n";
    cin.getline(fathername, 30);
    cout << "Enter contact number :\n";
    cin.getline(contactno, 15);
    cout << "Enter total fee paid :\n";
    cin >> totalfee;
<<<<<<< HEAD
    if (cin.fail())
    {
        cout << "Invalid input! Please enter a float value.";
    }
=======
>>>>>>> b6893f23f88b5d8fe003f70cd106909baf4228c7
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
<<<<<<< HEAD
            {
            case 1:
                cout << "Enter new name: ";
                cin.ignore(); // Clear the input buffer before reading a new line
                cin.getline(name, 50);
                break;

            case 2:
                cout << "Enter new class name: ";
                cin.ignore(); // Clear the input buffer before reading a new line
                cin.getline(classsname, 20);
                break;

            case 3:
                cout << "Enter new section: ";
                cin.ignore();
                cin.getline(section, 5);
                break;

            case 4:
                cout << "Enter new father's name: ";
                cin.ignore(); // Clear the input buffer before reading a new line
                cin.getline(fathername, 30);
                break;

            case 5:
                cout << "Enter new contact number: ";
                cin.ignore(); // Clear the input buffer before reading a new line
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
=======
    case 1:
        cout << "Enter new name: ";
        cin.ignore(); // Clear the input buffer before reading a new line
        cin.getline(name, 50);
        break;
    case 2:
        cout << "Enter new class name: ";
        cin.ignore(); // Clear the input buffer before reading a new line
        cin.getline(classsname, 20);
        break;
    case 3:
        cout << "Enter new section: ";
        cin.ignore(); 
        cin.getline(section, 5);
        break;
    case 4:
        cout << "Enter new father's name: ";
        cin.ignore(); // Clear the input buffer before reading a new line
        cin.getline(fathername, 30);
        break;
    case 5:
        cout << "Enter new contact number: ";
        cin.ignore(); // Clear the input buffer before reading a new line
        cin.getline(contactno, 15);
        break;
    default:
        cout << "Invalid choice!" << endl;
}
        bool wantToUpdate ;
        cout<<"Do you want to make this change? (y/n): ";
        cin>>wantToUpdate;
        if(wantToUpdate){
            fu.seekp(fu.tellg()-sizeof(student));
            fu.write((char*)this,sizeof(student));
            cout<<"UPDATE SUCCESSFUL"<<endl;
            cout<<"-----------------------------"<<endl;
        }
        else{
            cout<<"Update cancelled."<<endl;
        }
            found=true;
        }
>>>>>>> b6893f23f88b5d8fe003f70cd106909baf4228c7
    }
    if (!found)
    {
        cout << "Student not found" << endl;
    }
    fu.close();
<<<<<<< HEAD
}
void student::del()
=======
}void student::del()
>>>>>>> b6893f23f88b5d8fe003f70cd106909baf4228c7
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
<<<<<<< HEAD

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
=======
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
>>>>>>> b6893f23f88b5d8fe003f70cd106909baf4228c7
            {
                temp.write((char *)this, sizeof(student));
            }
        }
<<<<<<< HEAD
        else
        {
            ft.write((char *)this, sizeof(student));
        }
=======
        fd.close();
        temp.close();
        remove("student.dat");
        rename("temp.dat", "student.dat");
        cout << "DELETED SUCCESSFULLY" << endl;
>>>>>>> b6893f23f88b5d8fe003f70cd106909baf4228c7
    }
    else
    {
<<<<<<< HEAD
        cout << "Invalid choice" << endl;
        remove("temp.dat");
        return;
    }

    remove("student.dat");
    rename("temp.dat", "student.dat");
=======
        cout << "Invalid choice";
    }
>>>>>>> b6893f23f88b5d8fe003f70cd106909baf4228c7
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
        cout << " Student not found" << endl;
    }
    fs.close();
}
<<<<<<< HEAD
void Admin()
{
    student s;
    int choice;
    cout << "-----------------------------" << endl;
    int code;
    cout << "if you are Admin, Enter code ";
    cin >> code;
    if (code == 1234)
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
=======
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
>>>>>>> b6893f23f88b5d8fe003f70cd106909baf4228c7
            {
            case 1:
                s.add();
                break;
            case 2:
                s.display();
                break;
            case 3:
<<<<<<< HEAD
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
=======
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
>>>>>>> b6893f23f88b5d8fe003f70cd106909baf4228c7
        cout << "MAKE CHOICE : ";
        cin >> choice;
      switch (choice)
        {
        case 1:
<<<<<<< HEAD
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
    cout << " ---STUDENT MANAGEMENT SYSTEM---" << endl;
    int position;
    cout << "Enter your position : ";
    cout << "\n1.Admin \n2. Student" << endl;
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
=======
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
>>>>>>> b6893f23f88b5d8fe003f70cd106909baf4228c7
