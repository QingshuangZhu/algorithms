# String
字符串是由来自于某个字符表中的一系列字符所有构成的一个长度有限的序列。
* 子串（substring）：串中任意个连续的字符组成的子序列称为该串的子串。
* 前缀（prefix）：是子串的一个特例，前缀在原串的开始位置出现。
* 后缀（suffix）：是子串的一个特例，后缀在原串的末端出现。
* 空串（empty string）：长度为零的字符串称之为空串。空串是任何串的子串，也是任何串的前缀与后缀。
* 子序列（subsequence）：是从最初序列通过去除某些元素但不破坏余下元素的相对位置（在前或在后）而形成的新序列。注意子序列和子串是不同的。

[模式匹配(Pattern Matching)](https://mp.weixin.qq.com/s?__biz=MzIxMjE5MTE1Nw==&mid=2653201142&idx=1&sn=8cac1bbcfdb94474f0cc3855705cc253&chksm=8c99d02cbbee593ae0fb7fa1c8c610e7c1f57009e0c0ecbe19d07f60951912c915bce65c8619&scene=21#wechat_redirect)：给定一个子串，要求在某个字符串中找出与该子串相同的所有子串。
* [KMP](https://mp.weixin.qq.com/s?__biz=MzIxMjE5MTE1Nw==&mid=2653201731&idx=1&sn=89a943000fdc0530a0c3f930002ab3cd&chksm=8c99d799bbee5e8fd88b3293fd396ac53a103db2cca95b3b46453c1740140857c77f3f69e2eb&scene=21#wechat_redirectt)：KMP算法的关键是利用匹配失败后的信息，消除朴素的模式匹配算法中的主串指针回溯问题；减少模式串与目标串的匹配次数以达到快速匹配。可以在O(n+m)的时间上完成。具体实现就是实现一个next()函数：已经匹配的模式子串中，找出最长的相同的前缀（除了最后一个字符以外，一个字符串的全部头部组合）和后缀（除了第一个字符以外，一个字符串的全部尾部组合）；然后移动使它们重叠。（KMP算法的整体思路：在已匹配的前缀当中寻找到最长可匹配后缀子串和最长可匹配前缀子串，在下一轮直接把两者对齐，从而实现模式串的快速移动）

* [Boyer-Moore](https://mp.weixin.qq.com/s?__biz=MzIxMjE5MTE1Nw==&mid=2653201540&idx=1&sn=645a3f5f3fbf30be4f6d1c23eebdf0e7&chksm=8c99d65ebbee5f482dd68efecf7b2a23e98b238ba04c1d3a6aed6c12cab76d4650c3bef5ea00&scene=21#wechat_redirect)：BM算法制定了两条规则，一个是「坏字符规则」（bad character），一个是「好后缀规则」（good suffix）。

* Karp-Rabin：依次比较文本串中和模式串长度相同的子串的哈希值是否与模式串的哈希值相等，若相等再依次比较各个字符是否相同。