#include <iostream>
#include <list>

class QuackObservable;

class Observer
{
public:
	virtual void update(QuackObservable* duck) = 0;
};

class QuackObservable
{
public:
	virtual void registerObserver(Observer* observer) = 0;
	virtual void notifyObserver() = 0;
};

class Quackable : public QuackObservable
{
public:
	virtual void quack() = 0;
};

class Observable : public QuackObservable
{
	std::list<Observer*> observers_;
	QuackObservable* duck;
public:
	Observable(QuackObservable* duck) : duck{ duck } {}
	void registerObserver(Observer* observer) override
	{
		observers_.emplace_back(observer);
	}
	void notifyObserver() override
	{
		for (auto it = observers_.begin(); it != observers_.end(); ++it)
		{
			(*it)->update(duck);
		}
	}
};







class MallardDuck : public Quackable
{
	Observable* observable_;
public:
	MallardDuck() : observable_{ new Observable(this) } {}
	void quack() override
	{
		std::cout << "�в�" << std::endl;
		notifyObserver();
	}
	void notifyObserver() override
	{
		observable_->notifyObserver();
	}
	void registerObserver(Observer* observer) override
	{
		observable_->registerObserver(observer);
	}
};
class RedheadDuck : public Quackable
{
	Observable* observable_;
public:
	RedheadDuck() : observable_{new Observable(this)} {}
	void quack() override
	{
		std::cout << "�в�" << std::endl;
		notifyObserver();
	}
	void notifyObserver() override
	{
		observable_->notifyObserver();
	}
	void registerObserver(Observer* observer) override
	{
		observable_->registerObserver(observer);
	}
};

class CallDuck : public Quackable
{
	Observable* observable_;
public:
	CallDuck() : observable_{ new Observable(this) } {}
	void quack() override
	{
		std::cout << "�˲�" << std::endl;
		notifyObserver();
	}
	void notifyObserver() override
	{
		observable_->notifyObserver();
	}
	void registerObserver(Observer* observer) override
	{
		observable_->registerObserver(observer);
	}
};
class RubberDuck : public Quackable
{
	Observable* observable_;
public:
	RubberDuck() : observable_{ new Observable(this) } {}
	void quack() override
	{
		std::cout << "���" << std::endl;
		notifyObserver();
	}
	void notifyObserver() override
	{
		observable_->notifyObserver();
	}
	void registerObserver(Observer* observer) override
	{
		observable_->registerObserver(observer);
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
	Observable* observable_;
public:
	GooseAdapter(Goose* goose) : goose{ goose }, observable_{ new Observable(this)} {}

	void quack() override
	{
		goose->honk();
		notifyObserver();
	}
	void notifyObserver() override
	{
		observable_->notifyObserver();
	}
	void registerObserver(Observer* observer) override
	{
		observable_->registerObserver(observer);
	}
};
class QuackCounter : public Quackable
{
	Quackable* duck;
	static int m_quack_counter;//��ü ������ ��Ƚ���� �����ϱ� ������ ���� ������ ����
public:
	QuackCounter(Quackable* duck) : duck{ duck } {}
	void quack() override
	{
		duck->quack();
		m_quack_counter++;
	}

	static int GetCount()
	{
		return m_quack_counter;
	}
	void notifyObserver() override
	{
		duck->notifyObserver();
	}
	void registerObserver(Observer* observer) override
	{
		duck->registerObserver(observer);
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
	void notifyObserver() override {}
	void registerObserver(Observer* observer) override
	{
		for (auto it = quackers.begin(); it != quackers.end(); ++it)
		{
			(*it)->registerObserver(observer);
		}
	}
};


class Quackologist : public Observer
{
public:
	void update(QuackObservable* duck) override
	{
		std::cout << "�в����ڰ� " << typeid(*duck).name() << "�� �в��Ѵٰ� ���Ѵ�." << std::endl;
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
		mallardFlocks->add(duckFactory->createMallardDuck());//�׸����� ������ ������ �����.
	}

	duckFlocks->add(mallardFlocks);//�������� ��ü ������ ���� ��Ų��.

	Quackologist* quackologist = new Quackologist;
	duckFlocks->registerObserver(quackologist);


	std::cout << "�������� �ùķ��̼�" << std::endl;
	Simulate(mallardFlocks);//�������鸸 �ùķ��̼�
	std::cout << "��ü���� �ùķ��̼�" << std::endl;
	Simulate(duckFlocks);//��ü ���� �ùķ��̼�

	std::cout << QuackCounter::GetCount() << std::endl;
}



int main()
{
	AbstractDuckFactory* duck_factory = new CounterDuckFactory;
	Simulator(duck_factory);
	return 0;
}