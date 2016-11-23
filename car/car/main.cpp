#include "stdafx.h"
#include <iostream>
#include "Car.h"
#include "CarController.h"

using namespace std;

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

