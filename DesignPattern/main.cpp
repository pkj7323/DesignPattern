#include <iostream>
#include <random>

class State
{
public:
	virtual void insertQuarter() = 0;
	virtual void ejectQuarter() = 0;
	virtual void turnCrank() = 0;
	virtual void dispense() = 0;
};

class Machine
{
public:
	virtual void insertQuarter() = 0;
	virtual void ejectQuarter() = 0;
	virtual void turnCrank() = 0;
	virtual void dispense() = 0;
	virtual void setState(State* state) = 0;

	virtual void release() = 0;
	virtual int getCount() const = 0;
	virtual State* getSoldOutState() const = 0;
	virtual State* getNoQuarterState() const = 0;
	virtual State* getHasQuarterState() const = 0;
	virtual State* getSoldState() const = 0;
	virtual State* getWinnerState() const = 0;

};



class SoldOutState : public State
{
	Machine& gumballMachine;
public:
	SoldOutState(Machine& gumballMachine) : gumballMachine(gumballMachine) {}
	void insertQuarter() override
	{
		std::cout << "�����Ǿ����ϴ�\n";
	}
	void ejectQuarter() override
	{
		std::cout << "������ ���� �ʾҽ��ϴ�\n";
	}
	void turnCrank() override
	{
		std::cout << "�����Ǿ����ϴ�\n";
	}
	void dispense() override
	{
		std::cout << "�����Ǿ����ϴ�\n";
	}
};

class NoQuarterState : public State
{
	Machine& gumballMachine;
public:
	NoQuarterState(Machine& gumballMachine) : gumballMachine(gumballMachine) {}
	void insertQuarter() override
	{
		std::cout << "������ �־����ϴ�\n";
		gumballMachine.setState(gumballMachine.getHasQuarterState());
	}
	void ejectQuarter() override
	{
		std::cout << "������ ���� �ʾҽ��ϴ�\n";
	}
	void turnCrank() override
	{
		std::cout << "������ �־��ּ���\n";
	}
	void dispense() override
	{
		std::cout << "������ �־��ּ���\n";
	}
};

class HasQuarterState : public State
{
	Machine& gumballMachine;
	std::random_device rd;
	std::mt19937 gen{ rd() };
public:
	HasQuarterState(Machine& gumballMachine) : gumballMachine(gumballMachine) {}
	void insertQuarter() override
	{
		std::cout << "�̹� ������ �ֽ��ϴ�\n";
	}
	void ejectQuarter() override
	{
		std::cout << "������ ��ȯ�˴ϴ�\n";
		gumballMachine.setState(gumballMachine.getNoQuarterState());
	}
	void turnCrank() override
	{
		std::cout << "�����̸� ���Ƚ��ϴ�\n";
		std::uniform_int_distribution<int> dist(0, 9);
		int winner = dist(gen);
		if (winner == 0 && gumballMachine.getCount() > 1)
		{
			gumballMachine.setState(gumballMachine.getWinnerState());
		}
		else
		{
			gumballMachine.setState(gumballMachine.getSoldState());
		}
	}
	void dispense() override
	{
		std::cout << "�˸��̰� �����ϴ�\n";
	}
};

class SoldState : public State
{
	Machine& gumballMachine;
public:
	SoldState(Machine& gumballMachine) : gumballMachine(gumballMachine) {}
	void insertQuarter() override
	{
		std::cout << "��� ��ٷ��ּ���\n";
	}
	void ejectQuarter() override
	{
		std::cout << "�̹� �˸��̸� �̾ҽ��ϴ�\n";
	}
	void turnCrank() override
	{
		std::cout << "�����̸� �ѹ��� �����ּ���\n";
	}
	void dispense() override
	{
		gumballMachine.release();
		if (gumballMachine.getCount() > 0)
		{
			gumballMachine.setState(gumballMachine.getNoQuarterState());
		}
		else
		{
			std::cout << "�� �̻� �˸��̰� �����ϴ�\n";
			gumballMachine.setState(gumballMachine.getSoldOutState());
		}
	}
};

class WinnerState : public State
{
	Machine& gumballMachine;
public:
	WinnerState(Machine& gumballMachine) : gumballMachine(gumballMachine) {}
	void insertQuarter() override
	{
		std::cout << "��� ��ٷ��ּ���\n";
	}
	void ejectQuarter() override
	{
		std::cout << "�̹� �˸��̸� �̾ҽ��ϴ�\n";
	}
	void turnCrank() override
	{
		std::cout << "�����̸� �ѹ��� �����ּ���\n";
	}
	void dispense() override
	{
		std::cout << "�����մϴ�! �˸��̸� �ϳ� �� ������ �� �ֽ��ϴ�\n";
		gumballMachine.release();
		if (gumballMachine.getCount() == 0)
		{
			gumballMachine.setState(gumballMachine.getSoldOutState());
		}
		else
		{
			gumballMachine.release();
			if (gumballMachine.getCount() > 0)
			{
				gumballMachine.setState(gumballMachine.getNoQuarterState());
			}
			else
			{
				std::cout << "�� �̻� �˸��̰� �����ϴ�\n";
				gumballMachine.setState(gumballMachine.getSoldOutState());
			}
		}
	}
};

class GumballMachine : public Machine
{
	State* sold_out_state;
	State* no_quarter_state;
	State* has_quarter_state;
	State* sold_state;
	State* winnerState;

	State* state;
	int count = 0;
	std::string location;
public:
	GumballMachine(std::string location, const int count) : count(count), location(std::move(location))
	{
		sold_out_state = new SoldOutState(*this);
		no_quarter_state = new NoQuarterState(*this);
		has_quarter_state = new HasQuarterState(*this);
		sold_state = new SoldState(*this);
		winnerState = new WinnerState(*this);
		if (count > 0)
		{
			state = no_quarter_state;
		}
		else
		{
			state = sold_out_state;
		}
	}

	void insertQuarter() override
	{
		state->insertQuarter();
	}

	void ejectQuarter() override
	{
		state->ejectQuarter();
	}

	void turnCrank() override
	{
		state->turnCrank();
		state->dispense();
	}

	void dispense() override
	{
		state->dispense();
	}

	friend std::ostream& operator<<(std::ostream& os, const GumballMachine& gumballMachine)
	{
		os << "�ֽ�ȸ�� �ջ̱�\n";
		os << "���� ����: " << gumballMachine.count << "��\n";
		os << "����: " << typeid(*gumballMachine.state).name() << "\n\n";
		return os;
	}
	int getCount() const override
	{
		return count;
	}
	std::string getLocation() const
	{
		return location;
	}
	State* getState() const
	{
		return state;
	}
	void setState(State* state) override
	{
		this->state = state;
	}
	void release() override
	{
		std::cout << "�˸��̸� �������� �ֽ��ϴ�.\n";
		if (count != 0)
		{
			count--;
		}
	}
	State* getSoldOutState() const override
	{
		return sold_out_state;
	}
	State* getNoQuarterState() const override
	{
		return no_quarter_state;
	}
	State* getHasQuarterState() const override
	{
		return has_quarter_state;
	}
	State* getSoldState() const override
	{
		return sold_state;
	}
	State* getWinnerState() const override
	{
		return winnerState;
	}

};
class GumballMonitor
{
	GumballMachine& gumballMachine;
public:
	GumballMonitor(GumballMachine& gumballMachine) : gumballMachine(gumballMachine) {}
	void report()
	{
		std::cout << "Gumball Machine: " << gumballMachine.getLocation() << "\n";
		std::cout << "Current inventory: " << gumballMachine.getCount() << " gumballs\n";
		std::cout << "Current state: " << typeid(*gumballMachine.getState()).name() << "\n\n";
	}
};
int main()
{
	int count = 0;
	std::string location;
	std::cout << "�˸����� ��ġ�� �Է��ϼ���: ";
	std::cin >> location;
	std::cout << "�˸����� ������ �Է��ϼ���: ";
	std::cin >> count;
	
	GumballMachine gumballMachine(location, count);

	GumballMonitor monitor(gumballMachine);

	monitor.report();

	return 0;
}
