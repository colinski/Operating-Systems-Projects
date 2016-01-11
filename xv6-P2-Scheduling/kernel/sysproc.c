#include "types.h"
#include "x86.h"
#include "defs.h"
#include "param.h"
#include "mmu.h"
#include "proc.h"
#include "sysfunc.h"
#include "spinlock.h"
#include "ptable.h"
// P2 include
#include "pstat.h"

// set the call counters to 0
unsigned int callCount = 0;
unsigned int succCount = 0;

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return proc->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = proc->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;
  
  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(proc->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since boot.
int
sys_uptime(void)
{
  uint xticks;
  
  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

int
sys_getsyscallnumtotal(void)
{
	return callCount;
}

int
sys_getsyscallnumsuccess(void)
{
	return succCount;
}

int 
sys_getpinfo(void)
{
	//return getpinfo();
	struct pstat *p_s;
	struct proc *p;
	
	int check = argptr(0, (void *)&p_s, sizeof(*p_s));
	if (check < 0) {
		return -1;
	}
	acquire(&ptable.lock);
	int i;
	for (i = 0; i < NPROC; i++) {
		p = &ptable.proc[i];
		p_s->pid[i] = p->pid;
		if (p->state == UNUSED) {
			p_s->inuse[i] = 0;
		} else {
			p_s->inuse[i] = 1;
		}
		p_s->priority[i] = p->priority;
		//p->ticks = p->ticks_buffer;
		p_s->ticks[i][0] = p->total_ticks[0];	
		p_s->ticks[i][1] = p->total_ticks[1];	
		p_s->ticks[i][2] = p->total_ticks[2];	
		p_s->ticks[i][3] = p->total_ticks[3];	
	}
	release(&ptable.lock);
	return 0;
}
