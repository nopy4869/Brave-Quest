//floattest.c
//testing storage of floats in int data structures!

#include <stdio.h>

int floatpacker(float f)
{
	union int_to_float {
		float f;
		int i;
	} itf;
	itf.f = f;
	return itf.i;
}

float intpacker(int i)
{
	union int_to_float {
		float f;
		int i;
	} itf;
	itf.i = i;
	return itf.f;
}

int main()
{
	int x = 0;
	float y;
	y = 3.5;
	x = floatpacker(y);
	printf("%d, %f\n",x, intpacker(x));
	return 0;
}
