#include "def.h"
extern void displayVector(char *, int *, int);

// Global variables
unsigned PHYMEM[MEM_SIZE_INTS];
unsigned * PhysicalBaseAddress;  // Base address of array A. Arrays A, B, C are contiguous.

struct cacheTagBlock    CACHE_TAG_ARRAY[CACHE_SIZE_SETS][NUM_WAYS];  
struct cacheDataBlock  CACHE_DATA_ARRAY[CACHE_SIZE_SETS][NUM_WAYS];  
int usage[CACHE_SIZE_SETS][NUM_WAYS]; // To implement pseudo-LRU

// Cache Statistics
int cache_hits[NUM_THREADS], cache_misses[NUM_THREADS];
int cache_reads[NUM_THREADS], cache_writes[NUM_THREADS];
int cache_writebacks[NUM_THREADS];

// Yacsim Simulator-relted variables
PROCESS *proccntrl;







void UserMain(int argc, char *argv[])
{
  int i;
  void Thread();
 
  initializePhysicalMemory();
  initializeCache(); 
 
  printf("\nCACHE SIZE (Bytes): %d\nAssociativity (ways): %d\nBlock Size (Bytes): %d\nData Size (ints): %d\nBase Address: %p\n\n", CACHE_SIZE_BYTES, NUM_WAYS, BLK_SIZE_BYTES, SIZE, PhysicalBaseAddress);


// Create a Yacsim process to model activities of each thread
  for (i=0; i < NUM_THREADS; i++){
    initializeStatistics(i);
    proccntrl = NewProcess("proccntrl",Thread,0);
    ActivitySetArg(proccntrl,NULL,i);
    ActivitySchedTime(proccntrl,0.00000,INDEPENDENT);
  }

  printf("\n*****************************************************************************************\n");
  DriverRun(1000000000.0); // Maximum time of the simulation (in cycles). 
}


initData(int *p, int *q, int count) {
  int i;

  for (i=0; i < count; i++) {
    *(p + i) = i+1;  
    *(q + i) = i-1;   
  }
}

void  vectorAdd(int threadId, int *p, int *q, int *r, int count) {
  int i, temp1,  temp2, sum;

  if (threadId != 0) 
    exit(1);
   
  for (i=0; i < count; i++) {
    temp1 = read(threadId,  p + i);
    temp2 = read(threadId,  q + i);
    sum = temp1 + temp2;
    write(threadId, sum, r+i);
    if (DEBUG)
      printf("i=%d\tAddress A: %p\tAddress B: %p\tAddress C:  %p\t sum: %d\n", i, p+i, q+i, r+i, sum);
  }
}


// The threa does an elment-wise addition of two vectors A and B and puts the result in C. 
void Thread()
{
  int thread_id;

  int  *A = PhysicalBaseAddress;  // Array A  of SIZE  ints
  int  *B = PhysicalBaseAddress + SIZE;  // Array B  of SIZE ints immediately following A
  int  *C =  PhysicalBaseAddress + SIZE + SIZE;  // 1-d array of SIZE ints immediately following B
  

  thread_id = ActivityArgSize(ME) ;
  printf("Thread %d: Activated at time %5.2f\n", thread_id, GetSimTime());
  printf("Base address A: %p  Size: %d (ints)\n", A,  SIZE);
  printf("Base Address B: %p  Size: %d (ints)\n", B,  SIZE);
  printf("Base Address C: %p  Size: %d (ints)\n", C,  SIZE);


  initData(A, B, SIZE);  // Initialize A[i] = i+1; B[i] = i-1]. Bypass cache.
  vectorAdd(thread_id, A, B, C, SIZE); // C[i] = A[i] + B[i]
  //    displayVector("C", C, SIZE);   // Uncomment to display result vector C
  printStatistics(thread_id);
}



