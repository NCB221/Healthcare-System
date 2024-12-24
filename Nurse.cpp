#include "Nurse.h"

Nurse::Nurse(){}
Nurse::Nurse(string name){
    nurse_name = name;
}

void Nurse::setName(string name){
    nurse_name = name;
}
string Nurse::getName(){return nurse_name;}

void edit_menu(){
    cout << endl;
    cout << "1. Weigh" << endl;
    cout << "2. Height" << endl;
    cout << "3. Blood pressure" << endl;
    cout << "4. Stop editing and save" << endl;
    cout << "Choose the part that needed updating: ";
}

void Nurse::edit_Patient_record( string patient_name, string medical_record[]){
    string weigh, height, blood_presure;
    fstream outFile;
    string patient_record_file = "";
        patient_record_file = patient_name + "MedicalRecord.txt";
        outFile.open(patient_record_file, ios::out);
    int opt;
    edit_menu();
    cin >> opt;
    while (opt != 4){
    switch(opt){
        case 1:
        cin.ignore();
        cout << endl << "Enter patient weigh: " ;
        getline(cin, weigh);
        medical_record[3] = weigh;
        edit_menu();
        cin >> opt;
        break;
        case 2:
        cin.ignore();
        cout << endl << "Enter patient height: ";
        getline(cin, height);
        medical_record[4] = height;
        edit_menu();
        cin >> opt;
        break;
        case 3: 
        cin.ignore();
        cout << endl << "Enter patient blood presure: ";
        getline(cin, blood_presure);
        medical_record[5] = blood_presure;
        edit_menu();
        cin >> opt;
        break;
        case 4:
        cout << "Record saved successfully.";
        break;
    }
    }
    for(int i = 0; i < 6; i++){
        outFile << medical_record[i] << endl;
    }
    outFile.close();
}

void Nurse::view_patient_medical_record(fstream &inFile, string patient_name){
    char c;
    string medical_record[9];
    string weigh, height, blood_presure,n , reason, treatment_content, prescription;
    for(int i = 0; i < 9; i++){
        getline(inFile, medical_record[i]);
    }
    system("clear");
    cout << "Doctor name: " << medical_record[0] << endl;
    cout << "Date: " << medical_record[1] << endl;
    cout << "Appointment confirmation: " << medical_record[2] << endl;
    cout << "Patient name: " << patient_name << endl;
    cout << "Weigh(pound): " << medical_record[3] << endl;
    cout << "Height(feet): " << medical_record[4] << endl;
    cout << "Blood presure(mmHg): " << medical_record[5] << endl;
    cout << "Reason: " << medical_record[6] << endl;
    cout << "Treatment content: " << medical_record[7] << endl;
    cout << "Prescription: " << medical_record[8] << endl;
    inFile.close();
    cout << "Do you want to edit this record?" << endl;
        cout << "Enter 'y' to edit or press anything to go back: ";
        cin >> c;
        if(c == 'y' || c == 'Y'){
    edit_Patient_record(patient_name, medical_record);} else {exit(0);}
}

void Nurse::access_Patient_record(){
    string patient_name;
    bool name_found = false;
    string patient_name_list[1024];
    int  i = 0, tried = 3;
    char c;
    cin.ignore();
    cout << "Enter patient name: ";
    getline(cin, patient_name);
    fstream inFile;
    inFile.open("PatientName.txt", ios::in);
     while(!name_found && !inFile.eof()){
        inFile >> patient_name_list[i];
        if(patient_name_list[i] == patient_name){
            name_found = true;
            i++;
        }
        if(!name_found){
            while(!name_found && tried != -1){
                int n = 0;
                cout << "Patient name incorrect, please enter again: ";
                getline(cin, patient_name);
                while(!name_found && n < i){
                    if(patient_name_list[n] == patient_name){
                        name_found = true;
                        inFile.close();
                    } n++;
                } tried--;
            }
        }
    }
     if(tried == -1){
             inFile.close();
                system("clear");
                cout << "-------------Log in fail--------------" << endl;
                cout << "Press anything to go back to main menu" << endl;
                cin >> c;
        }
    if(name_found){
        int tried = 3;
        bool phone_found = false;
        fstream inFile;
        long int patient_phone;
        string patient_infor_file = "";
        patient_infor_file = patient_name + "Information.txt";
        inFile.open(patient_infor_file, ios::in);
        string n1, n2;
        long int phone_number;
        getline(inFile, n1, ',');
        getline(inFile, n1, ',');        
        inFile >> phone_number;
        inFile.close();
        cout << "Enter patient phone number: ";
        cin >> patient_phone;
        while(tried != -1 && phone_found == false){
            if(patient_phone == phone_number){
            phone_found = true;
        } else {
        cout << "Number incorrect, please enter again: ";
        cin >> patient_phone;
        tried--;}
        }

        string patient_record_file = "";
        patient_record_file = patient_name + "MedicalRecord.txt";
        inFile.open(patient_record_file, ios::in);
        view_patient_medical_record(inFile, patient_name);
    }
    inFile.close();
}