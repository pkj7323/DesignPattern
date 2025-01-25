#include <iostream>

class Tea
{
public:
	void prepareRecipe()
	{
		boilWater();
		steepTeaBag();
		pourInCup();
		addLemon();
	}
	void boilWater()
	{
		std::cout << "Boiling water" << std::endl;
	}
	void steepTeaBag()
	{
		std::cout << "Steeping the tea" << std::endl;
	}
	void pourInCup()
	{
		std::cout << "Pouring into cup" << std::endl;
	}
	void addLemon()
	{
		std::cout << "Adding Lemon" << std::endl;
	}
};





int main() {
	
	return 0;
}