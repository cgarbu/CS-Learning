## Mechanics of Program Execution

1. Programs are stored in memory as sequential binary numbers, where mnemonics and register names map directly to specific bit patterns and opcodes (operation codes).

2. Machine instructions are organized into defined bit fields that designate the addressing mode, opcode, source operands, and destination registers or immediate values.

3. Memory instructions follow these binary layouts to execute loads and stores using immediate addresses, register addresses, or register-relative base-plus-offset addressing.

4. The programming model abstracts hardware into accessible resources, centered around general-purpose registers, the arithmetic logic unit, and the control unit.

5. The program counter holds the memory address of the next instruction to fetch, while the instruction register stores the instruction currently being decoded.

6. The processor executes code through a continuous fetch-execute loop that retrieves an instruction, advances the program counter, decodes the bit pattern, and executes.

7. An external system clock generates rhythmic pulses that synchronize the internal hardware through each phase of the fetch-execute cycle.

8. Branch instructions break sequential execution by loading a new target destination directly into the program counter.

9. Conditional branches inspect outcome flags stored in the processor status word (PSW), such as zero, negative, or overflow, to decide whether to take a jump. Arithmetic or comparison instructions may update these flags based on their results, and the processor's control logic evaluates them when executing a conditional branch. The CPU must know enough about the previous instruction's result to evaluate a branch (the flags are contained in the PSW).

10. Symbolic labels allow programmers to reference jump targets without hardcoding absolute addresses before the program is placed in a memory code segment.

11. Upon power-on, the CPU automatically executes hardwired bootstrap instructions from a read-only BIOS to verify system hardware and load the operating system.