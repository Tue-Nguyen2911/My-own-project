#include <iostream>
#include <cstring>
#include "Tasks.h"
using namespace std;
namespace TueNg
{
	Tasks::Tasks()
	{
		m_theTask = nullptr;
		//m_completed = 0;
	}
	Tasks::Tasks(const char* theTask /*, int completed*/)
	{
		if (theTask != nullptr && strlen(m_theTask) > 0)
			setTask(theTask);
		else
			m_theTask = nullptr;
	}
	Tasks::~Tasks()
	{
		delete[] m_theTask;
		m_theTask = nullptr;
	}
	bool Tasks::operator==(const char* theTask) const
	{
		bool equal=true;
		if (strlen(m_theTask) != strlen(theTask))
			equal = false;
		else
		{
			for (int unsigned i = 0; i < strlen(theTask); i++)
			{
				if (m_theTask[i] != theTask[i])
					equal = false;
			}
		}
		return equal;
	}
	bool Tasks::operator==(const Tasks& task) const
	{
		return *this == task.m_theTask;
	}
	bool Tasks::isEmpty() const
	{
		return m_theTask == nullptr;
	}
	void Tasks::setTask(const char* theTask)
	{
		if (theTask != nullptr && strlen(theTask) > 0)
		{
			delete[] m_theTask;
			m_theTask = new char[strlen(theTask) + 1];
			strcpy(m_theTask, theTask);
		}
		else
			m_theTask = nullptr;
	}
	istream& Tasks::read(istream& is)
	{
		if (ReadWritable::isCsv())
		{
			char theTask[100]{ '\0' };
			is.getline(theTask, 100, ',');
			is.ignore(100, '\n');
			setTask(theTask);
		}
		else 
		{
			char theTask[100]{ '\0' };
			cout << "What do you want to accomplish: ";
			is.getline(theTask, 100);
			while (strlen(theTask) < 2 || strlen(theTask) > 100)
			{
				cout << "Invalid Task! Please Enter again: ";
				is.getline(theTask, 100);
			}
			setTask(theTask);
		}
		return is;
	}
	ostream& Tasks::write(ostream& os) const
	{
		if (isCsv())
		{
			os << m_theTask << "," << endl;
		}
		else
		{
			os << m_theTask << endl;
		}
		return os;
	}

	//Save for later
		/*Tasks::Tasks(const Tasks& aTask)
	{
		if (aTask.m_theTask != nullptr)
		{
			m_theTask = new char[strlen(aTask.m_theTask) + 1];
			strcpy(m_theTask, aTask.m_theTask);
		}
		else
			m_theTask = nullptr;
	}
	Tasks& Tasks::operator=(const Tasks& aTask)
	{
		if (this != &aTask)
		{
			if (aTask.m_theTask != nullptr)
			{
				m_theTask = new char[strlen(aTask.m_theTask) + 1];
				strcpy(m_theTask, aTask.m_theTask);
			}
			else
				m_theTask = nullptr;
		}
		return *this;
	}*/
}