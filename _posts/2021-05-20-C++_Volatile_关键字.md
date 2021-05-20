---
layout: post
title: C++ volatile 关键字
---

> 转载[C/C++ 中 volatile 关键字详解](https://www.runoob.com/w3cnote/c-volatile-keyword.html)

## 1. 为什么使用 volatile?

C/C++ 中的 volatile 关键字和 const 对应，用来修饰变量，通常用于建立语言级别的 memory barrier。这是 BS 在 "The C++ Programming Language" 对 volatile 修饰词的说明：

> A volatile specifier is a hint to a compiler that an object may change its value in ways not specified by the language so that aggressive optimizations must be avoided.

volatile 关键字是一种类型修饰符，用它声明的类型变量表示可以被某些编译器未知的因素更改，比如：操作系统、硬件或者其它线程等。因此，遇到这个关键字声明的变量，编译器对访问该变量的代码就不能再进行优化，从而可以提供对特殊地址的稳定访问。声明时语法：`int volatile vInt;` 当要求使用 volatile 声明的变量值的时候，系统总是重新从它所在的内存读取数据，即使它前面的指令刚刚从该处读取过数据。而且读取的数据立刻被保存。例如：

```c++
volatile int i = 10; 
int a = i;

...

// 其他代码，并未明确告诉编译器，对 i 进行过操作；
int b = i;
```

volatile 指出 i 是随时可能发生变化的，每次使用它的时候必须从 i的地址中读取，因而编译器生成的汇编代码会重新从i的地址读取数据放在 b 中。而优化做法是，由于编译器发现两次从 i读数据的代码之间的代码没有对 i 进行过操作，它会自动把上次读的数据（例如从 a 中读到的数据）放在 b 中。而不是重新从 i 里面读。这样以来，如果 i是一个寄存器变量或者表示一个端口数据就容易出错，所以说 volatile 可以保证对特殊地址的稳定访问。下面通过插入汇编代码，测试有无 volatile 关键字，对程序最终代码的影响，输入下面的代码：

```c
#include <stdio.h> 

void main() {
  int i = 10;
  int a = i;

  printf("i = %d", b);

  // 下面的汇编的作用就是改变内存中 i 的值
  // 但是又不让编译器知道
  __asm {
    mov dword ptr [ebp-4], 20h
  } 
  
  int b = i;
  printf("i = %d", b);
}
```

然后，在 Debug 模式运行程序，输出结果如下：

```
i = 10
i = 32
```

然而，在 Release 模式运行程序，输出结果如下：

```
i = 10
i = 10
```

输出的结果明显表明，Release 模式下，编译器对代码进行了优化，第二次没有输出正确的 i 值。下面，我们把 i 的声明加上 volatile 关键字，看看有什么变化：

```C 
#include <stdio.h>
 
void main() {
  volatile int i = 10;
  int a = i;
 
  printf("i = %d", a);
  __asm {
    mov dword ptr [ebp-4], 20h
  }
 
  int b = i;
  printf("i = %d", b);
}
```

分别在 Debug 和 Release 模式运行程序，结果都是：

```c
i = 10
i = 32
```

这说明这个 volatile 关键字发挥了它的作用。其实不只是**内嵌汇编操纵栈**这种方式属于编译无法识别的变量改变，另外更多的可能是多线程并发访问共享变量时，一个线程改变了变量的值，怎样让改变后的值对其它线程 visible。一般说来，volatile 用在如下的几个地方： 

- 中断服务程序中修改的供其它程序检测的变量需要加 volatile； 
- 多线程间被几个任务共享的变量；
- 状态寄存器一类的并行设备硬件寄存器，因为每次对它的读写都可能有不同的意义。

## 2. volatile 指针

和 const 修饰词类似，const 有常量指针和指针常量的说法， volatile 也有相应的概念：

修饰由指针指向的对象，数据是 const 或者 volatile 的：

```c
const char* cpch;
volatile char* vpch;
```

指针自身的值——一个代表地址的整数变量，是 const 或 volatile 的：

```c
char* const pchc;
char* volatile pchv;
```

**注意：**

- 除了基本类型外，对用户定义类型也可以用volatile类型进行修饰。 
- 可以把一个非volatile int赋给volatile int，但是不能把非volatile对象赋给一个volatile对象。 

此外，基本类型的对象用volatile修饰后，仍旧支持所有的操作（加、乘、赋值等）。但是，用户定义的非基本类型（class、struct、union）的对象被volatile修饰后，具有不同行为： 

- 只能调用 volatile 成员函数，即只能访问它的接口的子集；
- 只能通过 const_cast 运算符转为没有 volatile 修饰的普通对象，即由此可以获得对类型接口的完全访问；
- volatile 性质会传递给它的数据成员；

## 3. 多线程下的 volatile

有些变量是用 volatile 关键字声明的。当两个线程都要用到某一个变量且该变量的值会被改变时，应该用 volatile 声明，该关键字的作用是防止优化编译器把变量从内存装入 CPU 寄存器中。如果变量被装入寄存器，那么两个线程有可能一个使用内存中的变量，一个使用寄存器中的变量，这会造成程序的错误执行。volatile 的意思是让编译器每次操作该变量时一定要从内存中真正取出，而不是使用已经存在寄存器中的值，如下： 

```c++
volatile bool bStop = false;
```

(1) 在一个线程中：

```c++
while(!bStop) { ... }
bStop = false;
return;
```

(2) 在另一个线程中，要终止上面的线程循环：

```c++
bStop = true;
while(bStop);
// 等待上面的线程终止，如果 bStop 不使用 volatile 申明，那么这个循环将是一个死循环
// 因为 bStop 已经读取到了寄存器中，寄存器中 bStop 的值永远不会变成 FALSE
// 加上volatile，程序在执行时，每次均从内存中读出 bStop 的值，就不会死循环了
```

这个关键字是用来设定某个对象的存储位置在内存中，而不是寄存器中。因为一般的对象编译器可能会将其拷贝放在寄存器中用以加快指令的执行速度，例如下段代码中：

```c++
int nMyCounter = 0;
for (; nMyCounter < 100; nMyCounter++) {

}
```

在此段代码中，nMyCounter 的拷贝可能存放到某个寄存器中（循环中，对 nMyCounter 的测试及操作总是对此寄存器中的值进行），但是另外又有段代码执行了这样的操作：nMyCounter -= 1; 这个操作中，对 nMyCounter 的改变是对内存中的 nMyCounter 进行操作，于是出现了这样一个现象：nMyCounter 的改变不同步。
