## Superscalar Execution
1. Superscalar computing... a computer that handles more than one scalar (an integer). Superscalar computing allows a microprocessor to increase the number of instructions per clock that it completes beyond one instruction per clock.
2. An execution unit is a block of circuitry in the processor’s back end that executes a certain category of instruction (e.g. the ALU).
3. Scalars are values that have only one numerical component, and they’re best understood in contrast with vectors. Briefly, a vector is a multicomponent value, most often seen as an ordered sequence or array of numbers.
4. Two kinds of operation:
* Arithmetic operations are operations like addition, subtraction, multiplication, and division, all of which can be performed on any type of number.
* Logical operations are Boolean operations like AND, OR, NOT, and XOR, along with bit shifts and rotates. Such operations are performed on scalar and vector integers, as well as on the contents of special-purpose registers like the processor status word (PSW).
5. Some CPUs will have an integer ALU (Integer Unit) and a seperate floating-point ALU (FPU). 
> For instance, an integer execution unit (IU) is an ALU that executes integer arithmetic and logical instructions, a floating-point execution unit (FPU) is an ALU that executes floating-point arithmetic and logical instructions, and so on.
6. The load-store unit (LSU) is responsible for the execution of load and store instructions, as well as for address generation.
7. The branch execution unit (BEU) is responsible for executing conditional and unconditional branch instructions.
8. We can call the programmer-centric combination of a programming model (registers, etc.) and an instruction set (opcodes and operands) an instruction set architecture (ISA).
9. A particular processor’s hardware implementation of an ISA is generally referred to as that processor’s microarchitecture.
10. The ISA sits between the software and the hardware, providing a consistent interface to the software across hardware generations.
11. A microcode engine is sort of like a CPU within a CPU. It consists of a tiny bit of storage, the microcode ROM, which holds microcode programs, and an execution unit that executes those programs. The job of each of these microcode programs is to translate an instruction into a series of commands that controls the internal parts of the chip.
12. Neo-luddites came up with Reduced Instruction Set Computing (RISC), which tossed out features like the microcode engine to go up up up. Non-RISC ISAs featured richer, more complex instruction sets, they were labeled complex instruction set computing (CISC) ISAs in order to distinguish them from the new RISC ISAs.
> The x86 ISA (Intel) is the most popular example of a CISC ISA, while PowerPC, MIPS, and Arm are all examples of popular RISC ISAs.
13. Parallel arithematric instructions into superscalar computing has some limiations and hazards:
* Data hazards (e.g. one operation depending on the result of the last)
* Structural hazards (e.g. one processor doesn't share the same registers)
* Control hazards/branch hazards (i.e. hazards that arise when the processor arrives at a conditional branch and has to decide which instruction to fetch next)
14. In superscalar designs with a large number of registers, a CPU’s registers are grouped together into a unit called a register file (read ports and the write ports) -- with that interface also consisting of a data bus for transport and access. For one ALU, the register file needs two read ports and one write port.