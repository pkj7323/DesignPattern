#include <iostream>
class AbstractClass
{//�޼ҵ� = ����Լ�
	virtual void templetMethod() final // ���ø� �޼ҵ�
	{	// Ŭ������ �޼ҵ��̸鼭
		//������ �˰����� �����ϵ��� �����ϴ� ���ø��ΰ�

		primativeOperation1();// �߻� �޼ҵ� 1
		primativeOperation2();// �߻� �޼ҵ� 2
		concreteOperation(); // ���� �޼ҵ�
	}
	virtual void primativeOperation1() = 0;// �߻� �޼ҵ� 1
	virtual void primativeOperation2() = 0;// �߻� �޼ҵ� 2
	void concreteOperation()// ���� �޼ҵ�
	{
		std::cout << "���� �Լ��Դϴ�." << std::endl;
	}
};



int main() {
	

	return 0;
}