# Algorithms

## Repository Status

| Path | Status | Scope |
|---|---|---|
| `list/`, `queue/`, `stack/` | implemented | 顺序及链式容器实现 |
| `sort/` | partial | 头文件中的排序接口已实现；外部排序仅为笔记 |
| `heap/` | partial | 数组最小堆已实现；优先队列和左式堆仅为笔记 |
| `tree/` | partial | 构造、深度、叶子计数、遍历、反转和 AVL 基本旋转已实现；其余树 ADT 名称仅保留为 notes-only 设计清单 |
| `string/` | partial | BF 和 KMP 已实现；Boyer-Moore 和 Karp-Rabin 仅为笔记 |
| `graph/` | interface-only | 提供数据结构和接口声明，没有实现 |
| `hashTable/`, `dynamicProgramming/` | notes-only | 仅包含学习笔记 |

### API Compatibility Notes

- 循环队列的队头访问函数由 `getHead` 改名为 `getCHead`，以避免与链式队列的 C linkage 符号冲突。
- 二叉树元素类型由通用名称 `dataType` 改名为 `biTreeDataType`，以便与其他容器头文件同时包含。
- 二叉树中从未提供定义的 14 个 ADT 操作不再作为可链接 API 声明；名称和预期范围仅保留在 `tree/tree.md` 的 notes-only 设计清单中。
- `listAttach` 和 `cListAttach` 现在返回独立的深拷贝，两个输入保持不变；`listAttach2` 同样产生独立结果并允许输出对象与任一输入对象相同。
- 原有字符串匹配符号现在由 `string/patternMatching.h` 统一声明，模式串和文本串参数为只读指针。

任何一个算法的设计取决于选定的数据（逻辑）结构，而算法的实现依赖于采用的存储结构（物理结构）。

## Data Structures
数据结构（data structures）：相互之间存在一种或多种特定关系的数据元素的集合。数据元素之间的关系称为结构，根据元素之间关系的不同特性，通常有4类基本结构：
1. 集合
2. 线性结构
3. 树形结构
4. 图状结构或网状结构

其结构定义中的关系描述的是数据元素之间的逻辑关系，称为数据的逻辑结构。

数据结构在计算机中的表示称为数据的物理结构，又称存储结构。它包括数据元素的表示和关系的表示。数据元素之间的关系在计算机中有两种不同的表示方法：顺序映像和非顺序映像，并由此得到两种不同的存储结构：顺序存储结构和链式存储结构。

数据类型（data type）是一个值的集合和定义在该值集上的一组操作。抽象数据类型（abstract data type）描述逻辑上的值、关系和操作，不规定具体存储表示；数据结构则是其可能采用的一种实现方式。

## Algorithms 
算法（algorithm）：对特定问题求解步骤的一种描述，它是指令有限序列。具有以下特征有穷性（finiteness）、确定性（definiteness）、可行性（effectiveness）、输入（input）、输出（output）。

算法分析：正确性和性能。
* 大O符号（BigONotation）：是用于描述函数渐进行为的数学符号（is a mathematical notation that describes the limiting behavior of a function when the argument tends towards a particular value or infinity）。
* 时间复杂度（time complexity）：算法中基本操作重复执行的次数是问题规模n的某个函数f(n)。T(n)=O(f(n))表示f(n)是T(n)的渐近上界；只有T(n)=Θ(f(n))时，才表示二者具有相同的渐近增长阶，称为算法的渐近时间复杂度（asymptotic time complexity）。
* 空间复杂度（space complexity）：算法所需存储空间的量度，记作S(n)=O(f(n))。

[P(Polynomial)问题](https://mp.weixin.qq.com/s?__biz=MzIxMjE5MTE1Nw==&mid=2653199528&idx=1&sn=87a25e5a35fcea443f324a89e4dbb8e1&chksm=8c99ee72bbee67643e3eaf6fb0fb35bd7175ee9e882510fcfea49c684bbd64d7b86207509480&scene=21#wechat_redirect)
：能由确定性算法在多项式时间内解决的判定问题组成复杂度类P。

[NP(Non-deterministic Polynomial)问题](https://en.m.wikipedia.org/wiki/NP-completeness)：能够由非确定性图灵机在多项式时间内求解的判定问题；等价地，其“是”实例具有可在多项式时间内验证的证书。P是NP的子集，而P是否等于NP仍是未解决问题。

NP-C(Non-deterministic Polynomial Complete)问题：同时属于NP，并且所有NP问题都可在多项式时间内归约到它的判定问题。旅行商问题（Traveling Salesman Problem, TSP）的判定版本是NP-complete，求最短回路的优化版本是NP-hard。
