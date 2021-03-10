---
layout: post
title: cpp_functor
---

# 仿函数

<!-- TOC -->

- [仿函数](#仿函数)
  - [1. 仿函数的定义](#1-仿函数的定义)
    - [为什么要有仿函数](#为什么要有仿函数)
  - [2. 函数适配器（函数配接器）](#2-函数适配器函数配接器)
  - [3. 预先定义的仿函数](#3-预先定义的仿函数)
  - [4. 预定义的函数适配器](#4-预定义的函数适配器)
  - [5. 仿函数(以及函数适配器)的使用示例](#5-仿函数以及函数适配器的使用示例)
    - [5.1 查找 25 或者 35 第一次出现的位置](#51-查找-25-或者-35-第一次出现的位置)
    - [5.2 将集合中全部元素设为相反值](#52-将集合中全部元素设为相反值)
    - [5.3 对集合所有的元素求平方](#53-对集合所有的元素求平方)
    - [5.4 所有元素乘以 10](#54-所有元素乘以-10)
    - [5.5 将a替换为b](#55-将a替换为b)
    - [5.6 删除小于50的元素](#56-删除小于50的元素)
    - [5.7 返回第一个偶数](#57-返回第一个偶数)
    - [5.8 调整数组顺序，使得奇数位于偶数前面](#58-调整数组顺序使得奇数位于偶数前面)
    - [5.9 mem_fun_ref 与mem_fun 的区别以及用法](#59-mem_fun_ref-与mem_fun-的区别以及用法)
    - [5.10 ptr_fun](#510-ptr_fun)

<!-- /TOC -->

> [https://www.cnblogs.com/wuchanming/p/4411867.html](https://www.cnblogs.com/wuchanming/p/4411867.html)

## 1. 仿函数的定义

《C++标准程序库》里对仿函数的解释是：仿函数是泛型编程强大威力和纯粹抽象概念的又一例证。你可以说，任何东西，只要其行为像函数，它就是一个函数。因此如果你定义了一个对象，行为像函数，它就可以被当做函数来用。那么，什么才算具备函数行为呢？所谓函数行为，是指可以"使用小括号传递参数，籍以调用某个东西"。例如：

```c++
function(argc1, argc2);
```

如果你指望对象也可以如此这般，就必须让它们也可以被"调用"——通过小括号的运用和参数的传递。你只需要定义operator()，并给予合适的参数型别：

```c++
class X 
{
public:
  // define 'function call' operator
  return-value operator()(arguments) const;
    ......
};
```

现在，你可以把这个类别的对象当做函数来调用了：

```c++
X fo;

......

// call operator () for function object to
fo(argc1, argc2);
```

上述调用等价于：

```c++
fo.operator() (argc1, argc2);
```

总结如下：

- 函数对象是一个普通对象；
- 重载了 operator() 操作符；
- 函数对象一般都比较简单，主要用到operator()操作，其他成员函数和成员变量都是为operator()服务。

为了帮助理解仿函数，我们来看一个例子：

```c++
#include <algorithm>
class gen_by_two {
public:
  gen_by_two(int seed = 0) : _seed( seed ){}
  int operator()() { return _seed += 2; }
private:
  int _seed;
};
vector<int> ivec( 10 );

// fills ivec: 102 104 106 108 110 112 114 116 118 120
generate_n( ivec.begin(), ivec.size(), gen_by_two(100) );
// 或者
generate_n( ivec.begin(), ivec.size(), gen_by_two());
```

### 为什么要有仿函数

如果编程者要将某种“操作”当做算法的参数(假设我们现在有一个数组，数组中存有任意数量的数字，我们希望能够统计出这个数组中大于 10 的数字的数量)，一般有两种方法：
- 一个办法就是先将该“操作”设计为一个函数，再将函数指针当做算法的一个参数。
- 将该“操作”设计为一个仿函数（就语言层面而言是个 class），再以该仿函数产生一个对象，并以此对象作为算法的一个参数。

很明显第二种方法会更优秀，因为第一种方法扩展性较差，当**函数参数**有所变化，则无法兼容旧的代码。在我们写代码时有时会发现有些功能代码，会不断地被使用。为了复用这些代码，实现为一个公共的函数是一个解决方法。不过函数用到的一些变量，可能是公共的全局变量。引入全局变量，容易出现同名冲突，不方便维护。这时就可以使用仿函数了，写一个简单类，除了维护类的基本成员函数外，只需要重载 operator() 运算符。这样既可以免去对一些公共变量的维护，也可以使重复使用的代码独立出来，以便下次复用。而且相对于函数，仿函数还可以进行依赖、组合与继承等，这样有利于资源的管理。

## 2. 函数适配器（函数配接器）

函数适配器又称"函数配接器"，是只能够将仿函数和另一个仿函数（或某个值，或某一个函数）结合起来的仿函数。函数适配器声明于\<functional\>中。

```c++
find_if(coll.begin(), coll.end(), // range
        bind2nd(greater<int>(), 42)); // criterion
```

其中表达式bind2nd(greater<int>(),42) 导致一个组合型的仿函，检查某个 int 值是否大于 42。实际上 bind2nd 是将一个二元仿函数转换为一个一元仿函数。bind2nd 的意思就是将 42 作为比较(greater<int>())函数的第二个参数，也就相当于是 elem.value > 42，如果容器中没有 42 这个值，那么下面这条语句和上面的语句是一样的。

> 什么叫容器中没有 42 这个值，就是不必考虑等于的情况；

```c++
find_if(coll.begin(), coll.end(), //range
        bind1st(less<int>(), 42)); // criterion
```

## 3. 预先定义的仿函数

![](https://raw.githubusercontent.com/v1otusc/PicBed/master/%E9%A2%84%E5%AE%9A%E4%B9%89%E4%BB%BF%E5%87%BD%E6%95%B0.png
)

## 4. 预定义的函数适配器

![](https://raw.githubusercontent.com/v1otusc/PicBed/master/%E4%BB%BF%E5%87%BD%E6%95%B0%E9%80%82%E9%85%8D%E5%99%A8.png
)

## 5. 仿函数(以及函数适配器)的使用示例

### 5.1 查找 25 或者 35 第一次出现的位置

```c++
pos = find_if(coll.begin(), coll.end(), //range
        compose_f_gx_hx(logical_or<bool>(), //criterion
            bind2nd(equal_to<int>(), 25),
            bind2nd(equal_to<int>(), 35)));
```

### 5.2 将集合中全部元素设为相反值

```c++
transform(coll.begin(), coll.end(),//source
        coll.begin(),//destination
        negate<int>());//operation
```

### 5.3 对集合所有的元素求平方

```c++
transform(coll.begin(), coll.end(),//first source
        coll.begin(),//second source
        coll.begin(),//destination
        multiplies<int>());//operation
```

### 5.4 所有元素乘以 10

```c++
transform(coll.begin(), coll.end(),//source
        back_inserter(coll2),//destination
        bind2nd(multiplies<int>(),10));//operation
```

### 5.5 将a替换为b

```c++
replace_if(coll2.begin(), coll2.end(),//range
        bind2nd(equal_to<int>(), 70),//replace criterion
        42);//new value
```

### 5.6 删除小于50的元素

```c++
coll.erase(remove_if(coll.begin(), coll.end(),//range
            bind2nd(less<int>(), 50)), //remove criterion
        coll.end());
```

### 5.7 返回第一个偶数

```c++
pos = find_if(coll.begin(), coll.end(), //range
        not1(bind2nd(modulus<int>(), 2)));
```

### 5.8 调整数组顺序，使得奇数位于偶数前面

```c++
stable_partition(v.begin(), v.end(), bind2nd(modulus<int>(), 2));
```

### 5.9 mem_fun_ref 与mem_fun 的区别以及用法

- mem_fun_ref:调用某个对象的成员函数；
- mem_fun:功能和 mem_fun_ref 一样，如果容器里存放的是指向对象的指针，而不是对象，则应该使用mem_fun

下面来看一个使用 mem_fun_ref 的例子，假设我们定义了一个类 Person,并且定义了一个 print() 的成员函数，容器coll 里存放了 coll.size() 个Person 对象，现在要调用每个对象的print 成员函数，那么我们就可以像下面这样。

```c++
class Person 
{
public:
  ...
  void print() const {
    std::cout << name << std::endl;
  }

  void printWithPrefix(std::string prefix) const {
    std::cout << prefix << name << std::endl;
  }
private:
  std::string name;
};


void foo(const std::vector<Person> &coll) {
  for_each(coll.begin(), coll.end(), 
           mem_fun_ref(&Person::print));
}
```

我们不能直接把一个成员函数传递给一个算法，所以这里必须运用函数适配器，下面这种做法会导致编译错误。

```c++
for_each(coll.begin(), coll.end(),
        &Person::print); //ERROR
```

通过使用函数适配器，我们还可以像被调用的成员函数传递一个参数。如下所示：

```c++
//call member function printWithPrefix() for each element
for_each(coll.begin(), coll.end(), 
         bind2nd(mem_fun_ref(&Person::printWithPrefix),
                "person:"));
```

### 5.10 ptr_fun

ptr_fun 使得我们能够在其他函数适配器中使用一般函数，加入你自己定义了一个函数check()，用于检验容器中的中的元素是否符合某种条件，你就可以这样：

```c++
pos = find_if(coll.begin(), coll.end(),
              not1(ptr_fun(check)));
```

这里不能使用not1(check)，因为not1()需要用到由仿函数提供的某些特殊型别。

第二种用法是，当你有一个双参数的全局函数，又想把它当做一个单参数函数来使用，可以用如下语句：

```c++
//find first string that is not empty
pos = find_if(coll.begin(), coll.end(), 
              bind2nd(ptr_fun(strcmp),""));
```