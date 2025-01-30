#include <iostream>
#include <map>
#include <vector>
#include <unordered_map>

class MenuComponent
{
public:
	virtual ~MenuComponent() = default;
	virtual void add(MenuComponent* menuComponent)
	{
		throw std::runtime_error("Unsupported Operation");
	}
	virtual void remove(MenuComponent* menuComponent)
	{
		throw std::runtime_error("Unsupported Operation");
	}
	virtual MenuComponent* getChild(int i)
	{
		throw std::runtime_error("Unsupported Operation");
	}
	virtual std::string getName()
	{
		throw std::runtime_error("Unsupported Operation");
	}
	virtual std::string getDescription()
	{
		throw std::runtime_error("Unsupported Operation");
	}
	virtual double getPrice()
	{
		throw std::runtime_error("Unsupported Operation");
	}
	virtual bool isVegetarian()
	{
		throw std::runtime_error("Unsupported Operation");
	}
	virtual void print()
	{
		throw std::runtime_error("Unsupported Operation");
	}
};

class MenuItem : public MenuComponent
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
	void print() override
	{
		std::cout << " " << getName();
		if (isVegetarian())
		{
			std::cout << "(v)";
		}
		std::cout << ", " << getPrice() << std::endl;
		std::cout << "     -- " << getDescription() << std::endl;
	}
};


class Menu : public MenuComponent
{
	std::vector<MenuComponent*> menuComponents;
	std::string name;
	std::string description;
public:
	Menu(const std::string& name, const std::string& description)
	{
		this->name = name;
		this->description = description;
	}
	void add(MenuComponent* menuComponent) override
	{
		menuComponents.push_back(menuComponent);
	}
	void remove(MenuComponent* menuComponent) override
	{
		menuComponents.erase(std::remove(menuComponents.begin(), menuComponents.end(), menuComponent), menuComponents.end());
	}
	MenuComponent* getChild(int i) override
	{
		return menuComponents[i];
	}
	std::string getName() override
	{
		return name;
	}
	std::string getDescription() override
	{
		return description;
	}
	void print() override
	{
		std::cout << std::endl << getName();
		std::cout << ", " << getDescription() << std::endl;
		std::cout << "---------------------" << std::endl;
		for (auto& menuComponent : menuComponents)
		{
			menuComponent->print();
		}
	}
};





class Waitress
{
	MenuComponent* allMenus;
public:
	Waitress(MenuComponent* allMenus) : allMenus{ allMenus } {}
	void printMenu()
	{
		allMenus->print();
	}


};

int main()
{
	MenuComponent* pancakeHouseMenu = new Menu("PANCAKE HOUSE MENU", "Breakfast");
	MenuComponent* dinerMenu = new Menu("DINER MENU", "Lunch");
	MenuComponent* cafeMenu = new Menu("CAFE MENU", "Dinner");
	MenuComponent* dessertMenu = new Menu("DESSERT MENU", "Dessert of course!");
	MenuComponent* allMenus = new Menu("ALL MENUS", "All menus combined");
	MenuComponent* coffeeMenu = new Menu("COFFEE MENU", "Stuff to go with your afternoon coffee");

	allMenus->add(pancakeHouseMenu);
	allMenus->add(dinerMenu);
	allMenus->add(cafeMenu);

	pancakeHouseMenu->add(new MenuItem(
		"K&B's Pancake Breakfast",
		"Pancakes with scrambled eggs and toast",
		true,
		2.99));
	pancakeHouseMenu->add(new MenuItem(
		"Regular Pancake Breakfast",
		"Pancakes with fried eggs, sausage",
		false,
		2.99));
	pancakeHouseMenu->add(new MenuItem(
		"Blueberry Pancakes",
		"Pancakes made with fresh blueberries, and blueberry syrup",
		true,
		3.49));
	pancakeHouseMenu->add(new MenuItem(
		"Waffles",
		"Waffles with your choice of blueberries or strawberries",
		true,
		3.59));

	dinerMenu->add(new MenuItem(
		"Vegetarian BLT",
		"(Fakin') Bacon with lettuce & tomato on whole wheat",
		true,
		2.99));
	dinerMenu->add(new MenuItem(
		"BLT",
		"Bacon with lettuce & tomato on whole wheat",
		false,
		2.99));
	dinerMenu->add(new MenuItem(
		"Soup of the day",
		"A bowl of the soup of the day, with a side of potato salad",
		false,
		3.29));
	dinerMenu->add(new MenuItem(
		"Hot Dog",
		"A hot dog, with saurkraut, relish, onions, topped with cheese",
		false,
		3.05));
	dinerMenu->add(new MenuItem(
		"Steamed Veggies and Brown Rice",
		"Steamed vegetables over brown rice",
		true,
		3.99));

	dinerMenu->add(new MenuItem(
		"Pasta",
		"Spaghetti with marinara sauce, and a slice of sourdough bread",
		true,
		3.89));

	dinerMenu->add(dessertMenu);

	dessertMenu->add(new MenuItem(
		"Apple Pie",
		"Apple pie with a flakey crust, topped with vanilla icecream",
		true,
		1.59));

	dessertMenu->add(new MenuItem(
		"Cheesecake",
		"Creamy New York cheesecake, with a chocolate graham crust",
		true,
		1.99));
	dessertMenu->add(new MenuItem(
		"Sorbet",
		"A scoop of raspberry and a scoop of lime",
		true,
		1.89));

	cafeMenu->add(new MenuItem(
		"Veggie Burger and Air Fries",
		"Veggie burger on a whole wheat bun, lettuce, tomato, and fries",
		true,
		3.99));
	cafeMenu->add(new MenuItem(
		"Soup of the day",
		"A cup of the soup of the day, with a side salad",
		false,
		3.69));
	cafeMenu->add(new MenuItem(
		"Burrito",
		"A large burrito, with whole pinto beans, salsa, guacamole",
		true,
		4.29));

	cafeMenu->add(coffeeMenu);

	coffeeMenu->add(new MenuItem(
		"Coffee Cake",
		"Crumbly cake topped with cinnamon and walnuts",
		true,
		1.59));
	coffeeMenu->add(new MenuItem(
		"Bagel",
		"Flavors include sesame, poppyseed, cinnamon raisin, pumpkin",
		false,
		0.69));
	coffeeMenu->add(new MenuItem(
		"Biscotti",
		"Three almond or hazelnut biscotti cookies",
		true,
		0.89));

	Waitress* waitress = new Waitress(allMenus);

	waitress->printMenu();
	return 0;
}