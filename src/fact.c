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

int main(void) {
	PROFILE
	fact(10);
	return 1;
}
