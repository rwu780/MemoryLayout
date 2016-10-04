/*Reference from
linux.die.net/man/mprotect
*/
#include "memlayout.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
unsigned int PAGESIZE = 4096;

int main(){
        char *mode[3]={"RW","RO","NO"};

        struct memregion *regions = (struct memregion*)malloc(sizeof(struct memregion)*20);
        struct memregion *diff = (struct memregion*)malloc(sizeof(struct memregion)*20);
        //int numberOfRegion = get_mem_layout(regions, 20);
	
	char *buffer = (char *)memalign(PAGESIZE, 4*PAGESIZE);
	mprotect(buffer+PAGESIZE*2,PAGESIZE,PROT_READ);
	
	int numberOfRegion = get_mem_layout(regions, 20);        
	int i = 0;
        for(i=0;i<numberOfRegion;i++){
                printf("%p - %p, %s\n",regions[i].from, regions[i].to, mode[regions[i].mode]);
        }

	mprotect(buffer+PAGESIZE*2,PAGESIZE,PROT_WRITE);
        int diffSize = get_mem_diff(regions, numberOfRegion, diff, 20);

        printf("The difference: %d\n", diffSize);

        for(i=0;i<diffSize;i++){
                printf("%p - %p, %s\n",diff[i].from, diff[i].to, mode[diff[i].mode]);
        }
        return 0;
}
   
