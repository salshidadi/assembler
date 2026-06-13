# Minimal Custom Assembler

A lightweight, fast, and dependency-free custom assembler written in C. This tool reads human-readable assembly instructions (`.zasm` files) and translates them into a simplified comma-separated machine code format (`.zx` files) for a custom Virtual Machine architecture.

## Features
* **Memory Efficient:** Processes files line-by-line using stack-based buffers (`fgets`) instead of loading the entire file into the heap, keeping RAM usage flat regardless of file size.
* **Flexible Syntax:** Automatically strips trailing commas and ignores formatting inconsistencies (e.g., `ADD 9, 7` and `ADD 9 7` are parsed identically).

## Supported Instruction Set

| Mnemonic | Opcode | Description |
| :--- | :--- | :--- |
| `ADD`, `SUB`, `MUL`, `DIV`, `MOD` | `0` - `4` | Standard arithmetic operations. |
| `STP` | `5` | Stop/Halt execution. |
| `LDI`, `ADR`, `SUR`, `INC`, `DEC` | `6` - `10` | Register loading and manipulation. |
| `JMP`, `CMP`, `JE` | `11` - `13` | Control flow and comparisons. |
| `STI` | `14` or `15` | Store Instruction (14 for direct memory, 15 for registers). |
| `LDM` | `15` | Load from memory. |
| `PUSH`, `POP` | `16`, `17` | Stack operations. |

*(Note: Registers are defined as `R0` through `R3` and are parsed directly into their numeric equivalents 0-3).*

## File Formats

### Input: `example.zasm`
The assembler expects standard opcode followed by up to two operands.
```assembly
ADD 9, 7
LDI R2, 77
JMP 45
STI 0, 17
STI R3, 0
PUSH 22
POP R2
STP 0
