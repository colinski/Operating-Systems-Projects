#include "types.h"
#include "stat.h"
#include "user.h"

int main() {
	int ret;
	char *p = malloc(sizeof(char));
	//printf(1, "t is %d\n", t);
	ret = open(p + 512, 0);
	//*(p + 512) = 4;
	printf(1, "open returned %d\n", ret);
	exit();	
}
