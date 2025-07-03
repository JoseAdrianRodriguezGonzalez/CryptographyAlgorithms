## Euclidean Algorithm

The **Euclidean algorithm** is a fundamental method in number theory and cryptography. It allows us to compute the **greatest common divisor (GCD)** of two integers efficiently.

### Mathematical Foundation

Given two integers $a$ and $b$ with $b > 0$, there exist integers $q$ and $r$ such that:

\[
a = bq + r \quad \text{with} \quad 0 \leq r < b
\]

This is the **division algorithm**. Using this relationship, we can state the key property of the Euclidean algorithm:

> If $a = bq + r$, then:
> $$\gcd(a, b) = \gcd(b, r) $$

This recursive property forms the basis of the algorithm.

### Pseudocode

```pseudo
a ← integer
b ← integer (b ≠ 0)

while b ≠ 0 do
    r ← a mod b
    a ← b
    b ← r

return a  // a is the GCD
```
