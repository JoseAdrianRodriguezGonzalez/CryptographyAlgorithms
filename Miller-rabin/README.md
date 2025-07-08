# Test Miller-Rabin

## Theorem

let $n>2$ an odd number

$$n-1=2^s\cdot d\text{ as d an odd number}$$
Then, if $n \in \mathbb{Z_p}$ for each $a \in \mathbb{Z}^*_n$  

$$ a^d\equiv 1 \mod n \text{ or } a^{2^rd}\equiv -1 \mod n \text{ for some } 0\leq r<s$$
If both conditions aren't true for a base, the number is not a prime 
```pseudo 
function is_probable_prime(n, k):
    if n ≤ 1 then return false
    if n = 2 or n = 3 then return true
    if n is even then return false
    s ← 0
    d ← n - 1
    while d mod 2 = 0:
        d ← d / 2
        s ← s + 1
    repeat k times:
        a ← random integer in [2, n−2]
        x ← a^d mod n
        if x = 1 or x = n − 1 then continue
        repeat r from 1 to s−1:
            x ← x^2 mod n
            if x = n − 1 then break
        else:
            return false 
    return true 
```

It is important to notice, that is relevan to make the operation 
$$a^d \mod n$$
So, it is necessary to make proper optimizations to make it faster

```Pseudo
function mod_exp(base, exponent, modulus):
    result ← 1
    base ← base mod modulus
    while exponent > 0 do:
        if exponent mod 2 = 1 then:
            result ← (result × base) mod modulus  
        base ← (base × base) mod modulus          
        exponent ← floor(exponent / 2)            
    return result
```