---
layout: post
title: Sigmoid拟合曲线
---

https://stackoverflow.com/questions/60160803/scipy-optimize-curve-fit-for-logistic-function/60210529

```python
def sigmoid(x, L ,x0, k, b):
    y = L / (1 + np.exp(-k*(x-x0)))+b
    return (y)

p0 = [max(ydata), np.median(xdata),1,min(ydata)] # this is an mandatory initial guess

popt, pcov = curve_fit(sigmoid, xdata, ydata,p0, method='dogbox')
```

- L 负责将输出范围从 [0,1] 缩放到 [0,L]
- b 向输出添加偏差并将其范围从 [0,L] 更改为 [b,L+b]
- k 负责缩放输入，保留在 (-inf,inf)
- x0 是 Sigmoid 中间的点（因为如果 x=x0，我们得到 1/(1+exp(0)) = 1/2）

