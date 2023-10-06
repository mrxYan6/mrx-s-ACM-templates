# tricks

## d(i, j)

$d(i, j)$ 为 $i$ 和 $j$ 的约数个数数量，其等价于 $\sum\limits_{i|x}\sum\limits_{j|y} [gcd(x, y) = 1]$
然后套用莫反搞掉gcd

## 整除的tirck

$\lfloor\frac{n}{a*b} \rfloor = \lfloor \frac{\lfloor\frac{n}{a} \rfloor}{b}  \rfloor$

可以用来解决分母有一项是被枚举的值，但另一个不是被枚举的值的表达式化简

证明如下: 假设 $n = a*t + y$，有 $y \le a- 1$, 则 $\lfloor\frac{n}{a} \rfloor = t$，然后证明 $\lfloor \frac{t}{b} \rfloor = \lfloor\frac{n}{a*b} \rfloor$假设 $t = b*k + x$，有 $x \le b-1$，则 $\lfloor \frac{t}{b} \rfloor = k$，用上面的展开式来表示 $\lfloor \frac{n}{a*b} \rfloor = \lfloor \frac{a*b*k + a*x+y}{a*b} \rfloor = k + \lfloor \frac{a*x+y}{a*b} \rfloor $由于 $x \le b-1 , y \le a -1$，则 $\lfloor \frac{a*x+y}{a*b} \rfloor = 0$，所以 $\lfloor\frac{n}{a*b} \rfloor = \lfloor \frac{\lfloor\frac{n}{a} \rfloor}{b}  \rfloor$

## gcdsum
$$ \sum\limits_{i}^{n_1}\sum\limits_{j}^{n_2}...gcd(i, j,...) = 
\\
\sum\limits_{i}\sum\limits_{j}...\sum\limits_{x|gcd(i,j,...)}{\varphi(x)} = 

\\

\sum\limits_{x}\varphi(x) \prod\lfloor\frac{n_i}{x}\rfloor
$$

## 分治fft求 $i < j$ 的卷积

考虑分治

把区间[l,r]分为[l, mid]和[mid, r]，发现左半边区间和右半边区间进行多项式乘法满足 $i < j$的限制，然后加上这两半区间内的贡献（用分治求解）就算完了。

代码例子如下:

```cpp
std::function<void(int, int)> solve = [&] (int l, int r) {
        if (l == r) {
            return;
        }
        int mid = (l + r) >> 1;
        solve(l, mid);
        solve(mid + 1, r);
        Poly a = Poly(f.begin() + l, f.begin() + mid + 1);
        Poly b = Poly(g.begin() + mid + 1, g.begin() + r + 1);
        auto now = a * b;
        for (int i = 0; i <= r - l; ++i) {
            res[i + l + mid + 1] += now[i];
        }
    };
```