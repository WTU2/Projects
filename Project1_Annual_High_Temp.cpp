#include <iostream>

using namespace std;

int main() 
{
	double NYCTemp = 85.0;
	double DenvTemp = 88.0;
	double PhoenixTemp = 106.0;
	const double tempRise = .02;

	NYCTemp = NYCTemp * (tempRise + 1);
	DenvTemp = DenvTemp * (tempRise + 1);
	PhoenixTemp = PhoenixTemp * (tempRise + 1);

	cout << "New average temperatures: " << endl;
	cout << "NYC: " << NYCTemp << endl;
	cout << "Denver: " << DenvTemp << endl;
	cout << "Phoenix: " << PhoenixTemp << endl;
	
	system("pause>nul");
	return 0;



}