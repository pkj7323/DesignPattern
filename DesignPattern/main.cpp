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

class CallDuck : public Quackable
{
public:
	void quack() override
	{
		std::cout << "²Ë²Ë" << std::endl;
	}
};
class RubberDuck : public Quackable
{
public:
	void quack() override
	{
		std::cout << "»à»à" << std::endl;
	}
};

class Goose
{
public:
	void honk()
	{
		std::cout << "³£³£" << std::endl;
	}
};
class GooseAdapter : public Quackable
{
	Goose* goose;
public:
	GooseAdapter(Goose* goose) : goose{goose} {}

	void quack() override
	{
		goose->honk();
	}
};
class QuackCounter : public Quackable
{
	Quackable* duck;
	static int m_quack_counter;//ÀüÃ¼ ¿À¸®ÀÇ ²ÐÈ½¼ö¸¦ ¼¼¾ßÇÏ±â ¶§¹®¿¡ Á¤Àû º¯¼ö·Î ¼±¾ð
public:
	QuackCounter(Quackable* duck) : duck{ duck } {  }
	void quack() override
	{
		duck->quack();
		m_quack_counter++;
	}

	static int GetCount()
	{
		return m_quack_counter;
	}
};
int QuackCounter::m_quack_counter = 0;

class AbstractDuckFactory
{
public:
	virtual Quackable* createMallardDuck() = 0;
	virtual Quackable* createRedheadDuck() = 0;
	virtual Quackable* createCallDuck() = 0;
	virtual Quackable* createRubberDuck() = 0;
};
class DuckFactory : public AbstractDuckFactory
{
public:
	Quackable* createMallardDuck() override
	{
		return new MallardDuck;
	}
	Quackable* createCallDuck() override
	{
		return new CallDuck;
	}
	Quackable* createRedheadDuck() override
	{
		return new RedheadDuck;
	}
	Quackable* createRubberDuck() override
	{
		return new RubberDuck;
	}
};
class CounterDuckFactory : public AbstractDuckFactory
{
public:
	Quackable* createMallardDuck() override
	{
		return new QuackCounter(new MallardDuck);
	}
	Quackable* createCallDuck() override
	{
		return new QuackCounter(new CallDuck);
	}
	Quackable* createRedheadDuck() override
	{
		return new QuackCounter(new RedheadDuck);
	}
	Quackable* createRubberDuck() override
	{
		return new QuackCounter(new RubberDuck);
	}
};




void Simulate(Quackable* duck)
{
	duck->quack();
}

int main()
{
	Quackable* mallard = new QuackCounter(new MallardDuck());
	Quackable* redhead = new QuackCounter(new RedheadDuck());
	Quackable* call = new QuackCounter(new CallDuck());
	Quackable* rubber = new QuackCounter(new RubberDuck());
	Quackable* goose = new GooseAdapter(new Goose);

	
	Simulate(mallard);
	Simulate(redhead);
	Simulate(call);
	Simulate(rubber);
	Simulate(goose);

	std::cout << QuackCounter::GetCount() << std::endl;
	return 0;
}