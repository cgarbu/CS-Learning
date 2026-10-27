## Pipelined Execution

1. A computer repeats three basic steps over and over again in order to execute a program:
* Fetch the next instruction from the address stored in the program counter and load that instruction into the instruction register. Increment the program counter
* Decode the instruction in the instruction register (look at opcodes, what operation to perform with operands)
* Execute the instruction in the instruction register (and then read, add, write... write-back... store the result in a register or memory, as appropriate) 

2. Fetch, decode, execute, write.

3. Front end (fetch, decode) -> Back end (ALU(execute), write)

4. Working definition of pipelining: 
> Pipelining makes more efficient use of the CPU’s existing resources by putting all of its units to work simultaneously, thereby allowing it to do more total work each nanosecond (by use of staging)

5. Key takeaway: One processor performs better than another if it executes all of a program’s instructions in a shorter amount of time, so reducing program execution time is the key to increasing processor performance.

6. A more common performance metric in the real world is a pipeline’s instruction throughput, or the number of instructions that the processor completes each clock cycle.

7. Instruction throughput is the number of instructions that the processor finishes executing on each clock cycle. You’ll also see instruction throughput referred to as instructions per clock (IPC).

8. Pipeline stalls, or "bubbles," can effect instruction throughput. 

9. An instruction’s latency is the number of clock cycles it takes for the instruction to pass through the pipeline. For example, in a single-cycle processor, all instructions have a latency of one clock cycle (not particularly a fixed number).

10. The clock pulse that coordinates all pipeline stages can be no faster than the pipeline’s slowest stage. In other words, the amount of time it takes for the slowest stage in the pipeline to complete will determine the length of the CPU’s clock cycle and thus the length of every pipeline stage.

11. Pipeline stalls and refills must be avoided.