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
			std::cout << "동전을 이미 넣었습니다\n";
		else if (state == NO_QUARTER)
		{
			state = HAS_QUARTER;
			std::cout << "동전을 넣었습니다\n";
		}
		else if (state == SOLD_OUT)
			std::cout << "매진되었습니다. 동전을 넣을 수 없습니다\n";
		else if (state == SOLD)
			std::cout << "잠시만 기다려 주세요. 알맹이가 나가고 있습니다\n";
    }

    void ejectQuarter()
    {
		if (state == HAS_QUARTER)
		{
			std::cout << "동전이 반환됩니다\n";
			state = NO_QUARTER;
		}
		else if (state == NO_QUARTER)
			std::cout << "동전을 넣지 않았습니다\n";
		else if (state == SOLD)
			std::cout << "이미 알맹이를 뽑으셨습니다\n";
		else if (state == SOLD_OUT)
			std::cout << "동전을 넣지 않았습니다. 반환할 동전이 없습니다\n";
    }

    void turnCrank()
    {
		if (state == SOLD)
			std::cout << "손잡이를 두 번 돌려도 알맹이가 더 나오지 않습니다\n";
		else if (state == NO_QUARTER)
			std::cout << "동전을 넣어주세요\n";
		else if (state == SOLD_OUT)
			std::cout << "매진되었습니다\n";
		else if (state == HAS_QUARTER)
		{
			std::cout << "손잡이를 돌리셨습니다...\n";
			state = SOLD;
			dispense();
		}
    }

    void dispense()
    {
		if (state == SOLD)
		{
			std::cout << "알맹이가 나옵니다\n";
			count--;
			if (count == 0)
			{
				std::cout << "알맹이가 다 떨어졌습니다\n";
				state = SOLD_OUT;
			}
			else
				state = NO_QUARTER;
		}
		else if (state == NO_QUARTER)
			std::cout << "동전을 넣어주세요\n";
		else if (state == SOLD_OUT)
			std::cout << "알맹이가 없습니다\n";
		else if (state == HAS_QUARTER)
			std::cout << "알맹이가 나올 수 없습니다\n";
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