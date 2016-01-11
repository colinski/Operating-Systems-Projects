#include "types.h"
#include "stat.h"
#include "user.h"


int function(){
	int x;
	int y;
	int z;
	x = 5;
	y = 6;
	z = 7;
	printf(1, "variable x is at addr : %d\n", &x);
	printf(1, "variable y is at addr : %d\n", &y);
	printf(1, "variable z is at addr : %d\n", &z);
	return 0;
}
int main() {
	function();
	exit();
}
