---
layout: post
title: 论文_2DLiDAR_falko
---

论文：Fast Keypoint Features from Laser Scanner for Robot Localization and Mapping. 

**Introduction && Related works**

Apart from standard geometric features like segments, there are few works related to 2D range keypoint features; these can be classified into two categories:

- 将 lase scans 转化为图像，这样就可以使用图像中的方法，但是计算比较复杂，并且需要 rasterization
- keypoint features explicitly designed for the laser scan peculiarities. Indeed, the scan radial order is taken into account in all the operations involving neighbor points, e.g. smoothing, downsampling, curvature computation
  - 代表有 FLIRT，本文属于这类

提出了关键点和描述子

- keypoint
  - FALKO (Fast Adaptive Laser Keypoint Orientation-invariant) 
  - Orthogonal Corner (OC)
- descriptors
  - Binary Shape Context (BSC)
  - Cumulative Gaussian Histogram (CGH)

**Keypoint Detectors**

A Orthogonal Corner Detector

假设

Human-made indoor environments often consist of straight linear walls and architectural elements arranged along orthogonal directions. This condition can be exploited to find stable keypoints at the intersection of orthogonal line pairs.

首先根据霍夫变换求 Hough Spectrum 可以得到 laser scan points 集合的 dominant direction 

找到方向后，就可以找交点了

$$
\begin{aligned}
C\left(p_i\right) & =\left\{p_j \in \overline{\mathcal{S}}:|| p_j-p_i \|<r_i\right\} \\
C_x\left(p_i\right) & =\left\{p_j \in C\left(p_i\right):\left|p_{j, x}-p_{i, x}\right|<w \wedge\left|p_{j, y}-p_{i, y}\right|>w\right\} \\
C_y\left(p_i\right) & =\left\{p_j \in C\left(p_i\right):\left|p_{j, y}-p_{i, y}\right|<w \wedge\left|p_{j, x}-p_{i, x}\right|>w\right\}
\end{aligned}
$$

where w is the tolerance on point alignment, a good corner is defined by points aligned on both directions.

$$
n_x=\left|C_x\left(p_i\right)\right|
$$

$$
n_y=\left|C_y\left(p_i\right)\right|
$$

然后算谁的 score 高，定义是

$$
\operatorname{score}\left(p_i\right)=\frac{n_x+n_y}{\epsilon+\left|n_x-n_y\right|}
$$

然后用一下 NMS 抑制一下就可以了

B FALKO

首先还是得到 C(p<sub>i</sub>)，然后根据 *逆时针顺序* 得到子集：

$$
\begin{aligned}
& C_L\left(p_i\right)=\left\{p_j \in C\left(p_i\right): j<i\right\} \\
& C_R\left(p_i\right)=\left\{p_j \in C\left(p_i\right): j>i\right\}
\end{aligned}
$$

The first step of the proposed method avoids evaluation of points which cannot be considered as candidate corners due to the lack of neighbors, geometric inconsistency or artifacts originated by range discontinuities.

如果有子集中的数量小于 2，那么 p<sub>i</sub> 就不会是 key point，然后求 C(p<sub>i</sub>) 的左右端点：

$$
\begin{array}{ll}
x_L=p_{j_{\min }}: & j_{\text {min }}=\arg \min _j\left\{p_j \in C_L\left(p_i\right)\right\} \\
x_R=p_{j_{\text {max }}}: & j_{\text {max }}=\arg \max _j\left\{p_j \in C_R\left(p_i\right)\right\}
\end{array}
$$

然后根据 p<sub>i</sub> x<sub>L</sub> 和 x<sub>R</sub> 组成的三角形，把 x<sub>L</sub> 和 x<sub>R</sub> 组成的边作为 base of the triangle，从而可以限制三角形的角度，不满足的就可以排除了，然后计算 cornerness score 

主要思路是在极坐标网格中，计算角度的距离函数 d，然后根据距离累加。看原文中 Fig2 很好理解

$$
\begin{aligned}
& \phi_{j, L}=\left\lfloor\frac{s_n}{2 \pi} \tan ^{-1}\left(\frac{p_{j, y}-p_{i, y}}{p_{j, x}-p_{i, x}}\right)\right\rfloor, \quad \forall p_j \in C_L\left(p_i\right) \\
& \phi_{j, R}=\left\lfloor\frac{s_n}{2 \pi} \tan ^{-1}\left(\frac{p_{j, y}-p_{i, y}}{p_{j, x}-p_{i, x}}\right)\right\rfloor, \quad \forall p_j \in C_R\left(p_i\right) \\
&
\end{aligned}
$$

$$
d_\theta\left(\phi_1, \phi_2\right)=\left(\left(\phi_1-\phi_2\right)+\frac{s_n}{2}\right)\left(\bmod s_n\right)-\frac{s_n}{2}
$$

$$
\begin{aligned}
\operatorname{score}_L\left(p_i\right) & =\sum_{h=i-1}^{j_{\min }} \sum_{k=h-1}^{j_{\min }}\left|d_\theta\left(\phi_h, \phi_k\right)\right| \\
\operatorname{score}_R\left(p_i\right) & =\sum_{h=i+1}^{j_{\max }} \sum_{k=h+1}^{j_{\max }}\left|d_\theta\left(\phi_h, \phi_k\right)\right| \\
\operatorname{score}\left(p_i\right) & =\operatorname{score}_L\left(p_i\right)+\operatorname{score}_R\left(p_i\right)
\end{aligned}
$$

分数越小越好，说明两条直线都比较 alignment，注意并不过滤非直角点，对角度的发生在判断底边长度的过程中。最后，同样地需要用 NMS 来抑制一下

**Keypoint Descriptors**

A Binary Shape Context

Shape context is a local descriptor which represents the points distribution in a linear-polar histogram，due to the angular quantization of the laser scanner, the same shape detected from two different viewpoints may results in two different histogram distributions. 可看 Fig3(a)

BSC 将其二值化而不再累加了，然后求一 Hamming-like distance function，见 Fig3(b)

$$
d_{B S C}\left(B S C_1, B S C_2\right)=\sum_{m=1}^{r_n} \sum_{j=1}^{\alpha_n} B S C_{1, m j} \oplus B S C_{2, m j}
$$

B Cumulative Gaussian Histogram

采用了一种计算相对角度分布的方案，见 Fig3(c)

C Computing Corner Orientation

在用描述子匹配之前，要考虑计算 keypoint 时的角度，需要 align

**Experiments**

We compared features by changing the viewpoint, the noise level and the number of measurements of a scan. Furthermore, global localization and loop closure capabilities have been exploited comparing the proposed features to FLIRT.

方法参考

- A performance evaluation of local descriptors
- Flirt-interest regions for 2D range data
- A comparison of affine region detectors

**Conclusions**

FALKO + BSC 效果好，用时短
