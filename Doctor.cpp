#include "Doctor.h"

Doctor::Doctor(){}
Doctor::Doctor(string name){
    doctor_name = name;
}
void Doctor::setName(string name){
    this->doctor_name = name;
}
string Doctor::getName(){return doctor_name;}
void Doctor::access_Payment_record(){
    
}
void Doctor::access_Patient_payment(){}
void Doctor::edit_Patient_record(){}