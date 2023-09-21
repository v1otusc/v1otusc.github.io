---
layout: post
title: 论文_标定_CalibrationWizard
---

图像中要保证能覆盖到标定板，并且占据的比例尽可能大，旋转尽可能多

https://github.com/pengsongyou/CalibrationWizard

- calibrationWizard 可以据此，指导 user 标定时的拍摄位置
  - 即 interactively guides users towards taking optimal calibration images
  - 通过最小二乘计算下一个 target 的位置
  - 并且考虑提取角点的不确定性
    - 论文 A combined corner and edge detector 需要看看
  - *真实数据对估计出的内参的两种评估方法*
    - pose estimation
    - Structure from Motion test 比较特殊
