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

$$0<c<\varphi(n) \text{ y }cd\equiv 1 mód \varphi(n)$$
We define the functions

> $cipherRSA^n_c:\mathbb{Z_n}\rightarrow \mathbb{Z_n} \text{  } cipherRSA^n_c(x)=x^c$

> $decipherRSA^n_d:\mathbb{Z_n}\rightarrow \mathbb{Z_n} \text{  } decipherRSA^n_d(x)=x^d$

As first insight on the creation RSA Cipher, 