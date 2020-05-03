#ifndef TUENG_TODOLIST_H
#define TUENG_TODOLIST_H
#include <iostream>
#include "Menu.h"
#include "ReadWritable.h"
#include "Tasks.h"

namespace TueNg
{
	const int MAX_OF_LIST = 10;
	class ToDoList
	{
		char* m_filename;
		Tasks* m_list_of_tasks[MAX_OF_LIST];
		Menu* m_mainMenu;
		int m_num_of_tasks;
		bool isEmpty() const;
		void ListStatus() const;
		void Add();
		void Complete();
		void List_Tasks() const;
		void Complete_All();
		bool Exit() const;
		bool LoadData();
		void SaveData() const;
		void seperator() const;
		void Title_display(const char* title) const;
		bool YesNo() const;
	public:
		ToDoList();
		ToDoList(const char* filename);
		~ToDoList();
		int run();
	};
}

#endif // !TueNg_TODOLIST_H
