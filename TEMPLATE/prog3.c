#include "def.h"
extern void displayVector(char *, int *, int);

// Global variables
unsigned PHYMEM[MEM_SIZE_INTS];
unsigned * PhysicalBaseAddress;  // Starting address for matrix A, A, B, C are contiguous in memory.


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
  int i, j;

  for (i=0; i < count; i++)
    for (j=0; j < count; j++)
      *(p + i*count + j) = i+j+1;  

  for (i=0; i < count; i++) 
    *(q+i) = -(i+1); 
}

void  matrixVectorMul(int threadId, int *p, int *q, int *r, int count) {
  int i, j, temp1,  temp2, sum;

  if (threadId != 0) 
    exit(1);

   for (i=0; i < count; i++) {
     for (j=0, sum = 0; j < count; j++) {
       temp1 = read(threadId,  p + i * count +j);
       temp2 = read(threadId,  q+j);
       sum += temp1*temp2;
     }
     write(threadId, sum, r+i);
     if (DEBUG)
       printf("C[%d] = %d\n", i, sum);
   }
}





// Thread multiples square matrix A with vector B to get vector C.
// A is a SIZE x SIZE matrox of ints and B, C are int vectors of size SIZE.

void Thread() {
  int thread_id;
  int i;
  int  *A = PhysicalBaseAddress;  // Matrix of f SIZE x SIZE ints
  int  *B = PhysicalBaseAddress + SIZE * SIZE;  // Vector of SIZE ints immediately following A
  int  *C = PhysicalBaseAddress + SIZE * (SIZE+1);  // Vector of SIZE ints  immediately following B


  thread_id = ActivityArgSize(ME) ;
  printf("Thread %d: Activated at time %5.2f\n", thread_id, GetSimTime());
  printf("A: %p Size: %d x %d  (ints)\n", A, SIZE, SIZE);  
  printf("B: %p Size: %d (ints)\n", B, SIZE);  
  printf("C: %p Size: %d (ints)\n", C, SIZE);  


  initData(A, B, SIZE);  // Initialize A[i][j] = i+j+1; B[i] = -(i+1)]. Bypass cache.
  matrixVectorMul(thread_id, A, B, C, SIZE); // C[i] = SUM_k (A[i][k] *  B[k])
  //     displayVector("C", C, SIZE);   // Uncomment to display result vector C
  printStatistics(thread_id);
  }

