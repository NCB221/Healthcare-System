#include <iostream>
#include <cstring>
#include <cstdlib>
#include <fstream>
using namespace std;

class Nurse{
    private:
   string nurse_name;
    public:
    Nurse();
    Nurse(string);
    void setName(string);
    string getName();
    void view_patient_medical_record(fstream&, string);
    void edit_Patient_record(string, string[]);
    void access_Patient_record();
};