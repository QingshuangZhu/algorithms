# String

> Status: partial。`bruteForce1`、`bruteForce2` 和 `KMP` 已实现；Boyer-Moore 与 Karp-Rabin 仅为学习笔记。

字符串是由来自于某个字符表中的一系列字符所有构成的一个长度有限的序列。
* 子串（substring）：串中任意个连续的字符组成的子序列称为该串的子串。
* 前缀（prefix）：是子串的一个特例，前缀在原串的开始位置出现。
* 后缀（suffix）：是子串的一个特例，后缀在原串的末端出现。
* 空串（empty string）：长度为零的字符串称之为空串。空串是任何串的子串，也是任何串的前缀与后缀。
* 子序列（subsequence）：是从最初序列通过去除某些元素但不破坏余下元素的相对位置（在前或在后）而形成的新序列。注意子序列和子串是不同的。

[模式匹配(Pattern Matching)](https://mp.weixin.qq.com/s?__biz=MzIxMjE5MTE1Nw==&mid=2653201142&idx=1&sn=8cac1bbcfdb94474f0cc3855705cc253&chksm=8c99d02cbbee593ae0fb7fa1c8c610e7c1f57009e0c0ecbe19d07f60951912c915bce65c8619&scene=21#wechat_redirect)：给定模式串和文本串，在文本中查找与模式串相同的子串。当前三个公开实现返回第一个匹配位置；完整枚举所有匹配不在当前接口范围内。

当前接口的长度均以字符数表示：找到时返回从0开始的首个下标，未找到或参数无效时返回-1，空模式返回0。模式长度大于文本长度时返回-1；非零长度对应的字符指针必须非空。`KMP` 的前缀表分配失败时同样返回-1。

两个朴素匹配实现的最坏时间复杂度均为O(nm)、辅助空间为O(1)；`KMP` 的时间复杂度为O(n+m)、辅助空间为O(m)。三者都只返回首个匹配位置，不修改模式串或文本串。

* [KMP](https://mp.weixin.qq.com/s?__biz=MzIxMjE5MTE1Nw==&mid=2653201731&idx=1&sn=89a943000fdc0530a0c3f930002ab3cd&chksm=8c99d799bbee5e8fd88b3293fd396ac53a103db2cca95b3b46453c1740140857c77f3f69e2eb&scene=21#wechat_redirectt)：KMP算法利用失配信息消除朴素模式匹配中的文本指针回溯。它通过内部前缀表记录可复用的最长真前缀/后缀信息，在O(n+m)时间和O(m)辅助空间内找到首个匹配。

* [Boyer-Moore](https://mp.weixin.qq.com/s?__biz=MzIxMjE5MTE1Nw==&mid=2653201540&idx=1&sn=645a3f5f3fbf30be4f6d1c23eebdf0e7&chksm=8c99d65ebbee5f482dd68efecf7b2a23e98b238ba04c1d3a6aed6c12cab76d4650c3bef5ea00&scene=21#wechat_redirect)：BM算法制定了两条规则，一个是「坏字符规则」（bad character），一个是「好后缀规则」（good suffix）。

* Karp-Rabin：依次比较文本串中和模式串长度相同的子串的哈希值是否与模式串的哈希值相等，若相等再依次比较各个字符是否相同。
