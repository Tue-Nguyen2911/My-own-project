#include <fstream>
#include <iostream>
#include <ctype.h>
#include "ToDoList.h"
using namespace std;
using namespace TueNg;
int main()
{
	ToDoList aList("ToDoList.csv");
	aList.run();
	return 0;
}