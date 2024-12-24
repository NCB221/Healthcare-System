#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <ctime>
using namespace std;

string Encrypt_input(string &plain_text){
    for(int i = 0; i < plain_text.length(); i++){
        plain_text[i] = plain_text[i] + 3;
    }
    return plain_text;
}

string Decrypt_input(string &encrypted_text){
    for(int i = 0; i < encrypted_text.length(); i++){
        encrypted_text[i] = encrypted_text[i] - 3;
    }
    return encrypted_text;
}

using namespace std;

struct current_patient_appointment{
    string doctor_name;
    string date;
    string confirmationNumber;
};

int main( )
{
     // tra ve date/time hien tai dua tren system hien tai
   fstream appointment_file;
  string patient_appoint = "";
  current_patient_appointment pat;
  vector<current_patient_appointment>pat_list;
//cout << patient_appoint << endl;
string a = "Alex";
string n = "";
n = a + " Appointment.txt";
appointment_file.open(n, ios::in);
while(!appointment_file.eof()){
        getline(appointment_file, pat.doctor_name);
        getline(appointment_file, pat.date);
        getline(appointment_file, pat.confirmationNumber);
        pat_list.push_back(pat);
    }
    appointment_file.close();

    for(int i = 0; i < pat_list.size(); i++){
        cout << i << endl;
        cout << pat_list[i].doctor_name << endl;
        cout << pat_list[i].date << endl;
        cout << pat_list[i].confirmationNumber << endl;
    }
    time_t now = time(0);
    string s = to_string(now);
    current_patient_appointment pat1;

    pat1.doctor_name = "Angel";
    pat1.date = "Apr 20 13:00:00 2024";
    pat1.confirmationNumber = s;
    pat_list.push_back(pat1);

    cout << endl;
    for(int i = 0; i < pat_list.size(); i++){
        cout << i << endl;
        cout << pat_list[i].doctor_name << endl;
        cout << pat_list[i].date << endl;
        cout << pat_list[i].confirmationNumber << endl;
    }

    appointment_file.open("Alex Appointment.txt", ios::out);
    for(int i = 0; i < pat_list.size(); i++){
        appointment_file << pat_list[i].doctor_name << endl;
        appointment_file << pat_list[i].date << endl;
        appointment_file << pat_list[i].confirmationNumber << endl;
    }
    appointment_file.close();
  return 0;
}

 /*  tra ve date/time hien tai dua tren system hien tai
   time_t baygio = time(0);

   cout << "So giay ke tu 1/1/1970 la: " << baygio << endl;

   tm *ltm = localtime(&baygio);

   // in cac thanh phan cua cau truc tm struct.
   cout << "Nam: "<< 1900 + ltm->tm_year << endl;
   cout << "Thang: "<< 1 + ltm->tm_mon<< endl;
   cout << "Ngay: "<<  ltm->tm_mday << endl;
   cout << "Thoi gian: "<< 1 + ltm->tm_hour << ":";
   cout << 1 + ltm->tm_min << ":";
   cout << 1 + ltm->tm_sec << endl;*/

/*int pin_number, tried1 = 3;
    string credit_card_number;
    string card_number;
    vector<string>card_number_list;
    int arr[1000];
    char c;
    bool credit_card_found = false;
    //cin.ignore();

    fstream inFile;
    inFile.open("credit card database.txt", ios::in);
    if(inFile.is_open()){
        while(inFile.eof() == false){
            getline(inFile, card_number);
            card_number_list.push_back(card_number);
        }
        inFile.close();
    }

    while(credit_card_found == false && tried1 > 0){
        tried1--;
        int i = 0;
        cout << "Enter credit card number: ";
        getline(cin, credit_card_number);

        Encrypt_input(credit_card_number);

        while(!credit_card_found && i < card_number_list.size()){
            if(credit_card_number == card_number_list[i] && !credit_card_number.empty()){
                credit_card_found = true;
            }
            i++;
        }
        if(credit_card_found == false){
            cout << "Credit card number incorrect, enter again" << endl;}
            if(tried1 == 0 && !credit_card_found){exit(0);}
    }*/



