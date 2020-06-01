---
layout: post
title: Induced Matrix Norms 诱导矩阵范数证明
---

## 意义

向量的范数可以看做是对向量长度的度量，诱导矩阵通过与向量范数类似的方法来达到相同的目的。

An m × n matrix can be viewed as a vector in an mn-dimensional space: each of the mn entries of the matrix is an independent coordinate. Any mn-dimensional norm can therefore be used for measuring the ‘size’ of such a matrix. **In dealing with a space of matrices, these are the induced matrix norms, defined in terms of the behavior of a matrix as an operator between its normed domain and range space.**

## 形式

Given vector norms \|\| · \|\|<sub>(m)</sub> , \|\| · \|\|<sub>(n)</sub> and on the domain and the range of A ∈ R<sup>m×n</sup>, respectively, the induced matrix norm \|\| A \|\|<sub>(m,n)</sub> is the smallest number C for which the following inequilty holds for any x ∈ R<sup>n</sup>.

$$
\|\mathbf{A} \mathbf{x}\|_{(m)} \leq C\|\mathbf{x}\|_{(n)}
$$

The induced matrix norm can be defined equivalently as following:

$$
\|\mathbf{A}\|_{(m, n)}=\sup _{\mathbf{x} \in \mathbb{R}^{n}, \mathbf{x} \neq 0} \frac{\|\mathbf{A} \mathbf{x}\|_{(m)}}{\|\mathbf{x}\|_{(n)}}=\sup _{\mathbf{x} \in \mathbb{R}^{n},\|\mathbf{x}\|=1}\|\mathbf{A} \mathbf{x}\|_{(m)}
$$

**注意**

The (m) and (n) in subscript are only represented the dimensionality of vectors, rather than Lm or Ln norm.  The notations \|\| · \|\|<sub>(m)</sub> and \|\| · \|\|<sub>(n)</sub> can be any the same type of vector norm.

## 证明

证明主要的内容是以下两种矩阵范数形式：

1-范数，列和范数
$$
\|\mathbf{A}\|_{1}=\max _{i} \sum_{j=1}^{n}\left|A_{i j}\right| = \max _{1 \leq j \leq n}\left\|\mathbf{a}_{j}\right\|_{1}
$$

∞-范数，行和范数
$$
\|\mathbf{A}\|_{\infty}=\max _{j} \sum_{i=1}^{m}\left|A_{i j}\right| =  \max _{1 \leq i \leq m}\left\|\mathbf{a}_{(i)}\right\|_{1}
$$

2-范数的形式为

$$
\|\mathbf{A}\|_{2}=\max \mu
$$

表示最大的奇异值(sigular value)。

### 1-范数形式的证明

****

将矩阵 **A** 记作：

$$
\mathbf{A}=\left[\begin{array}{cccc}
| & | & \cdots & | \\
\mathbf{a}_{1} & \mathbf{a}_{2} & \cdots & \mathbf{a}_{n} \\
| & | & \cdots & |
\end{array}\right]
$$

涉及到的两向量的 1-范数分别为：

$$
\|x\|_{1}=\sum_{i=1}^{n}\left|x_{i}\right| \\ \\
\|\mathbf{A} \mathbf{x}\|_{1} = \left\|\sum_{i=1}^{n} x_{i} \mathbf{a}_{i}\right\|_{1}
$$

根据向量范数的三角不等式：

$$
\|a+b\| \leq \|a\|+\|b\|
$$

有：

$$
\left\|\sum_{i=1}^{n} x_{i} \mathbf{a}_{i}\right\|_{1} \leq \sum_{i=1}^{n}\left|x_{i}\right||| \mathbf{a}_{i}|| \leq \sum_{i=1}^{n}\left|x_{i}\right|\left(\max _{1 \leq j \leq n}\left\|\mathbf{a}_{j}\right\|_{1}\right)
$$

所以：

$$
\frac{\|\mathbf{A} \mathbf{x}\|_{1}}{\|\mathbf{x}\|_{1}} \leq \max _{1 \leq j \leq n}\left\|\mathbf{a}_{j}\right\|_{1}
$$

### ∞-范数形式的证明

****

涉及到的两向量的 ∞-范数分别为：

$$
\|x\|_{\infty}= \max_i \left|x_{i}\right| \\ \\
\|\mathbf{A} \mathbf{x}\|_{\infty} = \left\|\sum_{i=1}^{n} x_{i} \mathbf{a}_{i}\right\|_{\infty} = \max_i\left|\sum_{j=1}^{n}A_{ij}x_{j}\right|
$$

> 注意一下上面符号的下标表示的含义。

并且有：

$$
\begin{aligned}
\left|\sum_{j=1}^{n} A_{i j} x_{j}\right| &\leq \sum_{j=1}^{n}\left|A_{i j} x_{j}\right|=\sum_{j=1}^{n}\left|A_{i j} \| x_{j}\right| \\
&\leq \sum_{j=1}^{n}\left|A_{i j}\right| \max _{i}\left|x_{i}\right|
\end{aligned}
$$

所以：

$$
\frac{\|\mathbf{A} \mathbf{x}\|_{\infty}}{\|\mathbf{x}\|_{\infty}} = \frac{\max_i\left|\sum_{j=1}^{n}A_{ij}x_{j}\right|}{\max_i \left|x_{i}\right|} \leq \max_i \sum_{j=1}^n|A_{ij}|
$$
