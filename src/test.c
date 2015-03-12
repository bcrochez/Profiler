#include <stdio.h>
#include <stdlib.h>
#include "../include/macro_profiler.h"

int fact(int n) {
	PROFILE
	int ans;
	if(n <= 1) {
		return 1;
	}
	else {
		ans = n*fact(n-1);
		return ans;
	}
}

int hello() {
	PROFILE
	return 1;
}

int bonjour() {
	PROFILE
	return 1;
}

int testA() {
	PROFILE
	hello();
	bonjour();
	return 1;
}

int testB() {
	PROFILE
	testA();
	hello();
	return 1;
}

int testC() {
	PROFILE
	testA();
	testB();
	return 1;
}

int main(void) {
	PROFILE
	fact(10);
	fact(10);
	testA();
	testB();
	testC();
	return 1;
}
