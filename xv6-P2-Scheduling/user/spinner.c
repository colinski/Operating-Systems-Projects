#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"

int main(int argc, char *argv[]){
	int i;
	int x;
	x = 0;
	if(argc != 2){
		exit();
	}
	int val;
	val = atoi(argv[1]);
	for (i = 0; i < val; i++){
		x += i;
	}
	exit();
}
