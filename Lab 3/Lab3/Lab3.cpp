#include "lab3.h"
// add your tests here.
int main()
{

	char code[1000] = "";

	char variables[1000] = "";

	FindAllVariables(variables, code);
	FindAllVariablesInScope(variables, code, 12);


}