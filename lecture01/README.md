For example, ADD,

the first 6 numbers are code for operation,
2^6 = 64, so there are at most 64 commands.

the next 5 number is the address of rd,
5 for rs
and 5 for rt .

Totally 6+15 = 21 bits.

2^5 = 32, so the address are 5 bit numbers,
so there're at most 32 numbers in the register file?

and each number is 2^32, for unsigned
and 2^31 for sign, for example, int in java is from - 2^31 to 2^31.

---

ext(d) is to convert a 16 bit number to 32 bit.

so the number in memory is also 32 bits.

### why target address = PC + 4 + Extended(d)?

why pc + 4 rather than pc+1?

### several modules .


![](https://ws1.sinaimg.cn/large/006tNc79ly1fzn7lg532rj30jk08mjsg.jpg)

Register File,
like said before, is 32 numbers and each number is 32 bits.

Instruction Memory, fetch instruction according to the PC.

Data memory, the target if we use store, and the source if we use load.

each number in data memory is also 32 bit.

ALU, the place we calculate.

Decoder, decode the instruction into op-code, rs, rt, rd, and other number, offset.

Program Counter, the indicator of current instruction.
