# 输入处理专题模板

这份模板专门总结 `bits/test` 里最常见的输入方式。目标不是把所有情况都背下来，而是让你一看到题目输入格式，就能立刻选出合适写法。

参考代表题：14、15、16、19、22、31、39、59。

## 1. 通用主程序骨架

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    return 0;
}
```

适用场景：绝大多数竞赛题。

作用：
- 提高输入输出效率
- `cin` / `cout` 基本够用，不必急着写快读

## 2. 单个整数 / 多个整数

### 1. 读一个整数

```cpp
int n;
cin >> n;
```

### 2. 读一行里的多个整数

```cpp
int a, b, c;
cin >> a >> b >> c;
```

### 3. 防止输入失败

```cpp
int n;
if (!(cin >> n)) return 0;
```

适用场景：
- 不确定是否有输入
- 多组数据读到文件末尾

## 3. 先读 n，再读数组

```cpp
int n;
cin >> n;
vector<int> a(n);
for (int i = 0; i < n; ++i) cin >> a[i];
```

变体：读 `long long` 数组

```cpp
int n;
cin >> n;
vector<long long> a(n);
for (int i = 0; i < n; ++i) cin >> a[i];
```

常见坑：
- 数据范围大时还在用 `int`
- 数组大小开错
- 循环写成 `i <= n`

## 4. 读矩阵

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

适用场景：
- 地图
- 成绩表
- 二维覆盖问题
- 邻接矩阵

常见坑：
- 把 `n` 行 `m` 列写反
- 遍历输出时行列顺序混乱

## 5. 多组数据，读到 EOF

```cpp
int x;
while (cin >> x) {
    cout << x << '\n';
}
```

读两个数：

```cpp
int a, b;
while (cin >> a >> b) {
    cout << a + b << '\n';
}
```

适用场景：
- 输入不给组数
- 文件结束就是结束

代表题思路：和 [bits/test/22.cpp](bits/test/22.cpp)、[bits/test/31.cpp](bits/test/31.cpp) 的持续读取模式很接近。

## 6. 多组数据，读到特殊结束标记

### 1. 读到 `-1 -1 -1` 结束

```cpp
long long x, y, z;
while (cin >> x >> y >> z) {
    if (x == -1 && y == -1 && z == -1) break;
    cout << x << ' ' << y << ' ' << z << '\n';
}
```

### 2. 读字符直到 `E`

```cpp
vector<char> seq;
char ch;
while (cin >> ch) {
    if (ch == 'E') break;
    if (ch == 'W' || ch == 'L') seq.push_back(ch);
}
```

代表题：可参考 [bits/test/31.cpp](bits/test/31.cpp)。

关键点：
- 先判断终止条件
- 再决定是否存入容器

## 7. 读字符串但字符串里没有空格

```cpp
string s;
cin >> s;
```

适用场景：
- 大整数
- 单词
- 编码串
- 二进制串 / 数字串

代表题：可参考 [bits/test/59.cpp](bits/test/59.cpp)。

说明：
- 大整数不要读成 `long long`
- 直接读成 `string` 最稳

## 8. 读整行字符串

```cpp
string s;
getline(cin, s);
```

适用场景：
- 句子
- 含空格文本
- 原始一整行输入

代表题：可参考 [bits/test/14.cpp](bits/test/14.cpp)、[bits/test/15.cpp](bits/test/15.cpp)、[bits/test/16.cpp](bits/test/16.cpp)。

常见坑：
- 前面刚用了 `cin >> n`，这里直接 `getline` 会读到空行

## 9. `cin` 和 `getline` 混用

这是你最容易踩坑的一类。

### 正确写法

```cpp
int n;
cin >> n;
cin.ignore(numeric_limits<streamsize>::max(), '\n');

string line;
getline(cin, line);
```

为什么要 `ignore`：
- `cin >> n` 读完数字后，行末换行还留在缓冲区里
- 下一次 `getline` 会直接把这个空换行读走

代表题：可参考 [bits/test/39.cpp](bits/test/39.cpp)。

## 10. 读若干整行，直到某个结束单词

```cpp
string all_text, line;
while (getline(cin, line) && line != "EOF") {
    if (!all_text.empty()) all_text.push_back('\n');
    all_text += line;
}
```

适用场景：
- 多行文本输入
- 文本编辑模拟
- 特殊输入块

代表题：可参考 [bits/test/19.cpp](bits/test/19.cpp)。

常见坑：
- Windows 文本可能带 `\r`
- 如果题目需要精确比较行内容，可能要手动去掉结尾 `\r`

例如：

```cpp
if (!line.empty() && line.back() == '\r') line.pop_back();
```

## 11. 用 `stringstream` / `istringstream` 拆一整行

### 1. 把一整行拆成若干单词

```cpp
string line;
getline(cin, line);
stringstream ss(line);

string word;
vector<string> parts;
while (ss >> word) {
    parts.push_back(word);
}
```

### 2. 用于每行有名字、数字、标记混合输入

```cpp
int n;
cin >> n;
cin.ignore(numeric_limits<streamsize>::max(), '\n');

vector<vector<string>> rows(n);
for (int i = 0; i < n; ++i) {
    string line;
    getline(cin, line);
    stringstream ss(line);
    string token;
    while (ss >> token) rows[i].push_back(token);
}
```

代表题：可参考 [bits/test/39.cpp](bits/test/39.cpp)。

适用场景：
- 每行字段数固定，但字段类型混合
- 题目给的是“整行记录”

## 12. 字符串转数字

### 1. 用 `stoi`

```cpp
string s = "12345";
int x = stoi(s);
```

### 2. 用字符减 `'0'`

```cpp
char ch = '7';
int x = ch - '0';
```

适用场景：
- `stoi`：多位数字字符串
- `ch - '0'`：单个数字字符

代表题：可参考 [bits/test/17.cpp](bits/test/17.cpp)、[bits/test/15.cpp](bits/test/15.cpp)。

常见坑：
- 非法字符直接 `stoi`
- 大整数还想用 `stoi`

## 13. 读大整数

```cpp
string a, b;
cin >> a >> b;
```

后面自己写高精加减乘除。

代表题：可参考 [bits/test/59.cpp](bits/test/59.cpp)、[bits/test/67.cpp](bits/test/67.cpp)。

记住：
- 超过 `long long` 范围的数，一律先按字符串读

## 14. 字符串大小写处理

```cpp
for (char& ch : s) {
    ch = tolower(static_cast<unsigned char>(ch));
}
```

代表题：可参考 [bits/test/16.cpp](bits/test/16.cpp)。

为什么这么写：
- 更稳，避免字符为负时直接传给 `tolower` 的未定义风险

## 15. 常用输入辅助函数

### 1. 拆分整行

```cpp
vector<string> split_words(const string& line) {
    stringstream ss(line);
    vector<string> parts;
    string word;
    while (ss >> word) parts.push_back(word);
    return parts;
}
```

### 2. 清理换行

```cpp
void clear_newline() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
```

### 3. 去掉行尾 `\r`

```cpp
void trim_cr(string& s) {
    if (!s.empty() && s.back() == '\r') s.pop_back();
}
```

## 16. 输入处理的高频易错点

### 1. `getline` 读到空串
- 根因：前面用了 `cin >>`，但没 `ignore`

### 2. 明明是大整数，却读成 `int` / `long long`
- 根因：没看清数据范围

### 3. 题目是多组数据，却只写了一次读取
- 根因：没注意 EOF 或结束标记

### 4. 文本题把空格读没了
- 根因：该用 `getline` 的地方用了 `cin >> s`

### 5. 逐字符题没先过滤无效字符
- 根因：终止字符和有效字符混在一起时，逻辑顺序写错

### 6. 一行记录里字段很多，直接硬写 `cin >>`
- 根因：没意识到更适合 `getline + stringstream`

## 17. 一张输入格式判断表

看到题面输入格式时，先这样判断：

### 1. 没空格、没整行文本
- 用 `cin >>`

### 2. 有整行句子、空格有意义
- 用 `getline`

### 3. 先有数字，再有整行文本
- `cin >> ...` 后加 `cin.ignore(...)`

### 4. 输入组数未知
- `while (cin >> ...)`

### 5. 输入到特定标记结束
- 在循环里判断 `break`

### 6. 一整行里有多个字段，类型混合
- `getline + stringstream`

### 7. 数值特别大
- 先按 `string` 读

## 18. 你现阶段最该背熟的 6 个输入模板

如果只背最常用的，先背这 6 个：

### 1. `n + 数组`
### 2. `n m + 矩阵`
### 3. `getline` 读整行
### 4. `cin + getline` 混用
### 5. `while (cin >> ...)` 读到 EOF
### 6. `getline + stringstream` 拆记录

把这 6 个写熟，你现在 test 目录里至少一大半输入都能稳住。
