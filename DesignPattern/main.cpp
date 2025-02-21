#include <iostream>

class Quackable
{
public:
	virtual void quack() = 0;
};

class MallardDuck : public Quackable
{
public:
	void quack() override
	{
		std::cout << "²Ð²Ð" << std::endl;
	}
};
class RedheadDuck : public Quackable
{
public:
	void quack() override
	{
		std::cout << "²Ð²Ð" << std::endl;
	}
};