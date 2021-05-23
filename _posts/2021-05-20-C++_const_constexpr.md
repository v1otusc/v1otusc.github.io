---
layout: post
title: const 与 constexpr
---

## 1. 运行期常量与编译期常量的通俗理解

编译期是编译器将你写的代码和资源文件链接编译成可执行文件的这一过程。运行期是运行前面编译期生成的可执行文件的过程。

运行期常量(const 修饰)从一开始就存在，而编译期常量( constexpr 修饰)在 C++11 标准之后才加入。const 修饰的运行期常量，会在运行编译完成后的代码时，先在内存的 **常量区** 开辟空间存放常量的值，以确保常量值不可变，保证程序的正确性。

而编译期常量是由编译器在编译时通过计算来确定常量的值，然后在代码中直接进行替换，类似于 #define MAX 5 在编译时将代码中所有的MAX替换成5一样，就不需要在后面的运行时再在内存上开辟空间存放常量，以达到优化的效果。

## 2. const 变量

const 修饰变量，表示这个变量是不可修改，const 变量必须初始化，一经初始化就不可修改：

- 编译时初始化
- 运行时初始化

在编译时，可以使用编译时常量来初始化 const 变量：

```c++
const int size = 100;
```

那么，由于 SIZE 的值是在编译时就已经确定的，编译器会使用常量 100 来替代程序中出现的 SIZE。而另一方面，const 变量也可以运行时才初始化：

```c++
vector<int> v;
const int i = v.size();
```

## 3. constexpr 变量

const 变量的值可以在编译时或运行时确定，与 const 相比，constexpr 的限制更多，因为 constexpr 变量的值必须在编译时就能确定。

在一些场合之下，变量的值要求是编译期就必须确定的，constexpr变量正好满足要求：

- 数组的大小必须是编译器常量
- std::array的大小必须是编译期常量
- std::bitset的大小必须是编译期常量

```c++
constexpr int SIZE = 100;
std::array<int, SIZE> arr;
```

## 4. constexpr 函数

constexpr 函数则与编译期计算有关，要是 constexpr 函数所使用的变量其值能够在编译时就确定，那么 constexpr 函数就能在编译时执行计算。另一方面，要是 constexpr 函数所使用的变量其值只能在运行时确定，那么 constexpr 就和一般的函数没区别。

C++11 要求 constexpr 函数不能多于一条语句，碰到 if-else 语句时，只能使用条件操作符来替代：

```c++
constexpr unsigned long long fib( unsigned n ) {
  return ( n == 0 || n == 1 ? n : fib( n - 1 ) + fib( n - 2 ) );
}
```

C++14 则放松了这个要求：

```c++
constexpr unsigned long long fib( unsigned n )
{
  if( n == 0 || n == 1 ) {
    return n;
  } else {
    return fib( n - 1 ) + fib( n - 2 );   
  }
}
```

要是我们传递一个编译时常量给 fib()，那么 fib() 在程序编译的时候就已经执行好了。代价是增加编译时间，但程序能执行得更高效。

----

但是，定义 constexpr 变量的时候，变量的类型只能是基本数据类型、指针和引用，而不能是其它类型。

```c++
// error: constexpr variable cannot have non-literal type
constexpr string str = "hello";
```

但是，我们自己定义的类型却没有这个限制，因为构造函数和成员函数可以是 constexpr 函数：

```c++
class Point {
 public:
  constexpr Point(double x = 0, double y = 0) : x_(x), y_(y) {}

  constexpr double x() const noexcept { return x_; }
  constexpr double y() const noexcept { return y_; }
  void set_x(double x) noexcept { x_ = x; }
  void set_y(double y) noexcept { y_ = y; }

 private:
  double x_, y_;
};
```

要是我们使用编译期常量来初始化 Point 对象，那么，在编译的时候编译器就已经创建了这个对象：

```c++
constexpr Point pt( 10, 20 );     // Evaluate at compiling time
```

另一方面，注意到成员函数也可以是 constexpr 的，也就是说：

```c++
constexpr Point addTwoPoint(const Point &pt1, const Point &pt2) {
  return {pt1.x() + pt2.x(), pt1.y() + pt2.y()};
}
// ...
constexpr Point pt1(10, 20);
constexpr Point pt2(20, 10);
constexpr auto add = addTwoPoint(pt1, pt2);
```

要是 pt1 和 pt2 是 constexpr 变量，那么，addTwoPoint()这个函数会在编译时就执行。
