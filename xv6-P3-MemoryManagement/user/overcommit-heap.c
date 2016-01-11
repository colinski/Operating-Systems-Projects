#include "types.h"
#include "stat.h"
#include "user.h"

int main() {
	while (1) {
		if(malloc(sizeof(int)) == NULL) {
			printf(1, "couldn't allocate memory on the heap (malloc returned null)\n");
			exit();
		}
	}
	exit();
}
