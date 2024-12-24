#ifndef DOCTOR_H
#define DOCTOR_H
#include <iostream>
#include <cstring>
using namespace std;

class Doctor{
private:
string doctor_name;
public:
Doctor();
Doctor(string);
void setName(string);
string getName();
void access_Payment_record();
void access_Patient_payment();
void edit_Patient_record();
};
#endif