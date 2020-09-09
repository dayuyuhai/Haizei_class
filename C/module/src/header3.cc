#include<stdio.h>
#include"header1.h"
#include"header3.h"

void funcD(int a, int b) {
	printf("funcD : %d", a);
	funcA(2);
	return ;
}
