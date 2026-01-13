# test 文件夹函数与用法速记

## 基础函数封装
- [bits/test/01.cpp](bits/test/01.cpp)：`he(x,y)` 纯函数做加法，返回值类型设成 `long long` 避免溢出。
- [bits/test/03.cpp](bits/test/03.cpp)：`minium`、`price` 分拆逻辑；包装计算时先整除再补 1 包；注意参数顺序一致。
- [bits/test/04.cpp](bits/test/04.cpp)：用全局变量配合 `price_total`、`price_last`；提前退出用 `exit(0)`，并在每月结算后对 100 元整块归档（避免重复扣减）。
- [bits/test/05.cpp](bits/test/05.cpp)：`maximum` 找最晚超过 8 小时的天；拆成 `output`→`compare`→`maximum` 保持职责单一。
- [bits/test/06.cpp](bits/test/06.cpp)：`sequence` 生成调和级数，`compare` 遍历求和直到首次超过阈值；大数据建议边加边判，避免巨型数组。
- [bits/test/07xiugai.cpp](bits/test/07xiugai.cpp)：`prepare` 先求对角线编号，再依据奇偶决定分子分母走向；示范辅助函数改良主逻辑。
- [bits/test/20.cpp](bits/test/20.cpp)：`legal(n)` 递归+备忘录统计整数拆分，`digit_` 预分配并缓存。
- [bits/test/21.cpp](bits/test/21.cpp)：`combine` 回溯生成组合，配合 `isPrime_optimized`（只试奇数到 √n）统计素数和。
- [bits/test/22.cpp](bits/test/22.cpp)：三维 `dp` 预处理 `w(a,b,c)`；读入后直接查表，边界 (≤0→1，>20→dp[20][20][20])。
- [bits/test/24.cpp](bits/test/24.cpp)：台阶问题 `fin(N,K,mem)` 递归记忆化，返回前取模。
- [bits/test/25.cpp](bits/test/25.cpp)：`solve(sum, parts, minVal)` 递归/记忆化求非降整数拆分数；上界 `upper=sum/parts` 防止无效枚举。
- [bits/test/27.cpp](bits/test/27.cpp)：`xun` 自后向前扫描矩形列表，找到最上层覆盖点的编号。

## 输入输出与字符串处理
- [bits/test/08.cpp](bits/test/08.cpp)：把整数转字符串反向输出，正负数分别处理，先丢弃前导 0。
- [bits/test/10.cpp](bits/test/10.cpp)：区间伐木，`start_data` 以 0/1 记录是否保留，嵌套循环易退化，需注意 O(L·M)。
- [bits/test/11.cpp](bits/test/11.cpp)：读到 0 截止并逆序输出；用 `do...while` 收尾元素。
- [bits/test/13.cpp](bits/test/13.cpp)：读取考试日程，按天去重统计所用试卷；`day[k]` 收集出现的卷号，最后用 `seen` 去重。
- [bits/test/14.cpp](bits/test/14.cpp)：`getline` 读整行统计非空白字符；变量名保持一致（示例里 `c`/`s` 易写错）。
- [bits/test/15.cpp](bits/test/15.cpp)：ISBN 校验，遍历字符串时只取数字，最后一位可能为 `X`。
- [bits/test/16.cpp](bits/test/16.cpp)：忽略大小写匹配单词次数；逐词比较避免子串误判，返回首次位置。
- [bits/test/17.cpp](bits/test/17.cpp)：枚举回文日期；`is_leap`、`days_in_month` 拆开便于复用。
- [bits/test/18.cpp](bits/test/18.cpp)：最大数拼接，排序比较 `x+y` 与 `y+x`；全 0 时输出单个 0。
- [bits/test/19.cpp](bits/test/19.cpp)：处理带退格的两段文本（`<` 删除前一字符但不跨行），计算相同字符数并换算 WPM；用字符串重建避免直接在原文本上删。
- [bits/test/29.cpp](bits/test/29.cpp)：自定义“拳”规则函数 `fin(a,b)` 判胜负，循环序列对局时用取模展开。
- [bits/test/30.cpp](bits/test/30.cpp)：转向+报数模拟，`lookfor` 根据朝向决定逆/顺时针移动并取模。

## 数学与模拟
- [bits/test/02.cpp](bits/test/02.cpp)：纯算式 `total_money/price`；注意整除截断。
- [bits/test/04.cpp](bits/test/04.cpp)：理财模拟，每月先+300 再扣款，再存整百；`have_money` 负数直接退出。
- [bits/test/06.cpp](bits/test/06.cpp)：累加浮点，边加边比较减少误差累积。
- [bits/test/07xiugai.cpp](bits/test/07xiugai.cpp)：三角序列找分数，先算对角线，再决定分子/分母方向。
- [bits/test/09.cpp](bits/test/09.cpp)：苹果高度统计，bench=30；两层条件能合并（`<=max+bench`）。
- [bits/test/12.cpp](bits/test/12.cpp)：三重循环判 `num[j]==num[k]+num[l]`；可用排序+双指针降为 O(n^2)。
- [bits/test/20.cpp](bits/test/20.cpp)：递推整数拆分；记忆数组初始全 0 时需对 n=0 特判。
- [bits/test/21.cpp](bits/test/21.cpp)：组合求和判素数；剪枝：当前和 + 剩余最小值/最大值越界时可提前返回。
- [bits/test/23.cpp](bits/test/23.cpp)：等差数列求和 `((a+fin)*c)/2`，使用 `long long` 防止溢出。
- [bits/test/24.cpp](bits/test/24.cpp)：楼梯走法枚举 1..K 步，记忆化避免指数爆炸。
- [bits/test/25.cpp](bits/test/25.cpp)：整数拆分数（非降序）；递归参数 `minVal` 约束单调性。
- [bits/test/26.cpp](bits/test/26.cpp)：先求完整斐波那契再取模，空间大；注释提示应边模边算。
- [bits/test/26优化.cpp](bits/test/26优化.cpp)：改为在线取模并寻找序列重置 `(0,1)` 的最短周期（Pisano）。

## 常见易错点速记
- `exit(0)` 直接结束进程，调用前确保输出完毕（[bits/test/04.cpp](bits/test/04.cpp)）。
- 全局/静态数组默认 0，但备忘录用 0 可能与合法值冲突时要单独处理 n=0（[bits/test/20.cpp](bits/test/20.cpp)）。
- `getline` 与 `cin` 混用需清理换行；变量名要一致（[bits/test/14.cpp](bits/test/14.cpp)）。
- 字符退格模拟不要跨行删除，重建字符串更安全（[bits/test/19.cpp](bits/test/19.cpp)）。
- 组合/递归类函数注意上界与剪枝，防止爆栈或超时（[bits/test/21.cpp](bits/test/21.cpp)、[bits/test/25.cpp](bits/test/25.cpp)）。
- 模运算的周期性可大幅降复杂度，斐波那契取模应边算边模并检测 `0,1` 循环（[bits/test/26优化.cpp](bits/test/26优化.cpp)）。
- 处理字符串数字反转、ISBN 校验时谨慎对待负号和末位 `X`（[bits/test/08.cpp](bits/test/08.cpp)、[bits/test/15.cpp](bits/test/15.cpp)）。

> 以上整理侧重函数拆分、调用方式与易踩坑点，可按题目编号快速回查示例实现。