#include <iostream>
#include <string>
#include <cstdio>
#include <fstream>
#include <stdexcept>
using namespace std;

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
    cout << "\n---------- Record Fee Payment ----------\n";
    cout << "Enter Receipt Number: ";
    cin >> receiptNo;
    if (cin.fail())
    {
        cout << "\n< ERROR: Receipt Number must be an integer >" << endl;
        cin.clear();
        cin.ignore(1000, '\n');
        return;
    }
    cin.ignore();
    ifstream f1("payment.txt");

    if (f1)
    {
        int existingReceipt;
        int existingStudentID;
        float existingAmount;
        string existingDate;
        string existingMethod;
        string existingRemarks;

        while (f1 >> existingReceipt >> existingStudentID >> existingAmount >> existingDate >> existingMethod)
        {
            getline(f1, existingRemarks);

            if (existingReceipt == receiptNo)
            {
                cout << "\nERROR: Receipt Number already exists!" << endl;

                f1.close();
                return;
            }
        }

        f1.close();
    }

    cout << "Enter Student ID: ";
    cin >> studentID;
    if (cin.fail())
    {
        cout << "\n< ERROR: Student ID must be an integer >" << endl;
        cin.clear();
        cin.ignore(1000, '\n');
        return;
    }
    cin.ignore();
    ifstream f2("payment.txt");

    if (f2)
    {
        int existingReceipt;
        int existingStudentID;
        float existingAmount;
        string existingDate;
        string existingMethod;
        string existingRemarks;

        while (f2 >> existingReceipt >> existingStudentID >> existingAmount >> existingDate >> existingMethod)
        {
            getline(f2, existingRemarks);

            if (existingStudentID == studentID)
            {
                cout << "\nERROR: Student ID already exists!" << endl;

                f2.close();
                return;
            }
        }

        f2.close();
    }

    cout << "Enter Amount Paid: ";
    cin >> amountPaid;
    if (cin.fail())
    {
        cout << "\n< ERROR: Amount Paid must be a number >" << endl;
        cin.clear();
        cin.ignore(1000, '\n');
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
        return;
    }

    ofstream file("payment.txt", ios::app);

    if (!file)
    {
        cout << "\n< ERROR: Unable to open payment file >" << endl;
        return;
    }

    file << receiptNo << " ";
    file << studentID << " ";
    file << amountPaid << " ";
    file << paydate << " ";
    file << paymentMethod << " ";
    file << remarks << endl;

    file.close();
    cout << "\n< Payment recorded successfully >"
         << endl;
}

void FeeReceipt::displayReceipt()
{
    bool found = false;
    int searchreceiptno;
    cout << "Enter Receipt Number to Search: ";
    cin >> searchreceiptno;

    ifstream file("payment.txt");

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

    ifstream file("payment.txt");

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

    ofstream tempFile("temp.txt");

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
        remove("temp.txt");
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
                        ifstream f3("payment.txt");

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
                        ifstream f3("payment.txt");

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

                cout << "\nAre you sure you want to save "
                     << "these changes? (Y/N): ";
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
        remove("temp.txt");
        cout << "\n< ERROR: Receipt not found >" << endl;
        return;
    }

    if (cancelled || !changed)
    {
        remove("temp.txt");

        if (!cancelled)
            cout << "\n< No changes made >" << endl;

        return;
    }

    remove("payment_backup.txt");

    if (rename("payment.txt", "payment_backup.txt") != 0)
    {
        remove("temp.txt");
        cout << "\n< ERROR: Unable to back up payment file >" << endl;
        return;
    }

    if (rename("temp.txt", "payment.txt") == 0)
    {
        remove("payment_backup.txt");
        cout << "\n< Payment record updated successfully >" << endl;
    }
    else
    {
        if (rename("payment_backup.txt", "payment.txt") == 0)
        {
            cout << "\n< ERROR: Changes not saved; original restored >" << endl;
        }
        else
        {
            cout << "\n< ERROR: Restore payment_backup.txt manually >" << endl;
        }

        remove("temp.txt");
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

    ifstream file("payment.txt");
    if (!file)
    {
        cout << "\n< ERROR: Unable to open payment file >" << endl;
        return;
    }

    ofstream tempFile("temp.txt");
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
                    remove("temp.txt");
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
        remove("temp.txt");
        cout << "\n< ERROR: Receipt not found >" << endl;
        return;
    }
    remove("payment_backup.txt");

    if (rename("payment.txt", "payment_backup.txt") != 0)
    {
        remove("temp.txt");
        cout << "\n< ERROR: Unable to back up payment file >" << endl;
        return;
    }

    if (rename("temp.txt", "payment.txt") == 0)
    {
        remove("payment_backup.txt");
        cout << "\n< Payment record deleted successfully >" << endl;
    }
    else
    {
        if (rename("payment_backup.txt", "payment.txt") == 0)
        {
            cout << "\n< ERROR: Deletion failed, original restored >" << endl;
        }
        else
        {
            cout << "\n< ERROR: Restore payment_backup.txt manually >" << endl;
        }

        remove("temp.txt");
        return;
    }
}

void Admin()
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
void stu()
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
int main()
{
    system("cls");
    int position;
    cout << "\n< ---STUDENT MANAGEMENT SYSTEM--->\n" << endl;
    cout << "1. Admin\n";
    cout << "2. Student\n";
    cout << "Enter your position: ";
    cin >> position;
    if (position == 1)
    {
        Admin();
    }
    else if (position == 2)
    {
        stu();
    }
    else
    {
        cout << "Invalid position. Exiting...\n";
        exit(0);
    }
}