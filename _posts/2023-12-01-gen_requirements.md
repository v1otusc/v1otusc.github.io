---
layout: post
title: 生成requirements
---

有了 requirements.txt 就可以

```
pip install -r requirements.txt
```

但是直接用

```
pip freeze > requirements.txt
```

会保存了保存当前环境下所有类库包，包括没有在当前项目中使用的类库...

解决方法：pipreqs 加上当前路径即可

```
pip install pipreqs
pipreqs .
```

有用...
