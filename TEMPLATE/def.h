#include <stdlib.h>
#include<stdio.h>
#include<math.h>
#include "sim.h"

#define TRUE 1
#define FALSE 0
#define NUM_THREADS 1

#define SIZE 128
#define DEBUG FALSE

// Memory Parameters
#define MEM_SIZE_BITS 24
#define MEM_SIZE_BYTES  (0x1 << MEM_SIZE_BITS)
#define MEM_SIZE_INTS (MEM_SIZE_BYTES/sizeof(int)) // Size in units of ints
#define MAX_DATA_SIZE  MEM_SIZE_INTS


// Cache Parameters
#define NUM_WAY_BITS 0
#define NUM_WAYS (0x1 << NUM_WAY_BITS)  // Cache Associativity

#define BLK_SIZE_BITS  5
#define  BLK_SIZE_BYTES   (0x1 << BLK_SIZE_BITS)  // Size in Bytes
#define  BLK_SIZE_INTS    (BLK_SIZE_BYTES/sizeof(int))  // Size in units of "ints"

#define CACHE_SIZE_BITS 8
#define  CACHE_SIZE_BYTES  (0x1 << CACHE_SIZE_BITS)  // Size in Bytes
#define  CACHE_SIZE_SETS   (CACHE_SIZE_BYTES/(NUM_WAYS * BLK_SIZE_BYTES))

// Timing Parameters
#define CLOCK_CYCLE 1.0
#define CACHE_LOOKUP_TIME 1.0
#define CACHE_TAGCHECK_TIME 1.0
#define CACHE_INSERT_TIME 1.0
#define MEM_CYCLE_TIME 50.0


struct cacheTagBlock {
  int V;
  int D;
  int TAG;
};

struct cacheDataBlock {
  int  BLKDATA[BLK_SIZE_INTS]; // Treating block as array of integers rather than bytes
};




