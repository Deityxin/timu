#include <bits/stdc++.h>
using namespace std;
int main(){
    const int n = 100;
    map<pair<int,int>, int> mp;
    int x = 0, y = 0;
    mp[{x, y}] = n;
    int k = n - 1, step = 1, dir = 0;
    const int dx[4] = {1, 0, -1, 0};
    const int dy[4] = {0, 1, 0, -1};
    int minX=0, maxX=0, minY=0, maxY=0;

    while (k > 0){
        for (int rep = 0; rep < 2 && k > 0; ++rep){
            for (int s = 0; s < step && k > 0; ++s){
                x += dx[dir];
                y += dy[dir];
                mp[{x, y}] = k--;
                minX = min(minX, x); maxX = max(maxX, x);
                minY = min(minY, y); maxY = max(maxY, y);
            }
            dir = (dir + 1) % 4;
        }
        ++step;
    }
    int rows = maxY - minY + 1, cols = maxX - minX + 1;
    vector<vector<int>> grid(rows, vector<int>(cols, 0));
    for (auto &kv : mp){
        int cx = kv.first.first, cy = kv.first.second;
        grid[cy - minY][cx - minX] = kv.second;
    }
    for (int r = 0; r < rows; ++r){
        for (int c = 0; c < cols; ++c){
            if (c) cout << ' ';
            cout << grid[r][c];
        }
        cout << '\n';
    }
    return 0;
}