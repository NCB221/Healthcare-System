#include "CEO.h"

CEO::CEO() : ID(1111), passWord("12345"){}
CEO::CEO(int id, string p ){
    ID = id;
    passWord = p;
}
void CEO::setID(int id){ ID = id;}
int CEO::getID(){ return ID;}
void CEO::setPassword(string p){ passWord = p;}
string CEO::getPassword(){ return passWord;}
void CEO::access_Payment_record(){}
void CEO::access_Patient_information(){}
void CEO::access_Dailyly_report(){}
void CEO::access_Monthly_report(){}
void CEO::adjustSalary(){}
