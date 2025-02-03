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
};

int main()
{
	GumballMachine gumballMachine(5);
	gumballMachine.insertQuarter();
	gumballMachine.turnCrank();
	gumballMachine.insertQuarter();
	gumballMachine.turnCrank();
	gumballMachine.insertQuarter();
	gumballMachine.turnCrank();
	gumballMachine.insertQuarter();
	gumballMachine.turnCrank();


	return 0;
}