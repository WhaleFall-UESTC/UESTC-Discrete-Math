# 离散数学期末作业：图上的好友预测

> 数据集：https://snap.stanford.edu/data/ca-HepTh.html
> 
> 评分算法：简易的社会资本指数打分
> 
> 评估算法：AUC

依照作业要求使用 python 实现了划分数据集，连边打分，评估算法的步骤。在源代码中为每个函数做了说明，并在 main() 函数中以 Log 的形式解释主要步骤，得到输出如下：

```batchfile
whalefall@thx: python net.py
Initializing graph and selecting samples... Done
Calculating scores... Done
Seek eval_score table... Done
Calculating AUC... Done
AUC: 0.9366404249264915
```