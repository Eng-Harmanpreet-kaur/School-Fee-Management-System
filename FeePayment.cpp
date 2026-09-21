#include<iostream>
#include<fstream>
#include<string.h>
#include <sstream>
using namespace std;

class FeePayment
{
private:

    int receiptNo;
    int studentID;
    float amountPaid;

    string paymentDate;
    string paymentMode;
    string remarks;

public:

    void recordPayment();
    void displayReceipt();
    void updatePayment();
    void deletePayment();
};


void FeePayment::recordPayment()
{
    cout << "\n========== Record Fee Payment ==========\n";

    cout << "Enter Receipt Number: ";
    cin >> receiptNo;

    cout << "Enter Student ID: ";
    cin >> studentID;

    cout << "Enter Amount Paid: ";
    cin >> amountPaid;

    cin.ignore();

    cout << "Enter Payment Date: ";
    getline(cin, paymentDate);

    cout << "Enter Payment Mode: ";
    getline(cin, paymentMode);

    cout << "Enter Remarks: ";
    getline(cin, remarks);

    ofstream file("fee_payments.txt", ios::app);

    if (!file)
    {
        cout << "Error: Unable to open payment file.\n";
        return;
    }

    file << receiptNo <<"\n";
    file << studentID << "\n";
    file << amountPaid << "\n";
    file << paymentDate << "\n";
    file << paymentMode << "\n";
    file << remarks << "\n";

    file.close();

    cout << "\nFee payment recorded successfully!\n";
}




void FeePayment::displayReceipt()
{
    int searchReceipt;

    cout << "\n========== Display Receipt ==========\n";

    cout << "Enter Receipt Number: ";
    cin >> searchReceipt;

    ifstream file("fee_payments.txt");

    if (!file)
    {
        cout << "Payment file not found.\n";
        return;
    }

    int rNo;
    int sID;
    float amount;

    string date;
    string mode;
    string remark;

    bool found = false;

    while (file >> rNo >> sID >> amount)
    {
        file.ignore();

        getline(file, date,'|');
        getline(file, mode, '|');
        getline(file, remark);

        if (rNo == searchReceipt)
        {
            cout << "\n====================================\n";
            cout << "          FEE PAYMENT RECEIPT\n";
            cout << "====================================\n";

            cout << "Receipt No.   : " << rNo << endl;
            cout << "Student ID    : " << sID << endl;
            cout << "Amount Paid   : " << amount << endl;
            cout << "Payment Date  : " << date << endl;
            cout << "Payment Mode  : " << mode << endl;
            cout << "Remarks       : " << remark << endl;

            cout << "====================================\n";

            found = true;
            break;
        }
    }

    file.close();

    if (!found)
    {
        cout << "Receipt not found.\n";
    }
}






void FeePayment::updatePayment()
{
    int updateReceipt;

    cout << "Enter Receipt Number to update: ";
    cin >> updateReceipt;

    ifstream inFile("fee_payments.txt");

    if (!inFile)
    {
        cout << "Error opening file!" << endl;
        return;
    }

    ofstream tempFile("fee_payments.tmp");

    if (!tempFile)
    {
        cout << "Error creating temporary file!" << endl;
        inFile.close();
        return;
    }

    bool found = false;
    string line;

    while (getline(inFile, line))
    {
        stringstream ss(line);

        string receiptStr;
        string studentIDStr;
        string amountStr;

        string date;
        string mode;
        string remark;

        getline(ss, receiptStr, '|');
        getline(ss, studentIDStr, '|');
        getline(ss, amountStr, '|');
        getline(ss, date, '|');
        getline(ss, mode, '|');
        getline(ss, remark);

        int currentReceipt = stoi(receiptStr);

        if (currentReceipt == updateReceipt)
        {
            found = true;

            receiptNo = currentReceipt;

            int choice;

            do
            {
                cout << "\n========== UPDATE PAYMENT ==========\n";
                cout << "1. Student ID\n";
                cout << "2. Amount Paid\n";
                cout << "3. Payment Date\n";
                cout << "4. Payment Mode\n";
                cout << "5. Remarks\n";
                cout << "6. Exit\n";

                cout << "Enter your choice: ";
                cin >> choice;

                switch (choice)
                {
                case 1:
                    cout << "Enter new Student ID: ";
                    cin >> studentID;
                    break;

                case 2:
                    cout << "Enter new Amount Paid: ";
                    cin >> amountPaid;
                    break;

                case 3:
                    cout << "Enter new Payment Date: ";
                    cin.ignore();
                    getline(cin, paymentDate);
                    break;

                case 4:
                    cout << "Enter new Payment Mode: ";
                    cin.ignore();
                    getline(cin, paymentMode);
                    break;

                case 5:
                    cout << "Enter new Remarks: ";
                    cin.ignore();
                    getline(cin, remarks);
                    break;

                case 6:
                    break;

                default:
                    cout << "Invalid choice!" << endl;
                }

            } while (choice != 6);

            // Write updated record
            tempFile << receiptNo << "|"
                     << studentID << "|"
                     << amountPaid << "|"
                     << paymentDate << "|"
                     << paymentMode << "|"
                     << remarks << endl;
        }
        else
        {
            // Copy old record without changing it
            tempFile << line << endl;
        }
    }

    inFile.close();
    tempFile.close();

    if (found)
    {
        remove("fee_payments.txt");
        rename("fee_payments.tmp", "fee_payments.txt");

        cout << "Payment record updated successfully." << endl;
    }
    else
    {
        remove("fee_payments.tmp");

        cout << "Receipt with number "
             << updateReceipt
             << " not found." << endl;
    }
}





void FeePayment::deletePayment()
{
    int deleteReceipt;

    cout << "Enter Receipt Number to delete: ";
    cin >> deleteReceipt;

    ifstream inFile("fee_payments.txt");

    if (!inFile)
    {
        cout << "Error opening file!" << endl;
        return;
    }

    ofstream tempFile("fee_payments.tmp");

    if (!tempFile)
    {
        cout << "Error creating temporary file!" << endl;
        inFile.close();
        return;
    }

    bool found = false;
    string line;

    while (getline(inFile, line))
    {
        stringstream ss(line);

        string receiptStr;
        string studentIDStr;
        string amountStr;

        string date;
        string mode;
        string remark;

        getline(ss, receiptStr, '|');
        getline(ss, studentIDStr, '|');
        getline(ss, amountStr, '|');
        getline(ss, date, '|');
        getline(ss, mode, '|');
        getline(ss, remark);

        int currentReceipt = stoi(receiptStr);

        if (currentReceipt == deleteReceipt)
        {
            found = true;

            // Do not write this record
            continue;
        }

        // Write all other records
        tempFile << line << endl;
    }

    inFile.close();
    tempFile.close();

    if (found)
    {
        remove("fee_payments.txt");
        rename("fee_payments.tmp", "fee_payments.txt");

        cout << "Payment record deleted successfully." << endl;
    }
    else
    {
        remove("fee_payments.tmp");

        cout << "Receipt with number "
             << deleteReceipt
             << " not found." << endl;
    }
}



int main()
{
 FeePayment fee;   
        int choice;
    do{
    cout << "Student Management System" << endl;
      cout << "Add Fee\n";
      cout<<"Display Receipt \n";
      cout<<"Update Receipt";
      cout<<"Delete Receipt";
      cout<<"Exit\n";
      cout<< "Enter your choice";
      cin>> choice;
      switch (choice)
      {
      case 1:
      fee.recordPayment();
        break;
      case 2:
      fee.displayReceipt();
      case 3:
     fee.updatePayment();
      break;
      case 4:
      fee.deletePayment();
      break;
      case 5:
      break;
      default:
      cout<<"Invalid choice! Please try again.";
        break;
      }
      
    }while (choice != 5);

    return 0;
}





