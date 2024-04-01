// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include<iostream>
#include<Windows.h>
#include<string>
using namespace std;

class User;
int ProfessorDashboardMenu();
int FindPerson(User List[], string Name, string Pass);

class User
{
public:
	User(string Name, string Pass, bool IsPro);
	~User();
	friend int FindPerson(User List[], string Name, string Pass);
private:
	string UserName;
	string PassWord;
	bool IsProfessor;
};

User::User(string Name, string Pass, bool IsPro)
{
	UserName = Name;
	PassWord = Pass;
	IsProfessor = IsPro;
}

User::~User()
{
}

int main()
{
	User Person[] = { {"Lotfi","1234",true},
					{"Hosseiny","5678",true},
					{"Sajjad","9101112",false},
					{"Maryam","121314",false},
					{"Sadra","151617",false},
					{"Amin","181920",false} };

	string Name, Pass;
	getline(cin, Name);
	getline(cin, Pass);

	if (FindPerson(Person, Name, Pass) >= 0)
	{
		/*Finded Currectly*/
	}
	else
	{
		if (FindPerson(Person, Name, Pass) == -1)
		{
			/*Wrong Pass*/
		}
		else
		{
			/*User Not Exist*/
		}
	}
}

int ProfessorDashboardMenu()
{
	system("cls");
	int Chosen;
	cout << " [ 1 ] Create a new quiz.\n"
		<< " [ 2 ] Show history of all examination.\n"
		<< " [ 3 ] Exams in the correction queue\n"
		<< " [ 4 ] List of students.\n"
		<< " [ 5 ] Back.\n"
		<< " Please select an option : ";
	cin >> Chosen;
	return Chosen;
}

int FindPerson(User List[], string Name, string Pass)
{
	for (int i = 0; i < 6; i++)
	{
		if (List[i].UserName == Name)
		{
			if (List[i].PassWord == Pass)
				return i;
			return -1;
		}
	}
	return -2;
}



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
