#include "memlayout.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <setjmp.h>
#include <unistd.h>

//Define global variable
jmp_buf restore;

void sigsegv_handler(int signo){
        siglongjmp(restore,1);
}

int get_mem_layout(struct memregion *regions, unsigned int size){
	struct sigaction sigsegv_act;
	sigsegv_act.sa_handler = sigsegv_handler;
	sigemptyset(&sigsegv_act.sa_mask);
	sigsegv_act.sa_flags = 0;
	sigaction(SIGSEGV, &sigsegv_act, NULL);

	unsigned char currentMode;
	unsigned char previousMode = MEM_NO;
	unsigned int pointerIndex = 0;

	char temp;

	char *start = 	(char *)0x00000000;
	char *end = 	(char *)0xffffffff;

	if(size != 0){
		regions[0].from = start;
	}

	while(start<end){
		
		int readFault = sigsetjmp(restore,1);

		//Check for readFault
		if(readFault == 0){
			temp = *start;
		}
		if(readFault == 1){
			//NO read and write
			currentMode = MEM_NO;
		}else if(readFault == 0){
			//Able to read, test write
			int writeFault = sigsetjmp(restore, 1);
			if(writeFault == 0){
				*start = temp;
			}
			if(writeFault == 0){
				//Able to write
				currentMode = MEM_RW;
			}else if(writeFault == 1){
				currentMode = MEM_RO;
			}
		}

		if(currentMode == previousMode){
			//Continue
		}else{
			if(pointerIndex<size){
				regions[pointerIndex].to = start -1;
				regions[pointerIndex].mode = previousMode;
				pointerIndex++;
			}
			
			if(pointerIndex < size){
				regions[pointerIndex].from = start;
			}
		}

		start += PAGESIZE;
		if(start == 0){
			
			//Finish the memory scan
			break;
		}
		previousMode = currentMode;

	}
	if(pointerIndex < size){
		regions[pointerIndex].to=end;
		regions[pointerIndex].mode = currentMode;
		pointerIndex++;
	}
	return pointerIndex;
}

int get_mem_diff(struct memregion *regions, unsigned int howmany, struct memregion *thediff, unsigned int diffsize){
	
	struct sigaction sigsegv_act;
	sigsegv_act.sa_handler = sigsegv_handler;
	sigemptyset(&sigsegv_act.sa_mask);
	sigsegv_act.sa_flags = 0;
	sigaction(SIGSEGV, &sigsegv_act, NULL);
	
	unsigned char currentMode;
	unsigned char previousMode = UNDEFINEMODE;
	unsigned char oldMode = regions[0].mode;

	char temp;
	unsigned int pointerIndex = 0;

	char *start = (char *)0x0;
	char *end = (char *)0xffffffff;
	int i = 0;

	while(start<end){
		int readFault = sigsetjmp(restore,1);

		//Check for readFault
		if(readFault == 0){
			temp = *start;
		}

		if(readFault == 1){
			//NO read and write
			currentMode = MEM_NO;
		}else if(readFault == 0){
			//Able to read, test write
			int writeFault = sigsetjmp(restore, 1);
			if(writeFault == 0){
				*start = temp;
			}
			if(writeFault == 0){
				//Able to write
				currentMode = MEM_RW;
			}else if(writeFault == 1){
				currentMode = MEM_RO;
			}
		}

		if((void *)start > regions[i].to){
			i++;
			oldMode = regions[i].mode;
		}

		if(currentMode != oldMode){
			
			if(previousMode == UNDEFINEMODE && pointerIndex < diffsize){
				thediff[pointerIndex].from = start;
				thediff[pointerIndex].mode = currentMode;
			}
			else if(currentMode != previousMode && pointerIndex < diffsize){
				thediff[pointerIndex].to = start - 1;
				pointerIndex++;

				if(pointerIndex < diffsize){
					thediff[pointerIndex].from = start;
					thediff[pointerIndex].mode = currentMode;
				}
			}
			previousMode = currentMode;
		}
		else if(previousMode != UNDEFINEMODE){
			thediff[pointerIndex].to = start - 1;
			previousMode = UNDEFINEMODE;
			pointerIndex++;
		}
		start +=PAGESIZE;
		if((void *)start > regions[howmany-1].to){
			break;
		}
		if(start == 0){
			break;
		}

	}
	if(pointerIndex<diffsize && currentMode != oldMode){
		thediff[pointerIndex].to = start - 1;
		pointerIndex++;
	}
	return pointerIndex;

};


