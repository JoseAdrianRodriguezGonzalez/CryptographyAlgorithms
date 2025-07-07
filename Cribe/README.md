# Cribe Eratosthenes

Let $n \in \mathbb{N}$ compute all prime number $\leq n$. The algorithm consist on

 1. Initialize $A[2,\dots,n]$ as `true`
 2. $\forall p \in [2,\sqrt{n}]|A[p]=$`true` as  `false`
        For each $k=2p,3p,4p,\dots\leq n \rightarrow A[k]:=$`false`
 3. Finally the indexes with `true` are primes

```Pseudo
function sieve(n):
    A[2..n] ← true
    for p from 2 to floor(√n) do
        if A[p] = true then
            for multiple from p*p to n step p do
                A[multiple] ← false
    return all i where A[i] = true
```

## First optimization 

### Definition 1

All primes greater than 2 are odd

#### Demonstration

Let a number $n \in \mathbb{N}$, an even number is $k=2n$. Let a $p \in \mathbb{Z}$. By definition a primer number can just be $1|p,p|p$ but not other number. So if we have $k=2n$, always $2|k$, so by the first insight, a prime number cannot be even, furthermore taking only the odd numbers, that are defined as $k=2n+1$, sometimes could be a prime.
The trick consist on reindexing: $A[i]$ represents $2i+3$

```Pseudo
function sieve_odd(n):
    m ← floor((n - 3) / 2) + 1
    A[0..m-1] ← true
    for i from 0 to floor((√n - 3)/2) do
        if A[i] = true then
            p ← 2i + 3
            for j from ((p*p - 3)/2) to m-1 step p do
                A[j] ← false
    print 2  
    for i from 0 to m-1 do
        if A[i] = true then
            print 2i + 3
```

## Second optimization Bitset/bitmask

Instead of using `bool[]` we use 1 bit by number, this reduces the memory by 8and it can be used bit by bit `bitset[i/8] &(1<<(i%8))`

```Pseudo
function sieve_bitset(n):
    m ← floor((n - 3)/2) + 1  // solo impares ≥ 3
    bits ← array of ⎡m / 8⎤ bytes, todos 1

    for i from 0 to floor((√n - 3)/2) do
        if bit_is_set(bits, i) then
            p ← 2i + 3
            for j from ((p*p - 3)/2) to m-1 step p do
                clear_bit(bits, j)

    print 2
    for i from 0 to m-1 do
        if bit_is_set(bits, i) then
            print 2i + 3

```

## Third optimization segmented sieve

You divide the range $[2,n]$ in little segments
Therefore make the sieve $\sqrt{n}$
In each block mark the multiples from the primes 

```Pseudo
function segmented_sieve(n):
    limit ← floor(√n)
    base_primes ← sieve_odd(limit)

    segment_size ← optimal_block_size  // ej. 32768
    for low from 2 to n step segment_size do
        high ← min(low + segment_size - 1, n)
        m ← number of odd numbers in [low, high]
        bits ← array of ⎡m / 8⎤ bytes, todos 1

        for p in base_primes do
            start ← max(p*p, ceil(low/p) * p)
            if start is even: start ← start + p
            for j from start to high step 2p do
                if j is odd:
                    index ← (j - low) / 2
                    clear_bit(bits, index)

        for i from 0 to m-1 do
            if bit_is_set(bits, i) then
                print low + 2i  // porque solo impares
```
## Complexity


| Versión                        | Tiempo            | Memoria             |
| ------------------------------ | ----------------- | ------------------- |
| Clásica                        | $O(n \log\log n)$ | $O(n)$              |
| Solo impares                   | $O(n \log\log n)$ | $O(n/2)$            |
| Bitset (con impares)           | $O(n \log\log n)$ | $O(n/16)$           |
| Segmentada + impares + bits | $O(n \log\log n)$ | $O(\sqrt{n} + S/8)$ |
