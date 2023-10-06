# Powerful Number 筛

存在一个函数 $g$ 满足 :

 - g为积性函数
 - g易求前缀和
 - 对于质数p，$g(p) = f(p)$

对于一个整数n,记n的质因数分解为:$\prod\limits_{i = 1}^{m} p_i^{e_i}$ n是一个powerful number当且仅当$\forall i, e_i \ge 2$.

性质1: 所有pn可以表示成$a^2b^3$的形式，其中a,b为整数,显然。

性质2: n以内的pn个数为$O(\sqrt{n})$

如何求pn?通过线性筛筛$\sqrt{n}$,然后dfs找。



