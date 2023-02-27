#pragma once
#include <iostream>
#include "mylib.h"
#include <functional>
template <typename T, typename N>
class Menu
{
private:
	typedef void(N::* Fun)(T&);
	struct Item
	{
		std::string itemName;
		Fun fun;
	} ;
	int menuItemCount;
	std::string menu;
	std::vector<Fun> functs;
	T& instance ;
	N& invoker;
public:
	Menu(const std::string& name, const std::string& exitName, std::initializer_list<Item> itemList, T& instance,N& invoker) :instance(instance), invoker(invoker)
	{
		int ind = 1;
		std::stringstream ss;
		if (itemList.size() == 0) throw std::exception("Меню повинно мати пункти");
		if (isBlank(name)) throw std::exception("Пуста назва меню");
		if (isBlank(exitName)) throw std::exception("Пуста назва виходу");

		ss << "         " << name << std::endl;
		for (const auto& val : itemList)
		{
			if (!isBlank(val.itemName)) functs.push_back(val.fun);
			else  throw std::exception("Пустий елемент меню");
			ss << "         [" << ind << "] " << val.itemName << std::endl;
			++ind;
		}
		ss << "         [" << ind << "] " << exitName << std::endl;
		menu = ss.str();
		menuItemCount = (int)itemList.size();
	}
	
	void getMenuItem()
	{
		int select;
		do {
			system("cls");
			std::cout << menu;
			select = getValue(1, menuItemCount + 1);
			if (select < menuItemCount + 1) (invoker.*functs[select - 1])(instance);
		} while (select != menuItemCount + 1);

	}
};

