#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdio>
#include <stdexcept>
#include <cstdlib>
using namespace std;

int stu();
int recpt();

int main()
{
    int choice;
    system("cls");
    do
    {
        cout << "\n========== MAIN MENU ==========" << endl;
        cout << "1. Student Management System" << endl;
        cout << "2. Fee Receipt Management System" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail())
        {
            cout << "\n< ERROR: Choice must be an integer >" << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        switch (choice)
        {
        case 1:
            stu();
            break;
        case 2:
            recpt();
            break;
        case 3:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 3);

    return 0;
}

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

void studentAdmin()
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

void studentMenu()
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
            break;
        default:
            cout << "Invalid Choice" << endl;
        }
    } while (choice != 3);
}

int stu()
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
            studentAdmin();
        }
        else if (position == 2)
        {
            studentMenu();
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

class FeeReceipt
{
private:
    int receiptNo;
    int studentID;
    float amountPaid;
    string paydate;
    string paymentMethod;
    string remarks;

public:
    void recordPayment();
    void displayReceipt();
    void updatePayment();
    void deletePayment();
};

void FeeReceipt::recordPayment()
{
    int ex_rec, stuID;
    char confirm;
    FeeReceipt temp;
    cout << "\n---------- Record Fee Payment ----------\n";
    cout << "Enter Receipt Number : ";
    cin >> ex_rec;
    if (cin.fail())
    {
        cout << "\n< ERROR: Receipt Number must be an integer >" << endl;
        cin.clear();
        cin.ignore(1000, '\n');
        return;
    }
    cin.ignore();
    cout << "Enter student id : ";
    cin >> stuID;
    if (cin.fail())
    {
        cout << "\n< ERROR: Student ID must be integer >\n";
        cin.clear();
        cin.ignore(1000, '\n');
        return;
    }
    cin.ignore();
    ifstream f2("payment.dat");
    if (!f2)
    {
        cout << "< Error Opening File >\n";
        return;
    }
    if (f2)
    {
        cout << "\nReading Existing Data..." << endl;
        while (f2 >> temp.receiptNo >> temp.studentID >> temp.amountPaid >> temp.paydate >> temp.paymentMethod)
        {
            getline(f2, temp.remarks);
            if (ex_rec == temp.receiptNo || stuID == temp.studentID)
            {
                cout << "Payment already exists...\n";
                f2.close();
                return;
            }
        }
        f2.close();
    }
    fstream f("payment.dat", ios::app);
    if (!f)
    {
        cout << "< Error with File Opening >\n";
        return;
    }
    cout << "---Enter Student Payment Record ---\n";
    receiptNo = ex_rec;
    studentID = stuID;
    cout << "Enter Amount Paid: ";
    cin >> amountPaid;
    if (cin.fail())
    {
        cout << "\n< ERROR: Amount Paid must be a number >" << endl;
        cin.clear();
        cin.ignore(1000, '\n');
        f.close();
        return;
    }
    cin.ignore();
    cout << "Enter Payment Date (DD-MM-YYYY): ";
    cin >> paydate;
    cin.ignore();
    cout << "Enter Payment Method (cash/card/online): ";
    cin >> paymentMethod;
    cin.ignore();
    cout << "Enter Remarks: ";
    getline(cin, remarks);
    try
    {
        if (amountPaid < 0 && paymentMethod != "cash" && paymentMethod != "card" && paymentMethod != "online")
        {
            throw invalid_argument(
                "Amount paid cannot be negative AND Payment method is also Invalid");
        }
        if (amountPaid < 0)
        {
            throw invalid_argument(
                "Amount paid cannot be negative");
        }
        if (paymentMethod != "cash" && paymentMethod != "card" && paymentMethod != "online")
        {
            throw invalid_argument("Invalid payment method");
        }
    }
    catch (const invalid_argument &e)
    {
        cout << "\n< ERROR: " << e.what() << " >" << endl;
        f.close();
        return;
    }
    cout << "---------------------------\n";
    cout << "Are you sure to add this info (Y/N): ";
    cin >> confirm;
    if (confirm == 'Y' || confirm == 'y')
    {
        f << receiptNo << " " << studentID << " " << amountPaid << " " << paydate << " " << paymentMethod << " " << remarks << endl;
        cout << "< Record added Successfully >\n";
    }
    else if (confirm == 'N' || confirm == 'n')
    {
        cout << "< Record addition cancelled >\n";
    }
    else
    {
        cout << "< Invalid Action >\n";
    }
    f.close();
}

void FeeReceipt::displayReceipt()
{
    bool found = false;
    int searchreceiptno;
    cout << "Enter Receipt Number to Search: ";
    cin >> searchreceiptno;
    ifstream file("payment.dat", ios::in | ios::binary);
    try
    {
        if (!file)
        {
            throw runtime_error("Unable to open payment file");
        }
    }
    catch (const runtime_error &e)
    {
        cout << "\n< ERROR: " << e.what() << " >" << endl;
        return;
    }
    while (file >> receiptNo >> studentID >> amountPaid >> paydate >> paymentMethod)
    {
        file.ignore();
        getline(file, remarks);
        if (receiptNo == searchreceiptno)
        {
            cout << "\n";
            cout << "-----------------------------" << endl;
            cout << "     FEE PAYMENT RECEIPT\n";
            cout << "-----------------------------" << endl;
            cout << "Receipt Number: " << receiptNo << endl;
            cout << "Student ID: " << studentID << endl;
            cout << "Amount Paid: " << amountPaid << endl;
            cout << "Payment Date: " << paydate << endl;
            cout << "Payment Method: " << paymentMethod << endl;
            cout << "Remarks: " << remarks << endl;
            cout << "-----------------------------" << endl;
            found = true;
            break;
        }
    }
    file.close();
    try
    {
        if (!found)
        {
            throw runtime_error("Receipt not found");
        }
    }
    catch (const runtime_error &e)
    {
        cout << "\n< ERROR: " << e.what() << " >" << endl;
    }
}

void FeeReceipt::updatePayment()
{
    int updateReceipt;
    bool found = false;
    bool changed = false;
    bool cancelled = false;
    ifstream file("payment.dat", ios::in | ios::binary);
    try
    {
        if (!file)
        {
            throw runtime_error("Unable to open payment file");
        }
    }
    catch (const runtime_error &e)
    {
        cout << "\n< ERROR: " << e.what() << " >" << endl;
        return;
    }
    ofstream tempFile("temp.dat", ios::out | ios::binary);
    if (!tempFile)
    {
        cout << "\n< ERROR: Unable to open temporary file >" << endl;
        file.close();
        return;
    }
    cout << "Enter Receipt Number to Update: ";
    cin >> updateReceipt;
    if (cin.fail())
    {
        cout << "\n< ERROR: Receipt Number must be an integer >" << endl;
        cin.clear();
        cin.ignore(1000, '\n');
        file.close();
        tempFile.close();
        remove("temp.dat");
        return;
    }
    while (file >> receiptNo >> studentID >> amountPaid >> paydate >> paymentMethod)
    {
        file.ignore();
        getline(file, remarks);
        if (receiptNo == updateReceipt && !found)
        {
            found = true;
            int choice = 0;
            cout << "\n------ CURRENT FEE RECEIPT ------\n";
            cout << "Receipt Number: " << receiptNo << endl;
            cout << "Student ID: " << studentID << endl;
            cout << "Amount Paid: " << amountPaid << endl;
            cout << "Payment Date: " << paydate << endl;
            cout << "Payment Method: " << paymentMethod << endl;
            cout << "Remarks: " << remarks << endl;
            do
            {
                cout << "\n";
                cout << "-----------------------------" << endl;
                cout << "     UPDATE MENU\n";
                cout << "-----------------------------" << endl;
                cout << "1. Receipt Number" << endl;
                cout << "2. Student ID" << endl;
                cout << "3. Amount Paid" << endl;
                cout << "4. Payment Date" << endl;
                cout << "5. Payment Method" << endl;
                cout << "6. Remarks" << endl;
                cout << "7. Finish Editing\n";
                cout << "8. Cancel All Changes\n";
                cout << "-----------------------------" << endl;
                cout << "Enter your choice to update: ";
                cin >> choice;
                if (cin.fail())
                {
                    cout << "< ERROR: Enter a valid number >" << endl;
                    cin.clear();
                    cin.ignore(1000, '\n');
                    choice = 0;
                    continue;
                }
                switch (choice)
                {
                case 1:
                {
                    int value;
                    cout << "Enter new Receipt Number: ";
                    cin >> value;
                    if (!cin.fail())
                    {
                        cin.ignore(1000, '\n');
                        ifstream f3("payment.dat", ios::in | ios::binary);
                        if (f3)
                        {
                            int existingReceipt;
                            int existingStudentID;
                            float existingAmount;
                            string existingDate;
                            string existingMethod;
                            string existingRemarks;
                            while (f3 >> existingReceipt >> existingStudentID >> existingAmount >> existingDate >> existingMethod)
                            {
                                getline(f3, existingRemarks);
                                if (existingReceipt == value)
                                {
                                    cout << "\nERROR: Receipt Number already exists!" << endl;
                                    f3.close();
                                    return;
                                }
                            }
                            f3.close();
                        }
                        receiptNo = value;
                        changed = true;
                    }
                    else
                    {
                        cout << "< Invalid receipt number >" << endl;
                        cin.clear();
                        cin.ignore(1000, '\n');
                    }
                    break;
                }
                case 2:
                {
                    int value;
                    cout << "Enter new Student ID: ";
                    cin >> value;
                    if (!cin.fail())
                    {
                        cin.ignore(1000, '\n');
                        ifstream f3("payment.dat", ios::in | ios::binary);
                        if (f3)
                        {
                            int existingReceipt;
                            int existingStudentID;
                            float existingAmount;
                            string existingDate;
                            string existingMethod;
                            string existingRemarks;
                            while (f3 >> existingReceipt >> existingStudentID >> existingAmount >> existingDate >> existingMethod)
                            {
                                getline(f3, existingRemarks);
                                if (existingStudentID == value)
                                {
                                    cout << "\nERROR: Student ID already exists!" << endl;
                                    f3.close();
                                    return;
                                }
                            }
                            f3.close();
                        }
                        studentID = value;
                        changed = true;
                    }
                    else
                    {
                        cout << "< Invalid student ID >" << endl;
                        cin.clear();
                        cin.ignore(1000, '\n');
                    }
                    break;
                }
                case 3:
                {
                    float value;
                    cout << "Enter new Amount Paid: ";
                    cin >> value;
                    if (!cin.fail() && value >= 0)
                    {
                        amountPaid = value;
                        changed = true;
                    }
                    else
                    {
                        cout << "< Invalid amount >" << endl;
                        cin.clear();
                        cin.ignore(1000, '\n');
                    }
                    break;
                }
                case 4:
                    cout << "Enter new Payment Date (DD-MM-YYYY): ";
                    cin >> paydate;
                    if (!cin.fail())
                        changed = true;
                    break;
                case 5:
                {
                    string payment;
                    cout << "Enter new Payment Method (cash/card/online): ";
                    cin >> payment;
                    if (payment == "cash" ||
                        payment == "card" ||
                        payment == "online")
                    {
                        paymentMethod = payment;
                        changed = true;
                    }
                    else
                    {
                        cout << "< Invalid payment method >" << endl;
                    }
                    break;
                }
                case 6:
                    cout << "Enter new Remarks: ";
                    cin.ignore();
                    getline(cin, remarks);
                    changed = true;
                    break;
                case 7:
                    cout << "\nEditing completed.\n";
                    break;
                case 8:
                    cancelled = true;
                    cout << "\nAll changes cancelled.\n";
                    break;
                default:
                    cout << "< Invalid choice >" << endl;
                }
            } while (choice != 7 && choice != 8);
            if (changed && !cancelled)
            {
                char confirm;
                cout << "\nAre you sure you want to save " << "these changes? (Y/N): ";
                cin >> confirm;
                if (confirm != 'Y' && confirm != 'y')
                {
                    cancelled = true;
                    cout << "\n< Changes cancelled >" << endl;
                }
            }
        }
        tempFile << receiptNo << " " << studentID << " " << amountPaid << " " << paydate << " " << paymentMethod << " " << remarks << endl;
    }
    file.close();
    tempFile.close();
    if (!found)
    {
        remove("temp.dat");
        cout << "\n< ERROR: Receipt not found >" << endl;
        return;
    }
    if (cancelled || !changed)
    {
        remove("temp.dat");
        if (!cancelled)
            cout << "\n< No changes made >" << endl;

        return;
    }
    remove("payment_backup.dat");
    if (rename("payment.dat", "payment_backup.dat") != 0)
    {
        remove("temp.dat");
        cout << "\n< ERROR: Unable to back up payment file >" << endl;
        return;
    }
    if (rename("temp.dat", "payment.dat") == 0)
    {
        remove("payment_backup.dat");
        cout << "\n< Payment record updated successfully >" << endl;
    }
    else
    {
        if (rename("payment_backup.dat", "payment.dat") == 0)
        {
            cout << "\n< ERROR: Changes not saved; original restored >" << endl;
        }
        else
        {
            cout << "\n< ERROR: Restore payment_backup.txt manually >" << endl;
        }
        remove("temp.dat");
        return;
    }
}

void FeeReceipt::deletePayment()
{
    int deleteReceipt;
    bool found = false;
    cout << "Enter Receipt Number to Delete: ";
    cin >> deleteReceipt;
    if (cin.fail())
    {
        cout << "\n< ERROR: Receipt Number must be an integer >" << endl;
        cin.clear();
        cin.ignore(1000, '\n');
        return;
    }
    cin.ignore();
    ifstream file("payment.dat", ios::in | ios::binary);
    if (!file)
    {
        cout << "\n< ERROR: Unable to open payment file >" << endl;
        return;
    }
    ofstream tempFile("temp.dat", ios::out | ios::binary);
    if (!tempFile)
    {
        cout << "\n< ERROR: Unable to open temporary file >" << endl;
        file.close();
        return;
    }
    while (file >> receiptNo >> studentID >> amountPaid >> paydate >> paymentMethod)
    {
        file.ignore();
        getline(file, remarks);
        if (receiptNo == deleteReceipt)
        {
            cout << "\n------ RECEIPT DETAILS ------\n";
            cout << "Receipt Number: " << receiptNo << endl;
            cout << "Student ID: " << studentID << endl;
            cout << "Amount Paid: " << amountPaid << endl;
            cout << "Payment Date: " << paydate << endl;
            cout << "Payment Method: " << paymentMethod << endl;
            cout << "Remarks: " << remarks << endl;
            char confirm;
            while (true)
            {
                cout << "\nAre you sure you want to delete this receipt? (Y/N): ";
                cin >> confirm;
                if (confirm == 'Y' || confirm == 'y')
                {
                    found = true;
                    break;
                }
                else if (confirm == 'N' || confirm == 'n')
                {
                    cout << "\n< Deletion cancelled >" << endl;
                    file.close();
                    tempFile.close();
                    remove("temp.dat");
                    return;
                }
                else
                {
                    cout << "\n< Invalid input! Enter Y or N only >" << endl;
                    cin.ignore(1000, '\n');
                }
            }
            continue;
        }
        tempFile << receiptNo << " "
                 << studentID << " "
                 << amountPaid << " "
                 << paydate << " "
                 << paymentMethod << " "
                 << remarks << endl;
    }
    file.close();
    tempFile.close();
    if (!found)
    {
        remove("temp.dat");
        cout << "\n< ERROR: Receipt not found >" << endl;
        return;
    }
    remove("payment_backup.dat");
    if (rename("payment.dat", "payment_backup.dat") != 0)
    {
        remove("temp.dat");
        cout << "\n< ERROR: Unable to back up payment file >" << endl;
        return;
    }
    if (rename("temp.dat", "payment.dat") == 0)
    {
        remove("payment_backup.dat");
        cout << "\n< Payment record deleted successfully >" << endl;
    }
    else
    {
        if (rename("payment_backup.dat", "payment.dat") == 0)
        {
            cout << "\n< ERROR: Deletion failed, original restored >" << endl;
        }
        else
        {
            cout << "\n< ERROR: Restore payment_backup.txt manually >" << endl;
        }
        remove("temp.dat");
        return;
    }
}

void receiptAdmin()
{
    FeeReceipt fee;
    int choice;
    cout << "-----------------------------" << endl;
    cout << "if you are Admin, Enter code: ";
    int code;
    cin >> code;
    if (code == 1357)
    {
        do
        {
            cout << "\n< STUDENT MANAGEMENT SYSTEM >" << endl;
            cout << "1. Add Fee Record\n";
            cout << "2. Display Receipt Record\n";
            cout << "3. Update Receipt Record\n";
            cout << "4. Delete Receipt Record\n";
            cout << "5. Exit\n\n";
            cout << "Enter your choice: ";
            cin >> choice;
            switch (choice)
            {
            case 1:
                fee.recordPayment();
                break;
            case 2:
                fee.displayReceipt();
                break;
            case 3:
                fee.updatePayment();
                break;
            case 4:
                fee.deletePayment();
                break;
            case 5:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
            }
        } while (choice != 5);
    }
    else
    {
        cout << "Invalid code. Access denied." << endl;
    }
}
void receiptMenu()
{
    FeeReceipt fee;
    int choice;
    do
    {
        cout << endl;
        cout << "--------MENU--------";
        cout << "\n1. Display Receipt Record\n";
        cout << "2. exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            fee.displayReceipt();
            break;
        case 2:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 2);
}
int recpt()
{
    system("cls");
    int position;
    cout << "\n< ---STUDENT MANAGEMENT SYSTEM--->\n"<< endl;
    cout << "1. Admin\n";
    cout << "2. Student\n";
    cout << "Enter your position: ";
    cin >> position;
    if (position == 1)
    {
        receiptAdmin();
    }
    else if (position == 2)
    {
        receiptMenu();
    }
    else
    {
        cout << "Invalid position. Exiting...\n";
        return 0;
    }
    return 0;
}