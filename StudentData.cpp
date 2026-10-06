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
    ofstream outFile("students.txt", ios::app);

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

    outFile << studentID << endl;
    outFile << name << endl;
    outFile << className << endl;
    outFile << section << endl;
    outFile << contactNo << endl;
    outFile << totalFeeDue << endl;

    outFile.close();
}

void Student::displayStudent(){
    ifstream inFile("students.txt");

    if (!inFile)
    {
        cout << "Error opening file!" << endl;
        return;
    }

    cout << "Student Records:" << endl;

    Student temp;
    bool found = false;

    while (inFile >> temp.studentID)
    {
        inFile.ignore();

        getline(inFile, temp.name);
        getline(inFile, temp.className);
        getline(inFile, temp.section);
        getline(inFile, temp.contactNo);

        inFile >> temp.totalFeeDue;
        inFile.ignore();

        cout << "\nStudent ID: " << temp.studentID << endl;
        cout << "Name: " << temp.name << endl;
        cout << "Class Name: " << temp.className << endl;
        cout << "Section: " << temp.section << endl;
        cout << "Contact Number: " << temp.contactNo << endl;
        cout << "Total Fee Due: " << temp.totalFeeDue << endl;

        cout << "------------------------------------" << endl;

        found = true;
    }

    if (!found)
    {
        cout << "No student records found." << endl;
    }

    inFile.close();
}

void Student::searchStudent(){
    int searchID;

    cout << "Enter Student ID to search: ";
    cin >> searchID;

    ifstream inFile("students.txt");

    if (!inFile)
    {
        cout << "Error opening file!" << endl;
        return;
    }

    bool found = false;
    Student temp;

    while (inFile >> temp.studentID)
    {
        inFile.ignore();

        getline(inFile, temp.name);
        getline(inFile, temp.className);
        getline(inFile, temp.section);
        getline(inFile, temp.contactNo);

        inFile >> temp.totalFeeDue;
        inFile.ignore();

        if (temp.studentID == searchID)
        {
            cout << "\nStudent Found!" << endl;
            cout << "-----------------------------" << endl;

            cout << "Student ID: " << temp.studentID << endl;
            cout << "Name: " << temp.name << endl;
            cout << "Class Name: " << temp.className << endl;
            cout << "Section: " << temp.section << endl;
            cout << "Contact Number: " << temp.contactNo << endl;
            cout << "Total Fee Due: " << temp.totalFeeDue << endl;

            cout << "-----------------------------" << endl;

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

void Student::updateStudent()
{
    int updateID;
    int choice;

    cout << "Enter Student ID to update: ";
    cin >> updateID;

    ifstream inFile("students.txt");

    if (!inFile)
    {
        cout << "Error opening file!" << endl;
        return;
    }

    ofstream tempFile("temp.txt");

    if (!tempFile)
    {
        cout << "Error creating temporary file!" << endl;
        inFile.close();
        return;
    }

    bool found = false;
    Student temp;

    while (inFile >> temp.studentID)
    {
        inFile.ignore();

        getline(inFile, temp.name);
        getline(inFile, temp.className);
        getline(inFile, temp.section);
        getline(inFile, temp.contactNo);

        inFile >> temp.totalFeeDue;
        inFile.ignore();

        if (temp.studentID == updateID)
        {
            found = true;

            cout << "\nStudent Found!" << endl;

            cout << "1. Update Name" << endl;
            cout << "2. Update Class Name" << endl;
            cout << "3. Update Section" << endl;
            cout << "4. Update Contact Number" << endl;
            cout << "5. Update Total Fee Due" << endl;

            cout << "Enter your choice: ";
            cin >> choice;
            cin.ignore();

            switch (choice)
            {
            case 1:
                cout << "Enter New Name: ";
                getline(cin, temp.name);
                break;

            case 2:
                cout << "Enter New Class Name: ";
                getline(cin, temp.className);
                break;

            case 3:
                cout << "Enter New Section: ";
                getline(cin, temp.section);
                break;

            case 4:
                cout << "Enter New Contact Number: ";
                getline(cin, temp.contactNo);
                break;

            case 5:
                cout << "Enter New Total Fee Due: ";
                cin >> temp.totalFeeDue;
                cin.ignore();
                break;

            default:
                cout << "Invalid choice!" << endl;
            }
        }

        tempFile << temp.studentID << endl;
        tempFile << temp.name << endl;
        tempFile << temp.className << endl;
        tempFile << temp.section << endl;
        tempFile << temp.contactNo << endl;
        tempFile << temp.totalFeeDue << endl;
    }

    inFile.close();
    tempFile.close();

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found)
    {
        cout << "\nStudent record updated successfully." << endl;
    }
    else
    {
        cout << "\nStudent with ID " << updateID
             << " not found." << endl;
    }
}

void Student::deleteStudent()
{
    int deleteID;

    cout << "Enter Student ID to delete: ";
    cin >> deleteID;

    ifstream inFile("students.txt");

    if (!inFile)
    {
        cout << "Error opening file!" << endl;
        return;
    }

    ofstream tempFile("temp.txt");

    if (!tempFile)
    {
        cout << "Error creating temporary file!" << endl;
        return;
    }

    bool found = false;
    Student temp;

    while (inFile >> temp.studentID)
    {
        inFile.ignore();

        getline(inFile, temp.name);
        getline(inFile, temp.className);
        getline(inFile, temp.section);
        getline(inFile, temp.contactNo);

        inFile >> temp.totalFeeDue;
        inFile.ignore();

        if (temp.studentID == deleteID)
        {
            found = true;

            // Do not write this student
            continue;
        }

        // Write other students
        tempFile << temp.studentID << endl;
        tempFile << temp.name << endl;
        tempFile << temp.className << endl;
        tempFile << temp.section << endl;
        tempFile << temp.contactNo << endl;
        tempFile << temp.totalFeeDue << endl;
    }

    inFile.close();
    tempFile.close();

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found)
    {
        cout << "\nStudent record deleted successfully." << endl;
    }
    else
    {
        cout << "\nStudent with ID " << deleteID
             << " not found." << endl;
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
