#include <iostream>
#include <fstream>
#include <string.h>
#include <sstream>
using namespace std;

int calculateBlockNumber(string id)
{
	/**
	 * return number of block student in 
	 * @param studentId
	 * @return number of block that contain student
	 */
	fstream staticIndex;
	char fromIndex[6], toIndex[6];
	int count = 1;
	staticIndex.open("staticIndex.txt", ios::in);
	while (!staticIndex.eof())
	{
		staticIndex.getline(fromIndex, 6, '-');
		staticIndex.getline(toIndex, 6, ':');
		if (stoi(fromIndex) <= stoi(id) && stoi(id) < stoi(toIndex))
		{
			return count;
		}
		count++;
	}

	staticIndex.close();
	return 0;
}

string getBlockName(string id)
{
	/**
	 * Returns the name of block that contain studentId
	 * @param student_id 
	 * @return name of block student_id exist in 
	*/
	int num = calculateBlockNumber(id);
	string blockName;
	blockName = "block" + to_string(num) + ".txt";
	return blockName;
}

class Student
{
public:
	char name[12];
	char id[5];
	char age[5];
	void insertCurrentStudent(string fileNameToInsertIn)
	{
		ofstream studentFile;
		studentFile.open(fileNameToInsertIn, ios::app);
		studentFile << this->name << "/" << this->id << "/" << this->age << ":";
		studentFile.close();
		return;
	}
};

bool searchForBlockName(string blockName)
{
	fstream opendFile;
	opendFile.open("blockes.txt", ios::in);
	char name[11];
	while (!opendFile.eof())
	{
		opendFile.getline(name, 10, ':');
		if (strcmp(blockName.c_str(), name) == 0)
		{
			opendFile.close();
			return true;
		}
	}
	opendFile.close();
	return false;
}

void addNewBlockName(string blockName)
{
	/**
	 * add block name in file called blocks when 
	 * it is not exist to know exist blocks for search , display 
	 */
	fstream blocks;
	blocks.open("blockes.txt", ios::in | ios::app);
	if (searchForBlockName(blockName))
	{
		blocks.close();
	}
	else
	{
		blocks << blockName << ":";
		blocks.close();
	}
	return;
}

void insertStudent()
{
	/**
	 * insert new Student  
	 */

	Student student;

	cout << "\nenter id :";
	cin >> student.id;
	cout << "\nenter Student name :";
	cin >> student.name;
	cout << "\nenter age :";
	cin >> student.age;

	string fileName = getBlockName(student.id);
	addNewBlockName(fileName);
	student.insertCurrentStudent(fileName);
}

// retrieve specific student
void search()
{
	/*
        it search in file by student and retrieve all student with that name
    */
	ifstream item;

	bool flag = false;
	char name[25];
	char id[13];
	char age[13];
	char search[25];

	item.open("item.txt", ios::in);

	cout << "enter name of item you want to search  : ";
	cin.getline(search, 25);
	cout << endl;

	while (!item.eof())
	{
		item.getline(name, 25, '/');
		item.getline(id, 13, '/');
		item.getline(age, 13, ':');
		if (strcmp(name, search) == 0)
		{
			flag = true;
			cout << "name \t id  \t age  \n";
			cout << name << "\t" << id << "\t" << age << "\n";
		}
	}

	if (flag == false)
	{
		cout << "item not found " << endl;
	}

	item.close();
}
// display info about user
void display()
{
	ifstream item;
	Student student;

	item.open("item.txt", ios::in);

	cout << "name \t id  \t age  \n";

	while (!item.eof())
	{
		item.getline(student.name, 25, '/');
		item.getline(student.id, 4, '/');
		item.getline(student.age, 13, ':');
		if (student.name[0] == '*')
			continue;
		cout << student.name << "\t " << student.id << "\t " << student.age << "\n";
	}

	item.close();
}

// delete student or all student with specific name
void Delete()
{
	fstream item;

	item.open("item.txt", ios::in | ios::out);

	bool flag = false;
	char name[25];
	char id[13];
	char age[13];
	char search[25];

	cout << "enter name of student you want to delete  : ";
	cin.getline(search, 25);
	cout << endl;

	while (!item.eof())
	{

		item.getline(name, 25, '/');
		item.getline(id, 13, '/');
		item.getline(age, 13, ':');

		if (strcmp(name, search) == 0)
		{
			flag = true;
			int len;

			len = strlen(name) + strlen(id) + strlen(age) + 3;
			int beg;
			int cursorplace = item.tellg();
			beg = cursorplace - len;
			item.seekp(beg, ios::beg);
			item << "*";
		}
	}
	if (flag == false)
	{
		cout << "student not found " << endl;
	}
	else
	{
		cout << "student deleted " << endl;
	}
	item.close();
}

void update()
{
	Delete();
	cout << "insert student again" << endl;
	insertStudent();
}

int main()
{

	cout << "Student File System "
			 << "\n";
	while (true)
	{
		int i;
		cout << "enter 1 to insert new Student \n";
		cout << "enter 2 to search  For Student\n";
		cout << "enter 3 to delete Student  \n";
		cout << "enter 4 to display Student \n";
		cout << "enter 5 to update Student \n";
		cout << "enter option  \n ";
		cin >> i;

		switch (i)
		{
		case 1:
			insertStudent();
			break;
		case 3:
			cin.ignore();
			Delete();
			break;
		case 2:
			cin.ignore();
			search();
			break;
		case 5:
			cin.ignore();
			update();
			break;
		case 4:
			display();
		}
	}
	return 0;
}
