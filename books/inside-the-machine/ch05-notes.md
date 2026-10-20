## Intel Pentium & Pentium Pro
* Intel officially discontinued and retired the Pentium brand in 2023.

1.  In fact, as a general rule of thumb, the faster the memory technology, the more it costs per unit of storage. As a result, computer system designers fill the speed gap by placing smaller amounts of faster, more expensive memory, called cache memory, in between main memory and the registers.

2. In most systems, there are multiple levels of cache between main memory and the registers:
* The level 1 cache (called L1 cache or just L1 for short) is the smallest, most expensive bit of cache, so it’s located the closest to the processor’s back end.
* Most PC systems have another level of cache, called level 2 cache (L2 cache or just L2), located between the L1 cache and main memory.
* Some systems even have a third cache level, L3 cache, located between the L2 cache and main memory.

3. When the processor needs a particular piece of code or data, it first checks the L1 cache to see if the desired item is present. If it is—a situation called a cache hit—it moves that item directly to either the fetch stage (in the case of code) or the register file (in the case of data). 

If the item is not present—a cache miss—the processor checks the slower but larger L2 cache. If the item is present in the L2, it’s copied into the L1 and passed along to the front end or back end. If there’s a cache miss in the L2, the processor checks the L3, and so on, until there’s either a cache hit, or the cache miss propagates all the way out to main memory.

4. The code half of the cache is often referred to as the instruction cache or I-cache, and the data half of the cache is referred to as the data cache or D-cache.

5.  The Pentium’s basic integer pipeline is five stages long, with the stages broken down as follows:
* Prefetch/Fetch Instructions are fetched from the instruction cache and aligned in prefetch buffers for decoding.
* Decode-1 Instructions are decoded into the Pentium’s internal instruction format using a fast set of hardware-based rules. Branch prediction also takes place at this stage.
* Decode-2 Instructions that require the microcode ROM are decoded here. Also, address computations take place at this stage.
* Execute The integer hardware ALU executes the instruction.
* Write-back The results of the computation are written back to the register file.

Addressing modes require extra address computations, and these computations are relegated to the decode-2 stage. The decode-2 stage is also where the Pentium’s microcode ROM kicks in. The Pentium decodes many x86 instructions directly in its decoding hardware.

6. Modern processors use a technique called speculative execution, which involves making an educated guess at which direction the branch will ultimately take and then beginning execution at the new branch target before the branch’s condition is actually evaluated. Instructions that are speculatively executed cannot write their results back to the register file until the branch condition is evaluated.

7. There are two main types of branch prediction: static prediction and dynamic prediction.

8. Dynamic branch prediction algorithms usually involve the use of both of two types of tables—the branch history table (BHT) and the branch target buffer (BTB).

9. A stack is a simple data storage structure commonly used by programmers and some scientific calculators to perform arithmetic. A stack is often called a FILO (first in,
last out) data structure (also LIFO). 

10. It was the stack’s utility for evaluating postfix arithmetic expressions that recommended it to the designers of the x87 floating-point unit (FPU), so they arranged the FPU’s eight floating-point registers as a stack.
