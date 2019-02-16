# scoreboard architecture.


## 1. what is scoreboard architecture?

## 2. what are data hazards?

## 3. when should we stall the issue? what does issue stalls mean?


We should stall the issue when their is a dependency, WAW or WAR, with an in-flight instruction.

write after write WAW
write after read WAR


## 4. what does causal relationship mean?

causal 1. 因果 /ˈkôzəl/
casual 1. 随便 2. 漫不经心

`WAR dependency is not a true causal relationship`, what does this mean?

![](https://ws1.sinaimg.cn/large/006tKfTcly1g07u31817aj31860pygrr.jpg)

artifact 1. 人工品

artifact of using the same storage location,
does this mean, this is caused we used the same name and storage for this variable.
if we use different registers, we can avoid WAR dependency.

![](https://ws1.sinaimg.cn/large/006tKfTcly1g07u0p5181j314s0omq77.jpg)

for example, if we rename Q1 to be Q2 in step C, then B and C will not have dependency.

in the first image, C have to wait for B, because C try to write something into Q1, if we use different name, then C don't need to wait for B, because we will write the result to other place.

![](https://ws4.sinaimg.cn/large/006tKfTcly1g07u86wvcdj31r00hsdjp.jpg)

So the idea here is that ** use another register can avoid Write after Read Dependency.**



---

## Page 6,

RAW hazard is causal dependency,

![](https://ws4.sinaimg.cn/large/006tKfTcly1g07ucpwfgaj31120am40b.jpg)




** No WAW dependence if different destination registers used. **

Other wise, the second write will cover the first write.




## 5. what is SSA? static single assignment?


all variables assigned to only once, this is not we do in this slide, we used other variable to avoid some dependency

** <font color=blue>idealized goal, every instruction writes to a different register, which can completely avoid WAR and WAW dependency.
</font>**


and we want to do this use a finite set of registers. to approximate this ideal!

---

## Page 10/51

Renaming, dynamic binding of architectural (name) to physical register storage location,

maintain map between architectural and physical register.

![](https://ws1.sinaimg.cn/large/006tKfTcly1g07uu7fkopj313m0u078w.jpg)

so by using a free register list , when we want to write, fetch a location from this list, and write the result to this location.


## 6. what is retirement stage?

![](https://ws3.sinaimg.cn/large/006tKfTcly1g07uybqhh5j313y0rigo5.jpg)

so rename is happen in issue, when we decode the instruction and determine if we should use a new variable to write our result.

## 7. some benefits and problems of this?

![](https://ws2.sinaimg.cn/large/006tKfTcly1g07v0khuvqj31c10u0gre.jpg)

## 8. rename source register?

above this, what we did is to rename the destination register, so we will write the result to other places.

But here we want to rename source register? why?

we will skip this until we find this is useful.

[24/51]

![](https://ws2.sinaimg.cn/large/006tKfTcly1g0854rpx55j31420u0age.jpg)

 copy those what we need to use to T_

 ![](https://ws4.sinaimg.cn/large/006tKfTcly1g0860n76q7j30pk040t9p.jpg)


## 9. How can we know a register value is stable or a future value?

 ![](https://ws3.sinaimg.cn/large/006tKfTcly1g0863snxooj314k0u0th6.jpg)



![](https://ws2.sinaimg.cn/large/006tKfTcly1g0865rg72jj30fo09e74v.jpg)

![](https://ws3.sinaimg.cn/large/006tKfTcly1g086676903j313q0fi76d.jpg)

Each issued instruction is allocated a Reservation Station slot A is allocated RS index 0
so 0 is for A
1 is for B
2 is for C.

![](https://ws2.sinaimg.cn/large/006tKfTcly1g08671v2wej30zn0u0gpg.jpg)

## 10. what do we do with RS?

![](https://ws2.sinaimg.cn/large/006tKfTcly1g08btuwvbsj318a0u07an.jpg)

## 11. what is functional unit?

In computer engineering, an execution unit (also called a functional unit) is a part of the central processing unit (CPU) that performs the operations and calculations as instructed by the computer program.

so RS will dispatch operation to free functional unit when the operand are ready and free functional unit are available.


![](https://ws4.sinaimg.cn/large/006tKfTcly1g08ck9eig7j31d608wjt5.jpg)


![](https://ws1.sinaimg.cn/large/006tKfTcly1g08cmillipj31940ictbg.jpg)

for example, the result of DIVD is 25, and we want to write it to F0, then we need to update TAG=F0 to be 25 as well.

![](https://ws1.sinaimg.cn/large/006tKfTcly1g08cnub6cpj30rq0zmadh.jpg)

Also Tag is not True for F0 anymore.

After these three operation are executed, the RS becomes empty again.

![](https://ws4.sinaimg.cn/large/006tKfTcly1g08col6b8xj31240lumz9.jpg)

## 11. what if two operation will update F0

![](https://ws3.sinaimg.cn/large/006tKfTcly1g08csr5ggmj313a0i8mzf.jpg)





















































---
