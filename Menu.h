#ifndef TUENG_MENU_H
#define TUENG_MENU_H
#include<iostream>

namespace TueNg
{
	const int MAX_NO_OF_ITEMS = 10;
	class MenuItem
	{
		char* m_content;
		MenuItem();
		MenuItem(const char* content);
		MenuItem(const MenuItem&) = delete;
		MenuItem& operator=(const MenuItem&) = delete;
		~MenuItem();
		void display(std::ostream& os = std::cout) const;
		friend class Menu;
	};

	//class Menu which owns MenuItem 
	class Menu
	{
		int m_numItems;
		char* m_title;
		MenuItem* m_menuItems[MAX_NO_OF_ITEMS];
		int m_ind;
		void indent() const;

	public:
		Menu();
		Menu(const char* title, int identation = 0);
		Menu(const Menu&);
		~Menu();
		Menu& operator=(const char*);
		Menu& operator=(const Menu&);

		operator bool() const;
		bool isEmpty() const;
		void display(std::ostream& os = std::cout) const;
		void add(const char* ItemContent);
		int run(std::istream& in = std::cin) const;
		operator int() const;
		//		Menu& operator<<(const char* items);
	};

}

#endif // !TUENG_MENU_H
