#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "fs.h"


int ppid;
#define assert(x) if (x) {} else { \
   printf(1, "%s: %d ", __FILE__, __LINE__); \
   printf(1, "assert failed (%s)\n", # x); \
   kill(ppid); \
   exit(); \
}

int
main(int argc, char *argv[])
{
   ppid = getpid();

   int fd;
   fd = open(argv[1], O_RDWR);
   assert(fd >= 0);


   struct stat st;
   fstat(fd, &st);
   if (st.type == T_CHECKED) {
	   printf(1, "This is a checked file\n");
   } else {
	   printf(1, "This is not a checked file\n");
   }
   printf(1, "inode number: %d\n", st.ino);
   printf(1, "size: %d\n", st.size);
   printf(1, "checksum: %d\n", (int) st.checksum);
   int r;
   r = close(fd);
   assert(r == 0);
   exit();
}
