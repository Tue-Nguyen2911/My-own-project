#ifndef TUENG_TASKS_H
#define TUENG_TASKS_H
#include<iostream>
#include "ReadWritable.h"
namespace TueNg
{
	class Tasks : public ReadWritable
	{
		char* m_theTask; 
	public: 
		Tasks();
		Tasks(const char* theTask);
		~Tasks();
		Tasks(const Tasks&) = delete;
		Tasks& operator=(const Tasks&) = delete;

		bool operator==(const Tasks& task) const;
		bool operator==(const char* theTask) const;
		std::istream& read(std::istream& is = std::cin);
		std::ostream& write(std::ostream& os = std::cout) const;
		bool isEmpty() const;
		void setTask(const char* theTask); 
		char getTask() const { return m_theTask != nullptr ? m_theTask[0] : '\0'; }
		const char* getTheTask() const { return m_theTask; }
	};
}

#endif // !TUENG_TASKS_H
