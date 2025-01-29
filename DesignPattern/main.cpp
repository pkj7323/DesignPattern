#include <iostream>
#include <vector>
#include <stdio.h>



class MenuItem
{
	std::string name;
	std::string description;
	bool vegetarian;
	double price;
public:
	MenuItem() : vegetarian{ false }, price{ 0 } {}
	MenuItem(const std::string& name, const std::string& description, bool vegetarian, double price)
	{
		this->name = name;
		this->description = description;
		this->vegetarian = vegetarian;
		this->price = price;
	}
	std::string getName() const
	{
		return name;
	}
	std::string getDescription() const
	{
		return description;
	}
	double getPrice() const
	{
		return price;
	}
	bool isVegetarian() const
	{
		return vegetarian;
	}
};
class Iterator
{
public:
	virtual bool hasNext() = 0;
	virtual MenuItem next() = 0;
};

class PancakeHouseMenuIterator : public Iterator
{
	std::vector<MenuItem> menuItems;
	size_t position = 0;
public:
	PancakeHouseMenuIterator(std::vector<MenuItem> menuItems)
	{
		this->menuItems = menuItems;
	}
	MenuItem next() override
	{
		MenuItem menuItem = menuItems[position];
		position++;
		return menuItem;
	}
	bool hasNext() override
	{
		if (position >= menuItems.size() || menuItems[position].getName().empty())
		{
			return false;
		}
		else
		{
			return true;
		}
	}
};

class PancakeHouseMenu
{
	std::vector<MenuItem> menuItems;
public:
	PancakeHouseMenu()
	{
		addItem("K&B's Pancake Breakfast", "Pancakes with scrambled eggs, and toast", true, 2.99);
		addItem("Regular Pancake Breakfast", "Pancakes with fried eggs, sausage", false, 2.99);
		addItem("Blueberry Pancakes", "Pancakes made with fresh blueberries", true, 3.49);
		addItem("Waffles", "Waffles, with your choice of blueberries or strawberries", true, 3.59);
	}
	void addItem(const std::string& name, const std::string& description, bool vegetarian, double price)
	{
		MenuItem menuItem(name, description, vegetarian, price);
		menuItems.push_back(menuItem);
	}
	Iterator* createIterator() const
	{
		return new PancakeHouseMenuIterator(menuItems);
	}
};
#define MAX_ITEMS 6
class DinerMenuIterator : public Iterator
{
	MenuItem* menuItems;
	int position = 0;
public:
	DinerMenuIterator(MenuItem* menuItems)
	{
		this->menuItems = menuItems;
	}
	MenuItem next() override
	{
		MenuItem menuItem = menuItems[position];
		position++;
		return menuItem;
	}
	bool hasNext() override
	{
		if (position >= MAX_ITEMS || menuItems[position].getName().empty())
		{
			return false;
		}
		else
		{
			return true;
		}
	}
};
class DinerMenu
{
	int numberOfItems = 0;
	MenuItem* menuItems;
public:
	DinerMenu()
	{
		menuItems = new MenuItem[MAX_ITEMS];
		addItem("Vegetarian BLT", "(Fakin') Bacon with lettuce & tomato on whole wheat", true, 2.99);
		addItem("BLT", "Bacon with lettuce & tomato on whole wheat", false, 2.99);
		addItem("Soup of the day", "Soup of the day, with a side of potato salad", false, 3.29);
		addItem("Hotdog", "A hot dog, with saurkraut, relish, onions, topped with cheese", false, 3.05);
	}
	void addItem(const std::string& name, const std::string& description, bool vegetarian, double price)
	{
		MenuItem menuItem(name, description, vegetarian, price);
		if (numberOfItems >= MAX_ITEMS)
		{
			std::cout << "Sorry, menu is full! Can't add item to menu" << std::endl;
		}
		else
		{
			menuItems[numberOfItems] = menuItem;
			numberOfItems++;
		}
	}
	Iterator* createIterator() const
	{
		return new DinerMenuIterator(menuItems);
	}
};




class Waitress
{
	PancakeHouseMenu* pancakeHouseMenu;
	DinerMenu* dinerMenu;
public:
	Waitress(PancakeHouseMenu* pancakeHouseMenu, DinerMenu* dinerMenu)
	{
		this->pancakeHouseMenu = pancakeHouseMenu;
		this->dinerMenu = dinerMenu;
	}
	void printMenu()
	{
		Iterator* pancakeIterator = pancakeHouseMenu->createIterator();
		Iterator* dinerIterator = dinerMenu->createIterator();
		std::cout << "MENU\n----\nBREAKFAST" << std::endl;
		printMenu(pancakeIterator);
		std::cout << "\nLUNCH" << std::endl;
		printMenu(dinerIterator);
	}
	void printMenu(Iterator* iterator)
	{
		while (iterator->hasNext())
		{
			MenuItem menuItem = iterator->next();
			std::cout << menuItem.getName() << ", ";
			std::cout << menuItem.getPrice() << " -- ";
			std::cout << menuItem.getDescription() << std::endl;
		}
	}


};

int main()
{
	PancakeHouseMenu* pancakeHouseMenu = new PancakeHouseMenu();
	DinerMenu* dinerMenu = new DinerMenu();
	Waitress* waitress = new Waitress(pancakeHouseMenu, dinerMenu);
	waitress->printMenu();
	return 0;
}