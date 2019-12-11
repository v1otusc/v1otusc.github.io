---
layout: post
title: ParaView笔记-Filter
---

> 这是我自己看文档时做的笔记(在笔记的标准要求较低的情况下), 可以减轻直接阅读英文手册的烦躁感.

<!-- TOC -->

- [1. Understanding filters](#1-understanding-filters)
- [2. Creating filters in paraview](#2-creating-filters-in-paraview)
  - [2.1 Multiple input connections](#21-multiple-input-connections)
  - [2.2 Multiple input ports](#22-multiple-input-ports)
- [3. Creating filters in pypython](#3-creating-filters-in-pypython)
- [4. Changing filter properties in paraview](#4-changing-filter-properties-in-paraview)
- [5. Changing filter properties in pvpython](#5-changing-filter-properties-in-pvpython)

<!-- /TOC -->

# 1. Understanding filters

filter 的 input 和 output ports 的数量都是一定的. **一个 filter 可以有多个 input 或者 output ports.** 一个 input ports 还可以有多个数据接口(例如 Append filter, 只有一个 input port 但是可以接收多个数据集).

<center>
<img src = "https://raw.githubusercontent.com/v1otusc/PicBed/master/filterModel.png">
</center>

# 2. Creating filters in paraview

点击 Pipeline 中的 source, 激活, 然后就可以添加 filter, [基本实践](https://v1otusc.github.io/2019/11/21/ParaView%E7%AC%94%E8%AE%B0-%E5%9F%BA%E6%9C%AC%E4%BB%8B%E7%BB%8D%E4%B8%8E%E7%AE%80%E5%8D%95%E5%AE%9E%E8%B7%B5/)中已经提到过了, 如果一个 filter 不可用, ParaView 是可以自己显示不可用的原因的.

## 2.1 Multiple input connections

点击多个 Pipeline 中的 source (通过 `Ctrl` 多选), 激活, 然后就可以添加 filter.



## 2.2 Multiple input ports

# 3. Creating filters in pypython



# 4. Changing filter properties in paraview


# 5. Changing filter properties in pvpython
