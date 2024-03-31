// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>

using namespace std;

int RoleMenu();
int ProfessorDashboardMenu();





int main()
{
	bool Back = false;
	while (true)
	{
		switch (RoleMenu())
		{
		case 1:
			while (!Back)
			{
				Back = false;
				switch (ProfessorDashboardMenu())
				{
				case 1:
					/*Create a new quiz.*/
					break;
				case 2:
					/*Show history of all examination.*/
					break;
				case 3:
					/*Exams in the correction queue*/
					break;
				case 4:
					/*List of students.*/
					break;
				case 5:
					/*Back*/
					Back = true;
					break;
				}
			}
			break;
		case 2:
			/*It is Student*/
			break;
		case 3:
			exit(1);
		}
	}
}

int RoleMenu()
{
	system("cls");
	int Chosen;
	cout << " [ 1 ] I'm Professor.\n"
		<< " [ 2 ] I'm Student.\n"
		<< " [ 3 ] Exit from Application.\n"
		<< " Please select an option : ";
	cin >> Chosen;
	return Chosen;
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





// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
