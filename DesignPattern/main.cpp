#include <iostream>

class Duck {
public:
	virtual void quack() = 0;
	virtual void fly() = 0;
};

class MallardDuck : public Duck {
public:
	void quack() {
		std::cout << "Quack" << std::endl;
	}
	void fly() {
		std::cout << "I'm flying" << std::endl;
	}
};

class Turkey
{
public:
	virtual void gobble() = 0;
	virtual void fly() = 0;
};
class WildTurkey : public Turkey
{
public:
	void gobble() {
		std::cout << "Gobble gobble" << std::endl;
	}
	void fly() {
		std::cout << "I'm flying a short distance" << std::endl;
	}
};

class TurkeyAdapter : public Duck, public Turkey
{
public:
	void quack() override
	{
		gobble();
	}
	void fly() override
	{
		for (int i = 0; i < 5; i++)
		{
			std::cout << "I'm flying a short distance" << std::endl;
		}
	}
	void gobble() override
	{
		std::cout << "Gobble gobble" << std::endl;
	}

};
void testduck(Duck* duck)
{
	duck->quack();
	duck->fly();
}
void main()
{
	MallardDuck* duck = new MallardDuck();
	WildTurkey* turkey = new WildTurkey();
	Duck* turkeyAdapter = new TurkeyAdapter();
	std::cout << "The Turkey says..." << std::endl;
	turkey->gobble();
	turkey->fly();
	std::cout << "The Duck says..." << std::endl;
	testduck(duck);
	std::cout << "The TurkeyAdapter says..." << std::endl;
	testduck(turkeyAdapter);
}