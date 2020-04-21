# Dynamic Programming
[动态规划（dynamic programming）](https://zh.wikipedia.org/wiki/%E5%8A%A8%E6%80%81%E8%A7%84%E5%88%92)：是一种在数学、管理科学、计算机科学、经济学和生物信息学中使用的，通过把原问题分解为相对简单的子问题的方式求解复杂问题的方法。动态规划的基本思想大致上，若要解一个给定的问题，我们需要解其不同部分（子问题），再根据子问题的解以得出原问题的解。通常许多子问题非常相似，为此动态规划法试图仅仅解决每个子问题一次，从而减少计算量：一旦某个给定子问题的解已经算出，则将其记忆化存储，以便下次需要同一个子问题解之时直接查表。动态规划常常适用于有重叠子问题和最优子结构性质的问题。
* 最优子结构（optimal substructure）：问题的最优解所包含的子问题的解也是最优的。
* 重叠子问题（overlapping subproblems）：如果一个问题可以分解为多个可以重复使用的子问题，或者该问题的递归算法可以反复解决相同的子问题，而不是总是生成新的子问题。
* 无后效性：子问题的解一旦确定，就不在改变，不受在这之后、包含它的更大的问题的求解决策影响。

# References
[1] [什么是动态规划](https://mp.weixin.qq.com/s?__biz=MzIxMjE5MTE1Nw==&mid=2653190796&idx=1&sn=2bf42e5783f3efd03bfb0ecd3cbbc380&chksm=8c990856bbee8140055c3429f59c8f46dc05be20b859f00fe8168efe1e6a954fdc5cfc7246b0&scene=21#wechat_redirect)。

[2] [什么是扔鸡蛋问题](https://mp.weixin.qq.com/s?__biz=MzIxMjE5MTE1Nw==&mid=2653194433&idx=1&sn=6039143d3046ec972c141d05f89f7b30&chksm=8c99fa1bbbee730d771ddb0077666a5dad58bdc646252cf54bffd882fad2278027aaf9e428a4&scene=21#wechat_redirect)。

[3] [什么是旅行商问题](https://mp.weixin.qq.com/s?__biz=MzIxMjE5MTE1Nw==&mid=2653199528&idx=1&sn=87a25e5a35fcea443f324a89e4dbb8e1&chksm=8c99ee72bbee67643e3eaf6fb0fb35bd7175ee9e882510fcfea49c684bbd64d7b86207509480&scene=21#wechat_redirect)。

[4] [什么是八皇后问题](https://mp.weixin.qq.com/s?__biz=MzIxMjE5MTE1Nw==&mid=2653193309&idx=1&sn=dd68a60873bb360e02afde21acde7d3f&chksm=8c99f687bbee7f91049c253dd3193c9a60d6d98cd315b0140a8635b2d34933b54a19127921a9&scene=21#wechat_redirect)。