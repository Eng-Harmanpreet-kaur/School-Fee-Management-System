#include<iostream>
#include<fstream>
using namespace std;
class student{
    private:
    int stuid;
    char name[50];
    char classname[20];
    char section[5];
    char fathername[50];
    long long  mno;
    float due_fee;
    public:
    void getdata(){
        cout<<"Enter student id: ";
        cin>>stuid;
        cin.ignore();
        cout<<"Enter student name: ";
        cin.getline(name, 50);
        cout<<"Enter class name: ";
        cin>>classname;
        cout<<"Enter section: ";
        cin>>section;
        cout<<"Enter father name: ";
        cin>>fathername;
        cout<<"Enter mobile number: ";
        cin>>mno;
        cout<<"Enter due fee: ";
        cin>>due_fee;
    }
    void displaydata(){
        cout<<"Student id: "<<stuid<<endl;
        cout<<"Student name: "<<name<<endl;
        cout<<"Class name: "<<classname<<endl;
        cout<<"Section: "<<section<<endl;
        cout<<"Father name: "<<fathername<<endl;
        cout<<"Mobile number: "<<mno<<endl;
        cout<<"Due fee: "<<due_fee<<endl;
    }

};
class feepay{
private:
    int receiptno;
    int stuid;
    float amountpaid;
    char pDate[20];
    char mode[20];
    char remark[40];
    public:
    void getdata(){
        cout<<"Enter receipt number: ";
        cin>>receiptno;
        
        cout<<"Enter student id: ";
        cin>>stuid;
        cout<<"Enter amount paid: ";
        cin>>amountpaid;
        cin.ignore();
        cout<<"Enter payment date: ";
        cin.getline(pDate, 20);   
        cout<<"Enter payment mode: ";
        cin.getline(mode, 20);    
        cout<<"Enter remark: ";
        cin.getline(remark, 40);  
    }
    void displaydata(){
        cout<<"Receipt number: "<<receiptno<<endl;
        cout<<"Student id: "<<stuid<<endl;
        cout<<"Amount paid: "<<amountpaid<<endl;
        cout<<"Payment date: "<<pDate<<endl;
        cout<<"Payment mode: "<<mode<<endl;
        cout<<"Remark: "<<remark<<endl;
    }

};
int main(){
    system("cls");
    student s;
    feepay f;
    ofstream fout;
    ifstream fin;
    // fout.open("student.txt",ios::app);
    // s.getdata();
    // fout.write((char*)&s,sizeof(s));
    // fout.close();
    // fout.open("feepay.txt",ios::app);
    // f.getdata();
    // fout.write((char*)&f,sizeof(f));
    // fout.close();
    // fout.open("student.txt",ios::in);
    fin.open("student.txt",ios::in);
    while(fin.read((char*)&s,sizeof(s))){
        s.displaydata();
    }
    fin.close();

    return 0;
}
