---
layout: post
title: 论文_自动驾驶综述_End-to-end Autonomous Driving_Challenges and Frontiers
---

项目地址：

https://github.com/OpenDriveLab/End-to-end-Autonomous-Driving

端到端驾驶综述和传统自动驾驶：

- The conventional approach feeds the output of each component, such as bounding boxes and vehicle trajectories, directly into sub-sequent units
- The end-to-end paradigm propagates feature representations across components. The optimized function is set to be, for example, the planning performance, and the loss is minimized via back-propagation (red arrow). Tasks are jointly and globally optimized in this process.

Note that the end-to-end paradigm does not necessarily indicate one black box with only planning/control outputs. It could be modular with intermediate representations and outputs as in the classical approach. In fact, several state-of-the-art systems propose a modular design but optimize all components together to achieve superior performance.

端到端方法分类：

- imitation learning
  - behavior cloning
    - 问题1 During training, behavior cloning treats each state as independently and identically distributed, resulting in an important problem known as **covariate shift.**
    - 问题2 Another common problem with behavior cloning is **causal confusion**, where the imitator exploits and relies on false correlations between certain input components and output signals.
  - inverse optimal control 
- reinforcement learning

数据集分类

- online or closed-loop evaluation in simulation
- offline open-loop evaluation on human driving datasets

挑战

- Input Modality
  - Multi-sensor Fusion
  - Language as Input
- Visual Abstraction
- World Model and Model-based RL
- Multi-task Learning with Policy Prediction
- Policy Distillation
- Interpretability
- Causal Confusion
- Robustness
  - Long-tailed Distribution
  - Covariate Shift
  - Domain Adaptation

Future trends

- Zero-shot and Few-shot learning
- Modular End-to-end Planning，增加可解释性，哪个部分出了问题
- Data Engine，高质量的数据，怎么强调都不为过
- Foundation Model 的应用
- Vehicle-to-everything (V2X)
