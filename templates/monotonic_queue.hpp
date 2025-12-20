#pragma once
#include <bits/stdc++.h>
using namespace std;

// 单调队列维护窗口最大值（或最小值），调用者传入比较逻辑
template<class T, class Cmp = less<T>>
struct MonotonicQueue {
    deque<pair<T,int>> dq; // (value, index)
    Cmp cmp; // 默认 less：维护非降序（用于求最小值）。若要最大值，传 greater<T>
    void push(T val, int idx){
        while(!dq.empty() && !cmp(dq.back().first, val)) dq.pop_back();
        dq.emplace_back(val, idx);
    }
    void pop(int left_idx){
        if(!dq.empty() && dq.front().second < left_idx) dq.pop_front();
    }
    T best() const { return dq.front().first; }
};
