# Euclidean Algorithm

The **Euclidean algorithm** is a fundamental method in number theory and cryptography. It allows us to compute the **greatest common divisor (GCD)** of two integers efficiently.

## Mathematical Foundation

Given two integers $a$ and $b$ with $b > 0$, there exist integers $q$ and $r$ such that:

$$
a = bq + r \quad \text{with} \quad 0 \leq r < b
$$

This is the **division algorithm**. Using this relationship, we can state the key property of the Euclidean algorithm:

> If $a = bq + r$, then:
>
> $$\gcd(a, b) = \gcd(b, r) $$

This recursive property forms the basis of the algorithm.

### Pseudocode

```pseudo
function gcd(a,b) do
    while b ≠ 0 do
        r ← a mod b
        a ← b
        b ← r

    return a  // a is the GCD
end
```

The Bézout identity states that for any two nonzero integers $a$ and $b$, the greatest common divisor $\gcd(a, b)$ can be expressed as a linear combination of $a$ and $b$:

$$
\gcd(a, b) = ra + sb
$$

To compute the values of $r$ and $s$, we define sequences of integers:

$$
\begin{cases}
r_0 = a,\quad r_1 = b \\
x_0 = 1,\quad x_1 = 0 \\
y_0 = 0,\quad y_1 = 1
\end{cases}
$$

Then, for each $i \geq 1$, we compute:

$$
\begin{cases}
q_i = \left\lfloor \dfrac{r_{i-1}}{r_i} \right\rfloor \\
r_{i+1} = r_{i-1} - q_i r_i \\
x_{i+1} = x_{i-1} - q_i x_i \\
y_{i+1} = y_{i-1} - q_i y_i
\end{cases}
$$

This process continues until $r_{n+1} = 0$. Then:

- $d = \gcd(a, b) = r_n$
- $r = x_n$, $s = y_n$
- So: $\boxed{ra + sb = d}$

### Pseudocode Euclidean algorithm

```pseudo
function euclidean(a,b) do
    x0 ← 1,y0 ← 0
    x1 ← 0,y1 ← 1
    while b ≠ 0 do:
      q ← a div b
      r ← a mod b
      tempX ← x0 - q × x1
      tempY ← y0 - q × y1
      a ← b, b ← r
      x0 ← x1, x1 ← tempX
      y0 ← y1, y1 ← tempY
    d ← a
    x ← x0
    y ← y0
    return d,x,y
end
```
