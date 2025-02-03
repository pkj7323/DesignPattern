#include <iostream>
class GumballMachine
{
	static constexpr int SOLD_OUT = 0;
	static constexpr int NO_QUARTER = 1;
	static constexpr int HAS_QUARTER = 2;
	static constexpr int SOLD = 3;

	int state = SOLD_OUT;
	int count = 0;
public:
	GumballMachine(int count) : count(count)
	{
		if (count > 0)
			state = NO_QUARTER;
	}

    void insertQuarter()
	{
		if (state == HAS_QUARTER)
			std::cout << "������ �̹� �־����ϴ�\n";
		else if (state == NO_QUARTER)
		{
			state = HAS_QUARTER;
			std::cout << "������ �־����ϴ�\n";
		}
		else if (state == SOLD_OUT)
			std::cout << "�����Ǿ����ϴ�. ������ ���� �� �����ϴ�\n";
		else if (state == SOLD)
			std::cout << "��ø� ��ٷ� �ּ���. �˸��̰� ������ �ֽ��ϴ�\n";
    }

    void ejectQuarter()
    {
		if (state == HAS_QUARTER)
		{
			std::cout << "������ ��ȯ�˴ϴ�\n";
			state = NO_QUARTER;
		}
		else if (state == NO_QUARTER)
			std::cout << "������ ���� �ʾҽ��ϴ�\n";
		else if (state == SOLD)
			std::cout << "�̹� �˸��̸� �����̽��ϴ�\n";
		else if (state == SOLD_OUT)
			std::cout << "������ ���� �ʾҽ��ϴ�. ��ȯ�� ������ �����ϴ�\n";
    }

    void turnCrank()
    {
		if (state == SOLD)
			std::cout << "�����̸� �� �� ������ �˸��̰� �� ������ �ʽ��ϴ�\n";
		else if (state == NO_QUARTER)
			std::cout << "������ �־��ּ���\n";
		else if (state == SOLD_OUT)
			std::cout << "�����Ǿ����ϴ�\n";
		else if (state == HAS_QUARTER)
		{
			std::cout << "�����̸� �����̽��ϴ�...\n";
			state = SOLD;
			dispense();
		}
    }

    void dispense()
    {
		if (state == SOLD)
		{
			std::cout << "�˸��̰� ���ɴϴ�\n";
			count--;
			if (count == 0)
			{
				std::cout << "�˸��̰� �� ���������ϴ�\n";
				state = SOLD_OUT;
			}
			else
				state = NO_QUARTER;
		}
		else if (state == NO_QUARTER)
			std::cout << "������ �־��ּ���\n";
		else if (state == SOLD_OUT)
			std::cout << "�˸��̰� �����ϴ�\n";
		else if (state == HAS_QUARTER)
			std::cout << "�˸��̰� ���� �� �����ϴ�\n";
    }
	
	friend std::ostream& operator<<(std::ostream& os, const GumballMachine& gumballMachine)
	{
		std::string state;
		if (gumballMachine.state == GumballMachine::SOLD_OUT)
			state = "����";
		else if (gumballMachine.state == GumballMachine::NO_QUARTER)
			state = "���� ����";
		else if (gumballMachine.state == GumballMachine::HAS_QUARTER)
			state = "���� ����";
		else if (gumballMachine.state == GumballMachine::SOLD)
			state = "�˸��� �Ǹ���";
		os << "�ֽ�ȸ�� �ջ̱�\n";
		os << "���� ����: " << gumballMachine.count << "��\n";
		os << "����: " << state << "\n\n";
		return os;
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