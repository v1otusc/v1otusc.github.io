---
layout: post
title: boost::optional
---

> [原文地址](https://katecpp.github.io/boost-optional/)

## 1. 问题

可选值(optional value)，是这样的一些值：他们可以存在，也可以不存在。存在很多这样的例子，例如：中间名(不是每个人都有)，vector的最小值(当vector为空时不存在)或者队列中最后一个未处理的命令。

boost::optional库就是为了这种情况设计的。

我将给出处理可选值的可能实现，首先不使用boost::optional，然后使用boost::optional。下面的例子中，Pool类可以作为对象Object的容器，它可以表示应处理的命令。Pool中的最重要的对象总是最后一个，因此Pool接口应该提供获取容器中最后一个对象的方法`getLastObject`。由于Object较小，可以接受按值返回的对象。

```c++
struct object {
  object() : m_value(0);
  int m_value;
}
```

```c++
class Pool {
public:
  Pool() {};

  object getLastObject() {
    // 在这里，m_data 有可能为空
    return m_data.back();
  }

private:
  std::vector<object> m_data;
};
```

问题是在getLastObject的实现中出现的。当vector为空时，我们需要确保正确的行为。但是如何设计return的内容呢？

## 2. Without boost::optional

### 2.1 call getLastObj carefully[anti-pattern!]

实现`Pool::isEmpty`方法。仅当Pool不为空时才调用`getLastObject`。

```c++
// pool 为 Pool 的实例化对象
if (!pool.empty()) {
  object = pool.getLastObject();
}
else {
  std::cout << "The pool was empty!";
}
```

这是一种考验类的使用者自觉性的写法，如果你认为这是最糟糕的实现，那么你是对的。接口应该是容错的。当你忘记做正确的检查或别人在不知道限制的情况下尝试使用它时，它会导致未定义的行为。

根据Scott Meyers的说法，这种实现显然违反了最重要的设计指导原则：

> Make interfaces easy to use correctly and hard to use incorrectly.

忘了这种信任用户的糟糕设计吧！

### 2.2 Return invalid-object value

如果vector为空，则返回Object的特定无效值。

```c++
Object Pool::getLastObject()
{
  if (!m_data.empty()) {
    return m_data.back();
  }
  else {
    return Object();
  }
}
```

else中返回的结果可以是默认值或任何其他值(负的，极端的)，只要它不可能是正常的对象出现的值。否则，将无法区分正常对象和非法对象。

```c++
Pool pool;
Object object = pool.getLastObject();
std::cout << "The last Object's value is: " << obj.m_value << std::endl;
// The last Object's value is: 0
// But wait, Pool was empty...
```

这样的代码可能会产生误导，它很容易忘记检查对象的值是否有效，并将非法对象视为正常对象。而且，并不总是可能使用这样的实现。一些对象需要完整的值范围，对于它们没有特定的不存在的非法值。

这种方法也有性能缺陷，我们需要调用构造函数，尽管我们并不真正需要这个非法对象。这里的假设对象很小，构造函数代价较少，无论如何，这里的调用是完全多余的。

### 2.3 Return bool value

返回值表示Object的值是否有效。Object是通过其引用作为函数的参数返回的。

```c++
bool getLastObject(object& object) {
  if (!m_data.empty()) {
    object = m_data.back();
    return true;
  } else {
    return false;
  }
}
```

```c++
Pool pool;
Object object;
bool retVal = pool.getLastObject(object);
if (retVal) {
  std::cout << "The last value is: " << object.m_value << std::endl;
} else {
  std::cout << "The pool was empty!" << std::endl;
}
```

这种方法看起来不错，但是还是不够完美。当retValue与Object分开时（例如，将Object传递给无法访问retValue的其他函数），也就无法判断该Object是否有效。让是否非法信息与Object对象耦合可能是更好的主意。这种效果可以通过几种方式实现:使用bool和Object组成一个pair，将bool成员添加到Object结构体中，或像下一节一样，使用指向Object的指针处理，其中nullptr表示vector中不存在值。

### 2.4 Use nullptr for not existing object

Pool将存储指向对象的指针的vector，而不是存储对象的vector。

```c++
class Pool
{
public:
  Pool() {}

  Object* getLastObject() {
    if (!m_data.empty())
    {
      return m_data.back();
    }
    else {
      return nullptr;
    }
  }

private:
  std::vector<Object*> m_data;
};
```

```c++
Pool pool;
Object* object = pool.getLastObject();

if (object != nullptr) {
  std::cout << "The last value is: " << object->m_value << std::endl;
}
else {
  std::cout << "The pool was empty!" << std::endl;
}
```

无法将nullptr与已经存在的对象进行匹配，仍然可以使用完整范围的m_value成员，并且无需在Object结构中添加其他成员。还避免了不必要的构造函数的开销。不管怎样，使用原始指针听起来像是自找麻烦。需要注意指针的重新分配和处理空引用。

上面的就是各种各样的解决方案啦，那么如何使用boost::optional呢？

## 3. With boost::optional

### 3.1 Setup

包含下列头文件：

```c++
#include <boost/optional/optional.hpp>
using boost::optional;
```

或者使用标准库的experimental:

```c++
#include <experimental/optional>
using std::experimental::optional;
```

### 3.2 Usage

模板类boost::optional是一个对象的包装，该对象可以具有有效值，也可以具有无效值。 可选对象的构造如下所示：

```c++
Object someObject;
optional<Object> object_initialized = someObject;
// copy constructor of `Object` invoked

optional<Object> object_uninitialized;
// doesn't call the `Object` constructor
```

对于未初始化的`optional<Object>`，不调用Object的构造函数。

然后就可以随时检查对象是否已初始化。这可以`is_initialized`函数或简单地将对象放入条件表达式来完成。`optional<Object>`将转换为bool类型。

```c++
// equal to object.is_initialized
if (object) {
    // The object was initialized.
} else {
    // The object was not initialized.
}
```

使用`boost::optional`的`Pool::getLastObject`的实现如下所示。返回类型为`optional<Object>`，如果vector非空，`optional<Object>`被正确的值初始化。否则返回`optional<object>`类型的空对象。

```c++
optional<Object> Pool::getLastObject()
{
  if (!m_data.empty()) {
    return m_data.back();
  } else {
    return optional<Object>{};
  }
}
```

上面的代码具有等效的简短形式：

```c++
optional<Object> Pool::getLastObject() {
  return !m_data.empty() ? m_data.back() : optional<Object>{};
}
```

现在我们可以用下面的代码从Pool中获得最后一个对象。使用->操作符从`optional<Object>`访问m_value。

```c++
Pool pool;
optional<Object> object = pool.getLastObject();
if (object) {
    std::cout << "The last value is: " << object->m_value << std::endl;
} else {
    std:: cout << "The pool was empty!" << std::endl;
}
```

你也可以使用get()方法从`optional<Object>`接收`Object`类型的实例。

```c++
std::cout << "The last value is: " << object.get().m_value << std::endl;
```

如果对象未初始化，则调用get()方法或->，*操作符将导致一个断言。

### 3.3 Conditional constructor

还有另一种构造可选对象的方法，使用特殊的双参数构造函数:`optional<T>{conditiaon, value}`，第一个参数是一个条件，第二个条件是一个初始化值，当条件为真的时候被使用。当条件为假时，对象保持未初始化。

当初始化值已经存在或是一个内置类型(如int)时，此构造函数非常有用:

```c++
optional<int> getValue() {
  return optional<int>{condition == true, 5};
}
```

## 4. Summary

- Boost.optional设计用于可以初始化和未初始化的值，这两种情况都很常见；
- Boost.optional并没有对对象可以使用的可能值的设置限制；
- Boost.optional比使用nullptr的方法更安全；
- Boost.optional不会为未初始化的值调用被包装类型构造函数；
- Boost.optional提供了有关对象状态（已初始化/未初始化）的易于访问和直接的信息；
- Boost.optional使您的代码美观，安全且易于调试。

## 5. Further reading

- [Boost.org doc:optional](http://www.boost.org/doc/libs/1_57_0/libs/optional/doc/html/index.html)
- [The Boost C++ Libraries:boost.optiona](http://theboostcpplibraries.com/boost.optional)
- [A gotcha with Optional](https://akrzemi1.wordpress.com/2014/12/02/a-gotcha-with-optional/)
