---
layout: post
title: 论文_BabelCalib
---

BabelCalib: A Universal Approach to Calibrating Central Cameras

作者的 Matlab 版本

https://github.com/ylochman/babelcalib

## 1. Introduction

- Cameras with very wide fields of view, such as fish-eye lenses and catadioptric rigs, usually require highly nonlinear models with many parameters. Calibrating these cameras can be a tedious process because of the camera model’s complexity and its underlying non-linearity, 由此引出了两种失败的情况:
  - Camera calibration is a very non-linear task, hence a good initial guess is typically needed to obtain accurate parameters e.g. initial values are often unavailable for parameters describing substantial lens distortions.
  - incorrect or grossly inaccurate measurements, e.g., corner detections, which are matched to fiducials on the calibration target.
- Our approach uses a **back-projection model as an intermediate camera model.** Back-projection models mapping image points to 3D ray directions are able to model a wide range of cameras (such as pinhole, fisheye and omni-directional cameras). Our approach (and therefore our main contribution) is to decouple the calibration task for general camera models into a much simpler calibration task for a powerful back-projection model followed by a regression task to obtain the parameters of the general target camera model. 将标定过程分为两步：求反投影模型，将反投影模型转化为投影模型(regression task)

## 2. 

