#ifndef MENU_H
#define MENU_H
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>

using namespace std;
class Menu
{
private:
	string name;
	string description;
	vector<Menu*> subMenu;
	int action;
public:
	Menu();
	Menu(string name, string description, int action = -1);
	~Menu();

	string getName();
	void setName(string s);

	string getDesription();
	void setDescription(string d);

	int getAction();
	void setAction(int a);

	void addSubMenu(Menu* m);
	Menu* getSubMenu(int index);

	void displayMenu();
	int pickOption();
};

#endif