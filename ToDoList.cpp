#include <iostream>
#include <cstring>
#include <fstream>
#include <Windows.h>
#include "ToDoList.h"
#include "Utils.h"
#include "Tasks.h"
using namespace std;
namespace TueNg
{
	//constructors and destructors
	ToDoList::ToDoList()
	{
		m_filename = nullptr;
		for (int i = 0; i < MAX_OF_LIST; i++)
			m_list_of_tasks[i] = nullptr;
		m_mainMenu = nullptr;
		m_num_of_tasks = 0;
	}

	ToDoList::ToDoList(const char* filename)
	{
		m_num_of_tasks = 0;
		for (int i = 0; i < MAX_OF_LIST; i++)
			m_list_of_tasks[i] = nullptr;
		if (filename != nullptr && strlen(filename) > 0)
		{
			m_filename = new char[strlen(filename) + 1];
			strcpy(m_filename, filename);
		}
		else
			m_filename = nullptr;
		if (LoadData())
		{
			m_mainMenu = new Menu("====== To Do List App ======");
			m_mainMenu->add("List the tasks");
			m_mainMenu->add("Add a task");
			m_mainMenu->add("Delete a task(completed)");
			m_mainMenu->add("Delete all task(completed all)");
			m_mainMenu->add("Exit");
		}
		else
			m_mainMenu = nullptr;
	}
	ToDoList::~ToDoList()
	{
		SaveData();
		delete[] m_filename;
		m_filename = nullptr;
		delete m_mainMenu;
		m_mainMenu = nullptr;
		for (int i = 0; i < m_num_of_tasks; i++)
		{
			delete m_list_of_tasks[i];
			m_list_of_tasks[i] = nullptr;
		}
	}
	bool ToDoList::isEmpty() const
	{
		return m_filename == nullptr;
	}
	void ToDoList::ListStatus() const
	{
		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(h, 9);
		cout << "****** What you gonna do today my friend? ******" << endl;
	}
	void ToDoList::Add()
	{
		seperator();
		Title_display("Adding task");
		if (m_num_of_tasks == 10)
		{
			cout << "Ayo, 10 tasks are enough to work on! Don't pressure yourself too much" << endl;
		}
		else
		{
			Tasks* aTask = new Tasks();
			aTask->setCsv(false);
			aTask->read();
			for (int i = 0; i < MAX_OF_LIST; i++)
			{
				if (aTask == m_list_of_tasks[i])
				{
					cout << "Can't add; there's an exact task in the list" << endl;
					break;
				}
				else if (m_list_of_tasks[i] == nullptr)
				{
					m_list_of_tasks[i] = new Tasks();
					m_list_of_tasks[i] = aTask;
					m_num_of_tasks++;
					cout << "Your task to do: ";
					m_list_of_tasks[i]->write();
					break;
				}
			}
		}
		seperator();
	}
	void ToDoList::Complete()
	{
		List_Tasks();
		Title_display("Deleting a task");
		int index = 0;
		if (m_num_of_tasks == 0)
		{
			cout << "No task(s) to delete" << endl;
		}
		else
		{
			cout << "Which task do you want to delete(number according to the list): ";
			cin >> index;
			while (index > m_num_of_tasks || cin.fail() || index == 0)
			{
				cin.clear();
				cin.ignore(10, '\n');
				cout << "Invalid number, try again: ";
				cin >> index;
			}
			for (int i = 0; i < m_num_of_tasks; i++)
			{
				if (m_list_of_tasks[index - 1] != nullptr)
				{
					cout << "Deleting the completed task: " << m_list_of_tasks[index - 1]->getTheTask() << endl;
					delete m_list_of_tasks[index - 1];
					m_list_of_tasks[index - 1] = nullptr;
					m_num_of_tasks--;
					for (int j = index - 1; j < m_num_of_tasks; j++)
					{
						Tasks* temp = new Tasks();
						temp->setTask(m_list_of_tasks[j + 1]->getTheTask());
						m_list_of_tasks[j] = temp;
					}
					delete m_list_of_tasks[m_num_of_tasks];
					m_list_of_tasks[m_num_of_tasks] = nullptr;
					break;
				}
				else if (i == m_num_of_tasks - 1)
					cout << "Task not found!" << endl;
			}
		}
		seperator();
	}
	void ToDoList::List_Tasks() const
	{
		if (m_num_of_tasks == 0)
		{
			seperator();
			cout << "You have no tasks!" << endl << endl;
		}
		else
		{
			seperator();
			Title_display("List of tasks");
			for (int i = 0; i < m_num_of_tasks; i++)
			{
				if (m_list_of_tasks[i] != nullptr)
				{
					cout << i+1  << ". ";
					m_list_of_tasks[i]->setCsv(false);
					m_list_of_tasks[i]->write();
					m_list_of_tasks[i]->setCsv(true);
				}
			}
		}
		seperator();
	}
	void ToDoList::Complete_All() 
	{
		seperator();
		Title_display("Deleting all tasks");
		if (ToDoList::isEmpty())
		{
			cout << "Deleting all the tasks" << endl; 
		}
		else
		{
			cout << "Have you done all your goals for today? " << endl;
			cout << "(Y)es/(N)o: ";
			if (!YesNo())
			{
				cout << "Aborted!" << endl;
			}
			else
			{
				cout << "Deleting all the tasks" << endl;
				for (int i = 0; i < MAX_OF_LIST; i++)
				{
					if (m_list_of_tasks[i] != nullptr)
					{
						m_list_of_tasks[i]->setCsv(false);
						cout << endl << "Tasks deleted" << endl << "``````````````" << endl;
						m_list_of_tasks[i]->write();
						delete m_list_of_tasks[i];
						m_list_of_tasks[i] = nullptr;
						m_num_of_tasks--;
					}
				}
			}
		}
		seperator();
	}
	bool ToDoList::Exit() const 
	{
		cout << "This will terminate the program!" << endl;
		cout << "Are you sure? (Y)es/(N)o: ";
		if (YesNo())
		{
			cout << "Exiting program!" << endl;
			return true;
		}
		else
		{
			cout << "Aborted!" << endl;
			return false;
		}

	}
	bool ToDoList::LoadData()
	{
		if (!ToDoList::isEmpty())
		{
			ifstream ifs(m_filename);
			Tasks* aTask = nullptr;
			while (ifs)
			{
				aTask = new Tasks();
				aTask->setCsv(true);
				aTask->read(ifs);
				if ((aTask->getTask() < 'a' || aTask->getTask() > 'z') && (aTask->getTask() < 'A' || aTask->getTask() > 'Z'))
				{
					delete aTask;
					aTask = nullptr;
					return true;
				}
				if (!ifs.fail())
				{
					for (int i = 0; i < MAX_OF_LIST; i++)
					{
						if (m_list_of_tasks[i] == nullptr)
						{
							m_list_of_tasks[i] = aTask;
							m_num_of_tasks++;
							break;
						}
					}
				}
				else
					return false;
				if (m_num_of_tasks == MAX_OF_LIST) break;
			}
		}
		return true;
	}
	void ToDoList::SaveData() const
	{
		if (!isEmpty())
		{
			ofstream ofs(m_filename);
			if (ofs)
			{
				for (int i = 0; i < m_num_of_tasks; i++)
				{
					if (m_list_of_tasks[i] != nullptr)
					{
						m_list_of_tasks[i]->setCsv(true);
						m_list_of_tasks[i]->write(ofs);
					}
				}
			}
		}
	}
	int ToDoList::run()
	{
		int empty;
		if (!isEmpty())
		{
			empty = 0;

			bool out = false;
			while (!out)
			{
				ListStatus();
				int option = m_mainMenu->run();
				switch (option)
				{
				case 1:
					List_Tasks();
					out = false;
					break;
				case 2:
					Add();
					out = false;
					break;
				case 3:
					Complete();
					out = false;
					break;
				case 4:
					Complete_All();
					out = false;
					break;
				case 5:
					if (Exit())
					{
						out = true;
						break;
					}
					else
						out = false;
					break;
				default:
					break;
				}
				system("pause");
				system("CLS");
			}
		}
		else
			empty = 1;
		return empty;
	}

	void ToDoList::seperator() const
	{
		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
		SetConsoleTextAttribute(h, 2);
		cout << endl;
		cout << "-------------------------------------------" << endl << endl;
		SetConsoleTextAttribute(h, 15);
	}
	void ToDoList::Title_display(const char* title) const
	{
		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
		SetConsoleTextAttribute(h, 14);
		cout << title << endl;
		cout << "``````````````````" << endl;
		SetConsoleTextAttribute(h, 15);
	}
	bool ToDoList::YesNo() const
	{
		{
			char option[10];
			bool response;
			bool correct = false;
			while (!correct)
			{
				cin >> option;
				cin.clear();
				cin.ignore(100, '\n');
				if (option[1] != '\0' || (option[0] != 'Y' && option[0] != 'y' && option[0] != 'N' && option[0] != 'n'))
				{
					cout << "Invalid response, only (Y)es or (N)o are acceptable, retry: ";
					correct = false;
				}
				else
					correct = true;
			}
			if (option[0] == 'Y' || option[0] == 'y')
			{
				response = true;
			}
			else
			{
				response = false;
			}
			return response;
		}
	}
}



