#include <iostream>
#include <map>
#include <vector>
#include <stdio.h>
#include <unordered_map>


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

template <typename T>
class Iterator
{
public:
	virtual ~Iterator() = default;
	virtual bool hasNext() = 0;
	virtual T next() = 0;
};
template <typename T>
class PancakeHouseMenuIterator : public Iterator<T>
{
	typename std::vector<T>::const_iterator current;
	typename std::vector<T>::const_iterator end;
public:
	PancakeHouseMenuIterator(const std::vector<T>& v)
	{
		current = v.begin();
		end = v.end();
	}
	bool hasNext() override
	{
		return current != end;
	}
	T next() override
	{
		return *current++;
	}
};

class Menu
{
public:
	virtual ~Menu()
	= default;
	virtual Iterator<MenuItem>* createIterator() const = 0;
};
class PancakeHouseMenu : public Menu
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
	Iterator<MenuItem>* createIterator() const override
	{
		return new PancakeHouseMenuIterator<MenuItem>(menuItems);
	}
};
#define MAX_ITEMS 6
class DinerMenuIterator : public Iterator<MenuItem>
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
class DinerMenu : public Menu
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
	~DinerMenu() override
	{
		delete[] menuItems;
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
	Iterator<MenuItem>* createIterator() const override
	{
		return new DinerMenuIterator(menuItems);
	}
};
class CafeIterator : public Iterator<MenuItem>
{
	std::unordered_map<std::string, MenuItem> menuItems;
	std::unordered_map<std::string, MenuItem>::const_iterator current;
	std::unordered_map<std::string, MenuItem>::const_iterator end;
public:
	CafeIterator(const std::unordered_map<std::string, MenuItem>& menuItems)
	{
		this->menuItems = menuItems;
		current = this->menuItems.begin();
		end = this->menuItems.end();
	}
	bool hasNext() override
	{
		return current != end;
	}
	MenuItem next() override
	{
		return current++->second;
	}
};
class CafeMenu : public Menu
{
	std::unordered_map<std::string, MenuItem> menuItems;
public:
	CafeMenu()
	{
		addItem("Veggie Burger and Air Fries", "Veggie burger on a whole wheat bun, lettuce, tomato, and fries", true, 3.99);
		addItem("Soup of the day", "A cup of the soup of the day, with a side salad", false, 3.69);
		addItem("Burrito", "A large burrito, with whole pinto beans, salsa, guacamole", true, 4.29);
	}
	void addItem(const std::string& name, const std::string& description, bool vegetarian, double price)
	{
		MenuItem menuItem(name, description, vegetarian, price);
		menuItems.insert(std::make_pair(name, menuItem));
	}
	Iterator<MenuItem>* createIterator() const override
	{
		return new CafeIterator(menuItems);
	}
};


class Waitress
{
	Menu* pancakeHouseMenu;
	Menu* dinerMenu;
	Menu* cafeMenu;
public:
	Waitress(Menu* pancakeHouseMenu, Menu* dinerMenu, Menu* cafeMenu)
	{
		this->pancakeHouseMenu = pancakeHouseMenu;
		this->dinerMenu = dinerMenu;
		this->cafeMenu = cafeMenu;
	}
	void printMenu()
	{
		Iterator<MenuItem>* pancakeIterator = pancakeHouseMenu->createIterator();
		Iterator<MenuItem>* dinerIterator = dinerMenu->createIterator();
		Iterator<MenuItem>* cafeIterator = cafeMenu->createIterator();
		std::cout << "MENU\n----\nBREAKFAST" << std::endl;
		printMenu(pancakeIterator);
		std::cout << "\nLUNCH" << std::endl;
		printMenu(dinerIterator);
		std::cout << "\nDINNER" << std::endl;
		printMenu(cafeIterator);
		delete pancakeIterator;
		delete dinerIterator;
		delete cafeIterator;
	}
	void printMenu(Iterator<MenuItem>* iterator)
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
	CafeMenu* cafeMenu = new CafeMenu();
	Waitress* waitress = new Waitress(pancakeHouseMenu, dinerMenu, cafeMenu);
	waitress->printMenu();
	delete waitress;
	delete cafeMenu;
	delete dinerMenu;
	delete pancakeHouseMenu;
	return 0;
}