# test 文件夹总复习模板

本模板结合 `bits/test` 下现有题目代码、`fuxi.md` 与 `newfuxi.md` 的复盘内容整理，目标不是逐题抄答案，而是把你已经写过的内容压缩成一套可重复使用的复习框架。

## 1. 当前 test 文件夹的知识图谱

从现有代码看，`bits/test` 里的题主要集中在下面这些方向：

### 1. 基础输入输出与格式控制
- `cin` / `cout` 的基础读写
- `fixed << setprecision(n)` 控制小数位数
- `setw(n)` + `setfill('0')` 控制前导零输出
- 多组输出之间的空格、换行、末尾换行控制

代表题：01、14、31、67、92、93、94

### 2. 模拟与枚举
- 按题意一步一步推过程
- 按天、按月、按轮、按顺序模拟
- 用循环枚举所有可能情况
- 先找规律，再落代码，避免直接暴力乱写

代表题：04、05、09、10、11、12、19、29、30、31、91、92

### 3. 数学与公式推导
- 向上取整
- 三角数与开方定位
- 调和级数累加
- 回文数构造
- 质数判断与质因数分解
- 公式化简后枚举

代表题：03、06、07、07xiugai、17、23、26、26优化、79修改、84、94

### 4. 排序、贪心与自定义比较
- `sort` 默认排序
- 自定义比较函数 / lambda
- 先排序，再统计、去重、贪心或构造答案

代表题：13、18、35、36、37、38、64、66、70、71、72、79修改、82、83、89、93

### 5. 字符串处理
- 整行输入
- 忽略大小写比较
- 数字字符串转整数
- 退格模拟
- 字符串拼接与反转
- 分词、解析、过滤

代表题：08、14、15、16、19、34未完成、39、47、59

### 6. 递归、回溯与记忆化
- 组合枚举
- 递归搜索
- 记忆化搜索
- 自顶向下递归 + 备忘录

代表题：20、21、24、25、91

### 7. 动态规划
- 记忆化 DP
- 递推 DP
- 三维 DP 预处理

代表题：22、24、25

### 8. 高精度与大整数
- 高精乘法
- 高精阶乘和
- 逆序存储每一位
- 万进制压位

代表题：59、67

### 9. 数组、vector 与矩阵
- 一维数组统计
- 二维矩阵输入
- `vector<vector<int>>` 建图或建表
- 用矩阵做覆盖、分块、递归构造

代表题：05、10、13、27、30、33、38、89、91

## 2. 你现在最常用的函数和 API

下面这些是你在 test 文件夹里已经实际用过、值得反复熟悉的内容。

### 1. 数学类
- `sqrt(x)`：开方，常用于三角数定位、质数判断上界、几何距离
- `abs(x)`：绝对值，常用于比分差、距离差
- `stoi(s)`：字符串转整数
- `static_cast<double>(x)`：显式类型转换，避免整除和精度问题

### 2. 字符串类
- `to_string(x)`：整数转字符串
- `getline(cin, s)`：读一整行
- `tolower(ch)`：转小写，做大小写无关匹配
- `isdigit(ch)`：判断字符是否为数字
- `reverse(s.begin(), s.end())`：字符串或数组反转
- `substr(pos, len)`：截取子串

### 3. 排序与算法类
- `sort(a.begin(), a.end())`：默认升序排序
- `sort(a.begin(), a.end(), cmp)`：自定义比较
- `max(x, y)` / `min(x, y)`：取最大最小值

### 4. 容器类
- `vector<int> a(n)`：定义长度为 `n` 的数组
- `vector<vector<int>> a(n, vector<int>(m))`：定义 `n * m` 矩阵
- `push_back(x)`：尾插
- `pop_back()`：删除最后一个元素
- `size()`：获取长度
- `resize(n)`：调整大小
- `back()`：最后一个元素

### 5. 输入解析类
- `stringstream ss(line)`：把整行拆成多个字段
- `istringstream ss(line)`：适合逐词读字符串
- `cin.ignore(numeric_limits<streamsize>::max(), '\n')`：清理 `cin` 后残留换行

### 6. 输出格式类
- `fixed << setprecision(2)`：保留两位小数
- `setw(2)`：输出宽度至少为 2
- `setfill('0')`：空位补 0

## 3. 你最常见的题型写法模板

### 1. 单组整数输入

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    cout << n << '\n';
    return 0;
}
```

### 2. 一行多个整数

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int a, b, c;
    cin >> a >> b >> c;
    cout << a + b + c << '\n';
    return 0;
}
```

### 3. 先读 n，再读数组

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];

    for (int i = 0; i < n; ++i) {
        cout << a[i] << (i + 1 == n ? '\n' : ' ');
    }
    return 0;
}
```

### 4. 读矩阵

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(n, vector<int>(m));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> a[i][j];
        }
    }

    return 0;
}
```

### 5. 读整行字符串

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    getline(cin, s);
    cout << s << '\n';
    return 0;
}
```

### 6. `cin` 和 `getline` 混用

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string s;
    getline(cin, s);
    cout << s << '\n';
    return 0;
}
```

### 7. 读到 EOF 结束

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int x;
    while (cin >> x) {
        cout << x << '\n';
    }
    return 0;
}
```

### 8. 读到特定结束标记

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    string line;
    while (getline(cin, line) && line != "EOF") {
        cout << line << '\n';
    }
    return 0;
}
```

### 9. 用 `stringstream` 拆一整行

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    string line;
    getline(cin, line);
    stringstream ss(line);

    string word;
    vector<string> parts;
    while (ss >> word) parts.push_back(word);

    cout << parts.size() << '\n';
    return 0;
}
```

## 4. 你最常见的函数模板

### 1. 质数判断

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

### 2. 最大公约数

```cpp
int gcd_int(int a, int b) {
    while (b != 0) {
        int t = a % b;
        a = b;
        b = t;
    }
    return a;
}
```

### 3. 向上取整

```cpp
int ceil_div(int a, int b) {
    return (a + b - 1) / b;
}
```

### 4. 组合回溯模板

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

### 5. 记忆化搜索模板

```cpp
int solve(int n, vector<int>& memo) {
    if (n <= 1) return 1;
    if (memo[n] != -1) return memo[n];
    return memo[n] = solve(n - 1, memo) + solve(n - 2, memo);
}
```

### 6. 归并排序统计逆序对

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

### 7. 高精乘法模板

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
    for (int i = (int)C.size() - 1; i >= 0; --i) ans.push_back(char('0' + C[i]));
    return ans;
}
```

## 5. 你在 test 里最容易错的地方

### 1. 输入相关
- `cin >> n` 之后直接 `getline`，会读到空行
- 多组输入题没有写 `while (cin >> x)` 或终止条件
- 把字符串整行题写成逐词读取，导致空格丢失

### 2. 边界相关
- 1-based 和 0-based 混用
- 最后一项、第一项、空数组、只有一个元素时没单独处理
- 负号、前导零、特殊字符 `X` 处理不完整
- `a - 2`、`n - 1` 这种表达式在小数据时可能变成 0 或负数

### 3. 类型相关
- 本该用 `long long` 的地方用了 `int`
- 浮点数比较和整除混在一起
- `sqrt` 返回的是浮点，转回整数时需要谨慎

### 4. 递归与记忆化
- 没写终止条件
- 备忘录初值和合法值冲突
- 回溯时忘记 `pop_back()`
- 状态设计不完整，导致重复搜索

### 5. 排序与比较函数
- 比较器不满足严格弱序
- 排序后忘了题目要求是原下标还是排序后值
- 排序前后数据语义变化，没有重新定义变量含义

### 6. 输出格式
- 题目要求保留两位小数却直接输出整数除法结果
- 行末多空格
- 缺空行或多空行
- 前导零题没用 `setw + setfill`

## 6. 做题时的检查清单

每写完一道题，强制过一遍下面这张表：

### 1. 题型判断
- 这是模拟、枚举、排序、贪心、字符串、递归还是 DP？
- 能不能先写出规律或公式，而不是直接上代码？

### 2. 输入输出
- 是逐个读，还是整行读？
- 有多组数据吗？
- 有结束标记吗？
- 输出是空格分隔、换行分隔，还是固定格式？

### 3. 边界
- 最小值、最大值、空值、只有一项时是否正确？
- 有没有越界？
- 是否需要 `long long`？

### 4. 复杂度
- 现在写的是暴力还是优化？
- 数据范围是否允许当前做法？

## 7. 可以直接复制使用的复盘模板

以后每做完一题，直接按下面这份模板记。

```text
题号：
题型：

一、题目本质
这题是在考什么：模拟 / 枚举 / 排序 / 贪心 / 字符串 / 递归 / DP / 数学。

二、核心思路
1. 先做什么。
2. 再做什么。
3. 最后如何得到答案。

三、关键代码点
1. 用到了哪些函数或容器。
2. 哪一步最容易写错。
3. 有没有固定模板可以套。

四、复杂度
时间复杂度：
空间复杂度：

五、易错点
1. 输入坑。
2. 边界坑。
3. 类型坑。
4. 输出格式坑。

六、能否优化
当前做法是否能过。
有没有更优做法。

七、下次看到什么题面特征，应该立刻想到这题
```

## 8. 现阶段最值得反复复习的题

如果你只想挑最有代表性的题反复看，优先看下面这些：

- 03：向上取整与封装函数
- 04：过程模拟与提前退出
- 07xiugai：数学推导与三角数定位
- 16：字符串整行输入与大小写处理
- 19：特殊输入块与退格模拟
- 21：组合回溯
- 22：三维 DP 预处理
- 25：记忆化搜索
- 35：归并统计逆序对
- 59：高精乘法
- 67：高精加法与万进制压位
- 79修改：构造回文数 + 质数判断
- 91：递归构造矩阵
- 94：公式化简后枚举

## 9. 一句话总结你这批代码的训练重点

你这批代码的核心训练价值，不在于高级算法很多，而在于你已经把竞赛里最常见的基础能力都碰到了：输入处理、模拟、字符串、排序、数学推导、递归、记忆化、高精度和格式输出。后面复习时不要只看“这题答案怎么写”，而要反复问自己：

- 这题是什么模型？
- 我为什么一开始没想到？
- 这题里哪一段代码能变成以后直接复用的模板？
