#include<iostream>
#include<Windows.h>
#include<string>
#include<vector>

using namespace std;

class User;
class Question;
class Examination;

int ProfessorDashboardMenu();
int FindPerson(User List[], string Name, string Pass);



class Question
{
public:
	friend class Examination;
	void SetTest();
private:
	string QuestionTxt;
	bool IsTest;
	string Option[4];
	int Answer;
	int QScore;
	int QTime;
};
void Question::SetTest()
{
	cout << "Is it a test question [Y/n] ? ";
	char YorN;
	cin >> YorN;
	cin.ignore(9223372036854775807, '\n');
	if (YorN == 'y' || YorN == 'Y')
		IsTest = true;
	else
		IsTest = false;
}




class Examination
{
public:
	Examination();
	inline void Print();
	inline int RetNumnerOfQ();
private:
	vector<Question>QList;
	int NumnerOfQ;
};
Examination::Examination()
{
	cout << "How many questions does the exam have? ";
	cin >> NumnerOfQ;
	cout << "=====================================\n";
	cin.ignore(9223372036854775807, '\n');
	Question TempQ;
	for (int i = 0; i < NumnerOfQ; i++)
	{
		cout << "Please enter #" << i + 1 << " text question :";
		getline(cin, TempQ.QuestionTxt);
		TempQ.SetTest();
		if (TempQ.IsTest)
		{
			for (int j = 0; j < 4; j++)
			{
				cout << "Please enter #" << j + 1 << " option :";
				getline(cin, TempQ.Option[j]);
			}
			cout << "Which option is correct ? ";
			cin >> TempQ.Answer;
			cin.ignore(9223372036854775807, '\n');
			TempQ.Answer--;
		}
		cout << " Enter score questions : ";
		cin >> TempQ.QScore;
		cin.ignore(9223372036854775807, '\n');
		cout << " Enter response time questions : ";
		cin >> TempQ.QTime;
		cin.ignore(9223372036854775807, '\n');
		cout << "=====================================\n";
		QList.push_back(TempQ);
	}
}
void Examination::Print()
{
	for (int Index = 0; Index < NumnerOfQ; Index++)
	{
		cout << "=====================================\n";
		cout << QList[Index].QuestionTxt << "(" << QList[Index].QScore << ")\n";
		if (QList[Index].IsTest)
		{
			for (int i = 0; i < 4; i++)
			{
				cout << "Option #" << i + 1 << " : " << QList[Index].Option[i] << endl;
			}
		}
	}
}
int Examination::RetNumnerOfQ()
{
	return NumnerOfQ;
}





class User
{
public:
	User(string Name, string Pass, bool IsPro);
	friend int FindPerson(User List[], string Name, string Pass);
	bool RetCondition();
	void CreateExam();
	void ShowAllExam();
private:
	string UserName;
	string PassWord;
	bool IsProfessor;
	vector<Examination> ExamList;
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
void User::CreateExam()
{
	Examination TempExam;
	ExamList.push_back(TempExam);
}
void User::ShowAllExam()
{
	if (ExamList.size() != 0)
		for (int i = 0; i < ExamList.size(); i++)
		{
			cout << "\n\nExam " << i + 1 << " : \n";
			cout << " Number of Questions : " << ExamList[i].RetNumnerOfQ() << endl;
			ExamList[i].Print();
		}
	else
		cout << "No Items Found.\n";
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

	int Index = FindPerson(Person, Name, Pass);
	if (Index >= 0)
	{
		/*Finded Currectly*/
		if (Person[Index].RetCondition())
		{
			while (true)
			{
				switch (ProfessorDashboardMenu())
				{
				case 1:
					Person[Index].CreateExam();
					break;
				case 2:
					Person[Index].ShowAllExam();
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
	cin.ignore(9223372036854775807, '\n');
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
