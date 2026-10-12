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

    file << receiptNo << " "
         << studentID << " "
         << amountPaid << " "
         << paydate << " "
         << paymentMethod << " "
         << remarks << endl;

    file.close();
    cout << "\n< Payment recorded successfully >"
         << endl;
}

void FeeReceipt::displayReceipt()
{
    int searchreceiptno;
    int receiptNo;
    int studentID;
    float amountPaid;
    string paydate;
    string paymentMethod;
    string remarks;
    bool found = false;

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

    int receiptNo;
    int studentID;
    float amountPaid;
    string paydate;
    string paymentMethod;
    string remarks;

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

        tempFile << receiptNo << " " << studentID << " " << amountPaid << " "
                 << paydate << " " << paymentMethod << " " << remarks << endl;
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

    cout << "Enter receipt number to delete: ";
    cin >> deleteReceipt;
    
}

int main()
{
    FeeReceipt fee;
    int choice;
    system("cls");

    do
    {
        cout << "\n";
        cout << "< STUDENT MANAGEMENT SYSTEM >" << endl;
        cout << "1. Add Fee Record\n";
        cout << "2. Display Receipt Record\n";
        cout << "3. Update Receipt Record\n";
        cout << "4. Delete Receipt Record\n";
        cout << "5. Exit\n";
        cout << "\n";

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