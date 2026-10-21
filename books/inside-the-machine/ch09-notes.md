## 64-bit Computing and x86-64 

1. Explicitly Parallel Instruction Computing (EPIC) is a mix of a very long instruction word (VLIW) ISA, predication, speculative loading, and other compiler-oriented techniques.

2. The labels 16-bit, 32-bit, or 64-bit, when applied to a microprocessor, characterize the processor’s data stream.
* In more specific terms, the labels 64-bit, 32-bit, and so on designate the number of bits that each of the processor’s general-purpose registers (GPRs) can hold.
* The data stream has doubled in size, but the instruction stream has not.
* The Program Counter also typically doubles in size on a 64-bit ISA. 
* Increased dynamic range (numerical representations).

3. Some applications, mostly in the realm of scientific computing and simulations, require 64-bit integers because they work with numbers outside the dynamic range of 32-bit integers. When the magnitude of the result of a calculation exceeds the range of possible integer values that the machine can represent, you get a situation called either overflow (the result was greater than the highest positive integer) or underflow (the result was less than the largest negative integer). When this happens, the number you get in the register isn’t the right answer.

4. Programmers who run into integer overflow or underflow problems on a 32-bit platform have the option of using a 64-bit integer construct provided by a high-level language like C. In such cases, the compiler uses two registers per integer—one for each half of the integer—to do 64-bit calculations in 32-bit hardware.

5. Larger general-purpose registers (GPRs) don’t just make for larger integers, but they make for larger addresses, as well. In fact, larger addresses are the primary advantage that 64-bit computers have over their 32-bit counterparts.

6. Every major component in a computer system must have an address. A range of addresses is called an address space.

7. A range of addresses is called an address space, and in a modern 32-bit desktop computer system, the processor and operating system work together to provide each running program with the illusion that it has access to a flat address space of up to 4GB in size. One large portion of this virtual address space that a running program sees consists of addresses through which it can interact with the operating system, and through the OS with the other parts of the system. The other portion of the address space is set aside to interact with main memory.

8. Full binary compatibility with existing x86 code, both 32-bit and older 16-bit flavors, is one of x86-64’s greatest strengths. x86-64 accomplishes this using a nested series of modes. The first and least interesting mode is legacy mode. Long mode provides two submodes—64-bit mode and compatibility mode—in which the OS can run either x86-64 or vanilla x86 code. 