#include "types.h"
#include "stat.h"
#include "user.h"

int main() {
	int *x = malloc(sizeof(int));
	*x = 5;
	*(x + 4) = 5;
	exit();
}
