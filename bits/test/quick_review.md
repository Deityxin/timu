# 考前速查版

适用范围：`bits/test` 这批题最常见的基础题型、输入写法、函数模板和易错点。

## 1. 先判断题型

- 模拟：按题意一步一步写，先列规则再写循环
- 枚举：范围不大，直接枚举所有可能
- 排序：先排再统计、去重、比较、贪心
- 字符串：先想清楚按词处理还是按整行处理
- 数学：先化简公式，再决定要不要枚举
- 递归 / 回溯：先写终止条件，再写搜索和恢复现场
- DP：先想状态、转移、初始化

## 2. 输入格式速判

- 没空格：`cin >> s`
- 一行句子、空格有意义：`getline(cin, s)`
- 先读数字再读整行：`cin.ignore(...)` 后再 `getline`
- 组数未知：`while (cin >> x)`
- 有结束标记：循环里 `break`
- 一整行里字段混合：`getline + stringstream`
- 大整数：先按 `string` 读

## 3. 最常用的 6 个输入模板

### 1. `n + 数组`

```cpp
int n;
cin >> n;
vector<int> a(n);
for (int i = 0; i < n; ++i) cin >> a[i];
```

### 2. `n m + 矩阵`

```cpp
int n, m;
cin >> n >> m;
vector<vector<int>> a(n, vector<int>(m));
for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
        cin >> a[i][j];
    }
}
```

### 3. 读整行

```cpp
string s;
getline(cin, s);
```

### 4. `cin + getline` 混用

```cpp
int n;
cin >> n;
cin.ignore(numeric_limits<streamsize>::max(), '\n');
string s;
getline(cin, s);
```

### 5. 读到 EOF

```cpp
int x;
while (cin >> x) {
    // process
}
```

### 6. 拆一整行记录

```cpp
string line;
getline(cin, line);
stringstream ss(line);
string token;
while (ss >> token) {
    // process
}
```

## 4. 最常用函数

### 数学
- `sqrt(x)`：开方、判质数上界、几何距离
- `abs(x)`：绝对值
- `stoi(s)`：字符串转整数
- `static_cast<double>(x)`：避免整除

### 字符串
- `to_string(x)`：数字转字符串
- `getline(cin, s)`：读整行
- `tolower(ch)`：统一转小写
- `isdigit(ch)`：判断数字字符
- `substr(pos, len)`：截取子串
- `reverse(begin, end)`：反转

### 容器和算法
- `sort(a.begin(), a.end())`
- `sort(a.begin(), a.end(), cmp)`
- `push_back(x)` / `pop_back()`
- `size()` / `resize(n)` / `back()`
- `max(x, y)` / `min(x, y)`

### 输出格式
- `fixed << setprecision(2)`
- `setw(2) << setfill('0')`

## 5. 高频模板

### 1. 向上取整

```cpp
int ceil_div(int a, int b) {
    return (a + b - 1) / b;
}
```

### 2. 质数判断

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

### 3. 回溯

```cpp
void dfs(const vector<int>& nums, int start, vector<int>& path) {
    for (int i = start; i < (int)nums.size(); ++i) {
        path.push_back(nums[i]);
        dfs(nums, i + 1, path);
        path.pop_back();
    }
}
```

### 4. 记忆化

```cpp
int solve(int n, vector<int>& memo) {
    if (n <= 1) return 1;
    if (memo[n] != -1) return memo[n];
    return memo[n] = solve(n - 1, memo) + solve(n - 2, memo);
}
```

### 5. 高精乘法核心

```cpp
for (int i = 0; i < (int)A.size(); ++i) {
    for (int j = 0; j < (int)B.size(); ++j) {
        C[i + j] += A[i] * B[j];
    }
}
for (int i = 0; i + 1 < (int)C.size(); ++i) {
    C[i + 1] += C[i] / 10;
    C[i] %= 10;
}
```

## 6. 最容易错的地方

- `cin >>` 后直接 `getline`，读到空行
- `i <= n` 导致越界
- 本该用 `long long` 却用了 `int`
- 忘记处理负号、前导零、特殊字符 `X`
- `pop_back()` 忘了写，回溯状态没恢复
- 排序后还拿排序前含义去理解下标
- 整数除法误当小数除法
- 少空行、多空格、格式不符
- 没先看数据范围就上暴力

## 7. 做题 30 秒检查表

- 输入该用 `cin` 还是 `getline`？
- 要不要 `ignore`？
- 要不要 `long long`？
- 是先找规律还是直接模拟？
- 有没有边界：空、1 个、最小值、最大值？
- 输出格式有没有前导零、小数位、空行要求？

## 8. 现阶段最值得回看的一组题

- 03：向上取整
- 04：过程模拟
- 07xiugai：数学推导
- 16：字符串匹配
- 19：特殊输入块
- 21：回溯
- 22：三维 DP
- 25：记忆化搜索
- 35：逆序对
- 59：高精乘法
- 67：高精加法与压位
- 79修改：回文构造 + 判质数
- 91：递归构造
- 94：公式化简

## 9. 临场原则

- 先看输入，再定写法
- 先看范围，再定复杂度
- 先找规律，再写代码
- 先保正确，再谈优化
