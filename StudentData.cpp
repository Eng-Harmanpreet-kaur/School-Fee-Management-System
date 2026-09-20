#include<iostream>
#include<fstream>
#include<string>
using namespace std;
class Student
{
private:

    int studentID;
    string name;
    string className;
    string section;
    string contactNo;
    float totalFeeDue;

public:

    void addStudent();
    void displayStudent();
    void searchStudent();
    void updateStudent();
    void deleteStudent();
};
void Student::addStudent(){
    ofstream outFile("students.txt", ios::binary | ios::app);
    if (!outFile)
    {
        cout << "Error opening file!" << endl;
        return;
    }

    cout << "Enter Student ID: ";
    cin >> studentID;
    cin.ignore();
    cout << "Enter Name: ";
    getline(cin, name);
    cout << "Enter Class Name: ";
    getline(cin, className);
    cout << "Enter Section: ";
    getline(cin, section);
    cout << "Enter Contact Number: ";
    getline(cin, contactNo);
    cout << "Enter Total Fee Due: ";
    cin >> totalFeeDue;

    outFile.write(reinterpret_cast<char*>(this), sizeof(Student));
    outFile.close();
}

void Student::displayStudent(){
    ifstream inFile("students.txt", ios::binary);
    if (!inFile)
    {
        cout << "Error opening file!" << endl;
        return;
    }

    cout << "Student Records:" << endl;
    while (inFile.read(reinterpret_cast<char*>(this), sizeof(Student)))
    {
        cout << "Student ID: " << studentID << endl;
        cout << "Name: " << name << endl;
        cout << "Class Name: " << className << endl;
        cout << "Section: " << section << endl;
        cout << "Contact Number: " << contactNo << endl;
        cout << "Total Fee Due: " << totalFeeDue << endl;
        cout << "------------------------" << endl;
    }
    inFile.close();
}

void Student::searchStudent(){
    int searchID;
    cout << "Enter Student ID to search: ";
    cin >> searchID;

    ifstream inFile("students.txt", ios::binary);
    if (!inFile)
    {
        cout << "Error opening file!" << endl;
        return;
    }

    bool found = false;
    while (inFile.read(reinterpret_cast<char*>(this), sizeof(Student)))
    {
        if (studentID == searchID)
        {
            cout << "Student Found:" << endl;
            cout << "Student ID: " << studentID << endl;
            cout << "Name: " << name << endl;
            cout << "Class Name: " << className << endl;
            cout << "Section: " << section << endl;
            cout << "Contact Number: " << contactNo << endl;
            cout << "Total Fee Due: " << totalFeeDue << endl;
            found = true;
            break;
        }
    }
    if (!found)
    {
        cout << "Student with ID " << searchID << " not found." << endl;
    }
    inFile.close();
}

void Student::updateStudent(){
    int updateID;
    cout << "Enter Student ID to update: ";
    cin >> updateID;

    fstream file("students.txt", ios::binary | ios::in | ios::out);
    if (!file)
    {
        cout << "Error opening file!" << endl;
        return;
    }

   bool found = false;
    while (file.read(reinterpret_cast<char*>(this), sizeof(Student)))
    {
        if (studentID == updateID)
       { found =true;
       }
int choice;

      do  {
        cout <<"1 Student ID\n";
        cout<<"2 Name\n";
        cout<<"3 Class";
        cout<<"4 Section";
        cout<<"5 Contact No";
        cout<<"6 Due Fee";
        cout <<"7 Exit";

        cout<<"Enter you choice that you want to update";
        cin>>choice;

        switch (choice)
        {
        case 1:
        cout<<"Enter your Student Id";
        cin>>studentID;
        break;
        case 2:
        cout << "Enter new Name: ";
            cin.ignore();
            getline(cin, name);
         break;
        case 3:
         cout << "Enter new Class Name: ";
        getline(cin, className);
         break;
        case 4:
         cout << "Enter new Section: ";
            getline(cin, section);
         break;
        case 5: 
         cout << "Enter new Contact Number: ";
        getline(cin, contactNo);
        
         break;
        case 6:
        cout << "Enter new Total Fee Due: ";
            cin >> totalFeeDue;
         break;
       case 7:
       break;
           
        default:
        cout << "Student with ID " << updateID << " not found." << endl;
            break;
        }}
        while (choice != 7);
           
          
            file.seekp(-static_cast<int>(sizeof(Student)), ios::cur);
            file.write(reinterpret_cast<char*>(this), sizeof(Student));
            // found = true;
            cout << "Student record updated successfully." << endl;
            break;
        
        
    }
    if (!found)
    {
        cout << "Student with ID " << updateID << " not found." << endl;
    }
    file.close();
}

void Student:: deleteStudent(){
    int deleteID;
    cout << "Enter Student ID to delete: ";
    cin >> deleteID;

    ifstream inFile("students.txt", ios::binary);
    if (!inFile)
    {
        cout << "Error opening file!" << endl;
        return;
    }

    ofstream tempFile("students.tmp", ios::binary);
    if (!tempFile)
    {
        cout << "Error creating temporary file!" << endl;
        return;
    }

    bool found = false;
    Student record;
    while (inFile.read(reinterpret_cast<char*>(&record), sizeof(Student)))
    {
        if (record.studentID == deleteID)
        {
            found = true;
        }
        else
        {
            tempFile.write(reinterpret_cast<char*>(&record), sizeof(Student));
        }
    }

    inFile.close();
    tempFile.close();

    remove("students.txt");
    rename("students.tmp", "students.txt");

    if (found)
    {
        cout << "Student record deleted successfully." << endl;
    }
    else
    {
        cout << "Student with ID " << deleteID << " not found." << endl;
    }
}


int main()
{
    Student student;
    int choice;

    do
    {
        cout << "Student Management System" << endl;
        cout << "1. Add Student" << endl;
        cout << "2. Display All Students" << endl;
        cout << "3. Search Student" << endl;
        cout << "4. Update Student" << endl;
        cout << "5. Delete Student" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            student.addStudent();
            break;
        case 2:
            student.displayStudent();
            break;
        case 3:
            student.searchStudent();
            break;
        case 4:
            student.updateStudent();
            break;
        case 5:
            student.deleteStudent();
            break;
        case 6:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 6);


    return 0;
}