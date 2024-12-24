#include <iostream>
#include <vector>
#include <cstdlib>
#include <math.h>
#include <cstring>
#include <fstream>
#include "CEO.cpp"
#include "Doctor.cpp"
#include "Patient.cpp"
#include "Nurse.cpp"
using namespace std;

void LogIn_menu();
void CEO_login();
void Doctor_login();
void Nurse_login();
void Staff_login();
void Patient_login();
void Log_In(string);

int pickOption(string actor)
{
    int opt;
	while (true) {
        int max;
        if(actor == "ceo") max = 6;
        if(actor == "doctor") max = 4;
        if(actor == "patient") max = 9;
        if(actor == "nurse") max = 2;

        std::cout << endl;
		cout << "Pick an Option: ";
		cin >> opt;
		try {
			if (cin.fail()) { throw "Invalid input"; }
			else if(opt < 1 || opt > max) { throw "Out of range";}
			else { return opt;}
		}
		catch (const char* mess) {
			cin.clear();
			cin.ignore();
			cout << "Error: " << mess << endl;
		}
	}
    return opt;
}

void logIn_menu(){
    int opt;
    system("clear");
    cout << "--Log In Menu--" << endl;
    cout << "1. CEO " << endl;
    cout << "2. Doctor" << endl;
    cout << "3. Nurse" << endl;
    cout << "4. Staff" << endl;
    cout << "5. Patient" << endl;
    cout << "Log in as: ";
    cin >> opt;
    switch(opt){
        case 1: CEO_login(); break;
        case 2: Log_In("Doctor"); break;
        case 3: Log_In("Nurse"); break;
        case 4: Log_In("Staff"); break;
        case 5: Log_In("Patient"); break;
    }
}

void CEO_menu(CEO * ceo){
    system("clear");
    cout << "Log in successfully" << endl;
    cout << "--CEO menu--"<< endl;
    cout << "1. Access payment record" << endl;
    cout << "2. Access patient record" << endl;
    cout << "3. Access daily report" << endl;
    cout << "4. Access monthly report" << endl;
    cout << "5. Adjust salary" << endl;
    cout << "6. Log out" << endl;
    int opt = pickOption("ceo");
    switch (opt)
    {
    case 1: ceo->access_Payment_record(); break;
    case 2: ceo->access_Patient_information(); break;
    case 3: ceo->access_Dailyly_report(); break;
    case 4: ceo->access_Monthly_report(); break;
    case 5: ceo->adjustSalary(); break;
    case 6: logIn_menu(); break;
    }
}

void Doctor_menu(Doctor * doctor){
    system("clear");
    cout << "Log in successfully" << endl;
    cout << "--Doctor menu--"<< endl;
    cout << "1. Access payment record" << endl;
    cout << "2. Access patient record" << endl;
    cout << "3. Edit patient record" << endl;
    cout << "4. Log out" << endl;
    cout << "Choose your option: ";
    int opt = pickOption("doctor");
    switch (opt){
    case 1: doctor->access_Payment_record(); break;
    case 2: doctor->access_Patient_payment(); break;
    case 3: doctor->edit_Patient_record(); break;
    case 4: logIn_menu(); break;}
}
void Nurse_menu(Nurse * nurse){
    system("clear");
    cout << "Log in successfully" << endl;
    cout << "--Nurse menu--"<< endl;
    cout << "1. View patient record" << endl;
    cout << "2. Log out" << endl;
    int opt = pickOption("nurse");
    switch(opt){
    case 1: nurse->access_Patient_record(); break;
    case 2: logIn_menu(); break;
    }
}

void Patient_menu(Patient * patient){
    system("clear");
    cout << "Log in successfully" << endl;
    cout << "--Patient menu--"<< endl;
    cout << "1. Make appointment" << endl;
    cout << "2. Change appointment" << endl;
    cout << "3. Cancel appointment" << endl;
    cout << "4. Access medical record" << endl;
    cout << "5. Pay with credit card" << endl;
    cout << "6. Pay with debit card" << endl;
    cout << "7. Pay with check" << endl;
    cout << "8. Pay invoice" << endl;
    cout << "9. Log out" << endl;
    //cout << "Choose your option: ";
    //cin >> opt;
    int opt = pickOption("patient");
    switch (opt){
    case 1: patient->make_appointment(); break;
    case 2: patient->change_appointment(); break;
    case 3: patient->cancel_appointment(); break;
    case 4: patient->access_medical_record(); break;
    case 5: patient->pay_with_creditCard(); break;
    case 6: patient->pay_with_debitCard(); break;
    case 7: patient->pay_with_check(); break;
    case 8: patient->pay_invoice(); break;
    case 9: logIn_menu();
    }
}

void Log_In(string actor){
   fstream inFile;
   string ID_file_name = "";
   ID_file_name = actor + "ID.txt";
   inFile.open(ID_file_name, ios::in);

   char c;
   int ID;
   int ID_arr[100];
   string passWord;
   string Password_arr[100];
   int tried1 = 3, tried2 = 3;
   int pos;
   bool check_login = false, ID_found = false, PassWordFound = false, found1 = false;

   cin.ignore();
   cout << "Enter ID: ";
   cin >> ID; //user input
   while(!ID_found && !PassWordFound){
   
        int i = 0;
        while(!found1 && !inFile.eof()){
            inFile >> ID_arr[i];
            if(ID_arr[i] == ID){ found1 = true; pos = i;}
            i++;
        } if(found1){
            ID_found = true; inFile.close();
        } else { 
            while(tried1 != -1 && !ID_found){
                int n = 0;
            cout << "ID incorrect, please enter again: ";
                cin >> ID;
            while(!ID_found && n < i){
                if(ID_arr[n] == ID){ 
                    ID_found = true;
                    pos = n;
                    inFile.close();
                    } n++;
            }tried1--;
            }
            }
         if(tried1 == -1){
             system("clear");
             inFile.close();
                system("clear");
                cout << "-------------Log in fail--------------" << endl;
                cout << "Press anything to go back to main menu" << endl;
                cin >> c;
                logIn_menu();
        }
        cin.ignore();
         cout << "Enter password: " ;
    getline(cin, passWord);
    int m = 0;
    string passWord_file_name = "";
    passWord_file_name = actor + "Password.txt";
    inFile.open(passWord_file_name, ios::in);
    while(m != pos + 1){
        inFile >> Password_arr[m];
        m++;
    }
    inFile.close();
    while(passWord != Password_arr[pos] && tried2 != -1){
        cin.ignore();
        cout << "Enter pass word again: ";
        getline(cin, passWord);
        tried2--;
    }
    if(tried1 == -1){
             system("clear");
             inFile.close();
                system("clear");
                cout << "-------------Log in fail--------------" << endl;
                cout << "Press anything to go back to main menu" << endl;
                cin >> c;
                logIn_menu();
        }
    if(passWord == Password_arr[pos]){
        PassWordFound = true;
    }
   } 
   int k = 0;
   string actor_name;
   string actor_name_list[1024];
   fstream iFile;
   string actor_file_name = "";
   actor_file_name = actor + "Name.txt";
   iFile.open(actor_file_name, ios::in);
    while(k != pos + 1){
        inFile >> actor_name_list[k];
        k++;
    }
    actor_name = actor_name_list[k];
    if(actor == "Patient"){
   Patient * patient = new Patient(actor_name);
   Patient_menu(patient);}
   if(actor == "Doctor"){
    Doctor * doctor = new Doctor(actor_name);
    Doctor_menu(doctor);}
    if(actor == "Nurse"){
        Nurse * nurse = new Nurse(actor_name);
        Nurse_menu(nurse);
    }
}


void CEO_login(){
    system("clear");
    int ID;
    string pass_word;
    CEO * ceo = new CEO;
    bool check_login = false;
    cin.ignore();
    cout << "ID: ";
    cin >> ID;
    int tried = 3, tried1 = 3;
    char c;
    while(check_login == false){
    while(ceo->getID() != ID && tried1 != 0){
        cout << "ID incorrect, please try again: ";  
            cin >> ID;
            tried1--;
            }
            if(tried1 == 0) {
                system("clear");
                cout << "-------------Log in fail--------------" << endl;
                cout << "Press anything to go back to main menu" << endl;
                cin >> c;
                logIn_menu();}
                cout << "Pass word: ";
    getline(cin, pass_word);
    while(ceo->getPassword() != pass_word && tried != -1){ 
        cout << "Password incorrect, please try again: "; 
            getline(cin, pass_word);
            tried--;
            }
            if(tried == -1) {
                system("clear");
                cout << "-------------Log in fail--------------" << endl;
                cout << "Press anything to go back to main menu" << endl;
                cin >> c;
                logIn_menu();}
    if(ID == ceo->getID() && pass_word == ceo->getPassword()){ check_login = true;}
} CEO_menu(ceo);
}

int main(){
    int opt;
    system("clear");
    cout << "1. Log in" << endl;
    cout << "2. Sign in" << endl;
    cout << "3. Pay invoice" << endl;
    cout << "4. End program" << endl;
    cout << "Choose your option: ";
    cin >> opt;
    switch (opt)
    {
    case 1:
    logIn_menu();
        break;
    
    case 2:
        break;
    case 4: exit(0); break;
    }
    return 0;
}