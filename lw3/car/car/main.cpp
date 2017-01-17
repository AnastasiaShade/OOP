#include "stdafx.h"
#include "Car.h"
#include "CarController.h"
 
using namespace std;

/*

1. —делать возможным запуск проекта и тестов к нему во всех конфигураци€х

2. ¬место конструкций вида
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
сделать в тестах функции, "разгон€ющие" машину до определенного состо€ни€

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

