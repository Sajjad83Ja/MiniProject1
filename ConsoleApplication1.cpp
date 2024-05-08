#include<iostream>
#include<Windows.h>
#include<string>
#include<vector>
#include<stdlib.h>
#include<cstdlib>

using namespace std;

class Question;
class Examination;
class StudentList;
class User;
class Student;
class Professor;

int ProfessorDashboardMenu();
int FindPerson(User* List[], string Name, string Pass);

class Question
{
private:
	string QuestionTxt;
	bool IsTest;
	string Option[4];
	int Answer;
	int QScore;
	double QTime;
public:
	friend class Examination;
	void SetTest();
};

class Examination
{
private:
	vector<Question>QList;
	int NumnerOfQ;
	int TotalScore;
	double TotalTime;
public:
	Examination();
	inline void Print();
	inline int RetNumnerOfQ();
	inline int Score();
	inline double Time();
};

class StudentList
{
private:
	vector<Student*> SList;
public:
	friend class Professor;
	StudentList(User* Person[]);
	void PrintSList();
};

class User
{
protected:
	string UserName;
	string PassWord;
public:
	friend class StudentList;
	User(string Name, string Pass);
	friend int FindPerson(User* List[], string Name, string Pass);
	virtual char RetType() = 0;
	virtual void CreateExam();
	virtual void ShowAllExam();
	virtual void CreateList(User* Person[]);
	virtual void PrintList();
};

class Student :public User
{
public:
	Student(string Name, string Pass);
	char RetType();
};

class Professor :public User
{
private:
	vector<Examination> ExamList;
	vector<StudentList>List;
public:
	friend class StudentList;
	Professor(string Name, string Pass);
	char RetType();
	void CreateExam();
	void ShowAllExam();
	void CreateList(User* Person[]);
	void PrintList();
};

int main()
{
	system("color F0");
	Student Slist[] = { {"Sajjad","9101112"},
						{"Maryam","121314"},
						{"Sadra","151617"},
						{"Amin","181920"} };
	Professor Plist[] = { {"Lotfi","1234"},
						{"hosseiny","5678"} };
	User* Person[6] = { &Slist[0],&Slist[1] ,&Slist[2] ,&Slist[3],&Plist[0],&Plist[1] };

	bool Back;
	while (true)
	{
		string Name, Pass;
		cout << "Enter Your UserName : ";
		getline(cin, Name);
		cout << "Enter Your PassWord : ";
		getline(cin, Pass);

		int Index = FindPerson(Person, Name, Pass);
		if (Index >= 0)
		{
			/*Finded Correctly*/
			system("cls");
			Back = false;
			if (Person[Index]->RetType() == 'P')
			{
				do
				{
					switch (ProfessorDashboardMenu())
					{
					case 1:
						Person[Index]->CreateExam();
						break;
					case 2:
						Person[Index]->ShowAllExam();
						break;
					case 3:

						break;
					case 4:
						int Chosen;
						cout << " [ 1 ] Create new List of student.\n"
							<< " [ 2 ] Show current lists.\n"
							<< "Enter an option : ";
						cin >> Chosen;
						cin.ignore(9223372036854775807, '\n');
						if (Chosen == 1)
							Person[Index]->CreateList(Person);
						else
							Person[Index]->PrintList();
						break;
					case 5:
						Back = true;
						system("cls");
						break;
					default:
						break;
					}
				} while (!Back);
			}
			else
			{
				/*Entrance Person Is a student.*/
			}
		}
		else
		{
			if (FindPerson(Person, Name, Pass) == -1)
				cout << "Wrong PassWord !\n";
			else
				cout << "User Not Found :|\n";
			Sleep(1500);
			system("cls");
		}
	}
	return 0;
}

int ProfessorDashboardMenu()
{
	int Chosen;
	cout << " [ 1 ] Create a new examination.\n"
		<< " [ 2 ] Show history of all examination.\n"
		<< " [ 3 ] Exams in the correction queue\n"
		<< " [ 4 ] List of students.\n"
		<< " [ 5 ] Back to LoginMenu.\n"
		<< " Please select an option : ";
	cin >> Chosen;
	cin.ignore(9223372036854775807, '\n');
	return Chosen;
}

int FindPerson(User* List[], string Name, string Pass)
{
	for (int i = 0; i < 6; i++)
	{
		if (List[i]->UserName == Name)
		{
			if (List[i]->PassWord == Pass)
			{
				return i;
			}
			return -1;
		}
	}
	return -2;
}
/* StudentList Functions. */
StudentList::StudentList(User* Person[])
{
	bool Existance;
	char YorN;
	while (true)
	{
		Existance = false;
		cout << " Enter StudentName to add in this list : \n";
		string InputName;
		getline(cin, InputName);
		for (int i = 0; i < 6; i++)
		{
			if ((InputName == Person[i]->UserName) && (Person[i]->RetType() == 'S'))
			{
				Student* Ptr = (Student*)Person[i];
				SList.push_back(Ptr);
				Existance = true;
				break;
			}
		}
		if (Existance)
			cout << " Student Added.\n";
		else
			cout << " Student not found.\n";

		cout << " Continue Adding [Y/n] ? ";
		cin >> YorN;
		cin.ignore(9223372036854775807, '\n');
		if (!(YorN == 'Y' || YorN == 'y'))
			break;
	}
}

void StudentList::PrintSList()
{
	for (int i = 0; i < SList.size(); i++)
	{
		cout << SList[i]->UserName << endl;
	}
}

/* Question Functions. */
void Question::SetTest()
{
	char YorN;
	cout << "Is it a test question [Y/n] ? ";
	cin >> YorN;
	cin.ignore(9223372036854775807, '\n');
	(YorN == 'y' || YorN == 'Y') ? IsTest = true : IsTest = false;
}

/* Examination Functions. */
Examination::Examination()
{
	cout << "How many questions does the exam have? ";
	cin >> NumnerOfQ;
	cout << "=====================================\n";
	cin.ignore(9223372036854775807, '\n');
	Question TempQ;
	TotalScore = TotalTime = 0;
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
		TotalScore += TempQ.QScore;
		cout << " Enter response time questions : ";
		cin >> TempQ.QTime;
		TotalTime += TempQ.QTime;
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
				cout << " #" << i + 1 << " : " << QList[Index].Option[i] << endl;
			}
		}
	}
}
int Examination::RetNumnerOfQ()
{
	return NumnerOfQ;
}
int Examination::Score()
{
	return TotalScore;
}
double Examination::Time()
{
	return TotalTime;
}

/* User Functions. */
User::User(string Name, string Pass)
{
	UserName = Name;
	PassWord = Pass;
}
void User::CreateExam()
{
}
void User::CreateList(User* Person[])
{
}
void User::ShowAllExam()
{
}
void User::PrintList()
{
}

/* Professor Functions. */
void Professor::CreateExam()
{
	Examination TempExam;
	ExamList.push_back(TempExam);
}
void Professor::ShowAllExam()
{
	if (ExamList.size() != 0)
		for (int i = 0; i < ExamList.size(); i++)
		{
			cout << "\nExam " << i + 1 << " : ("
				<< " Number of Questions: " << ExamList[i].RetNumnerOfQ()
				<< ",  " << " Total score: " << ExamList[i].Score()
				<< ",  " << " Total time: " << ExamList[i].Time() << " )\n";
			ExamList[i].Print();
		}
	else
		cout << "No Items Found.\n";
	cout << endl;
}
void Professor::CreateList(User* Person[])
{
	StudentList Temp(Person);
	if (Temp.SList.capacity() != 0)
		List.push_back(Temp);
}
void Professor::PrintList()
{
	if (List.size() != 0)
	{
		cout << "Number of Lists : " << List.size() << endl
			<< "====================================\n";
		for (int i = 0; i < List.size(); i++)
		{
			if (List[i].SList.capacity() != 0)
			{
				cout << " #" << i + 1 << " List :\n";
				List[i].PrintSList();
				cout << "-----------------------------------------\n";
			}
		}
	}
	else
		cout << "\nNo List founded !\n";
}
Professor::Professor(string Name, string Pass) :User(Name, Pass) {}

char Professor::RetType()
{
	return 'P';
}

/* Student Functions. */
Student::Student(string Name, string Pass) :User(Name, Pass) {}

char Student::RetType()
{
	return 'S';
}