#include "stdafx.h"
#include "Controller.h"
#include "Body.h"

using namespace std;

int main()
{
	vector<shared_ptr<CBody>> bodies;
	CController controller(bodies, cin, cout);
	controller.Info();
	while (!cin.eof() && !cin.fail())
	{
		cout << "> ";
		if (!controller.HandleCommand())
		{
			cout << "Unknown command!" << endl;
		}
	}
	controller.PrintAllBodies(bodies, cout);
	controller.FindBodyWithMaxMass(bodies);
	controller.FindBodyWithSmallestWeight(bodies);
}

