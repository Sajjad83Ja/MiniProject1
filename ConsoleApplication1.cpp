// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include<iostream>
#include<Windows.h>
#include<string>
#include<vector>
#include<limits>

using namespace std;

class User;
class Question;
class Examination;
int ProfessorDashboardMenu();
int FindPerson(User List[], string Name, string Pass);

class User
{
public:
	User(string Name, string Pass, bool IsPro);
	friend int FindPerson(User List[], string Name, string Pass);
	bool RetCondition();

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
bool User::RetCondition()
{
	return IsProfessor;
}


class Question
{
public:
	friend class Examination;
	Question();
	void SetTest();
private:
	string QuestionTxt;
	bool IsTest;
	string Option[4];
	int Answer;
	int QScore;
	int QTime;
};
Question::Question()
{
}
void Question::SetTest()
{
	cout << "Is it a test question [Y/n] ? ";
	char YorN;
	cin >> YorN;
	if (YorN == 'y' || YorN == 'Y')
		IsTest = true;
	else
		IsTest = false;
}



class Examination
{
public:
	Examination();
	void SetQuestion();
private:
	Question* Questions;
	int n;
};
Examination::Examination()
{
	cout << "How many questions does the exam have? ";
	cin >> n;
	Questions = new Question[n];
}
void Examination::SetQuestion()
{
	for (int i = 0; i < 5; i++)
	{
		cout << "Please enter #" << i + 1 << " text question :";
		getline(cin, Questions[i].QuestionTxt);
		Questions[i].SetTest();
		if (Questions[i].IsTest)
		{
			for (int j = 0; j < 4; j++)
			{
				cout << "Please enter #" << j + 1 << " option :";
				getline(cin, Questions[i].Option[j]);
			}
			cout << "Which option is correct ? ";
			cin >> Questions[i].Answer;
			Questions[i].Answer--;
		}
		cout << " Enter score questions : ";
		cin >> Questions[i].QScore;
		cout << " Enter response time questions : ";
		cin >> Questions[i].QTime;
	}
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
	cout << "Enter Your UserName : ";
	getline(cin, Name);
	cout << "Enter Your PassWord : ";
	getline(cin, Pass);

	if (FindPerson(Person, Name, Pass) >= 0)
	{
		/*Finded Currectly*/
		if (Person[FindPerson(Person, Name, Pass)].RetCondition())
		{
			while (true)
			{
				switch (ProfessorDashboardMenu())
				{
				case 1:

					break;
				default:
					break;
				}
			}
		}
		else
		{
			/*Enty Person Is a student.*/
		}
	}
	else
	{
		if (FindPerson(Person, Name, Pass) == -1)
		{
			cout << "\nWrong PassWord.";
		}
		else
		{
			cout << "\nUser Not Found.";
		}
	}
}

int ProfessorDashboardMenu()
{
	int Chosen;
	cout << " [ 1 ] Create a new examination.\n"
		<< " [ 2 ] Show history of all examination.\n"
		<< " [ 3 ] Exams in the correction queue\n"
		<< " [ 4 ] List of students.\n"
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
