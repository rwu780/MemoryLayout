#ifndef MEMLAYOUT_H_
#define MEMLAYOUT_H_

#define MEM_RW 0
#define MEM_RO 1
#define MEM_NO 2
#define UNDEFINEMODE 9

extern unsigned int PAGESIZE;

struct memregion{
	void *from;
	void *to;
	unsigned char mode;
};

void sigsegv_handler(int signo);
int get_mem_layout(struct memregion *regions, unsigned int size);
int get_mem_diff(struct memregion *regions, unsigned int howmany, struct memregion *thediff, unsigned int diffsize);





#endif