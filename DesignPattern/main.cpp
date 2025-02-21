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
		std::cout << "�в�" << std::endl;
	}
};
class RedheadDuck : public Quackable
{
public:
	void quack() override
	{
		std::cout << "�в�" << std::endl;
	}
};

class CallDuck : public Quackable
{
public:
	void quack() override
	{
		std::cout << "�˲�" << std::endl;
	}
};
class RubberDuck : public Quackable
{
public:
	void quack() override
	{
		std::cout << "���" << std::endl;
	}
};

class Goose
{
public:
	void honk()
	{
		std::cout << "����" << std::endl;
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
	static int m_quack_counter;//��ü ������ ��Ƚ���� �����ϱ� ������ ���� ������ ����
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
//class DuckFactory : public AbstractDuckFactory
//{//���ڷ����� ���� ���丮 ����
//public:
//	Quackable* createMallardDuck() override
//	{
//		return new MallardDuck;
//	}
//	Quackable* createCallDuck() override
//	{
//		return new CallDuck;
//	}
//	Quackable* createRedheadDuck() override
//	{
//		return new RedheadDuck;
//	}
//	Quackable* createRubberDuck() override
//	{
//		return new RubberDuck;
//	}
//};
class CounterDuckFactory : public AbstractDuckFactory
{//���ڷ��̼� ī���Ͱ� �ִ� ���丮 ����
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

void Simulator(AbstractDuckFactory* duckFactory)
{
	Quackable* mallard = duckFactory->createMallardDuck();
	Quackable* redhead = duckFactory->createRedheadDuck();
	Quackable* call = duckFactory->createCallDuck();
	Quackable* rubber = duckFactory->createRubberDuck();
	Quackable* goose = new GooseAdapter(new Goose);


	Simulate(mallard);
	Simulate(redhead);
	Simulate(call);
	Simulate(rubber);
	Simulate(goose);

	std::cout << QuackCounter::GetCount() << std::endl;
}



int main()
{
	AbstractDuckFactory* duck_factory = new CounterDuckFactory;
	Simulator(duck_factory);
	return 0;
}