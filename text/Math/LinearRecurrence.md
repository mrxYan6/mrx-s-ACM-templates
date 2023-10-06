# 常系数齐次线性递推

给定形如 $a_n = \sum\limits_{i=1}^k c_i * a_{n-i}$ 的递推式，求第 $n$ 项。

## 多项式除法和常系数递推是等价的。


假设有多项式除法: $ \frac{P(x)}{Q(x)} $ 记 $d = deg(Q(x))$ 并且 $deg(P(X)) + 1 \le d $ 。

那么就有: $ P(x) = Q(x) * A(x) $。

对于 $ i \gt d$ 展开可得: $ p_i = 0 = \sum\limits_{j=0}^{d} q_j * a_{i - j} $。 

变形可得: $ p_i = 0 = a_i - \sum\limits_{j=1}^{d} c_j * a_{i - j} $。
其中 $c_j = -q_j / q_0$。

这样就可以得到$ Q(x) = 1 - \sum\limits_{j=1}^{d} c_j * x^j $。

这样就证明了多项式除法和常系数递推的等价性。

然后使用Bostan-Mori算法高速求解多项式除法即可。

## 例题

求长度为m的字符串只有最后n位为s，其他子串均不为s的方案数。

记答案为$ g(x) $, 没有任何子串为s的方案数为$ h(x) $, 那么有:


根据容斥可得

$ g(n) = h(n - m) -\sum\limits_{p \in border}g(n - m + |p|) $

以及

$ 26 * h(n - 1) - h(n) = s(n)$

那么考虑消去h

$ 26 \cdot g(n - 1) = 26 \cdot h(n - m - 1) - 26 \cdot \sum\limits_{p \in border}g(n - m + |p| - 1) $

与

$ g(n) = h(n - m) -\sum\limits_{p \in border}g(n - m + |p|) $

相减得:

$ 26 \cdot g(n-1) - g(n) = 26 \cdot h(n-m-1) - h(n-m)  - 26 \cdot  \sum\limits_{p \in border}g(n - m + |p| - 1) + \sum\limits_{p \in border}g(n - m + |p|)$

$ 26 \cdot g(n-1) - g(n) = g(n - m)  - 26 * \sum\limits_{p \in border}g(n - m + |p| - 1) + \sum\limits_{p \in border}g(n - m + |p|)$

那么

$ g(n) = 26 \cdot g(n - 1) - g(n - m) - \sum\limits_{p \in border}g(n - m + |p|) + 26 \cdot \sum\limits_{p \in border}g(n - m + |p| - 1)$

那么就可以进行常系数齐次线性递推