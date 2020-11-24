#include "Cluster.h"
#include <iostream>

int main()
{
	setlocale(LC_ALL, "Russian");
	TaskStream s(1000);
	Cluster c(10);
	c.ClusterOn(s);
	c.Statistics();
	system("pause");
}


