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
		GumballMachine& gumballMachine;
	public:
		NoQuarterState(GumballMachine& gumballMachine) : gumballMachine(gumballMachine) {}
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
		GumballMachine& gumballMachine;
	public:
		HasQuarterState(GumballMachine& gumballMachine) : gumballMachine(gumballMachine) {}
		void insertQuarter() override
		{
			//�̻��¿����� �������� �޼ҵ�
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
			gumballMachine.setState(gumballMachine.getSoldState());
		}
		void dispense() override
		{
			//�̻��¿����� �� �޼ҵ嵵 �̻��¿��� ��������
			std::cout << "�˸��̰� �����ϴ�\n";
		}
	};

	class SoldState : public State
	{
		GumballMachine& gumballMachine;
	public:
		SoldState(GumballMachine& gumballMachine) : gumballMachine(gumballMachine) {}
		void insertQuarter() override
		{
			std::cout << "��� ��ٷ��ּ���\n";
			//������
		}
		void ejectQuarter() override
		{
			std::cout << "�̹� �˸��̸� �̾ҽ��ϴ�\n";
			//������
		}
		void turnCrank() override
		{
			std::cout << "�����̸� �ѹ��� �����ּ���\n";
			//������
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
				std::cout << "�� �̻� �˸��̰� �����ϴ�\n";
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
		os << "�ֽ�ȸ�� �ջ̱�\n";
		os << "���� ����: " << gumballMachine.count << "��\n";
		os << "����: " << typeid(*gumballMachine.state).name() << "\n\n";
		return os;
	}
	void setState(State* state)
	{
		this->state = state;
	}
	void release()
	{
		std::cout << "�˸��̸� ������ �ֽ��ϴ�.";
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