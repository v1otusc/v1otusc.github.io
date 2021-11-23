---
layout: post
title: ROS wstool 的使用
---

> 转载 https://blog.csdn.net/weixin_38258767/article/details/104260992

wstool 是用于管理 ROS 工作空间的工具，它通过 `.rosinstall` 文件规定工作空间的配置。一个使用样例如下：

```
cd ~/gilbreth_ws/src
wstool init .
wstool merge https://raw.githubusercontent.com/swri-robotics/gilbreth/kinetic-devel/gilbreth.rosinstall
wstool update
```

- wstool init .会创建本地的.rosinstall 文件
- wstool merge将对应的.rosinstall文件合并到本地
- wstool update就可以下载相应文件

这里的gilbreth.rosinstall文件内容如下：

```
- git:
    local-name: gilbreth
    uri: https://github.com/swri-robotics/gilbreth.git
    version: kinetic-devel
- git:
    local-name: universal_robot
    uri: https://github.com/ros-industrial/universal_robot.git
    version: kinetic-devel
```