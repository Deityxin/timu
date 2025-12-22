#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
class Solution {
public:
    vector<vector<int>> combine(const vector<int>& nums, int m) {
        vector<vector<int>> result;
        vector<int> path;
        backtrack(nums, m, 0, path, result);
        return result;
    }
private:
    void backtrack(const vector<int>& nums, int m, int start,
                   vector<int>& path, vector<vector<int>>& result) {
        if ((int)path.size() == m) {
            result.push_back(path);
            return;
        }
        for (int i = start; i < (int)nums.size(); ++i) {
            path.push_back(nums[i]);
            backtrack(nums, m, i + 1, path, result);
            path.pop_back();
        }
    }
};
bool isPrime_optimized(int n) {
    if (n <= 1) {
        return false;
    }
    if (n == 2) {
        return true;
    }
    if (n % 2 == 0) {
        return false;
    }
    int limit = sqrt(n); 
    for (int i = 3; i <= limit; i += 2) { 
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}
int main (){
    int n , m;
    cin >> n >> m;
    vector<int> nums(n);
    vector<int> ab;
    for (int i = 0; i < n; ++i) cin >> nums[i];
    Solution sol;
    auto rel = sol.combine(nums , m);
    int count = 0;
    for (const auto& comb : rel) {
        int sum = 0;
        for (int x : comb) sum += x;
        if (isPrime_optimized(sum)) ++count;
    }
    cout << count;
    return 0;
}