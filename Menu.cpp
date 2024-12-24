#include "Menu.h"


Menu::Menu()
{
	name = "Default name";
	description = "Default description";
	action = -1;
	subMenu.clear();
}

Menu::Menu(string name, string description, int action)
{
	this->name = name;
	this->description = description;
	this->action = action;
	subMenu.clear();
}

Menu::~Menu()
{
	if (subMenu.size() > 0) {
		for (int i = 0; i < subMenu.size(); i++) {
			if (subMenu[i]) delete subMenu[i];
		}
		subMenu.clear();
	}
}

string Menu::getName()
{
	return this->name;
}

void Menu::setName(string s)
{
	this->name = s;
}

string Menu::getDesription()
{
	return this->description;
}

void Menu::setDescription(string d)
{
	this->description = d;
}

int Menu::getAction()
{
	return action;
}

void Menu::setAction(int a)
{
	this->action = a;
}

void Menu::addSubMenu(Menu* m)
{
	this->subMenu.push_back(m);
	m->subMenu.push_back(this);
}

Menu* Menu::getSubMenu(int index)
{
	if (index >= 0 && index < subMenu.size())
		return subMenu[index];
	else
		return nullptr;
}

void Menu::displayMenu()
{
	
	system("clear");
	cout << "=====" << this->name << "=====" << endl;
	cout << this->description << endl;
	for (int i = 0; i < subMenu.size(); i++) {
		
		
		cout << i + 1 << ". " << subMenu[i]->getName() << endl;
		
	}
}

int Menu::pickOption()
{
	while (true) {
		cout << "Pick an Option: ";
		int opt;
		cin >> opt;
		try {
			if (cin.fail()) {
				throw "Invalid input";
			}
			else if(opt < 1 || opt > subMenu.size()) {
				throw "Out of range";
			}
			else {
				return opt;
			}
		}
		catch (const char* mess) {
			cin.clear();
			cin.ignore();
			cout << "Error: " << mess << endl;
		}
	}
}
