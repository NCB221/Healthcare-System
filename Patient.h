#ifndef PATIENT_H
#define PATIENT_H
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <ctime>
//#include "Healthcare_system_main.cpp"
using namespace std;

class Patient{
private:
string patient_name; 
string address; 
int phone_number; 
string email; 
string social_security_number; 
string insurance_name;
public:
Patient();
Patient(string);
Patient(string, string, int, string, string, string);
~Patient();
void set_patient_name(string);
void set_address(string);
void set_phone_number(int);
void set_email(string);
void set_social_security_number(string);
void set_insurance_name(string);
string get_patient_name();
string get_address();
int get_phone_number();
string get_email();
string get_social_security_number();
string get_insurance_name();

void make_appointment();
void change_appointment();
void cancel_appointment();
void access_medical_record();
void pay_with_creditCard();
void pay_with_debitCard();
void pay_with_check();
void pay_invoice();
};
#endif