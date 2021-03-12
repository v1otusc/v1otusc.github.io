---
layout: post
title: cpp_stl_deque
---

# C++ 标准库中的双端队列

<!-- TOC -->

- [C++ 标准库中的双端队列](#c-标准库中的双端队列)
  - [1. 概述](#1-概述)
  - [2. 定义及初始化](#2-定义及初始化)
  - [3. 基本操作函数](#3-基本操作函数)
    - [3.1 容量函数](#31-容量函数)
    - [3.2 添加函数](#32-添加函数)
    - [3.3 删除函数](#33-删除函数)
    - [3.4 访问函数](#34-访问函数)
    - [3.5 其他函数](#35-其他函数)
  - [4. 迭代器与算法](#4-迭代器与算法)
    - [4.1 迭代器](#41-迭代器)
    - [4.2 算法](#42-算法)
  - [5. 总结](#5-总结)

<!-- /TOC -->

## 1. 概述

deque（双端队列）是由一段一段的定量连续空间构成，可以向两端发展，因此不论在尾部或头部安插元素都十分迅速。但在中间部分安插元素则比较费时，因为必须移动其它元素。

## 2. 定义及初始化

使用之前必须加相应容器的头文件：

```c++
#include <deque> // deque 属于 std 命名域的，因此需要通过命名限定，例如 using std::deque;
```

定义的实现代码如下：

```c++
deque<int> a; // 定义一个int类型的双端队列 a
deque<int> a(10); // 定义一个 int 类型的双端队列 a，并设置初始大小为 10
deque<int> a(10, 1); // 定义一个 int 类型的双端队列 a，并设置初始大小为 10 且初始值都为 1
deque<int> b(a); // 定义并用双端队列 a 初始化双端队列 b
deque<int> b(a.begin(), a.begin()+3); // 将双端队列a中从第 0个 到第 2 个(共 3 个)作为双端队列 b的初始值
```

除此之外，还可以直接使用数组来初始化：

```c++
int n[] = { 1, 2, 3, 4, 5 };
// 将数组 n 的前 5 个元素作为双端队列a的初值
deque<int> a(n, n + 5); 
deque<int> a(&n[1], &n[4]); // 将n[1]、n[2]、n[3]作为双端队列a的初值
```

## 3. 基本操作函数

### 3.1 容量函数

- 容器大小：`deq.size()`;
- 容器最大容量：`deq.max_size()`;
- 更改容器大小：`deq.resize()`;
- 容器判空：`deq.empty()`;
- 减少容器大小到满足元素所占存储空间的大小：`deq.shrink_to_fit()`;

```c++
#include <iostream>
#include <deque>

using namespace std;

int main(int argc, char* argv[])
{
	deque<int> deq;
	for (int i = 0; i<6; i++)
	{
		deq.push_back(i);
	}

	cout << deq.size() << endl; // 输出：6
	cout << deq.max_size() << endl; // 输出：1073741823
	deq.resize(0); // 更改元素大小
	cout << deq.size() << endl; // 输出：0
	if (deq.empty())
		cout << "元素为空" << endl; // 输出：元素为空

	return 0;
}
```

### 3.2 添加函数

- 头部添加元素：`deq.push_front(const T& x)`;
- 末尾添加元素：`deq.push_back(const T& x)`;
- 任意位置插入一个元素：`deq.insert(iterator it, const T& x)`;
- 任意位置插入 n 个相同元素：`deq.insert(iterator it, int n, const T& x)`;
- 插入另一个向量的 \[first,last\] 间的数据：`deq.insert(iterator it, iterator first, iterator last)`;

```c++
#include <iostream>
#include <deque>

using namespace std;

int main(int argc, char* argv[])
{
	deque<int> deq;
	// 头部增加元素
	deq.push_front(4);
	// 末尾添加元素
	deq.push_back(5);
	// 任意位置插入一个元素
	deque<int>::iterator it = deq.begin();
	deq.insert(it, 2);
	// 任意位置插入n个相同元素
	it = deq.begin(); // 必须要有这句
	deq.insert(it, 3, 9);
	// 插入另一个向量的[first,last]间的数据
	deque<int> deq2(5,8);
	it = deq.begin(); // 必须要有这句
	deq.insert(it, deq2.end() - 1, deq2.end());

	// 遍历显示
	for (it = deq.begin(); it != deq.end(); it++)
		cout << *it << " "; // 输出：8 9 9 9 2 4 5
	cout << endl;

	return 0;
}
```

### 3.3 删除函数

- 头部删除元素：`deq.pop_front()`;
- 末尾删除元素：`deq.pop_back()`;
- 任意位置删除一个元素：`deq.erase(iterator it)`;
- 删除 \[first,last\] 之间的元素：`deq.erase(iterator first, iterator last)`;
- 清空所有元素：`deq.clear()`;

```c++
#include <iostream>
#include <deque>

using namespace std;

int main(int argc, char* argv[])
{
	deque<int> deq;
	for (int i = 0; i < 8; i++)
		deq.push_back(i);

	// 头部删除元素
	deq.pop_front();
	// 末尾删除元素
	deq.pop_back();
	// 任意位置删除一个元素
	deque<int>::iterator it = deq.begin();
	deq.erase(it);
	// 删除[first,last]之间的元素
	deq.erase(deq.begin(), deq.begin()+1);

	// 遍历显示
	for (it = deq.begin(); it != deq.end(); it++)
		cout << *it << " ";
	cout << endl;

	// 清空所有元素
	deq.clear();

	// 遍历显示
	for (it = deq.begin(); it != deq.end(); it++)
		cout << *it << " "; // 输出：3 4 5 6
	cout << endl;

	return 0;
}
```

### 3.4 访问函数

- 下标访问：`deq[1]`; // 并不会检查是否越界
- at 方法访问：`deq.at(1)`; // 以上两者的区别就是 at 会检查是否越界，是则抛出 out of range 异常
- 访问第一个元素：`deq.front()`;
- 访问最后一个元素：`deq.back()`;

```c++
#include <iostream>
#include <deque>

using namespace std;

int main(int argc, char* argv[])
{
	deque<int> deq;
	for (int i = 0; i < 6; i++)
		deq.push_back(i);

	// 下标访问
	cout << deq[0] << endl; // 输出：0
	// at方法访问
	cout << deq.at(0) << endl; // 输出：0
	// 访问第一个元素
	cout << deq.front() << endl; // 输出：0
	// 访问最后一个元素
	cout << deq.back() << endl; // 输出：5

	return 0;
}
```

### 3.5 其他函数

- 多个元素赋值：`deq.assign(int nSize, const T& x)`; // 类似于初始化时用数组进行赋值
- 交换两个同类型容器的元素：`swap(deque&)`;

```c++
#include <iostream>
#include <deque>

using namespace std;

int main(int argc, char* argv[])
{
	// 多个元素赋值
	deque<int> deq;
	deq.assign(3, 1);
	deque<int> deq2;
	deq2.assign(3, 2);

	// 交换两个容器的元素
	deq.swap(deq2);

	// 遍历显示
	cout << "deq: ";
	for (int i = 0; i < deq.size(); i++)
		cout << deq[i] << " "; // 输出：2 2 2
	cout << endl;

	// 遍历显示
	cout << "deq2: ";
	for (int i = 0; i < deq2.size(); i++)
		cout << deq2[i] << " "; // 输出：1 1 1
	cout << endl;

	return 0;
}
```

## 4. 迭代器与算法

### 4.1 迭代器

- 开始迭代器：`deq.begin()`;
- 末尾迭代器：`deq.end()`; // 指向最后一个元素的下一个位置
- 指向常量的开始迭代器：`deq.cbegin()`; // 意思就是不能通过这个迭代器来修改所指的内容，但还是可以通过其他方式修改的，而且迭代器也是可以移动的。
- 指向常量的末尾迭代器：`deq.cend()`;
- 反向迭代器，指向最后一个元素：`deq.rbegin()`;
- 反向迭代器，指向第一个元素的前一个元素：`deq.rend()`;

```c++
#include <iostream>
#include <deque>

using namespace std;

int main(int argc, char* argv[])
{
	deque<int> deq;
	deq.push_back(1);
	deq.push_back(2);
	deq.push_back(3);

	cout << *(deq.begin()) << endl; // 输出：1
	cout << *(--deq.end()) << endl; // 输出：3
	cout << *(deq.cbegin()) << endl; // 输出：1
	cout << *(--deq.cend()) << endl; // 输出：3
	cout << *(deq.rbegin()) << endl; // 输出：3
	cout << *(--deq.rend()) << endl; // 输出：1
	cout << endl;

	return 0;
}
```

### 4.2 算法

遍历元素

```c++
deque<int>::iterator it;
for (it = deq.begin(); it != deq.end(); it++)
    cout << *it << endl;
// 或者
for (int i = 0; i < deq.size(); i++) {
    cout << deq.at(i) << endl;
}
```

元素翻转

```c++
#include <algorithm>
reverse(deq.begin(), deq.end());
```

元素排序

```c++
#include <algorithm>
sort(deq.begin(), deq.end()); // 采用的是从小到大的排序

// 如果想从大到小排序，可以采用先排序后反转的方式，也可以采用下面方法:
// 自定义从大到小的比较器，用来改变排序方式
bool cmp(const int& a, const int& b) {
    return a > b;
}

sort(deq.begin(), deq.end(), cmp);
```

## 5. 总结

可以看到，deque 与 vector 的用法基本一致，除了以下几处不同：

- deque 没有 capacity() 函数，而 vector 有；
- deque 有 push_front() 和 pop_front() 函数，而 vector 没有；
- deque 没有 data() 函数，而 vector 有。

