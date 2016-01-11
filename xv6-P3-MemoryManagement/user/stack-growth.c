#include "types.h"
#include "stat.h"
#include "user.h"


/*int fib(int n){
	int x;
	x = 5;
	printf(1, "local variable is at addr: %d %d\n,", &x, n);
	if (n <= 1){
		return n;
	} else {
		return fib(n - 1) + fib(n - 2);
	}
}*/
int f8(){
	int v;
	int w;
	int x;
	int y;
	int z;
	v = 5;
	w = 6;
	x = 7;
	y = 8;
	z = 9;
	printf(1, "variable v is at addr : %d\n", &v);
	printf(1, "variable w is at addr : %d\n", &w);
	printf(1, "variable x is at addr : %d\n", &x);
	printf(1, "variable y is at addr : %d\n", &y);
	printf(1, "variable z is at addr : %d\n", &z);
	return 0;
}
int f7(){
	int s;
	int t;
	int u;
	s = 5;
	t = 6;
	u = 7;
	printf(1, "variable s is at addr : %d\n", &s);
	printf(1, "variable t is at addr : %d\n", &t);
	printf(1, "variable u is at addr : %d\n", &u);
	return f8();
}
int f6(){
	int p;
	int q;
	int r;
	p = 5;
	q = 6;
	r = 7;
	printf(1, "variable p is at addr : %d\n", &p);
	printf(1, "variable q is at addr : %d\n", &q);
	printf(1, "variable r is at addr : %d\n", &r);
	return f7();
}
int f5(){
	int m;
	int n;
	int o;
	m = 5;
	n = 6;
	o = 7;
	printf(1, "variable m is at addr : %d\n", &m);
	printf(1, "variable n is at addr : %d\n", &n);
	printf(1, "variable o is at addr : %d\n", &o);
	return f6();
}
int f4(){
	int j;
	int k;
	int l;
	j = 5;
	k = 6;
	l = 7;
	printf(1, "variable j is at addr : %d\n", &j);
	printf(1, "variable k is at addr : %d\n", &k);
	printf(1, "variable l is at addr : %d\n", &l);
	return f5();
}

int f3(){
	int g;
	int h;
	int i;
	g = 5;
	h = 6;
	i = 7;
	printf(1, "variable g is at addr : %d\n", &g);
	printf(1, "variable h is at addr : %d\n", &h);
	printf(1, "variable i is at addr : %d\n", &i);
	return f4();
}
int f2(){
	int d;
	int e;
	int f;
	d = 5;
	e = 6;
	f = 7;
	printf(1, "variable d is at addr : %d\n", &d);
	printf(1, "variable e is at addr : %d\n", &e);
	printf(1, "variable f is at addr : %d\n", &f);
	return f3();
}

int f1(){
	int a;
	int b;
	int c;
	a = 5;
	b = 6;
	c = 7;
	printf(1, "variable a is at addr : %d\n", &a);
	printf(1, "variable b is at addr : %d\n", &b);
	printf(1, "variable c is at addr : %d\n", &c);
	return f2();
}
int main() {
	f1();
	exit();
}
