#include <bits/stdc++.h>
using namespace std;
int main() {
	int n;
	cin >> n;
	vector<int> win(34, 0);
	for (int i = 0; i < 7; i++) {
		int x;
		cin >> x;
		win[x] = 1;
	}
	vector<int> ans(7, 0);
	for (int i = 0; i < n; i++) {
		int cnt = 0;
		for (int j = 0; j < 7; j++) {
			int x;
			cin >> x;
			cnt += win[x];
		}
		if (cnt >= 1) {
			ans[7 - cnt]++;
		}
	}
	for (int i = 0; i < 7; i++) {
		if (i) cout << ' ';
		cout << ans[i];
	}
	cout << '\n';
	return 0;
}

