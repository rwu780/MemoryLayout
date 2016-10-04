Name: Rui Wu, Runqi Wang
CCID: rwu4, runqi
ID: 1409366, 1290130
Group number:4

Collaborate with Mingjun Zhao and Nicholas Li

(nil) - 0x8047fff, NO 		kernal offset
0x8048000 - 0x80e9fff, RO	text segament
0x80ea000 - 0x80edfff, RW	Data Segament
0x80ee000 - 0x9ea6fff, NO	
0x9ea7000 - 0x9ec8fff, RW	Heap
0x9ec9000 - 0xb7774fff, NO	
0xb7775000 - 0xb7775fff, RO	Meomry Mapping
0xb7776000 - 0xbffcefff, NO	MMap Offset
0xbffcf000 - 0xbfff0fff, RW	Stack
0xbfff1000 - 0xffffffff, NO	Kernal Space

mem_mod1
(nil) - 0x8047fff, NO
0x8048000 - 0x80e9fff, RO
0x80ea000 - 0x80edfff, RW
0x80ee000 - 0x8a2dfff, NO
0x8a2e000 - 0x8a4ffff, RW
0x8a50000 - 0xb77d5fff, NO
0xb77d6000 - 0xb77d6fff, RO
0xb77d7000 - 0xbffb7fff, NO
0xbffb8000 - 0xbffd9fff, RW
0xbffda000 - 0xffffffff, NO
The difference: 2
0xb77d5000 - 0xb77d5fff, RW
0xbffb7000 - 0xbffb7fff, RW

Initially use mem_layout to scan memory region, then create a second struct to record the diff

The first difference result from Memory mapping, resulted from increasing amount of pointers

The second difference result from a incrase stack, that resulted in a increase number of local variables 

mem_mod2
output:
(nil) - 0x8047fff, NO
0x8048000 - 0x80e9fff, RO
0x80ea000 - 0x80edfff, RW
0x80ee000 - 0x902bfff, NO
0x902c000 - 0x904dfff, RW
0x904e000 - 0xb77f9fff, NO
0xb77fa000 - 0xb77fafff, RO
0xb77fb000 - 0xbfae9fff, NO
0xbfaea000 - 0xbfb0bfff, RW
0xbfb0c000 - 0xffffffff, NO
The difference: 3
0x9030000 - 0x9030fff, RO
0xb77f9000 - 0xb77f9fff, RW
0xbfae9000 - 0xbfae9fff, RW

Difference 1, we use memalign to allocate space in heap. 
Different 2 and 3 are resulted from mem_mod1 where memory had change in memory mapping region and stack. 

memalign is very similar to malloc, it dynamically alloc a memory block in heap. We use memalign to allocate a block of memory in heap, thus why mem_mod2 have one more difference than mem_mod1. And for better visualiiy, we change the block to a RO mode to demo a block is allocate in heap.

mem_mod3

Output:
(nil) - 0x8047fff, NO
0x8048000 - 0x80e9fff, RO
0x80ea000 - 0x80edfff, RW
0x80ee000 - 0x895efff, NO
0x895f000 - 0x8962fff, RW
0x8963000 - 0x8963fff, RO
0x8964000 - 0x8980fff, RW
0x8981000 - 0xb77d8fff, NO
0xb77d9000 - 0xb77d9fff, RO
0xb77da000 - 0xbfb49fff, NO
0xbfb4a000 - 0xbfb6bfff, RW
0xbfb6c000 - 0xffffffff, NO
The difference: 3
0x8963000 - 0x8963fff, RW
0xb77d8000 - 0xb77d8fff, RW
0xbfb49000 - 0xbfb49fff, RW

Use memalign to allocate 1 PAGE buffer in Heap, use mprotect to assign MEM_RO;
print out memory region

Use mprotect to change buffer to MEM_RW, print the different;

We allocate one page of buffer in heap which is MEM_RW. Thus we can use mprotect to change the accessibilty of the particular
buffer.

