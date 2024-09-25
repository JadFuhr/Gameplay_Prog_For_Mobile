#include "lab3.h"
// add your tests here.
int main()
{

	char code[1000] = "int main() \n{\n int var1 = 10; \n int var2 = 10; \n if (var1 < 10) \n {\n int var3 = 20; \n} \n}\ n";

	char variables[1000] = "";

	FindAllVariables(variables, code);
	FindAllVariablesInScope(variables, code, 12);


}