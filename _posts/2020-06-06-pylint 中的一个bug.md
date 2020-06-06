---
layout: post
title: pylint 找不到 pytorch 中的某些函数
---

使用 Anaconda 安装完 pytorch 后, 在 vscode 中输入代码时发现，torch 里的某些函数会报错：

<center>
<img src = "https://raw.githubusercontent.com/v1otusc/PicBed/master/pylint_bug.png">
</center>

原因是 pylint 检查时采用 PEP8，可以通过下面的方法来解决这**一类**问题：

<center>
<img src = "https://raw.githubusercontent.com/v1otusc/PicBed/master/pylint_bug_fixed.png">
</center>
