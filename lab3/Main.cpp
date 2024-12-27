#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include "Interface.h"


int main(int argc, char** argv)
{
	setlocale(LC_ALL, "ru");

	start();

	//int result = Catch::Session().run(argc, argv);
	//return result;

	return 0;
}
