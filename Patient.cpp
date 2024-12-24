#include "Patient.h"

const long int access_control = 87556789656;
Patient::Patient(){}

Patient::Patient(string patient_name){
    this->patient_name = patient_name;
}
Patient::Patient(string patient_name, string address, int phone_number, string email, string social_security_number, string insurance_name){
   this->patient_name = patient_name;
   this->address = address;
   this->phone_number = phone_number;
   this->email = email;
   this->social_security_number = social_security_number;
   this->insurance_name = insurance_name;
}

void Patient::set_patient_name(string patient_name){this->patient_name = patient_name;}
void Patient::set_address(string address){this->address = address;}
void Patient::set_phone_number(int phone_number){ this->phone_number = phone_number;}
void Patient::set_email(string email){this->email = email;}
void Patient::set_social_security_number(string social_security_number){this->social_security_number = social_security_number;}
void Patient::set_insurance_name(string insurance_name){this->insurance_name = insurance_name;}

string Patient::get_patient_name(){return patient_name;}
string Patient::get_address(){return address;}
int Patient::get_phone_number(){return phone_number;}
string Patient::get_email(){return email;}
string Patient::get_social_security_number(){return social_security_number;}
string Patient::get_insurance_name(){return insurance_name;}

struct Appointment_Made{
    string Patient_Name;
    string timeSlot;
    int confirmation_number;
};

struct patient_appointment{
    string appointment_date;
    int confirmation_number;
};

struct current_patient_appointment{
    string doctor;
    string date;
    string confirmationNumber;
};


void get_appointment_made(fstream &appointment_file, Appointment_Made Appointment,  vector <Appointment_Made> &appointments){
    while (!appointment_file.eof()) {
                getline(appointment_file,Appointment.Patient_Name);
                getline(appointment_file,Appointment.timeSlot);
                appointment_file >> Appointment.confirmation_number;
                appointments.push_back(Appointment);
            }
}

void made_appointment(fstream &appointment_file, vector <Appointment_Made> &appointments){
    for(int i = 0; i < appointments.size(); i++){
        appointment_file << appointments[i].Patient_Name << endl;
        appointment_file << appointments[i].timeSlot << endl;
        appointment_file << appointments[i].confirmation_number << endl;
       }
}

int pick_option(int max)
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


void check_access_control(){
    long int credential_number;
    cout << "Please enter credential number: ";
    cin >> credential_number;

    while(credential_number != access_control){
        cout << "Incorrect Credential " << endl;
        cout << "1. Enter a new crdential number" << endl;
        cout << "2. Exit " << endl;
        int option = pick_option(2);
        switch (option)
        {
        case 1:
        cout << "Enter credential number: ";
        cin >> credential_number;
            break;
        case 2: exit(0);
        default:
            break;
        }
    }
}

bool check_account(int balance, int daily_limit, int pay_amount){
    return (balance == 0 || daily_limit == 0 || pay_amount > balance || pay_amount > daily_limit);
}

string Encrypt_input(string &plain_text){
    for(int i = 0; i < plain_text.length(); i++){
        plain_text[i] = plain_text[i] + 3;
    }
    return plain_text;
}

struct appointment{
    string doctor_name;
    string date;
};

string Decrypt_input(string &encrypted_text){
    for(int i = 0; i < encrypted_text.length(); i++){
        encrypted_text[i] = encrypted_text[i] - 3;
    }
    return encrypted_text;
}

void Patient::make_appointment(){
    //check_access_control();
    bool check_access_control = false;
    int check = 3;
    long int credential_number;
    while(check_access_control == false && check >0){
        check--;
        cout << "Please enter credential number: ";
    cin >> credential_number;
    if(credential_number == access_control){
        check_access_control = true;
    } else {
        cout << endl << "Incorrect Credential, enter again: " << endl;
    }
    }

while(check_access_control == true){
    int option; 
    char cha = ' ';
    string appointment_date;
    string s;
  //vector<string> Appointments;
  appointment a;
    vector<appointment> Appointments;

  current_patient_appointment pat;
    vector<current_patient_appointment> pat_list;

  fstream appointment_file;

  string patient_appoint = "";
  patient_appoint = get_patient_name() + " Appointment.txt";
//cout << patient_appoint << endl;
bool not_full = false;
bool avai_appointment = false;
bool check_appoint = false;

while((cha == ' ' && check_access_control == true) && not_full == false){
appointment_file.open(patient_appoint, ios::in);
while(!appointment_file.eof()){
        getline(appointment_file, pat.doctor);
        getline(appointment_file, pat.date);
        getline(appointment_file, pat.confirmationNumber);
        pat_list.push_back(pat);
    }
    appointment_file.close();

    if(pat_list.size() > 3){
        cout << "You have reach maximum number of pending appointment" << endl;
    cout << "Press anything to exit: ";
    cin >> cha;
    check_access_control = false;
    } else {
        not_full = true;
        check_access_control = true;
    }
}

    while((not_full == true && cha == ' ') && check_access_control == true && check_appoint == false){
        appointment_file.open("Appointment Avaiable.txt", ios::in);
    if(appointment_file.peek() == std::ifstream::traits_type::eof()){
        std::cout << "There are no available time slots in the next 3 months." << endl;
        cout << "Check back later or call XXX-XXX-XXXX to schedule an appointment.";
        cout << "Enter anything to exit: ";
        cin >> cha;
        check_access_control = false;
            } else {
                avai_appointment = true;
                check_access_control = true;
                check_appoint = true;
            }
appointment_file.close();
    }
while((not_full == true && cha == ' ') && avai_appointment == true && check_access_control == true && check_appoint == true){
    appointment_file.open("Appointment Avaiable.txt", ios::in);
    if(appointment_file.is_open()){
    while (!appointment_file.eof()){
      getline(appointment_file, a.doctor_name);
      getline(appointment_file, a.date);
      Appointments.push_back(a);
    }
      appointment_file.close();
    }

    //Decrypt data from file
    for(int i = 0; i < Appointments.size(); i++){
        Decrypt_input(Appointments[i].doctor_name);
        Decrypt_input(Appointments[i].date);
    }

    cout << "Appointments for the next 3 months: " << endl;
    for(int i = 0; i < Appointments.size() - 1; i++){
      cout << i + 1 << ". " << Appointments[i].doctor_name << endl;
      cout << "   " << Appointments[i].date << endl;
    }

    cout << endl;
    cout << "Choose your option: ";
    option = pick_option(Appointments.size() - 1);
    while(cin.fail() || option > Appointments.size() || option < 1){
        cout << "Invalid in put, please try again: ";
        option = pick_option(Appointments.size() - 1);
    }

    time_t now = time(0);
    int confirmation_number = now;

    string doctor = Appointments[option - 1].doctor_name;
    appointment_date = Appointments[option-1].date;

    Appointments.erase(Appointments.begin() + option -1);

    //Encrypt data before push back to storage
    for(int i = 0; i < Appointments.size() - 1; i++){
        Encrypt_input(Appointments[i].doctor_name);
        Encrypt_input(Appointments[i].date);
    }

    appointment_file.open("Appointment Avaiable.txt", ios::out);
    for(int i = 0; i < Appointments.size(); i++){
        appointment_file << Appointments[i].doctor_name << endl;
        appointment_file << Appointments[i].date << endl;
    }
    appointment_file.close();

    current_patient_appointment pat1;
    pat1.doctor = doctor;
    pat1.date = appointment_date;
    pat1.confirmationNumber = to_string(confirmation_number);
    
    pat_list.push_back(pat1);
    
    appointment_file.open(patient_appoint, ios::out);
    for(int i = 0; i < pat_list.size(); i++){
        appointment_file << pat_list[i].doctor << endl;
        appointment_file << pat_list[i].date << endl;
        appointment_file << pat_list[i].confirmationNumber << endl;
    }
    appointment_file.close();


char c;
    system("clear");
       cout << "Appointment date " << appointment_date << " with doctor" << doctor << " is confirmed" << endl;
       cout << "Your confirmation number is: " << confirmation_number << endl;
       cout << "Press anything to exit: ";
       cin >> c ;
    check_access_control = false;
}
    //}
}
    }


void Patient::change_appointment(){
    

}
void Patient::cancel_appointment(){}
void Patient::access_medical_record(){}

int check_input(){
    int i;
while(true){
    cout << endl;
    cout << "Enter number: ";
    cin >> i;
    try {
			if (cin.fail()) { throw "Invalid input"; }
            else {return i;}
		}
		catch (const char* mess) {
			cin.clear();
			cin.ignore();
			cout << "Error: " << mess << endl;
		}
    }
    return i;
}

void Patient::pay_with_creditCard(){

      bool check_access_control = false;
    int check = 3;
    long int credential_number;
    while(check_access_control == false && check >0){
        check--;
        cout << "Please enter credential number: ";
    cin >> credential_number;
    if(credential_number == access_control){
        check_access_control = true;
    } else {
        cout << endl << "Incorrect Credential, enter again: " << endl;
    }
    }
while(check_access_control == true){
    system("clear");
    int pin_number, tried1 = 3;
    string credit_card_number;
    string card_number;
    vector<string>card_number_list;
    int arr[1000];
    char c;
    bool credit_card_found = false;
    bool PIN_found = false;
    cin.ignore();
    char cha = ' ';
    while(cha == ' ' && check_access_control == true){

    fstream inFile;
    inFile.open("credit card database.txt", ios::in);
    if(inFile.is_open()){
        while(inFile.eof() == false){
            getline(inFile, card_number);
            card_number_list.push_back(card_number);
        }
        inFile.close();
    }

    while((credit_card_found == false && tried1 > 0) && check_access_control == true){
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
            if(tried1 == 0 && !credit_card_found){ 
            cout << "Press anything to go back to exit: ";
    cin >> cha;
    check_access_control = false;}
    }
    int pay_amount, balance, account_infor[3];
    string PIN;
    string account = "";
    
while((credit_card_found == true && cha == ' ') && PIN_found == false && check_access_control == true){
Decrypt_input(credit_card_number);

    int PIN, i = 0, tried = 3;
    
    account = credit_card_number + ".txt";

    inFile.open(account, ios::in);
    for(int i = 0; i < 3; i++){
        inFile >> account_infor[i];
    }
    inFile.close();

    while(PIN_found == false && tried > 0){ 
        tried--;
        cout << "Enter your pin: ";
     PIN = check_input();
        if(PIN == account_infor[0]){
        PIN_found = true;
        }
        if(PIN_found == false){
        cout << "PIN incorrect, please enter again" << endl;  
        }
        }
    if(tried == 0){
        cout << "Press anything to go back to exit: ";
    cin >> cha;
    check_access_control = false;
    }
}

while( (credit_card_found == true && PIN_found == true) && cha == ' ' && check_access_control == true){

    cin.ignore();

    fstream payment_file;
    int payment_record;    
    int bill_amount;
    int m = 0;
    string paymentFile = "";
    paymentFile = get_patient_name() + "PaymentRecord.txt";

    payment_file.open(paymentFile, ios::in);
    while(!payment_file.eof()){
        payment_file >> payment_record;
    }
    payment_file.close();

    cout << "Amount needed to pay: " << payment_record << endl;

  //  string s = payment_record[m];

    cout << "Enter the amount of money: ";
    pay_amount = check_input();
    balance = account_infor[1];
    cin.ignore();

    // check checks whether customer has enough funds in the account and whether the daily limit will not be exceeded 
    if(!check_account(account_infor[1], account_infor[2], pay_amount)){

    account_infor[1] = balance - pay_amount;
    account_infor[2] = account_infor[2] - pay_amount;

    fstream outFile;
    outFile.open(account, ios::out);
    for(int i = 0; i < 3; i++){
    outFile << account_infor[i] << endl;
    }
    outFile.close();

    payment_file.open(paymentFile, ios::in);
    while(!payment_file.eof()){
        payment_file >> payment_record;
    }
    payment_file.close();

    payment_record = payment_record - pay_amount;
    payment_file.open(paymentFile, ios::out);
    payment_file << payment_record;
    payment_file.close();

    int hospital_balance;
    inFile.open("1111222233334444.txt", ios::in);
    inFile >> hospital_balance;
    inFile.close();
    outFile.open("1111222233334444.txt", ios::out);
    outFile << hospital_balance + pay_amount;
    outFile.close();
    cout << "Payment successfully" << endl;
    cout << "Press anything to go back to exit: ";
    cin >> cha;
    check_access_control = false;
    }
}
}
    }
}

void Patient::pay_with_debitCard(){}
void Patient::pay_with_check(){}
void Patient::pay_invoice(){}