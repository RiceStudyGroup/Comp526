## 1. what is pipelined processor?

## 2. what is ILP?

instruction level parallelsim.

## 3. what is DLX?

![](https://ws1.sinaimg.cn/large/006tNc79ly1fzk2ruluqnj30x0078q4v.jpg)

## 4. what is ALU?


## 5. what is ADD?

`ADD`

Example: ADD R2, R4, R5
R2 = R4+R5
![](https://ws4.sinaimg.cn/large/006tNc79ly1fzk2vxzx5aj315s08odh6.jpg)

All instructions are one word long, 32 bit aligned, then why op code 2 are in the purple position?

The 32-bit contents of registers rs and rt are added, and the sum is written to register rd.

[rd] = [rs] + [rt]
so rs is actually the address, actually what we are doing here is to add the number at rs and the number at rt and put the result to rd?

this will make sense why Integer.MIN_VALUE and Integer.MAX_VALUE are around 2**31.

## 6. what is ADDI?

![](https://ws4.sinaimg.cn/large/006tNc79ly1fzk33dqqr1j315c07kaay.jpg)

ADDI rt, rs, d | [rt] = [rs] + EXT(d)

ADDI R2, R4, 1000

EXT means extend,

![](https://ws3.sinaimg.cn/large/006tNc79ly1fzk341enwwj310e02i3zn.jpg)

The 16-bit value d is sign-extended to 32 bits and added to the 32-bit contents of register rs. The sum is written to register rt.

## 7. where is those numbers, for example, if rs point at a certain number, where is it?

Seems like in register.

## 8. what is LOAD?

![](https://ws2.sinaimg.cn/large/006tNc79ly1fzk364f8toj3174098dh5.jpg)

LW rt, d(rs) | ea = EXT(d) + (rs); (rt) = MEM[ea]


d = displacement also = offset?
ext(d) will convert d to be a sign-extended 32 bits number.

![](https://ws4.sinaimg.cn/large/006tNc79ly1fzk39q0dhoj30x004wjse.jpg)

so the address is at register[rs], and the real address is address+offset,
and the value at this real address will be read or write.

For the image above, the word at R2 will be loaded to R5,
the word in R5 will be stored to [1000 + register[R2]]

## 9. what is `ea`?

`ea` means effective address, i guess it's what I mean final address above.

## 10. what is BNEZ?

not equal to zero?



BEQZ rs, d(PC) | Go to Target Address if contents of register rs equals zero

![](https://ws3.sinaimg.cn/large/006tNc79ly1fzk3fo3zzdj30nc07eq3l.jpg)


d(PC)

go to target address, so this address is not a value but point to an instruction.

Target Address = PC + 4 + Extended(d)

![](https://ws3.sinaimg.cn/large/006tNc79ly1fzk5btf9r8j30i808kwfi.jpg)

The values are in data memory,
the instructions are in instruction memory.

some direct values are in register file,
if you want to load, you are load value from data memory to register file.

## 11. what are 5 stages

1. fetch, fetch instructions
2. decode instruction into register read
3. ALU operation
4. data memory read and write
5. write back to register.


IF instruction fetch
ID instruction decode
EX execute
MEM memory read and write
WB write back to register.

## 12. functional units

## 13. what is IPC?

instructions per cycle

CPI cycles per instruction.

## 14. how do we improve performance?

increase frequency
increase IPC?

each stage takes 1 clock cycle.

![](https://ws1.sinaimg.cn/large/006tNc79ly1fzk5pu137kj317y04k0sq.jpg)

is the time between two read stuff a cycle?

## 15. what is hazard?



---
