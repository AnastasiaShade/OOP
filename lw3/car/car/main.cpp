#include "stdafx.h"
#include "Car.h"
#include "CarController.h"
 
using namespace std;

/*

1. ������� ��������� ������ ������� � ������ � ���� �� ���� �������������

2. ������ ����������� ����
car.SetGear(1);
BOOST_CHECK(car.SetSpeed(10));
car.SetGear(2);
BOOST_CHECK(car.SetSpeed(30));
car.SetGear(3);
BOOST_CHECK(car.SetSpeed(50));
car.SetGear(4);
BOOST_CHECK(car.SetSpeed(50));
car.SetGear(5);
BOOST_CHECK(car.SetSpeed(70));
������� � ������ �������, "�����������" ������ �� ������������� ���������

3. > SetSpeed
Speed was successfully changed on -858993460
???

4. > SetSpeed 10000000000000000000000000000000000000000000000
Speed was successfully changed on -858993460
???

*/

int main()
{
	CCar car;
	CCarController controller(car, cin, cout);
	while (!cin.eof() && !cin.fail())
	{
		cout << "> ";
		if (!controller.HandleCommand())
		{
			cout << "Unknown command!" << endl;
		}
	}
	return 0;
}

