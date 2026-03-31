# Competitive Programming Knowledge Base
This file is automatically updated by the `/cp-archive` agent.

## Archive

### [P1319] 压缩技术 (Compression)

**Algorithm**: `Simulation`, `Streaming`, `Implementation` (Simu/Impl)
**Difficulty**: `Easy`
**Result**: AC

#### 💡 Key Insight
1.  **流式处理 (Streaming)**: 不需要先构建整个 $N \times N$ 矩阵（这会占用 $O(N^2)$ 空间），而是读到一个压缩长度就直接输出对应数量的字符。这就把空间复杂度从 $O(N^2)$ 降到了 $O(1)$。
2.  **状态翻转技巧**: 使用 `val = 1 - val` 来在 0 和 1 之间切换，非常简洁。

#### 🔥 Pitfalls & Edge Cases
1.  **无限循环风险**: 如果仅用 `while(cin >> len)`，当输入总和不等于 $N^2$ 时可能会死循环或输出过多。必须加上 `cnt < n * n` 的限制。
2.  **换行控制**: 每输出 $N$ 个字符换一行，需要维护一个全局计数器 `cnt` 并判断 `cnt % n == 0`。

#### 📝 Code Snippet (Core Logic Only)
```cpp
int val = 0; // 题目要求从 0 开始
while (cnt < n * n && cin >> len) {
    for (int k = 0; k < len; k++) {
        cout << val;
        cnt++;
        if (cnt % n == 0) cout << "\n"; // 每满 N 个换行
    }
    val = 1 - val; // 0 <-> 1 翻转
}
```

### [P1553] 数字反转（升级版）

**Algorithm**: `字符串处理, 模拟`
**Difficulty**: `EASY`
**Result**: AC

#### 💡 Key Insight
> 纯字符串处理：先识别类型（优先分数'/' → 小数'.' → 百分数'%' → 整数），然后按题意对对应部分逐段反转并按规则去除多余的0（整数：反转后不能有高位0；小数：反转小数部分后去除末尾多余的0；分数：分别反转分子和分母；百分数：只改变数字并在末尾加'%'）。全程避免转换为数值类型以免溢出或丢失格式。

#### 🔥 Pitfalls & Edge Cases
> - 注意“全部被删后要输出单个 0”。
> - 小数部分反转后要去掉末尾的多余 `0`（若只剩 `0`，保留一个 `0`）。
> - 分数不约分且分母不为 0。
> - 输入不会含负号；不要把字符串转为数值处理（位数可能超过整型范围）。
> - 保证按原结构（整数/小数/分数/百分数）输出，不交换部分位置。

#### 📝 Code Snippet (Core Logic Only)
```cpp
void reverse_num(string s){
    int l=0, r=(int)s.size()-1;
    while(l<=r && s[l]=='0') l++;
    while(l<=r && s[r]=='0') r--;
    if(l>r) cout<<"0";
    else for(int i=r;i>=l;i--) cout<<s[i];
}
string s;
getline(cin,s);
if(s.find('/')!=string::npos){ /* 处理 num/den */ }
else if(s.find('.')!=string::npos){ /* 处理小数 */ }
else if(s.back()=='%'){ /* 处理百分数 */ }
else { /* 处理整数 */ }
```

- 代码来源： [bits/test/130.cpp](bits/test/130.cpp)

