#include <bits/stdc++.h>
using namespace std ;

static bool isInt(const string &s){ return s != "n"; }
static bool mustZero(const string &x, const string &y){
    bool xi = isInt(x), yi = isInt(y);
    if (xi && yi) return stoi(x) > stoi(y);
    if (!xi && yi) return true;   // n > int
    if (xi && !yi) return false;  // int <= n
    return false;                 // n..n
}

int main () {
    int n ; 
    if (!(cin >> n)) return 0;
    vector<int> dig ;
    vector<string> s_ ;
    vector<string> s_1 ;
    dig.reserve(n); s_.reserve(n);
    for (int i = 0 ; i < n ; i++ ){
        int j ; string s0 ; 
        cin >> j >> s0 ;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 吃掉本行剩余
        dig.push_back(j);
        s_.push_back(s0) ;
        for(int b = 0 ; b < j ; b++){
            string lin ; 
            getline(cin , lin) ;
            s_1.push_back(lin) ;
        }
    }

    int pos = 0;
    for(int i = 0 ; i < n ; i ++){
        vector<string> parts ;
        int expect = 0;
        if (s_[i] == "O(1)") expect = 0;
        else {
            size_t p = s_[i].find('^');
            expect = stoi(s_[i].substr(p + 1, s_[i].size() - p - 2));
        }

        bool err = false;
        int cur = 0, best = 0;
        int noExecDepth = -1;
        vector<char> st_var;
        vector<int>  st_delta;
        vector<bool> st_openNo;
        int alive[26] = {0};

        for(int k = 0 ; k < dig[i] ; k++){
            string line = s_1[pos++];
            parts.clear();
            stringstream ss(line);
            string fen ;
            while(ss >> fen) parts.push_back(fen);
            if (parts.empty()) { err = true; break; }

            if (parts[0] == "F") {
                if (parts.size() != 4) { err = true; break; }
                char v = parts[1][0];
                string x = parts[2], y = parts[3];
                if (v == 'n') { err = true; break; }
                if (alive[v - 'a'] > 0) { err = true; }
                alive[v - 'a']++;

                bool alreadyNo = (noExecDepth != -1);
                bool zero = false;
                if (!alreadyNo) {
                    zero = mustZero(x, y);
                    if (zero) noExecDepth = (int)st_var.size();
                }

                int delta = 0;
                if (!alreadyNo && !zero) {
                    bool xi = isInt(x), yi = isInt(y);
                    if (xi && !yi) delta = 1;
                }

                st_var.push_back(v);
                st_delta.push_back(delta);
                st_openNo.push_back(!alreadyNo && zero);

                cur += delta;
                best = max(best, cur);
            } else if (parts[0] == "E") {
                if (st_var.empty()) { err = true; break; }
                char v = st_var.back(); st_var.pop_back();
                int d = st_delta.back(); st_delta.pop_back();
                bool openedNo = st_openNo.back(); st_openNo.pop_back();
                alive[v - 'a']--;
                cur -= d;
                if (openedNo && noExecDepth == (int)st_var.size())
                    noExecDepth = -1;
            } else {
                err = true; break;
            }
        }
        if (!st_var.empty()) err = true;
        if (err) cout << "ERR\n";
        else if (best == expect) cout << "Yes\n";
        else cout << "No\n";
    }
    return 0 ;
}