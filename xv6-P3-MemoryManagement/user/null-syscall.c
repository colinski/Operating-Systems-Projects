#include "types.h"
#include "stat.h"
#include "user.h"

int main() {
	int ret;
	char *p;
	p = NULL;
	ret = open(p, 0);
	printf(1, "open returned %d\n", ret);
	exit();	
}
