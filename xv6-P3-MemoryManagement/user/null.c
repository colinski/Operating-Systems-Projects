#include "types.h"
#include "stat.h"
#include "user.h"

int main() {
	int i, n, t;
	int *p;
	i = 5;
	p = &i;
	n = *p;
	p = NULL;
	t = *p;
	printf(1, "t is %d\n", t);
	exit();	
}
