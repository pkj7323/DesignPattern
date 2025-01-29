#include <iostream>
#include <vector>

class MenuItem
{
	std::string name;
	std::string description;
	bool vegetarian;
	double price;
public:
	MenuItem() : vegetarian{ false }, price{0} {}
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
	std::vector<MenuItem> getMenuItems() const
	{
		return menuItems;
	}
};

class DinerMenu
{
#define MAX_ITEMS 6
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
	MenuItem* getMenuItems() const
	{
		return menuItems;
	}
};

class Waitress
{
public:
	Waitress() {}
    void printMenu()
    {
		PancakeHouseMenu* pancakeHouseMenu = new PancakeHouseMenu();
		std::vector<MenuItem> breakfastItems = pancakeHouseMenu->getMenuItems();

		DinerMenu* dinerMenu = new DinerMenu();
		MenuItem* lunchMenu = dinerMenu->getMenuItems();

		for (const auto& menuItem : breakfastItems)
		{
			std::cout << menuItem.getName() << ", ";
			std::cout << menuItem.getPrice() << " -- ";
			std::cout << menuItem.getDescription() << std::endl;
		}
		std::cout << std::endl;
		for (int i = 0; i < MAX_ITEMS; i++)
		{
			if (!lunchMenu[i].getName().empty())
			{
				std::cout << lunchMenu[i].getName() << ", ";
				std::cout << lunchMenu[i].getPrice() << " -- ";
				std::cout << lunchMenu[i].getDescription() << std::endl;
			}
		}
    }
	
	
};

int main()
{
	Waitress* waitress = new Waitress();
	waitress->printMenu();
	return 0;
}