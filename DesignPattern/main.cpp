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
		std::cout << "매진되었습니다\n";
	}
	void ejectQuarter() override
	{
		std::cout << "동전을 넣지 않았습니다\n";
	}
	void turnCrank() override
	{
		std::cout << "매진되었습니다\n";
	}
	void dispense() override
	{
		std::cout << "매진되었습니다\n";
	}
};

class NoQuarterState : public State
{
	Machine& gumballMachine;
public:
	NoQuarterState(Machine& gumballMachine) : gumballMachine(gumballMachine) {}
	void insertQuarter() override
	{
		std::cout << "동전을 넣었습니다\n";
		gumballMachine.setState(gumballMachine.getHasQuarterState());
	}
	void ejectQuarter() override
	{
		std::cout << "동전을 넣지 않았습니다\n";
	}
	void turnCrank() override
	{
		std::cout << "동전을 넣어주세요\n";
	}
	void dispense() override
	{
		std::cout << "동전을 넣어주세요\n";
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
		std::cout << "이미 동전이 있습니다\n";
	}
	void ejectQuarter() override
	{
		std::cout << "동전이 반환됩니다\n";
		gumballMachine.setState(gumballMachine.getNoQuarterState());
	}
	void turnCrank() override
	{
		std::cout << "손잡이를 돌렸습니다\n";
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
		std::cout << "알맹이가 나갑니다\n";
	}
};

class SoldState : public State
{
	Machine& gumballMachine;
public:
	SoldState(Machine& gumballMachine) : gumballMachine(gumballMachine) {}
	void insertQuarter() override
	{
		std::cout << "잠깐만 기다려주세요\n";
	}
	void ejectQuarter() override
	{
		std::cout << "이미 알맹이를 뽑았습니다\n";
	}
	void turnCrank() override
	{
		std::cout << "손잡이를 한번만 돌려주세요\n";
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
			std::cout << "더 이상 알맹이가 없습니다\n";
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
		std::cout << "잠깐만 기다려주세요\n";
	}
	void ejectQuarter() override
	{
		std::cout << "이미 알맹이를 뽑았습니다\n";
	}
	void turnCrank() override
	{
		std::cout << "손잡이를 한번만 돌려주세요\n";
	}
	void dispense() override
	{
		std::cout << "축하합니다! 알맹이를 하나 더 받으실 수 있습니다\n";
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
				std::cout << "더 이상 알맹이가 없습니다\n";
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
		os << "주식회사 왕뽑기\n";
		os << "남은 개수: " << gumballMachine.count << "개\n";
		os << "상태: " << typeid(*gumballMachine.state).name() << "\n\n";
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
		std::cout << "알맹이를 내보내고 있습니다.\n";
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
	std::cout << "알맹이의 위치를 입력하세요: ";
	std::cin >> location;
	std::cout << "알맹이의 개수를 입력하세요: ";
	std::cin >> count;
	
	GumballMachine gumballMachine(location, count);

	GumballMonitor monitor(gumballMachine);

	monitor.report();

	return 0;
}
