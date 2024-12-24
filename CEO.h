#ifndef CEO_H
#define CEO_H
#include <iostream>
#include <cstring>
using namespace std;

class CEO{
private:
int ID;
string passWord;
public:
CEO();
CEO(int, string);
void setID(int);
int getID();
void setPassword(string);
string getPassword();
void access_Payment_record();
void access_Patient_information();
void access_Dailyly_report();
void access_Monthly_report();
void adjustSalary();
};
#endif