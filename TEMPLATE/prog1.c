#include "def.h"
extern void displayVector(char *, int *, int);


// Global variables
unsigned PHYMEM[MEM_SIZE_INTS];
unsigned * PhysicalBaseAddress; // Array A will begin at this address

struct cacheTagBlock    CACHE_TAG_ARRAY[CACHE_SIZE_SETS][NUM_WAYS];  
struct cacheDataBlock  CACHE_DATA_ARRAY[CACHE_SIZE_SETS][NUM_WAYS];  
int usage [CACHE_SIZE_SETS][NUM_WAYS]; // Can be used to implement pseuso-LRU eviction policy

// Cache Statistics
int cache_hits[NUM_THREADS], cache_misses[NUM_THREADS];
int cache_reads[NUM_THREADS], cache_writes[NUM_THREADS];
int cache_writebacks[NUM_THREADS];

// Yacsim Simulator-related variables
PROCESS *proccntrl;






void UserMain(int argc, char *argv[])
{
  int i, j;
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


initData(int *p, int count) {
  int i;

  for (i=0; i < count; i++)
    *(p + i) = i+1;   
}

int findSum(int threadId, int *p, int count) {
  int i, temp,  sum;

 if (threadId != 0) 
   exit(1);

   for (i=0, sum = 0; i < count; i++) {
     temp = read(threadId,  p + i); // Caches data
     sum += temp;
     if (DEBUG)
       printf("i=%d Address of element = %p sum: %d\n", i, p+i, sum);
   }
   return sum;
}



// Thread computes sum of the integer elements of array A[] starting at PhysicalBaseAddress.
// The number of elements is SIZE  and the array is initialized sothat A[i] = i+1;
void Thread()
{
  int thread_id;
  int sum;
  int  *A = PhysicalBaseAddress;  // 1-d array A of SIZE ints
  

  thread_id = ActivityArgSize(ME) ;
  printf("Thread %d: Activated at time %5.2f\n", thread_id, GetSimTime());
  printf("Base address of array A: %p  Array size (ints): %d \n", A,  SIZE);  


  initData(A, SIZE);  // Initialize A[i] = i+1; Bypasses  the  cache.
  sum = findSum(thread_id, A, SIZE); // Computes sum of A[0] to A[SIZE-1]
  printf("Array Sum: %d\n", sum);
  printStatistics(thread_id);
}


