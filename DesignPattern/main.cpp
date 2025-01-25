#include <iostream>
class AbstractClass
{//메소드 = 멤버함수
	virtual void templetMethod() final // 템플릿 메소드
	{	// 클래스의 메소드이면서
		//일종의 알고리즘을 정의하도록 유도하는 템플릿인것

		primativeOperation1();// 추상 메소드 1
		primativeOperation2();// 추상 메소드 2
		concreteOperation(); // 구상 메소드
	}
	virtual void primativeOperation1() = 0;// 추상 메소드 1
	virtual void primativeOperation2() = 0;// 추상 메소드 2
	void concreteOperation()// 구상 메소드
	{
		std::cout << "구상 함수입니다." << std::endl;
	}
};



int main() {
	

	return 0;
}