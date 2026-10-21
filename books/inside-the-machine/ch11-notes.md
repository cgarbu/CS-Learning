## Caching and Performance 

1. The L1 can be accessed very quickly by the CPU, so it’s a good place to keep the code and data that the CPU is most likely to request.
* The L1’s quick access time is a result of the fact that it’s made of the fastest and most expensive type of static RAM, or SRAM.
* If data that the CPU needs is not in the L1 -- a situation called a cache miss happens.

2. A series of caches, starting with the page file on the hard disk (the lumber-yard) and going all the way up to the registers on the CPU (the workshop’s work benches), is called a cache hierarchy. As you go up the cache hierarchy towards the CPU, the caches get smaller, faster, and more expensive to implement; conversely, as you go down the cache hierarchy, the caches get larger, cheaper, and much slower.

3. A compulsory miss is a cache miss that occurs because the desired data was never in the cache and therefore must be paged in for the first time in a program’s execution.

4. Caching works because of a very simple property exhibited to one degree or another by all types of code and data: locality of reference. We generally find it useful to talk about two types of locality of reference: spatial locality and temporal locality.
* Spatial locality is a fancy label for the general rule that if the CPU needs an item from memory at any given moment, it’s likely to need that item’s neighbors next.
* Temporal locality is the name we give to the general rule that if an item in memory was accessed once, it’s likely to be accessed again in the near future.
Depending on the type of application, both code and data streams can exhibit spatial and temporal locality.

5. A group of related blocks of code and/or data that the CPU uses and reuses over a period of time in order to complete a task is called a working set.

6. The code half of the cache is called the instruction cache, or I-cache, while the data half of the cache is called the data cache, or D-cache.

7. When the CPU requests a particular piece of data from the memory subsystem, that piece gets fetched and loaded into the L1 along with some of its nearest neighbors. The actual piece of data that was requested is called the critical word, and the surrounding group of bytes that gets fetched along with it is called a cache line or cache block.

8. Cache designers can choose from a few different schemes for governing which RAM blocks can be stored in which of the cache’s block frames. Such a scheme is called a cache placement policy, because it dictates where in the cache a block from memory can be placed.

9. When the CPU requests a byte from a particular block from RAM, it needs to be able to determine three things very quickly:
* whether or not the needed block is actually in the cache (i.e., whether there is a cache hit or a cache miss)
* the location of the block within the cache (in the case of a cache hit)
* the location of the desired byte (or critical word) within the block (again, in the case of a cache hit)
A cache accommodates all three needs by associating a special piece of memory—called a tag—with each block frame in the cache. The tag holds information about the blocks currently being stored in the frame, and that information allows the CPU to determine the answer to all three of the questions above.

Tags are stored in a special type of memory called the tag RAM. This memory has to be made of very fast SRAM because it can take some time to search it in order to locate the cache block.

10. The most conceptually simple scheme for mapping RAM blocks to cache block frames is called fully associative mapping. Under this scheme, any RAM block can be stored in any available block frame. Another, more popular way of organizing the cache is to use direct mapping. In a direct-mapped cache, each block frame can cache only a subset of the blocks in main memory.

11. Note that the kind of situation described here, where the CPU would like to store multiple blocks but it can’t because they all require the same frame, is called a collision.

12. One way to get some of the benefits of direct-mapped caches while lessening the amount of cache space wasted due to collisions is to restrict the caching of main memory blocks to a subset of the available cache frames. This technique is called set associative mapping, and a few popular implementations of it are described below:
* Four-Way Set Associative Mapping: caches blocked into 4s.
* Two-Way Set Associate Mapping: cahces blocked into 2s. 
Though a two-way cache’s latency is less than that of a four-way cache, its number of potential collisions (and hence its miss rate) is higher.

13. Caches can increase the amount of benefit they derive from temporal locality by implementing an intelligent replacement policy (also called, conversely, an eviction policy). A replacement policy dictates which of the blocks currently in the cache will be replaced by any new block that gets fetched in. 
> The optimal replacement policy that doesn’t involve predicting the future is to evict the block that has gone the longest period of time without being used, or the least recently used (LRU) block. The logic here is that if a block hasn’t been used in a while, it’s less likely to be part of the current working set than a block that was more recently used.

14. Write-through vs. write-back (write to both L1 and main memory vs. write to L1). A "dirty bit" flag is used to track modifications. 