#include "types.h"
#include "stat.h"
#include "user.h"

int main() {
	int *a = malloc(sizeof(int));
	*a = 5;
	printf(1, "variable (on heap) a : %d\n", *a);

	
	int *b = malloc(sizeof(int));
	*b = 6;
	printf(1, "variable (on heap) b : %d\n", *b);

	int *c = malloc(sizeof(int));
	*c = 7;
	printf(1, "variable (on heap) c : %d\n", *c);

	int *d = malloc(sizeof(int));
	*d = 8;
	printf(1, "variable (on heap) d : %d\n", *d);

	int *e = malloc(sizeof(int));
	*e = 9;
	printf(1, "variable (on heap) e : %d\n", *e);

	int *f = malloc(sizeof(int));
	*f = 10;
	printf(1, "variable (on heap) f : %d\n", *f);
	*(f + 1024) = 4;
	exit();
}
