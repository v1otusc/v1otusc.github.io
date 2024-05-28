---
layout: post
title: 论文_TartanCalib
---

TartanCalib: Iterative Wide-Angle Lens Calibration using Adaptive SubPixel Refinement of AprilTags

http://tartancalib.com/

## 1. introduction 

we focus on accurate and robust target detection in the high distortion regions. State-of-the-art target calibration pipelines fail in presence of high distortion.

之前方法 target detection 和 feature refinement 依赖 low or medium distortion && camera projection that is close to a pinhole camera。但实际上，wide-angle len 靠近边缘的图像畸变较大, The result is that many features are either not detected or are not detected in an accurate way.

## 2. related work

**A camera model**

Generic models have far more parameters, aiming to more accurately represent lens geometry. It has been shown that these models have a significantly lower reprojection error.

看下 Why Having 10,000 Parameters in Your Camera Model is Better Than Twelve

https://github.com/puzzlepaint/camera_calibration

参数量较大的通用模型能更好地表示镜头的几何特性

TartanCalib, supports both parametric and generic camera models to achieve the best possible calibration.

**B Calibration Toolboxes**

**C Pattern Design and Feature Detection**

Dot patterns are susceptible to perspective and lens distortion, whereas a checkerboard tends to fail when it is only partially observed, which makes calibrating wide-angle lenses extremely challenging.

## 3. method

The high-level idea behind TartanCalib is to iteratively optimize a camera model, by leveraging intermediate camera models to improve target detection. The iteration includes several key components that will be detailed in the following sections. The components are

- Undistortion
- Target Reprojection
- Corner Filtering
- Subpixel Refinement

**A Undistortion**

模拟虚拟针孔相机进行去畸变，利用图像重映射算法

https://blog.csdn.net/limingmin2020/article/details/127508176

camodocal 中的实现

```cpp
cv::Mat
PinholeCamera::initUndistortRectifyMap(cv::Mat& map1, cv::Mat& map2,
                                       float fx, float fy,
                                       cv::Size imageSize,
                                       float cx, float cy,
                                       cv::Mat rmat) const
{
    if (imageSize == cv::Size(0, 0))
    {
        imageSize = cv::Size(mParameters.imageWidth(), mParameters.imageHeight());
    }

    cv::Mat mapX = cv::Mat::zeros(imageSize.height, imageSize.width, CV_32F);
    cv::Mat mapY = cv::Mat::zeros(imageSize.height, imageSize.width, CV_32F);

    Eigen::Matrix3f R, R_inv;
    cv::cv2eigen(rmat, R);
    R_inv = R.inverse();

    // assume no skew factor
    // 忽略偏斜因子
    Eigen::Matrix3f K_rect;

    if (cx == -1.0f || cy == -1.0f)
    {
        K_rect << fx, 0, imageSize.width / 2,
                  0, fy, imageSize.height / 2,
                  0, 0, 1;
    }
    else
    {
        K_rect << fx, 0, cx,
                  0, fy, cy,
                  0, 0, 1;
    }

    if (fx == -1.0f || fy == -1.0f)
    {
        K_rect(0,0) = mParameters.fx();
        K_rect(1,1) = mParameters.fy();
    }

    Eigen::Matrix3f K_rect_inv = K_rect.inverse();

    for (int v = 0; v < imageSize.height; ++v)
    {
        for (int u = 0; u < imageSize.width; ++u)
        {
            Eigen::Vector3f xo;
            xo << u, v, 1;

            Eigen::Vector3f uo = R_inv * K_rect_inv * xo;

            Eigen::Vector2d p;
            // 这个函数中包含了 distortion 环节 
            spaceToPlane(uo.cast<double>(), p);

            mapX.at<float>(v,u) = p(0);
            mapY.at<float>(v,u) = p(1);
        }
    }

    cv::convertMaps(mapX, mapY, map1, map2, CV_32FC1, false);

    cv::Mat K_rect_cv;
    cv::eigen2cv(K_rect, K_rect_cv);
    return K_rect_cv;
}
```

**B Target Reprojection**



**C Corner Filtering**



**D Subpixel Refinement**



