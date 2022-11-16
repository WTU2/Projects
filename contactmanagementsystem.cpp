/*this program creates contactsand allows the option to display them through the use of a menu.*/
// side project/practice for C++
// 11/15/22
// program created by William Tu

#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h> /*allows the use of the exit(0) parameter*/
using namespace std;

/*allows functions to be called after the user-created function, "void menu(vector<string> contacts)"*/
int main();
vector<string> newContact(vector<string> contacts);
void print(vector<string>& contactNames);

void menu(vector<string> contacts) 	// displays menu for users to select
{
	vector<string> addingContacts;
	int userInp;

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
	if (userInp == 1)
	{
		newContact(addingContacts); // calling function
	}
	else if (userInp == 2)
	{
		print(contacts); // calling function

	}
	else if (userInp == 3)
	{
		exit(0);  /*stops the program and quits the program too*/
	}
}

vector<string> newContact(vector<string> contacts) 	// creates new contacts
{
	int numberContacts;
	string contactNames;
	
	cout << "\nEnter NUMBER of contacts\n" << "> ";
	cin >> numberContacts; // replaces current number of contacts
	/*not sure how to add onto existing list yet*/

	cout << "\nEnter contact name(s):\n";
	for (int i = 0; i < numberContacts + 1; ++i)
	{
		getline(cin, contactNames);
		contacts.push_back(contactNames); // push back names to the vector
	}
	cout << "\nContacts created\n" << endl;

	menu(contacts);

	return contacts;


}

void print(vector<string>& contactNames) // prints vector of names
{
	unsigned int i;
	vector<string> contacts;
	int userChoice;

	cout << "\nContacts:";
	for (i = 0; i < contactNames.size(); ++i)
	{
		cout << contactNames.at(i) << endl;
	}

	/*choices to go back to menu or quit after function finishes dispalying names*/
	cout << "\n1.) Back to menu\n2.) Quit applciation\n" << "> ";
	cin >> userChoice;

	if (userChoice == 1)
	{
		menu(contacts);
	}
	else if (userChoice == 2)
	{
		cout << "Goodbye!";
		exit(0);
	}


}

int main()
{
	vector<string> contacts; // empty vector

	// call the menu to start off program
	menu(contacts);


	system("pause>nul"); /*pauses program so the program doesn't close*/
	return 0;
}