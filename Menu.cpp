#include <iostream>
#include <cstring>
#include <Windows.h>
#include "Utils.h"
#include "Menu.h"

namespace TueNg
{
	//MenuItem class inplementations
	MenuItem::MenuItem() {
		m_content = nullptr;
	}
	MenuItem::MenuItem(const char* content)
	{
		if (content != nullptr && strlen(content) > 0)
		{
			m_content = new char[strlen(content) + 1];
			strcpy(this->m_content, content);
		}
		else
			m_content = nullptr;
	}
	MenuItem::~MenuItem()
	{
		delete[] m_content;
		m_content = nullptr;
	}
	void MenuItem::display(std::ostream& os) const
	{
		if (m_content != nullptr)
			os << m_content << std::endl;
	}

	//functions inplementation of Menu class
	void Menu::indent() const
	{
		for (auto i = 0; i < m_ind; i++)
			std::cout << "    ";
	}

	Menu::Menu()
	{
		this->m_ind = 0;
		this->m_numItems = 0;
		this->m_title = nullptr;
		for (auto i = 0; i < MAX_NO_OF_ITEMS; i++)
		{
			m_menuItems[i] = nullptr;
		}
	}

	Menu::Menu(const char* title, int identation)
	{
		m_ind = identation;
		m_numItems = 0;
		m_title = nullptr;
		*this = title;
		for (auto i = 0; i < MAX_NO_OF_ITEMS; i++)
		{
			m_menuItems[i] = nullptr;
		}

	}

	Menu::Menu(const Menu& menu)
	{
		m_title = nullptr;
		*this = menu.m_title;
	}
	Menu& Menu::operator=(const Menu& menu)
	{
		if (this != &menu)
		{
			for (auto i = 0; i < m_numItems; i++)
			{
				delete m_menuItems[i];
				m_menuItems[i] = nullptr;
			}
			*this = menu.m_title;
			m_numItems = 0;
			m_ind = menu.m_ind;
			for (auto i = 0; i < menu.m_numItems; i++)
			{
				if (menu.m_menuItems[i] != nullptr)
				{
					m_menuItems[i] = new MenuItem(menu.m_menuItems[i]->m_content);
					m_numItems++;
				}
			}
		}
		return *this;
	}
	Menu& Menu::operator=(const char* title)
	{
		delete[] m_title;
		m_title = nullptr;
		if (title != nullptr && strlen(title) > 0)
		{
			m_title = new char[strlen(title) + 1];
			strcpy(m_title, title);
		}
		else
		{
			Menu::m_title = nullptr;
		}
		return *this;
	}
	Menu::~Menu()
	{
		delete[] m_title;
		m_title = nullptr;
		for (auto i = 0; i < m_numItems; i++)
		{
			delete m_menuItems[i];
			m_menuItems[i] = nullptr;
		}
	}

	Menu::operator bool() const
	{
		return Menu::m_title != nullptr;
	}
	bool Menu::isEmpty() const
	{
		return !*this;
	}
	void Menu::display(std::ostream& os) const
	{
		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
		if (this->isEmpty())
		{
			os << "Invalid Menu!" << std::endl;
		}
		else if (m_numItems == 0)
		{
			os << m_title << std::endl;
			os << "No Items to display!" << std::endl;
		}
		else
		{
			SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
			os << m_title << std::endl;
			SetConsoleTextAttribute(h,15);
			for (auto i = 0; i < m_numItems; i++)
			{
				os << "|";
				os << i + 1 << "- ";
				os << this->m_menuItems[i]->m_content << std::endl;
			}
			os << "|";
			os << "> ";
		}
	}
	void Menu::add(const char* ItemContent)
	{
		if (ItemContent == nullptr || strlen(ItemContent) == 0)
		{
			delete[] m_title;
			m_title = nullptr;
		}
		else if (this->m_numItems < MAX_NO_OF_ITEMS)
		{
			for (int i = 0; i < MAX_NO_OF_ITEMS; i++)
			{
				if (Menu::m_menuItems[i] == nullptr)
				{
					m_menuItems[i] = new MenuItem(ItemContent);
					m_numItems++;
					break;
				}
			}
		}
	}
	int Menu::run(std::istream& in) const
	{
		display();
		int option;
		bool flag = true;
		if (m_numItems == 0 || isEmpty())
		{
			option = 0;
		}
		else
		{
			while (flag)
			{
				in >> option;
				bool correct = in.fail();
				in.clear();
				in.ignore(1000, '\n');
				if (correct == true)
				{
					std::cout << "Invalid Integer, try again: ";
				}
				else if (option > m_numItems || option <= 0)
				{
					std::cout << "Invalid selection, try again: ";
				}
				else
					flag = false;
			}
		}
		return option;
	}
	Menu::operator int() const
	{
		return run();
	}

	//Save for later
	/*Menu& Menu::operator<<(const char* items)
	{
		add(items);
		return *this;
	}*/
}