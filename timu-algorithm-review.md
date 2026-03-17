# TIMU 算法模板复习手册

这份手册按你当前仓库的做题记录整理，覆盖 `bits/test`、`bits/shiyan` 和 `templates` 里最值得背的模板。

目标不是把所有题逐题抄一遍，而是把已经反复出现的套路压成一套可复习、可默写、可直接套用的 Markdown 版模板。

## 1. TIMU 题型总览

### 1.1 `bits/test` 的高频题型

- 模拟与枚举：按题意一步一步推，先找规律再写循环。
  代表题：[bits/test/04.cpp](bits/test/04.cpp)、[bits/test/10.cpp](bits/test/10.cpp)、[bits/test/19.cpp](bits/test/19.cpp)、[bits/test/29.cpp](bits/test/29.cpp)、[bits/test/30.cpp](bits/test/30.cpp)、[bits/test/91.cpp](bits/test/91.cpp)
- 数学与数论：向上取整、调和级数、回文构造、质数判断、质因数分解。
  代表题：[bits/test/03.cpp](bits/test/03.cpp)、[bits/test/06.cpp](bits/test/06.cpp)、[bits/test/07xiugai.cpp](bits/test/07xiugai.cpp)、[bits/test/79修改.cpp](bits/test/79%E4%BF%AE%E6%94%B9.cpp)、[bits/test/84.cpp](bits/test/84.cpp)、[bits/test/103.cpp](bits/test/103.cpp)
- 排序与贪心：`sort`、自定义比较器、先排序再统计或构造。
  代表题：[bits/test/18.cpp](bits/test/18.cpp)、[bits/test/38.cpp](bits/test/38.cpp)、[bits/test/64.cpp](bits/test/64.cpp)、[bits/test/70.cpp](bits/test/70.cpp)、[bits/test/82.cpp](bits/test/82.cpp)、[bits/test/89.cpp](bits/test/89.cpp)
- 字符串处理：整行输入、大小写统一、分词、编辑模拟、数字串处理。
  代表题：[bits/test/14.cpp](bits/test/14.cpp)、[bits/test/15.cpp](bits/test/15.cpp)、[bits/test/16.cpp](bits/test/16.cpp)、[bits/test/19.cpp](bits/test/19.cpp)、[bits/test/39.cpp](bits/test/39.cpp)、[bits/test/59.cpp](bits/test/59.cpp)
- 递归、回溯、记忆化、DP：组合搜索、整数拆分、`w(a,b,c)`、台阶问题。
  代表题：[bits/test/20.cpp](bits/test/20.cpp)、[bits/test/21.cpp](bits/test/21.cpp)、[bits/test/22.cpp](bits/test/22.cpp)、[bits/test/24.cpp](bits/test/24.cpp)、[bits/test/25.cpp](bits/test/25.cpp)
- 高精度：大整数乘法、万进制压位、高精加法。
  代表题：[bits/test/59.cpp](bits/test/59.cpp)、[bits/test/67.cpp](bits/test/67.cpp)

### 1.2 `bits/shiyan` 的基础训练重点

- 二维数组 / 矩阵输入输出。
  代表题：[bits/shiyan/01.cpp](bits/shiyan/01.cpp)、[bits/shiyan/04.cpp](bits/shiyan/04.cpp)
- 排序找最值与位置。
  代表题：[bits/shiyan/05.cpp](bits/shiyan/05.cpp)、[bits/shiyan/06.cpp](bits/shiyan/06.cpp)
- 递归 + 记忆化函数值计算。
  代表题：[bits/shiyan/10.cpp](bits/shiyan/10.cpp)

### 1.3 `templates` 的进阶模板库

- 基础骨架：[templates/common.hpp](templates/common.hpp)
- 数论：[templates/sieve.hpp](templates/sieve.hpp)、[templates/fast_pow.hpp](templates/fast_pow.hpp)
- 数据结构：[templates/fenwick.hpp](templates/fenwick.hpp)、[templates/segment_tree.hpp](templates/segment_tree.hpp)、[templates/lazy_segment_tree.hpp](templates/lazy_segment_tree.hpp)、[templates/dsu.hpp](templates/dsu.hpp)
- 字符串：[templates/kmp.hpp](templates/kmp.hpp)、[templates/trie.hpp](templates/trie.hpp)
- 图论与树：[templates/dijkstra.hpp](templates/dijkstra.hpp)、[templates/lca.hpp](templates/lca.hpp)
- 查询结构：[templates/sparse_table.hpp](templates/sparse_table.hpp)

## 2. 先背这份主程序骨架

```cpp
#include <bits/stdc++.h>
#include "common.hpp"
using namespace std;

int main() {
    int n;
    cin >> n;
    return 0;
}
```

背诵点：

- 竞赛题默认先开 `bits/stdc++.h`
- 这个仓库优先带上 `common.hpp`
- 快速 IO 已在 `common.hpp` 里处理好

## 3. 质数专题模板

这一章单独背。你最近的题里，质数相关已经出现了：

- 判质数：[bits/test/21.cpp](bits/test/21.cpp)、[bits/test/79修改.cpp](bits/test/79%E4%BF%AE%E6%94%B9.cpp)、[bits/test/87.cpp](bits/test/87.cpp)
- 筛法与哥德巴赫：[bits/test/103.cpp](bits/test/103.cpp)
- 质因数分解：[bits/test/84.cpp](bits/test/84.cpp)

### 3.1 单个数判质数，最稳模板

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

- 只判几个数是不是质数
- 组合和判质数
- 回文素数、区间里少量判断

背诵口诀：

- 小于 2 不是质数
- 2 是质数
- 偶数直接排除
- 只试到根号

### 3.2 更快的判质数，6k 写法

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

适用：

- 判质数次数较多，但还不需要筛法
- 参考写法来自 [bits/test/79修改.cpp](bits/test/79%E4%BF%AE%E6%94%B9.cpp)

### 3.3 埃氏筛，最常用的质数生成模板

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

- 一次性求 `1~n` 所有质数
- 哥德巴赫猜想
- 需要多次快速判断 `x` 是否是质数

配套写法：

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

记忆点：

- 从 `i * i` 开始筛
- 倍数循环 `j += i`
- `isPrime[x]` 可直接 O(1) 判断

### 3.4 线性筛，模板库里现成有

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

来源：模板库 [templates/sieve.hpp](templates/sieve.hpp)

适用：

- 想顺便维护最小质因子
- 后续要做分解、筛函数值、欧拉函数时更好用

### 3.5 质因数分解模板

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

来源：整理自 [bits/test/84.cpp](bits/test/84.cpp)

适用：

- 输出所有质因子
- 求最大质因子
- 统计每个质因子的次数

### 3.6 哥德巴赫猜想模板

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

来源：当前做题 [bits/test/103.cpp](bits/test/103.cpp)

关键理解：

- 质数表先筛出来
- 对每个偶数，从小到大找第一个可行质数 `p`
- 第一个找到的方案，天然就是“第一个加数最小”

## 4. 基础数学模板

### 4.1 向上取整

```cpp
int ceil_div(int a, int b) {
    return (a + b - 1) / b;
}
```

来源：[bits/test/03.cpp](bits/test/03.cpp)

### 4.2 最大公约数 / 最小公倍数

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

### 4.3 快速幂

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

如果担心乘法爆 `long long`，
直接用 [templates/fast_pow.hpp](templates/fast_pow.hpp)
里的 `mul_mod` + `mod_pow`。

## 5. 排序与贪心模板

### 5.1 普通排序

```cpp
sort(a.begin(), a.end());
sort(a.begin(), a.end(), greater<int>());
```

### 5.2 结构体排序

```cpp
struct Node {
    string name;
    int score;
};

bool cmp(const Node& a, const Node& b) {
    if (a.score != b.score) return a.score > b.score;
    return a.name < b.name;
}

sort(v.begin(), v.end(), cmp);
```

### 5.3 字符串拼接贪心

```cpp
sort(a.begin(), a.end(), [](const string& x, const string& y) {
    return x + y > y + x;
});
```

来源：[bits/test/18.cpp](bits/test/18.cpp)

适用：

- 最大数拼接
- 排列后比较整体字典序

## 6. 搜索、回溯、记忆化模板

### 6.1 组合回溯

```cpp
void dfs(const vector<int>& nums, int m, int start,
         vector<int>& path, vector<vector<int>>& ans) {
    if ((int)path.size() == m) {
        ans.push_back(path);
        return;
    }
    for (int i = start; i < (int)nums.size(); ++i) {
        path.push_back(nums[i]);
        dfs(nums, m, i + 1, path, ans);
        path.pop_back();
    }
}
```

来源：[bits/test/21.cpp](bits/test/21.cpp)

背诵点：

- 终止条件先写
- 选一个数
- 递归下一层
- 恢复现场

### 6.2 记忆化搜索

```cpp
int solve(int n, vector<int>& memo) {
    if (n <= 1) return 1;
    if (memo[n] != -1) return memo[n];
    return memo[n] = solve(n - 1, memo) + solve(n - 2, memo);
}
```

适用：

- 台阶问题
- 递归有重叠子问题
- 状态数量不大

### 6.3 三维 DP 预处理

```cpp
static int dp[21][21][21];

for (int a = 0; a <= 20; ++a) {
    for (int b = 0; b <= 20; ++b) {
        for (int c = 0; c <= 20; ++c) {
            if (a == 0 || b == 0 || c == 0) dp[a][b][c] = 1;
            else if (a < b && b < c) {
                dp[a][b][c] = dp[a][b][c - 1]
                            + dp[a][b - 1][c - 1]
                            - dp[a][b - 1][c];
            } else {
                dp[a][b][c] = dp[a - 1][b][c]
                            + dp[a - 1][b - 1][c]
                            + dp[a - 1][b][c - 1]
                            - dp[a - 1][b - 1][c - 1];
            }
        }
    }
}
```

来源：[bits/test/22.cpp](bits/test/22.cpp)

适用：

- 状态范围很小
- 可以先打表再回答多组询问

## 7. 前缀和、差分、区间统计模板

### 7.1 一维前缀和

```cpp
vector<long long> pre(n + 1, 0);
for (int i = 1; i <= n; ++i) {
    pre[i] = pre[i - 1] + a[i];
}

long long rangeSum(int l, int r) {
    return pre[r] - pre[l - 1];
}
```

### 7.2 一维差分

```cpp
vector<int> diff(n + 2, 0);
diff[l] += val;
diff[r + 1] -= val;

for (int i = 1; i <= n; ++i) {
    diff[i] += diff[i - 1];
}
```

适用：

- 多次区间加减
- 覆盖统计
- 可用于优化 [bits/test/10.cpp](bits/test/10.cpp) 这类区间题

## 8. 高精度模板

### 8.1 高精乘法

```cpp
string multiply_bigint(string a, string b) {
    if (a == "0" || b == "0") return "0";

    vector<int> A, B;
    for (int i = (int)a.size() - 1; i >= 0; --i) A.push_back(a[i] - '0');
    for (int i = (int)b.size() - 1; i >= 0; --i) B.push_back(b[i] - '0');

    vector<int> C((int)A.size() + (int)B.size() + 1, 0);
    for (int i = 0; i < (int)A.size(); ++i) {
        for (int j = 0; j < (int)B.size(); ++j) {
            C[i + j] += A[i] * B[j];
        }
    }

    for (int i = 0; i + 1 < (int)C.size(); ++i) {
        C[i + 1] += C[i] / 10;
        C[i] %= 10;
    }
    while (C.size() > 1 && C.back() == 0) C.pop_back();

    string ans;
    for (int i = (int)C.size() - 1; i >= 0; --i) {
        ans.push_back(char('0' + C[i]));
    }
    return ans;
}
```

来源：[bits/test/59.cpp](bits/test/59.cpp)

### 8.2 万进制压位

```cpp
vector<int> a = {1};
int carry = 0;
for (int i = 0; i < (int)a.size(); ++i) {
    long long cur = 1LL * a[i] * mul + carry;
    a[i] = (int)(cur % 10000);
    carry = (int)(cur / 10000);
}
while (carry > 0) {
    a.push_back(carry % 10000);
    carry /= 10000;
}
```

输出时：

```cpp
cout << a.back();
for (int i = (int)a.size() - 2; i >= 0; --i) {
    cout << setw(4) << setfill('0') << a[i];
}
```

来源：[bits/test/67.cpp](bits/test/67.cpp)

背诵点：

- 每个数组元素存 4 位
- 运算快于逐位十进制
- 输出时最高位直接输出，后面补齐 4 位

## 9. 输入处理模板

### 9.1 `cin` 和 `getline` 混用

```cpp
int n;
cin >> n;
cin.ignore(numeric_limits<streamsize>::max(), '\n');

string s;
getline(cin, s);
```

### 9.2 读到 EOF

```cpp
int x;
while (cin >> x) {
    cout << x << '\n';
}
```

### 9.3 拆一整行

```cpp
string line;
getline(cin, line);
stringstream ss(line);

string word;
while (ss >> word) {
    // 处理每个单词
}
```

代表题：[bits/test/14.cpp](bits/test/14.cpp)、[bits/test/16.cpp](bits/test/16.cpp)、[bits/test/19.cpp](bits/test/19.cpp)、[bits/test/input_template.md](bits/test/input_template.md)

## 10. 归并排序统计逆序对

```cpp
long long merge_count(vector<int>& a, vector<int>& tmp, int l, int r) {
    if (r - l <= 1) return 0;
    int m = l + (r - l) / 2;
    long long ans = merge_count(a, tmp, l, m) + merge_count(a, tmp, m, r);

    int i = l, j = m, k = l;
    while (i < m && j < r) {
        if (a[i] <= a[j]) tmp[k++] = a[i++];
        else {
            tmp[k++] = a[j++];
            ans += m - i;
        }
    }
    while (i < m) tmp[k++] = a[i++];
    while (j < r) tmp[k++] = a[j++];
    for (int t = l; t < r; ++t) a[t] = tmp[t];
    return ans;
}
```

适用：

- 逆序对统计
- 排序过程中顺便计数

## 11. 模板库速查

这一节不是让你手写全部，而是让你知道仓库里已经有现成模板，比赛时直接 include。

### 11.1 快速幂

```cpp
#include "templates/fast_pow.hpp"
```

- 函数：`mod_pow(a, e, mod)`
- 适用：快速幂、乘法可能溢出的取模幂

### 11.2 并查集

```cpp
#include "templates/dsu.hpp"
```

- 结构：`DSU dsu(n)`
- 常用：`find(x)`、`unite(a, b)`、`size(x)`
- 适用：连通块、合并集合、判环

### 11.3 树状数组

```cpp
#include "templates/fenwick.hpp"
```

- 结构：`Fenwick bit(n)`
- 常用：`add(idx, delta)`、`sum(idx)`、`rangeSum(l, r)`
- 适用：单点修改、前缀和、逆序对

### 11.4 线段树

```cpp
#include "templates/segment_tree.hpp"
```

- 结构：`SegTree st(n)`
- 常用：`build(a)`、`pointAdd(idx, delta)`、`query(l, r)`
- 适用：区间和、点修改

### 11.5 懒标记线段树

```cpp
#include "templates/lazy_segment_tree.hpp"
```

- 结构：`LazySegTree st(n)`
- 常用：`rangeAdd(l, r, val)`、`rangeSum(l, r)`
- 适用：区间加、区间求和

### 11.6 最短路 Dijkstra

```cpp
#include "templates/dijkstra.hpp"
```

- 图结构：`vector<vector<pair<int, int>>> g(n)`
- 调用：`auto dist = dijkstra(n, g, s);`
- 适用：非负权最短路

### 11.7 KMP

```cpp
#include "templates/kmp.hpp"
```

- 函数：`kmp_prefix(p)`、`kmp_search(s, p)`
- 适用：模式串匹配

### 11.8 Trie

```cpp
#include "templates/trie.hpp"
```

- 结构：`Trie trie;`
- 常用：`insert(s)`、`countPrefix(s)`、`countWord(s)`
- 适用：字典树、前缀统计

### 11.9 Sparse Table

```cpp
#include "templates/sparse_table.hpp"
```

- 结构：`SparseTable st;`
- 调用：`st.build(a, [](int x, int y) { return min(x, y); });`
- 适用：静态 RMQ、区间最值

### 11.10 LCA

```cpp
#include "templates/lca.hpp"
```

- 结构：`LCA lca(n, root)`
- 常用：`addEdge(u, v)`、`build()`、`lca(a, b)`
- 适用：树上最近公共祖先

## 12. 最值得背的 10 个模板

如果时间有限，优先背这 10 个：

1. 主程序骨架 + 快速 IO
2. 判质数
3. 埃氏筛
4. 质因数分解
5. 向上取整
6. 结构体排序
7. 组合回溯
8. 记忆化搜索
9. 高精乘法
10. `cin` 和 `getline` 混用

## 13. 做题时最容易错的点

- `cin >> n` 后直接 `getline`，会读到空行
- 判质数忘了处理 `x < 2`
- 循环上界写成 `i <= n` 导致越界
- 明明要 `long long`，却用了 `int`
- 回溯少写了 `pop_back()`
- 排序后忘了原下标已经变了
- 高精输出时忘了补前导 0
- 总和、乘积、平方时没有写 `1LL`
- `vector<vector<int>>` 读入时用了值拷贝而不是引用

## 14. 复习顺序建议

建议按这个顺序复习：

1. 输入模板
2. 模拟与枚举
3. 数学基础：向上取整、gcd、快速幂
4. 质数专题：判定、筛法、分解
5. 排序与结构体
6. 字符串处理
7. 回溯与记忆化
8. 高精度
9. 模板库：并查集、树状数组、线段树、最短路

## 15. 一句话背诵版

- 判质数：小于 2 假，偶数先删，试到根号。
- 筛质数：开表全真，从 2 开始，倍数删掉。
- 回溯：做选择，递归，撤销选择。
- 记忆化：先判边界，再查缓存，再算答案。
- 排序题：先想比较规则，再看排序后输出的含义。
- 高精：逆序存储，逐位运算，最后倒着输出。
