# 数据结构专项强化（两周）

目标：系统掌握常用与进阶数据结构，能在题目中快速选型与实现。

## 第 1 周：基础 + 经典（纯洛谷）
- 第1天：栈/单调栈
  - 题：P1739（括号匹配）、P5788（单调栈模板）、P4147（单调栈综合-最大矩形）
  - 模板：`monotonic_queue.hpp`（用于窗口）+ 手写栈
- 第2天：队列/双端队列（滑动窗口）
  - 题：P1886（滑动窗口最大/最小值）
  - 模板：`monotonic_queue.hpp`
- 第3天：堆/优先队列
  - 题：P1090（合并果子）、P1168（中位数）
  - STL：`priority_queue`
- 第4天：集合/映射/哈希
  - 题：P3370（字符串哈希去重）、P4305（不重复数字）
  - STL：`set/multiset/unordered_map`
- 第5天：并查集 DSU
  - 题：P1551（亲戚）、P3367（并查集模板）
  - 模板：`dsu.hpp`
- 第6天：树状数组 Fenwick
  - 题：P1908（逆序对）、P3374（树状数组 1）
  - 模板：`fenwick.hpp`
- 第7天：复盘 + 小测（6 题）
  - 内容：单调栈/队列、堆、哈希、DSU、Fenwick

## 第 2 周：线段树/Trie/倍增与 RMQ（纯洛谷）
- 第8天：线段树（点改/区间和）
  - 题：P3372（区间和/单点）
  - 模板：`segment_tree.hpp`
- 第9天：懒标记线段树（区间加/区间和）
  - 题：P3373（区间乘/加 + 区间和）
  - 模板：`lazy_segment_tree.hpp`
- 第10天：Trie（字典树）
  - 题：P2580（Trie 应用）
  - 模板：`trie.hpp`
- 第11天：RMQ（Sparse Table）
  - 题：P3865（ST 表模板，静态区间最值）
  - 模板：`sparse_table.hpp`
- 第12天：LCA + 倍增
  - 题：P3379（最近公共祖先）
  - 模板：`lca.hpp`
- 第13天：综合训练（区间 + 树上）
  - 题：线段树/树状数组与 LCA 混合 3–4 题（自选 P3372/P3374/P3379 等组合）
- 第14天：复盘 + 小测（6 题）
  - 内容：懒标记线段树、Trie、RMQ、LCA

— 练习方式 —
- 同日题型连做，先“模板化”再“变化题”；
- 复杂数据结构优先从模板改起，理解接口与时间复杂度；
- 每晚 10 分钟复盘，记录坑点与通用套路。

  ## 参考题单链接（纯洛谷，可点击）
  - 第1天 栈/单调栈：
    - P1739 表达式括号匹配：https://www.luogu.com.cn/problem/P1739
    - P5788 【模板】单调栈：https://www.luogu.com.cn/problem/P5788
    - P4147 玉蟾宫（最大全 1 矩形）：https://www.luogu.com.cn/problem/P4147
  - 第2天 队列/滑动窗口：
    - P1886 滑动窗口（维护最小/最大）：https://www.luogu.com.cn/problem/P1886
  - 第3天 堆/优先队列：
    - P1090 合并果子：https://www.luogu.com.cn/problem/P1090
    - P1168 中位数：https://www.luogu.com.cn/problem/P1168
  - 第4天 集合/哈希：
    - P3370 【模板】字符串哈希：https://www.luogu.com.cn/problem/P3370
    - P4305 不重复数字：https://www.luogu.com.cn/problem/P4305
  - 第5天 并查集 DSU：
    - P1551 亲戚：https://www.luogu.com.cn/problem/P1551
    - P3367 并查集模板：https://www.luogu.com.cn/problem/P3367
  - 第6天 树状数组 Fenwick：
    - P1908 逆序对：https://www.luogu.com.cn/problem/P1908
    - P3374 树状数组 1：https://www.luogu.com.cn/problem/P3374
  - 第8天 线段树（点改/区间和）：
    - P3372 线段树 1（区间和/单点）：https://www.luogu.com.cn/problem/P3372
  - 第9天 懒标记线段树（区间增量）：
    - P3373 线段树 2（区间乘/加+区间和）：https://www.luogu.com.cn/problem/P3373
  - 第10天 Trie：
    - P2580 于是他错误的点名了：https://www.luogu.com.cn/problem/P2580
  - 第11天 RMQ（ST 表）：
    - P3865 ST 表（RMQ 模板）：https://www.luogu.com.cn/problem/P3865
  - 第12天 LCA + 倍增：
    - P3379 最近公共祖先（倍增模板）：https://www.luogu.com.cn/problem/P3379
