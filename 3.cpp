#include <iostream>
using namespace std;

int check_input(){
    int i;
while(true){
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
int main(){
    int i = check_input();
    return 0;
}