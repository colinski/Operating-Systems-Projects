#ifndef _PTABLE_H_
#define _PTABLE_H_

struct ptable{
	struct spinlock lock;
	struct proc proc[NPROC]; 
} ptable;

#endif
