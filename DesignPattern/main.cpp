#include <iostream>
#include <list>

class QuackObservalble;

class Observer
{
public:
	virtual void update(QuackObservalble* duck) = 0;
};
class QuackObservalble
{
public:
	virtual void registerObserver(Observer* observer) = 0;
	virtual void notifyObserver() = 0;
};

class Quackable : public QuackObservalble
{
public:
	virtual void quack() = 0;
};

class MallardDuck : public Quackable
{
public:
	void quack() override
	{
		std::cout << "꽥꽥" << std::endl;
	}
};
class RedheadDuck : public Quackable
{
public:
	void quack() override
	{
		std::cout << "꽥꽥" << std::endl;
	}
};

class CallDuck : public Quackable
{
public:
	void quack() override
	{
		std::cout << "꽉꽉" << std::endl;
	}
};
class RubberDuck : public Quackable
{
public:
	void quack() override
	{
		std::cout << "삑삑" << std::endl;
	}
};

class Goose
{
public:
	void honk()
	{
		std::cout << "끽끽" << std::endl;
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
	static int m_quack_counter;//전체 오리의 꽥횟수를 세야하기 때문에 정적 변수로 선언
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
//{//데코레이터 없는 팩토리 패턴
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
{//데코레이션 카운터가 있는 팩토리 패턴
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
class Flock : public Quackable
{
	std::list<Quackable*> quackers;
public:
	void add(Quackable* duck)
	{
		quackers.emplace_back(duck);
	}
	void quack() override
	{
		for (auto it = quackers.begin(); it != quackers.end(); ++it)
		{
			(*it)->quack();
		}
	}
};




void Simulate(Quackable* duck)
{
	duck->quack();
}

void Simulator(AbstractDuckFactory* duckFactory)
{
	Quackable* redhead = duckFactory->createRedheadDuck();
	Quackable* call = duckFactory->createCallDuck();
	Quackable* rubber = duckFactory->createRubberDuck();
	Quackable* gooseDuck = new GooseAdapter(new Goose);

	Flock* duckFlocks = new Flock;
	duckFlocks->add(redhead);
	duckFlocks->add(call);
	duckFlocks->add(rubber);
	duckFlocks->add(gooseDuck);

	Flock* mallardFlocks = new Flock;

	for (int i = 0; i < 4; i++)
	{
		mallardFlocks->add(duckFactory->createMallardDuck());//네마리의 물오리 무리를 만든다.
	}

	duckFlocks->add(mallardFlocks);//물오리르 전체 무리에 포함 시킨다.

	std::cout << "물오리만 시뮬레이션" << std::endl;
	Simulate(mallardFlocks);//물오리들만 시뮬레이션
	std::cout << "전체오리 시뮬레이션" << std::endl;
	Simulate(duckFlocks);//전체 오리 시뮬레이션

	std::cout << QuackCounter::GetCount() << std::endl;
}



int main()
{
	AbstractDuckFactory* duck_factory = new CounterDuckFactory;
	Simulator(duck_factory);
	return 0;
}