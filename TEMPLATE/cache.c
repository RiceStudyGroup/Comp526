#include "def.h"

extern int cache_hits[], cache_misses[];
extern int cache_reads[], cache_writes[];
extern int cache_writebacks[];
extern unsigned * PhysicalBaseAddress;

extern struct cacheTagBlock    CACHE_TAG_ARRAY[CACHE_SIZE_SETS][NUM_WAYS];  
extern struct cacheDataBlock  CACHE_DATA_ARRAY[CACHE_SIZE_SETS][NUM_WAYS];  


extern  int usage[][NUM_WAYS];  // May be used to implement the pseudo LRU policy. You are free to ignore this variable.
// You could implement the binary tree in locations 1 through NUM_WAYS-1 of the array.
// Even though the hardware implementation would use only 1 bit for each tree entry (Left/Right), one can use an int
// for each tree node in the C simulation for simplicity.
// The array is initialized elsewhere.


/* ************************************************************************************/
// Code the Pseudo LRU (P-LRU) policy in the stub below. Comment out the provided RANDOM policy implementation (below) to test PLRU.

/*
getVictim(int index) {

 }
*/



// updateUsage is called on every Cache Hit to update the P-LRU history tree.
updateUsage(int index,int way) {
  // The arguments are: the set index and the way of the cache hit.
  // Set the nodes of tree along the path to the "way" appropriately.

  }
 
 





// The default replacement choice is RANDOM (choose any way of the set with equal probability).
getVictim(int index) {
  return drand48() * NUM_WAYS;
}


// Invoked on a cache miss. Finds a victim block in the specfied "way" to evict. Performs a writeback of the
// block to memory if the block is dirty. Reads the requested block from memory and installs it in the cache.
// Returns the "way" of the new block.

int  handleCacheMiss(int thread_id, unsigned *address, int cacheIndex, int *pway) {
    int way;
    int myCacheTag;
    unsigned *writebackAddress, *loadAddress;


    // 1. Call getVictim() to select  a "way" to evict (victim block)
   
    // 2. If the victim  block needs to be written back to memory
    //          Calculate the memory address of the block (block start address);use "writeBlock()" to do the writeback.
    //          Increment statistics variable "cache_writebacks[thread_id]"
    

    // 3. Compute the memory address of the block (block start address) to read; use "loadBlock()" to copy it from memory to cache.
 
    // 4.  Update the TAG, V, and D bits of the CACHE_TAG_ARRAY for this block.
 

 
    
    cache_misses[thread_id]++;  // Update statistics
    ProcessDelay(CACHE_INSERT_TIME);
    if (DEBUG) printf("Block installed in cache  Index : %d  Way: %d at time %5.2f\n", cacheIndex, way, GetSimTime());
    *pway = way;  // Returns the way of the newly read block
    return;
}


// Checks the cache for the cache block specified by "address". If found (hit) returns TRUE along with the cache index and way.
// If a cache miss, it calls "handleCacheMiss" to fetch the block from memory into the cache, and then returns FALSE.
// Lookup() will be called again and should have a hit this time.

int   LookupCache(int thread_id, unsigned *address, int *pcacheIndex, int *pway) {
    unsigned cacheIndex;
    int way;
    int myCacheTag;
    int cacheV, cacheTag;

    cacheIndex = ((unsigned) (((unsigned long) address >> BLK_SIZE_BITS))) % CACHE_SIZE_SETS;
    myCacheTag = (unsigned) (((unsigned long) address >> BLK_SIZE_BITS) / CACHE_SIZE_SETS);

  for (way=0; way < NUM_WAYS; way++) {
    cacheV = CACHE_TAG_ARRAY[cacheIndex][way].V;
    cacheTag = CACHE_TAG_ARRAY[cacheIndex][way].TAG;
    
    if ((cacheV == TRUE)  && (cacheTag == myCacheTag) ) {
	cache_hits[thread_id]++;
	if (DEBUG) 
	  printf("Cache HIT for Address: %p   Cache Index: %d at time %5.2f\n", address, cacheIndex, GetSimTime());
	ProcessDelay(CACHE_TAGCHECK_TIME);
	*pcacheIndex = cacheIndex;   // Return the cache Index of block
	*pway = way;  // Return the way of the block
	updateUsage(cacheIndex, way);  // Update the Pseudo-LRU data structure for the access
	return (TRUE);;
      }
  }
  // Cache Miss: Not found in any way of the cache
  ProcessDelay(CACHE_TAGCHECK_TIME);
  if (DEBUG) 
    printf("Cache MISS for Address: %p   Cache Index: %d at time %5.2f\n", address, cacheIndex, GetSimTime());
  handleCacheMiss(thread_id, address, cacheIndex, &way); // Get requested block into the cache
  return(FALSE);

}


// Called to write a word (int) of memory with "value" at the specified "address".
void write(int thread_id, int value, unsigned * address) {
  int cacheIndex, way;
  int byteOffset;

  if (DEBUG)   
    printf("\nWRITE Request at time %5.2f: Thread %d Value %d address: %p\n", GetSimTime(), thread_id, value, address);

  
  // Get cache index for request. LookupCache will handle a cache miss  before returning.
  while (LookupCache(thread_id, address, &cacheIndex, &way) == FALSE);
  
  // Write the word from the cache block at cacheIndex
  byteOffset = (long unsigned) address & ((1 << BLK_SIZE_BITS) - 1);
  CACHE_DATA_ARRAY[cacheIndex][way].BLKDATA[byteOffset/sizeof(int)] = value;
  CACHE_TAG_ARRAY[cacheIndex][way].D = TRUE;

  cache_writes[thread_id]++; 
 if (DEBUG)
    printf("WRITE completed at time %5.2f: Thread %d Value %d address: %p\n", GetSimTime(), thread_id, value, address);
}


// Called to read a word (int) of memory at the specified "address".
int read(int thread_id,  unsigned * address) {
  int cacheIndex, way;
  int byteOffset;
  int value;

  if (DEBUG)   
    printf("\nREAD Request at time %5.2f: Thread %d address: %p\n", GetSimTime(), thread_id, address);

  while (LookupCache(thread_id, address, &cacheIndex, &way) == FALSE);

  // We now have the "cacheIndex" and "way" of the requested block

  byteOffset = (unsigned long) address & ((1 << BLK_SIZE_BITS) - 1);
  value = CACHE_DATA_ARRAY[cacheIndex][way].BLKDATA[byteOffset/sizeof(int)]; // Always read word-sized (int) data
  cache_reads[thread_id]++;

    if (DEBUG)
      printf("READ completed at time %5.2f: Thread %d Value %d address: %p  byteOffset: %x\n", GetSimTime(), thread_id, value, address, byteOffset);
  return value;
}











