#include <iostream>


class State
{
public:
	virtual void insertQuarter() = 0;
	virtual void ejectQuarter() = 0;
	virtual void turnCrank() = 0;
	virtual void dispense() = 0;
};
class GumballMachine
{
	State* sold_out_state;
	State* no_quarter_state;
	State* has_quarter_state;
	State* sold_state;

	State* state = sold_out_state;
	int count = 0;
public:
	class SoldOutState : public State
	{
		GumballMachine& gumballMachine;
	public:
		SoldOutState(GumballMachine& gumballMachine) : gumballMachine(gumballMachine) {}
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
		GumballMachine& gumballMachine;
	public:
		NoQuarterState(GumballMachine& gumballMachine) : gumballMachine(gumballMachine) {}
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
		GumballMachine& gumballMachine;
	public:
		HasQuarterState(GumballMachine& gumballMachine) : gumballMachine(gumballMachine) {}
		void insertQuarter() override
		{
			//이상태에서는 부적절한 메소드
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
			gumballMachine.setState(gumballMachine.getSoldState());
		}
		void dispense() override
		{
			//이상태에서는 이 메소드도 이상태에선 부적절함
			std::cout << "알맹이가 나갑니다\n";
		}
	};

	class SoldState : public State
	{
		GumballMachine& gumballMachine;
	public:
		SoldState(GumballMachine& gumballMachine) : gumballMachine(gumballMachine) {}
		void insertQuarter() override
		{
			std::cout << "잠깐만 기다려주세요\n";
			//부적절
		}
		void ejectQuarter() override
		{
			std::cout << "이미 알맹이를 뽑았습니다\n";
			//부적절
		}
		void turnCrank() override
		{
			std::cout << "손잡이를 한번만 돌려주세요\n";
			//부적절
		}

		void dispense() override
		{
			gumballMachine.release();
			if (gumballMachine.count > 0)
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

	GumballMachine(int count) : count(count)
	{
		sold_out_state = new SoldOutState(*this);
		no_quarter_state = new NoQuarterState(*this);
		has_quarter_state = new HasQuarterState(*this);
		sold_state = new SoldState(*this);
		if (count > 0)
		{
			state = no_quarter_state;
		}
		else
		{
			state = sold_out_state;
		}
	}

	void insertQuarter()
	{
		state->insertQuarter();
	}

	void ejectQuarter()
	{
		state->ejectQuarter();
	}

	void turnCrank()
	{
		state->turnCrank();
		state->dispense();
	}

	void dispense()
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
	void setState(State* state)
	{
		this->state = state;
	}
	void release()
	{
		std::cout << "알맹이를 내보고 있습니다.";
		if (count != 0)
		{
			count--;
		}
	}
	State* getSoldOutState() const
	{
		return sold_out_state;
	}
	State* getNoQuarterState() const
	{
		return no_quarter_state;
	}
	State* getHasQuarterState() const
	{
		return has_quarter_state;
	}
	State* getSoldState() const
	{
		return sold_state;
	}
};






int main()
{
	GumballMachine gumballMachine(5);

	std::cout << gumballMachine;

	gumballMachine.insertQuarter();
	gumballMachine.turnCrank();

	std::cout << gumballMachine;

	gumballMachine.insertQuarter();
	gumballMachine.ejectQuarter();
	gumballMachine.turnCrank();

	std::cout << gumballMachine;

	gumballMachine.insertQuarter();
	gumballMachine.turnCrank();
	gumballMachine.insertQuarter();
	gumballMachine.turnCrank();
	gumballMachine.ejectQuarter();

	std::cout << gumballMachine;

	gumballMachine.insertQuarter();
	gumballMachine.insertQuarter();
	gumballMachine.turnCrank();
	gumballMachine.insertQuarter();
	gumballMachine.turnCrank();
	gumballMachine.insertQuarter();
	gumballMachine.turnCrank();

	std::cout << gumballMachine;


	return 0;
}