---
layout: post
title: 交叉熵损失推导
---

对 https://zh.d2l.ai/chapter_linear-networks/softmax-regression.html#id8 中 (3.4.7) 推导的补充

假设整个数据集有 n 个样本

$$
P(\mathbf{Y} \mid \mathbf{X})=\prod_{i=1}^n P\left(\mathbf{y}^{(i)} \mid \mathbf{x}^{(i)}\right) .
$$

最小化负对数似然变成了

$$
-\log P(\mathbf{Y} \mid \mathbf{X})=\sum_{i=1}^n-\log P\left(\mathbf{y}^{(i)} \mid \mathbf{x}^{(i)}\right)=\sum_{i=1}^n l\left(\mathbf{y}^{(i)}, \hat{\mathbf{y}}^{(i)}\right)
$$

其中推导缺少的一步是

$$
P\left(\mathbf{y}^{(i)} \mid \mathbf{x}^{(i)}\right)=\prod_j\left[P\left(y_j^{(i)} \mid \mathbf{x}^{(i)}\right)\right]^{y_j}=\prod_j \hat{y}_j^{y_j}
$$

其中

$$
\hat{y}_j
$$

表示对给定输入的估计值(即是条件概率)，单独表示是

$$
\hat{y}_j = P(y_j^{(i)} \mid \mathbf{x}^{(i)})
$$

其中

$$
{y}_j = y_j^{(i)}
$$

表示条件概率对应的数据标签，可以用如下过程来理解

设

$$
\begin{aligned}
& \hat{y}=P(y=1 \mid x) \\
& 1-\hat{y}=P(y=0 \mid x)
\end{aligned}
$$

则有

$$
P(y \mid x)=\hat{y}^y \cdot(1-\hat{y})^{1-y}
$$

其中 y ∈ {0, 1} 为数据的标签

所以最后可以得到损失函数的表示为:

$$
l(\mathbf{y}, \hat{\mathbf{y}})=-\sum_{j=1}^q y_j \log \hat{y}_j .
$$

得到 (3.4.8)