#include "types.h"
#include "stat.h"
#include "user.h"


int fib(int n) {
	if (n <= 1) {
		return n;
	} else {
		return fib(n - 1) + fib(n - 2);
	}
}
int main() {
	int f;
	printf(1, "The 1000000th Fibonacci number is:\n");
	f = fib(1000000);
	printf(1, "%d\n", f);
	exit();
}
