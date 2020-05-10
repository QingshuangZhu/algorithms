# Algorithms
任何一个算法的设计取决于选定的数据（逻辑）结构，而算法的实现依赖于采用的存储结构（物理结构）。

## Data Structures
数据结构（data structures）：相互之间存在一种或多种特定关系的数据元素的集合。数据元素之间的关系称为结构，根据元素之间关系的不同特性，通常有4类基本结构：
1. 集合
2. 线形性结构
3. 树形结构
4. 图状结构或网状结构

其结构定义中的关系描述的是数据元素之间的逻辑关系，称为数据的逻辑结构。

数据结构在计算机中的表示称为数据的物理结构，又称存储结构。它包括数据元素的表示和关系的表示。数据元素之间的关系在计算机中有两种不同的表示方法：顺序映像和非顺序映像，并由此得到两种不同的存储结构：顺序存储结构和链式存储结构。

数据类型（data type）:一个值的集合和定义在这个值集上的一组操作的总称。（抽象数据类型abstract data type，数据结构+一组操作）

## Algorithms 
算法（algorithm）：对特定问题求解步骤的一种描述，它是指令有限序列。具有以下特征有穷性（finiteness）、确定性（definiteness）、可行性（effectiveness）、输入（input）、输出（output）。

算法分析：正确性和性能。
* 大O符号（BigONotation）：是用于描述函数渐进行为的数学符号（is a mathematical notation that describes the limiting behavior of a function when the argument tends towards a particular value or infinity）。
* 时间复杂度（time complexity）：算法中基本操作重复执行的次数是问题规模n的某个函数f(n)，算法的时间量度记作：T(n)=O(f(n))，它表示随问题规模n的增大，算法执行的时间增长率和f(n)的增长率相同，称为算法的渐近时间复杂度（asymptomatic time complexity），简称时间复杂度。
* 空间复杂度（space complexity）：算法所需存储空间的量度，记作S(n)=O(f(n))。

[P(Polynomial)问题](https://mp.weixin.qq.com/s?__biz=MzIxMjE5MTE1Nw==&mid=2653199528&idx=1&sn=87a25e5a35fcea443f324a89e4dbb8e1&chksm=8c99ee72bbee67643e3eaf6fb0fb35bd7175ee9e882510fcfea49c684bbd64d7b86207509480&scene=21#wechat_redirect)
：能用多项式算法解决的问题被称为P问题。

[NP(Non-deterministic Polynomial)问题](https://en.m.wikipedia.org/wiki/NP-completeness)：多项式复杂程度的非确定性问题。就目前的计算模型而言，不存在可在多项式时间内回答问题的算法，被称为NP问题。

NP-C(Non-deterministic Polynomial Complete)问题：把众多的NP问题层层归约，必定会得到一个或多个“终极问题”，这些归约的终点就是所谓的NPC问题。TPS(Traveling Salesman Problem)就属于NPC问题。