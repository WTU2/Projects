/*this program creates contacts and allows the option to display them through the use of a menu.*/
// side project/practice for C++
// 11/15/22
// program created by William Tu

#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h> /*allows the use of the exit(0) parameter*/
using namespace std;

/*allows functions to be called after the user-created function, "void menu(vector<string> contacts)"*/
void newContact(vector<string> contacts);
void print(const vector<string>& contactNames);

void menu(vector<string> contacts) 	// displays menu for users to select
{
	const vector<string> addingContacts{};
	int userInp{};

	cout << "	MENU SELECTION" << endl;
	cout << "---------------------------------" << endl;
	cout << "------- " << "Select an option" << " --------" << endl;
	cout << "---------------------------------" << endl;
	cout << "----- " << "1.) Create new contact" << " ----" << endl;
	cout << "----- " << "2.) Show contacts" << " ---------" << endl;
	cout << "----- " << "3.) Quit" << " ------------------" << endl;
	cout << "---------------------------------" << endl;
	cout << "> ";
	cin >> userInp;

	// choices for users
	do
	{
		switch (userInp)
		{
		case 1:
			newContact(addingContacts);
			break;
		case 2:
			print(contacts);
			break;
		case 3:
			exit(0);
			break;
		}
	} while ((userInp == 1) || (userInp == 2) || (userInp == 3));

	cout << "ERROR: Please enter a correct choice\n" << endl;
}

void newContact(vector<string> contacts) 	// creates new contacts
{
	int numberContacts{};
	string contactNames{};
	bool backToMenu;

	cout << "\nEnter NUMBER of contacts\n" << "> ";
	cin >> numberContacts; // replaces current number of contacts

	cout << "\nEnter contact name(s):\n";
	for (int i = 0; i < numberContacts + 1; ++i)
	{
		getline(cin, contactNames);
		contacts.push_back(contactNames); // push back names to the vector
	}
	cout << "\nContacts created\n" << endl;

	while (backToMenu = true)
	{
		menu(contacts);
	}

}

void print(const vector<string>& contactNames) // prints vector of names
{
	vector<string> contacts;
	int userChoice;

	cout << "\nContacts:";
	for (int i = 0; i < contactNames.size(); ++i)
	{
		cout << contactNames.at(i) << endl;
	}

	/*choices to go back to menu or quit after function finishes dispalying names*/
	cout << "\n1.) Back to menu\n2.) Quit application\n" << "> ";
	cin >> userChoice;

	do
	{
		switch (userChoice)
		{
		case 1:
			menu(contactNames);
			break;
		case 2:
			exit(0);
			break;
		}


	} while ((userChoice == 1) || (userChoice == 2));
	
	cout << "ERROR: Please enter a correct option" << endl;
}

int main()
{
	vector<string> contacts; // empty vector

	// call the menu to start off program
	while (bool menuSelection = true)
	{
		menu(contacts);

	}


	system("pause>nul"); /*pauses program so the program doesn't close*/
}