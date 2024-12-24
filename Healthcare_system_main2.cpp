#include <iostream>
#include <string.h>
#include <cstdlib>
#include <time.h>
#include <regex>
#include <fstream>

#include "Menu.cpp"
#include "Patient.cpp"
#include "Doctor.cpp"
#include "CEO.cpp"
#include "Nurse.cpp"
using namespace std;

enum ACTIONTYPE {
    LOG_IN,
	MAKE_APPOINTMENT,
    CHANGE_APPOINTMENT,
    CANCEL_APPOINTMENT,
    ACCESS_APPOINTMENT,
    ACCESS_MEDICAL_RECORD,
    PAY_WITH_CREDIT_CARD,
    PAY_WITH_DEBIT_CARD,
    PAY_WITH_CHECK,
    PAY_INVOICE,
    PATIENT_LOGIN,
    LOG_OUT,
    END_PROGRAM,
};

void Log_In(string);
void medical_app(string, string);


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
    medical_app(" ", " ");
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
        medical_app(actor, actor_name);
   }
   /*if(actor == "Doctor"){
    Doctor * doctor = new Doctor(actor_name);
    Doctor_menu(doctor);}
    if(actor == "Nurse"){
        Nurse * nurse = new Nurse(actor_name);
        Nurse_menu(nurse);
    }*/
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
// if log in successful, system find the name of the actor base on the position
  if(ID_found == true && pass_word_found == true){
    go_to_menu(actor, position);
  }
}

void medical_app(string actor, string actor_name){

    Menu * mainMenu = new Menu("Main menu","Main menu");
    Menu * SignIn_menu = new Menu("Sign in", "Sign in menu");
    Menu * PayInvoice = new Menu("Pay invoice", "Pay invoice menu");
    Menu * logInMenu = new Menu("Log in", "Log in menu");

    mainMenu->addSubMenu(logInMenu);
    mainMenu->addSubMenu(SignIn_menu);
    mainMenu->addSubMenu(PayInvoice);

    Menu * log_out = new Menu("Log out", "Log out successfully", LOG_OUT);

    Menu * CEO_login = new Menu("CEO", "Log in successfully", LOG_IN);
    Menu * Doctor_login = new Menu("Doctor", "Log in successfully");
    Menu * Nurse_login = new Menu("Nurse", "Log in successfully", LOG_IN);
    Menu * Staff_login = new Menu("Staff", "Log in successfully", LOG_IN);
    Menu * Patient_login = new Menu("Patient", "Log in successfully", LOG_IN);

    logInMenu->addSubMenu(CEO_login);
    logInMenu->addSubMenu(Doctor_login);
    logInMenu->addSubMenu(Nurse_login);
    logInMenu->addSubMenu(Staff_login);
    logInMenu->addSubMenu(Patient_login);

    Menu * Doctor_menu = new Menu("Doctor menu", "This is doctor menu");

    Menu * doctor_access_paymentRecord = new Menu("Access payment record", " ");
    Menu * doctor_access_patientRecord = new Menu("Access patient record", " ");
    Menu * doctor_edit_patientRecord = new Menu("Edit patient record", " ");

    Doctor_menu->addSubMenu(doctor_access_patientRecord);
    Doctor_menu->addSubMenu(doctor_access_patientRecord);
    Doctor_menu->addSubMenu(doctor_edit_patientRecord);

    Doctor_login->addSubMenu(Doctor_menu);
    

    Menu * Patient_menu = new Menu("Patient menu", "This is patient menu");

    
    Menu * patient_make_appointment = new Menu("Make appointment","Go back to menu", MAKE_APPOINTMENT);
    Menu * patient_change_appointment = new Menu("Change appointment","Go back to menu");
    Menu * patient_cancel_appointment = new Menu("Cancel appointment","Go back to menu");
    Menu * patient_access_medical_record = new Menu("Access medical record","Go back to menu");
    Menu * pay_with_creditcard = new Menu("Pay with credit card","Go back to menu", PAY_WITH_CREDIT_CARD);
    Menu * pay_with_debitcard = new Menu("Pay with debit card","Go back to menu");
    Menu * pay_with_check = new Menu("Pay with check","Go back to menu");
    Menu * pay_invoice = new Menu("Pay invoice","Go back to menu");
    Patient_menu->addSubMenu(patient_make_appointment);
    Patient_menu->addSubMenu(patient_change_appointment);
    Patient_menu->addSubMenu(patient_cancel_appointment);
    Patient_menu->addSubMenu(patient_access_medical_record);
    Patient_menu->addSubMenu(pay_with_creditcard);
    Patient_menu->addSubMenu(pay_with_debitcard);
    Patient_menu->addSubMenu(pay_with_check);
    Patient_menu->addSubMenu(pay_invoice);
    Patient_menu->addSubMenu(log_out);

    Menu * currentMenu;
    Patient * patient;
    Doctor * doctor;
    Nurse * nurse;

    if(actor == " "){
        currentMenu = mainMenu;
    }

    if(actor == "log in"){
        currentMenu = logInMenu;
    }

    if(actor == "Patient"){
    currentMenu = Patient_menu;
    patient = new Patient(actor_name);
    }
    while(true){
        currentMenu->displayMenu();
        int option = currentMenu->pickOption();
        currentMenu = currentMenu->getSubMenu(option - 1);
        string actor = currentMenu->getName();
        switch(currentMenu->getAction()){
            case -1:
            break;
            case LOG_IN:
            Log_In(actor);
            break;
            case MAKE_APPOINTMENT :
            patient->make_appointment();
            break;
            case CHANGE_APPOINTMENT:
            patient->change_appointment();
            break;
            case CANCEL_APPOINTMENT:
            patient->cancel_appointment();
            break;
            case PAY_WITH_CREDIT_CARD:
            patient->pay_with_creditCard();
            break;
            case LOG_OUT:
            medical_app("log in", " ");
            break;
            case END_PROGRAM:
            exit(0);
            break;
        }
    }
}

int main(){
   medical_app(" ", " ");
   return 0;
}