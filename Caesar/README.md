# Caesar Encryption / Decryption

The **Caesar cipher** is one of the oldest and simplest encryption methods. It consists in **shifting letters** of a message by a fixed number of positions, known as the **key**, within the alphabet.

## Mathematical Model

Let the alphabet be represented as the finite ring:

$$
\mathbb{Z}_{26} = \{0, 1, 2, \dots, 25\}
$$

We assign each letter of the English alphabet a number:

$$
\text{A} \mapsto 0,\ \text{B} \mapsto 1,\ \dots,\ \text{Z} \mapsto 25
$$

Let:

- $x \in \mathbb{Z}_{26}$ be the plaintext letter (as a number)
- $k \in \mathbb{Z}_{26}$ be the key (shift)
- $y \in \mathbb{Z}_{26}$ be the ciphertext letter (as a number)

Then:

### 🔐 Encryption function

$$
y = E_k(x) = (x + k) \mod 26
$$

### 🔓 Decryption function

$$
x = D_k(y) = (y - k) \mod 26
$$

---

### ✍️ Example

Encrypt the message:

> **HELLO**

Using the key $k = 11$, and the mapping  $\text{A} = 0, \text{B} = 1, \dots, \text{Z} = 25$:

| Letter | Value | Encrypted Value (mod 26) | Encrypted Letter |
|--------|--------|--------------------------|------------------|
| H      | 7      | $7 + 11 = 18$         | S                |
| E      | 4      | $4 + 11 = 15$         | P                |
| L      | 11     | $11 + 11 = 22$        | W                |
| L      | 11     | $11 + 11 = 22$        | W                |
| O      | 14     | $14 + 11 = 25$        | Z                |

> 🔐 **Encrypted message**: **SPWWZ**

---

### 🔓 Decryption example

Apply:

$$
x = (y - k) \mod 26
$$

For letter S → 18:
$$x = (18 - 11) \mod 26 = 7 \Rightarrow \text{H}$$

And so on. This retrieves the original message.

---

### 🧾 Note

This cipher is **not secure** against modern attacks (e.g., frequency analysis), but it is excellent to introduce the concepts of:

- Modular arithmetic
- Key-based encryption
- Monoalphabetic substitution

### Pseudocode

```Pseudo
function CaesarEncrypt(message, ring_base) do
    key ← random() mod ring_base
    ciphertext ← empty string

    for i ← 0 to length(message) - 1 do
        char ← message[i]
        if char is a letter then
            x ← ordinal(char) - ordinal('A')
            y ← (x + key) mod ring_base
            cipher_char ← chr(y + ordinal('A'))
        else
            cipher_char ← char  
        end if
        append cipher_char to ciphertext
    end for

    return (ciphertext, key)
end
```

```Pseudo
function CaesarDecrypt(ciphertext, key, ring_base) do
    plaintext ← empty string
    for i ← 0 to length(ciphertext) - 1 do
        char ← ciphertext[i]
        if char is a letter then
            y ← ordinal(char) - ordinal('A')
            x ← (y - key + ring_base) mod ring_base
            plain_char ← chr(x + ordinal('A'))
        else
            plain_char ← char
        end if
        append plain_char to plaintext
    end for
    return plaintext
end

```
