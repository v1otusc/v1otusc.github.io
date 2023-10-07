---
layout: post
title: 论文_标定_A comparative review of camera calibrating methods with accuracy evaluation
---

比较老的论文，对比了几种方法：

- Hall
- Faugeras
- Faugeras with radial distortion
- Tsai 只考虑 radial lens distortion
- Weng 考虑三种 radial/decentering/thin prism lens distortion

其中 decentering/thin prism lens distortion 本质上还是引起径向和切向 tangential 畸变

> 搜原文直接用上面名字加上 calibration

当不考虑相机畸变，可以通过各种变换表示成矩阵相乘，然后用线性最小二乘求解内参（直接法，求伪逆），考虑畸变，只能非线性最小二乘迭代了
