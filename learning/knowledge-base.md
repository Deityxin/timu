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
