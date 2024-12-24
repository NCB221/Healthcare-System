#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
//#include "2.cpp"
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

struct appointment{
    string doctor;
    string date;
};

int main() {
    fstream file;
    string s;
    vector<string> si;
    appointment a;
    vector<appointment> an;
   file.open("Appointment Avaiable.txt", ios::in);
/*while(!file.eof()){
    getline(file, s);
    si.push_back(s);
}
for(int i = 0; i < si.size(); i++){
    Decrypt_input(si[i]);
}
for(int i = 0; i < si.size(); i++){
    cout << si[i] << endl;;
}*/

while(!file.eof()){
    getline(file, a.doctor);
    getline(file, a.date);
    an.push_back(a);
}
file.close();

for(int i = 0; i < an.size();i++){
    Decrypt_input(an[i].doctor);
    Decrypt_input(an[i].date);
}

for(int i = 0; i < an.size(); i++){
    cout << i + 1 << ". " << an[i].doctor << endl;
    cout << "   " << an[i].date << endl;
}

si.push_back("John");
si.push_back("Josh");
si.push_back("Jensen");

/*for(int i = 0; i < si.size(); i++){
    Encrypt_input(si[i]);
}

for(int i = 0; i < si.size(); i++){
    cout << si[i] << endl;
}*/
   return 0;
}
