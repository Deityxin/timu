# TIMU 数论专题模板

这份手册只保留数论基础里最常用的内容，
目标是用于复习和背诵。

覆盖范围：

- 质数判断
- 筛法生成质数
- 质因数分解
- 最大公约数 / 最小公倍数
- 快速幂
- 哥德巴赫猜想这类数学枚举

## 1. 在 TIMU 里哪些题用到了这些内容

- 判质数：[bits/test/21.cpp](bits/test/21.cpp)、[bits/test/79修改.cpp](bits/test/79%E4%BF%AE%E6%94%B9.cpp)、[bits/test/87.cpp](bits/test/87.cpp)
- 筛法：[bits/test/103.cpp](bits/test/103.cpp)
- 质因数分解：[bits/test/84.cpp](bits/test/84.cpp)
- 向上取整：[bits/test/03.cpp](bits/test/03.cpp)
- 数学推导：[bits/test/07xiugai.cpp](bits/test/07xiugai.cpp)、[bits/test/94.cpp](bits/test/94.cpp)
- 模板库数论文件：[templates/sieve.hpp](templates/sieve.hpp)、[templates/fast_pow.hpp](templates/fast_pow.hpp)

## 2. 先记住怎么选方法

### 2.1 只判断一个数是不是质数

用试除法，枚举到 $\sqrt{n}$。

### 2.2 要判断很多个数是不是质数

先筛。

- 只想知道哪些数是质数：埃氏筛
- 还想知道最小质因子：线性筛

### 2.3 要分解一个数

从 2 开始试除，能除就一直除。

### 2.4 要算 $a^b \bmod mod$

用快速幂。

### 2.5 要算 gcd / lcm

用欧几里得算法。

## 3. 可直接背的模板

### 3.1 判质数，基础版

```cpp
bool isPrime(int x) {
    if (x < 2) return false;
    if (x == 2) return true;
    if (x % 2 == 0) return false;
    for (int i = 3; 1LL * i * i <= x; i += 2) {
        if (x % i == 0) return false;
    }
    return true;
}
```

适用：

- 只判少量整数
- 回文素数
- 组合和判质数

背诵点：

- 小于 2 不是质数
- 2 是质数
- 偶数直接排除
- 枚举到根号就够了

### 3.2 判质数，6k 优化版

```cpp
bool isPrime(int x) {
    if (x < 2) return false;
    if (x == 2 || x == 3) return true;
    if (x % 2 == 0 || x % 3 == 0) return false;
    for (int i = 5; 1LL * i * i <= x; i += 6) {
        if (x % i == 0 || x % (i + 2) == 0) return false;
    }
    return true;
}
```

来源参考：[bits/test/79修改.cpp](bits/test/79%E4%BF%AE%E6%94%B9.cpp)

记忆方式：

- 大于 3 的质数只可能在 `6k-1` 或 `6k+1`

### 3.3 埃氏筛

```cpp
vector<int> eratosthenes(int n) {
    vector<bool> isPrime(n + 1, true);
    vector<int> primes;

    if (n >= 0) isPrime[0] = false;
    if (n >= 1) isPrime[1] = false;

    for (int i = 2; 1LL * i * i <= n; ++i) {
        if (isPrime[i]) {
            for (int j = i * i; j <= n; j += i) {
                isPrime[j] = false;
            }
        }
    }

    for (int i = 2; i <= n; ++i) {
        if (isPrime[i]) primes.push_back(i);
    }
    return primes;
}
```

适用：

- 一次求出 `1~n` 所有质数
- 多次 O(1) 判断某个数是否是质数
- 哥德巴赫猜想

要点：

- 从 `i * i` 开始筛
- 因为更小的倍数早被筛过了

### 3.4 质数表版本

```cpp
vector<bool> buildPrimeTable(int n) {
    vector<bool> isPrime(n + 1, true);
    if (n >= 0) isPrime[0] = false;
    if (n >= 1) isPrime[1] = false;

    for (int i = 2; 1LL * i * i <= n; ++i) {
        if (isPrime[i]) {
            for (int j = i * i; j <= n; j += i) {
                isPrime[j] = false;
            }
        }
    }
    return isPrime;
}
```

这个版本适合直接写：

```cpp
if (isPrime[x]) {
    // x 是质数
}
```

### 3.5 线性筛

```cpp
struct LinearSieve {
    int n;
    vector<int> lp, primes;

    LinearSieve(int n = 0) {
        if (n) init(n);
    }

    void init(int n_) {
        n = n_;
        lp.assign(n + 1, 0);
        primes.clear();
        for (int i = 2; i <= n; ++i) {
            if (lp[i] == 0) {
                lp[i] = i;
                primes.push_back(i);
            }
            for (int p : primes) {
                long long v = 1LL * p * i;
                if (v > n || p > lp[i]) break;
                lp[v] = p;
            }
        }
    }
};
```

来源：[templates/sieve.hpp](templates/sieve.hpp)

适用：

- 既想筛质数
- 又想顺手得到最小质因子

### 3.6 质因数分解

```cpp
vector<int> primeFactors(int n) {
    vector<int> factors;
    for (int d = 2; 1LL * d * d <= n; ++d) {
        while (n % d == 0) {
            factors.push_back(d);
            n /= d;
        }
    }
    if (n > 1) factors.push_back(n);
    return factors;
}
```

来源：[bits/test/84.cpp](bits/test/84.cpp)

用途：

- 输出全部质因子
- 求最大质因子
- 做指数统计

### 3.7 gcd 和 lcm

```cpp
int gcd_int(int a, int b) {
    while (b != 0) {
        int t = a % b;
        a = b;
        b = t;
    }
    return a;
}

long long lcm_ll(long long a, long long b) {
    return a / gcd_int((int)a, (int)b) * b;
}
```

背诵点：

- `gcd(a, b) = gcd(b, a % b)`
- `lcm(a, b) = a / gcd(a, b) * b`

### 3.8 快速幂

```cpp
long long qpow(long long a, long long b, long long mod) {
    long long ans = 1 % mod;
    a %= mod;
    while (b > 0) {
        if (b & 1) ans = ans * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return ans;
}
```

适用：

- 求 `a^b mod mod`
- 幂很大，不能直接连乘

背诵点：

- 看二进制位
- 当前位是 1，就乘进答案
- 底数每次平方，指数每次右移

如果担心乘法中间过程爆掉，
直接用 [templates/fast_pow.hpp](templates/fast_pow.hpp)
里的 `mul_mod` 和 `mod_pow`。

### 3.9 向上取整

```cpp
int ceil_div(int a, int b) {
    return (a + b - 1) / b;
}
```

来源：[bits/test/03.cpp](bits/test/03.cpp)

虽然它不属于严格意义上的数论模板，
但在数学题里非常常用，建议一起背。

## 4. 哥德巴赫猜想模板

这个模板是最近这题最直接会用到的。

```cpp
int n;
cin >> n;

vector<bool> isPrime(n + 1, true);
isPrime[0] = isPrime[1] = false;

for (int i = 2; 1LL * i * i <= n; ++i) {
    if (isPrime[i]) {
        for (int j = i * i; j <= n; j += i) {
            isPrime[j] = false;
        }
    }
}

vector<int> primes;
for (int i = 2; i <= n; ++i) {
    if (isPrime[i]) primes.push_back(i);
}

for (int x = 4; x <= n; x += 2) {
    for (int p : primes) {
        if (p > x) break;
        if (isPrime[x - p]) {
            cout << x << '=' << p << '+' << x - p << '\n';
            break;
        }
    }
}
```

关键理解：

- 先筛出所有质数
- 对每个偶数，从小到大枚举第一个加数
- 第一个合法方案，就是题目要求的最小前项方案

## 5. 常见易错点

- 把 `1` 当成质数
- 判质数时循环写到 `x - 1`，复杂度太高
- 忘了写 `1LL * i * i <= x`，可能溢出
- 埃氏筛从 `2 * i` 开始也能做，但不够简洁
- `lcm = a * b / gcd` 可能先乘爆掉，应写成 `a / gcd * b`
- 快速幂里忘记先 `a %= mod`
- `mod = 1` 时答案应为 0
- 试除分解后，如果最后 `n > 1`，别忘了再放进答案

## 6. 一页背诵版

### 6.1 质数

- 质数：大于 1，只有 1 和自己两个正因子
- 判质数：试到根号
- 多次判质数：先筛
- 分解质因数：从 2 开始试除

### 6.2 gcd / lcm

- `gcd(a, b) = gcd(b, a % b)`
- `lcm(a, b) = a / gcd(a, b) * b`

### 6.3 快速幂

- 指数按二进制拆
- 位是 1 就乘进答案
- 底数不断平方

### 6.4 筛法

- 埃氏筛：标记倍数
- 线性筛：每个合数只被最小质因子筛一次

## 7. 现阶段最值得反复看的文件

- [bits/test/103.cpp](bits/test/103.cpp)：筛法 + 哥德巴赫
- [bits/test/79修改.cpp](bits/test/79%E4%BF%AE%E6%94%B9.cpp)：回文素数 + 6k 判质数
- [bits/test/84.cpp](bits/test/84.cpp)：质因数分解
- [bits/test/21.cpp](bits/test/21.cpp)：组合和判质数
- [templates/sieve.hpp](templates/sieve.hpp)：线性筛
- [templates/fast_pow.hpp](templates/fast_pow.hpp)：防爆乘法 + 快速幂
