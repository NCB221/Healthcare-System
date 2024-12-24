#include <iostream>
#include <vector>
#include <cstdlib>
#include <math.h>
#include <cstring>
#include <fstream>
#include <regex>
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

int pickOption(int max)
{
    int opt;
	while (true) {
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
    system("clear");
    cout << "--Log In Menu--" << endl;
    cout << "1. CEO " << endl;
    cout << "2. Doctor" << endl;
    cout << "3. Nurse" << endl;
    cout << "4. Staff" << endl;
    cout << "5. Patient" << endl;
    cout << "6. End program" << endl;
    cout << "Log in as: ";
    int opt = pickOption(6);
    switch(opt){
        case 1: CEO_login(); break;
        case 2: Log_In("Doctor"); break;
        case 3: Log_In("Nurse"); break;
        case 4: Log_In("Staff"); break;
        case 5: Log_In("Patient"); break;
        case 6: exit(0);
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
    int opt = pickOption(6);
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
    int opt = pickOption(4);
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
    int opt = pickOption(2);
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
    int opt = pickOption(9);
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

// Encryption function (Caesar Cipher)
string Encrypt(string &plain_text){
    for(int i = 0; i < plain_text.length(); i++){
        plain_text[i] = plain_text[i] + 3;
    }
    return plain_text;
}

// Decryption function (Caesar Cipher)
string Decrypt(string &encrypted_text){
    for(int i = 0; i < encrypted_text.length(); i++){
        encrypted_text[i] = encrypted_text[i] - 3;
    }
    return encrypted_text;
}

// check SQL Injection function
bool safe_input(string& input) {
    regex injection_regex("[';]|(--)|(/\\*)|DROP|SELECT", regex_constants::icase);
    return !regex_search(input, injection_regex);
}

void logIn_fail(){
    char c;
    system("clear");
    cout << "-------------Log in fail--------------" << endl;
    cout << "Press anything to go back to main menu" << endl;
    cin >> c;
    logIn_menu();
}

void go_to_menu(string actor, int position){
    string actor_name;
   string *actor_name_list = new string[1024];
   fstream iFile;
   string actor_file_name = "";
   actor_file_name = actor + "Name.txt";

   iFile.open("PatientName.txt", ios::in);
    for(int i = 0; i <= position; i++){
        iFile >> actor_name_list[i];
    }
    iFile.close();

    actor_name = actor_name_list[position];
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

struct Actor_login{
    string ID;
    string pass_word;
};

void get_login_infor(fstream &inFile, Actor_login & actor){
  getline(inFile, actor.ID);
  getline(inFile, actor.pass_word);
}

void Log_In(string actor){
    int position;
  int i = 0;
  int tried1 = 3, tried2 = 3;
  string ID, pass_word;
  fstream inFile;
  string actor_file = "";
  actor_file = actor + " ID and Password.txt";
  bool ID_found = false, pass_word_found = false;
  vector<Actor_login> login;
  Actor_login IDandPW;
  cin.ignore();
  system("clear");
  inFile.open(actor_file, ios::in);
  while(inFile.eof() == false){
  get_login_infor(inFile, IDandPW);
  login.push_back(IDandPW);
  }
  inFile.close();
  while(ID_found == false && tried1 > 0){
    tried1--;
    int i = 0;
    cout << "Enter ID: ";
  getline(cin, ID);

// check SQL injection 
  while(!safe_input(ID)){
    cout << "Input contain malicious character, please enter again." << endl;;
    cout << "Enter ID: ";
    getline(cin, ID);
  }

  Encrypt(ID); // Encrypt input data

  while(!ID_found && i < login.size()){
    if(ID == login[i].ID && !ID.empty()){
      ID_found = true;
      position = i;
    }
    i++;
  }
  if(ID_found == false){
  cout << "ID incorrect, enter again"<< endl;}
  }
  if(tried1 == 0 && !ID_found){ logIn_fail();}
 
  while(pass_word_found == false && tried2 > 0){
    tried2--;
    cout << "Enter pass word: ";
    getline(cin, pass_word);

    // check SQL injection 
  while(!safe_input(ID)){
    cout << "Input contain malicious character, please enter again." << endl;;
    cout << "Enter pass word: ";
    getline(cin, pass_word);
  }

    Encrypt(pass_word); // Encrypt input data

      if(pass_word == login[position].pass_word && !pass_word.empty()){
        pass_word_found = true;
      }
      if(pass_word_found == false){
  cout << "Pass word incorrect, enter again"<< endl;}
  }
  if(tried2 == 0 && !pass_word_found){ logIn_fail();}

  if(ID_found == true && pass_word_found == true){
    go_to_menu(actor, position);
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
    system("clear");
    cout << "1. Log in" << endl;
    cout << "2. Sign in" << endl;
    cout << "3. Pay invoice" << endl;
    cout << "4. End program" << endl;
    int opt = pickOption(4);
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