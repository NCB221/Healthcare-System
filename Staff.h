#ifndef STAFF_H
#define STAFF_H
#include <iostream>
#include <cstring>
using namespace std;

class Staff{
private:
string name;
public:
Staff();
Staff(string);
~Staff();
void set_staff_name(string);
string get_staff_name();
void update_patient_infor();
void make_patient_appointment();
void create_patient_record();
void access_patient_record();
void access_patient_payment();
};
#endif