# RSA algorithm

R.L. Rivest, A. Shamir and L.Adleman

It is important to notice the following defintions to construct the pseudocode for this algorithm.

## Defintion 1

> Let n a positive integer number
>$$\Phi(n)=\{j|1\leq j\leq n-1, j \text{ relative prime with n}\}$$

> It defines $\varphi(n)$ as ther $\Phi(n)$ cardinality.

### Lemma 1
> Being p and q both prime numbers and $n=pq$, then

> $$\varphi(n)=(p-1)(q-1)$$

With this background, can be built the cipher RSA. Let $n=pq$ both prime numbers, And $x\in \mathbb{Z_n}$ and c,d integer numbers such as

$$0<c<\varphi(n) \text{ y }cd\equiv 1 \mod \varphi(n)$$
We define the functions

> $cipherRSA^n_c:\mathbb{Z_n}\rightarrow \mathbb{Z_n} \text{  } cipherRSA^n_c(x)=x^c$

> $decipherRSA^n_d:\mathbb{Z_n}\rightarrow \mathbb{Z_n} \text{  } decipherRSA^n_d(x)=x^d$

As first insight on the creation RSA Cipher:

* Choose two prime numbers enoughly big to be a good ciphration

* Calculate $\varphi(n)$ with $(p-1)(q-1)$

* Choose an integer $c$ such as $0<c<\varphi(n)$ and also $\gcd(c,\varphi(n))=1$

* Calculate d with the $cd\equiv 1\mod \varphi(n)$

To know the value of the d, it is important to notice the following definition
## Definition 2

Let $m>1$ an integer number. Define $a\equiv b \mod m \Leftrightarrow m|(a-b)$. If $a\equiv b \mod m $, it will be said a is congruent with b module m. Is easy to see $a \equiv b \mod m \Leftrightarrow a-b$ is a multiple of  m only if $a=b+mq$

So, we know that, $cd \equiv 1 \mod \varphi(n)$, by definition can be 
$$\varphi(n)|(cd-1)=cd-1=k\varphi(n)$$
Wwe can identify if the equation has a solution if 
$$gcd(c,\varphi(n))|1$$
However, by the previous condition, the diofantique equation alway would have a solution.

```Pseudo
function RSAecnryption(bitlength) do
    p ← generateRandomPrime(bitLength)
    q ← generateRandomPrime(bitLength)
    n ← p * q
    φ ← (p - 1) * (q - 1)
    repeat
        c ← random integer such that 1 < c < φ
    until gcd(c, φ) = 1
    d ← modularInverse(c, φ)
    return (n, c, d)  // Public key: (n, c), Private key: (n, d)
```

```pseudo
function encryptRSA(x, c, n):
    return modExp(x, c, n)  // x^c mod n
```

```pseudo
function decryptRSA(y, d, n):
    return modExp(y, d, n)  // y^d mod n
```

To generate a random prime number, is necessary the usage of Miller-Rabin and Eratosthenes cribe

It can defined the following pseudocode to generate a prime number

```Pseudo
function generate_prime(bit_length, k):
    base_primes ← sieve(10000)
    repeat:
        n ← random_odd_integer(bit_length)
        divisible ← false
        for p in base_primes:
            if n mod p = 0 then:
                divisible ← true
                break
        if divisible = false and is_probable_prime(n, k):
            return n
```
To calculate the value of d, can be used the euclidean extend algorithm, due to:
$$cd\equiv 1 \mod \phi(n)\rightarrow cd=1+\varphi(n)q\rightarrow cd-\varphi(n)q=1 $$
So:
$$ax+by=d \text{ being x,y unknown}$$
$$cd+\varphi(n)k=1$$
This implies $\gcd(\varphi(n),c)=1$

### Encryption and Decryption

To make the following procedures it is produced by the previous functions
> $cipherRSA^n_c:\mathbb{Z_n}\rightarrow \mathbb{Z_n} \text{  } cipherRSA^n_c(x)=x^c$

> $decipherRSA^n_d:\mathbb{Z_n}\rightarrow \mathbb{Z_n} \text{  } decipherRSA^n_d(x)=x^d$

> Let's demonstrate the following statement

>Given an input x, the RSA algorithm allows
>$decipherRSA^n_d(cipherRSA^n_c(x))=x$

>Proof :

To demonstrate that statement, it goes the following equation $x^{cd}=x$, but $x^{cd \equiv 1 \mod \varphi (n)}=x $. So:
$$x^{cd}\equiv x \mod n $$

There are two paths, but the both has the same root. So, if we have $\gcd(x,n)=1$, it can be demonstrated with the Euler's theorem.
$$x^{1+k \varphi(n)}=x x^{k \varphi (n)}=x (x^{\varphi (n)})^k \equiv x 1^k \equiv x \mod n$$
So, this means that if n and x are correlative, RSA is compatible. $n$ is $pq$, both prime numbers.
The second case consist on both numbers are not correlative. So there are two subcases. These ones follows up byt $n=pq$, because it can be analyzed both numbers. However, by induction, both will have same solutions.  
If $x\equiv 0 \mod  p$
For trival value, it can be said $x\equiv 0 \equiv x mod p$

If $\gcd(x,p)$
At here, it is necesary to grab the Fermat's theorem. Given 
$$a^{p-1} \equiv 1 \mod p$$
So, the equation that we had for the Euler's theorem can be transformed to:
$$cd =1+k\varphi(n)=1+k(p-1)(q-1)$$
$$x^{cd}=x^{1+k(p-1)(q-1)}=x (x^{(p-1)})^{k(q-1)} \equiv x \mod p$$
$$x \cdot 1^{k(q-1)} \equiv x \mod p$$
$$x\equiv x \mod p$$

At here, with these last steps, has been proved the RSA algorithm and its Decryption


