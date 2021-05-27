#include "Controller.h"
#include <string>
#include <fstream>

int main()
{
	try
	{
		Controller controller;
		controller.run();
	}
	catch (std::string str)
	{
		std::ofstream errOut("log.txt");
		errOut << str << std::endl;
	}
	catch (...)
	{
		std::ofstream errOut("log.txt");
		errOut << "Unknown error ocoured" << std::endl;
	}
	return 0;
}