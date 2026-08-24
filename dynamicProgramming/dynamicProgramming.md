# Dynamic Programming

> Status: notes-only。仓库当前没有动态规划实现或公开接口。

[动态规划（dynamic programming）](https://zh.wikipedia.org/wiki/%E5%8A%A8%E6%80%81%E8%A7%84%E5%88%92)：是一种在数学、管理科学、计算机科学、经济学和生物信息学中使用的，通过把原问题分解为相对简单的子问题的方式求解复杂问题的方法。动态规划的基本思想大致上，若要解一个给定的问题，我们需要解其不同部分（子问题），再根据子问题的解以得出原问题的解。通常许多子问题非常相似，为此动态规划法试图仅仅解决每个子问题一次，从而减少计算量：一旦某个给定子问题的解已经算出，则将其记忆化存储，以便下次需要同一个子问题解之时直接查表。动态规划常常适用于有重叠子问题和最优子结构性质的问题。
* 最优子结构（optimal substructure）：问题的最优解所包含的子问题的解也是最优的。
* 重叠子问题（overlapping subproblems）：如果一个问题可以分解为多个可以重复使用的子问题，或者该问题的递归算法可以反复解决相同的子问题，而不是总是生成新的子问题。
* 无后效性：在状态定义充分的前提下，后续决策只依赖当前状态，而不需要知道到达该状态的完整历史。

## 迭代与递归（Iterate and Recurse）
迭代乃人工，递归方神通（To iterate is human, to recurse, divine）。
* Decrease and conquer：为求解一个大规模的问题，可以将其划分为两个子问题：其一平凡，另一规模缩减，分别求解子问题，由子问题的解，得到原问题的解。
* Divide and conquer：为求解一个大规模的问题，可以将其划分为若干规模更小、通常彼此独立的子问题，分别求解后再合并为原问题的解；子问题不必大小完全相同。

递归式算法分析：
1. 递归跟踪（recursion trace）分析：检查每个递归实例累计所需时间其总和即算法执行时间。
2. 递推方程（recurrence）：写出问题的递推方程以及边界条件。

动态规划既可以采用自顶向下的递归加记忆化，也可以采用自底向上的迭代填表。低效来自重复求解相同子问题，而不是递归形式本身；若递归实现缓存每个子问题的结果，同样可以达到动态规划的复杂度目标。
选择自顶向下还是自底向上，应依据子问题是否都会被访问、递归深度、常数开销和实现清晰度，而不是把“递归转迭代”作为动态规划的必要步骤。

# References
[1] [什么是动态规划](https://mp.weixin.qq.com/s?__biz=MzIxMjE5MTE1Nw==&mid=2653190796&idx=1&sn=2bf42e5783f3efd03bfb0ecd3cbbc380&chksm=8c990856bbee8140055c3429f59c8f46dc05be20b859f00fe8168efe1e6a954fdc5cfc7246b0&scene=21#wechat_redirect)。

[2] [什么是扔鸡蛋问题](https://mp.weixin.qq.com/s?__biz=MzIxMjE5MTE1Nw==&mid=2653194433&idx=1&sn=6039143d3046ec972c141d05f89f7b30&chksm=8c99fa1bbbee730d771ddb0077666a5dad58bdc646252cf54bffd882fad2278027aaf9e428a4&scene=21#wechat_redirect)。

[3] [什么是旅行商问题](https://mp.weixin.qq.com/s?__biz=MzIxMjE5MTE1Nw==&mid=2653199528&idx=1&sn=87a25e5a35fcea443f324a89e4dbb8e1&chksm=8c99ee72bbee67643e3eaf6fb0fb35bd7175ee9e882510fcfea49c684bbd64d7b86207509480&scene=21#wechat_redirect)。

[4] [什么是字符串匹配算法](https://mp.weixin.qq.com/s?__biz=MzIxMjE5MTE1Nw==&mid=2653201142&idx=1&sn=8cac1bbcfdb94474f0cc3855705cc253&chksm=8c99d02cbbee593ae0fb7fa1c8c610e7c1f57009e0c0ecbe19d07f60951912c915bce65c8619&scene=21#wechat_redirect)。

[5] [什么是Boyer-Moore算法](https://mp.weixin.qq.com/s?__biz=MzIxMjE5MTE1Nw==&mid=2653201540&idx=1&sn=645a3f5f3fbf30be4f6d1c23eebdf0e7&chksm=8c99d65ebbee5f482dd68efecf7b2a23e98b238ba04c1d3a6aed6c12cab76d4650c3bef5ea00&scene=21#wechat_redirect)。

[6] [什么是KMP算法](https://mp.weixin.qq.com/s?__biz=MzIxMjE5MTE1Nw==&mid=2653201731&idx=1&sn=89a943000fdc0530a0c3f930002ab3cd&chksm=8c99d799bbee5e8fd88b3293fd396ac53a103db2cca95b3b46453c1740140857c77f3f69e2eb&scene=21#wechat_redirectt)。

[7] [什么是八皇后问题](https://mp.weixin.qq.com/s?__biz=MzIxMjE5MTE1Nw==&mid=2653193309&idx=1&sn=dd68a60873bb360e02afde21acde7d3f&chksm=8c99f687bbee7f91049c253dd3193c9a60d6d98cd315b0140a8635b2d34933b54a19127921a9&scene=21#wechat_redirect)。
