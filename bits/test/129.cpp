 #include <iostream>
 using namespace std;
 int main(){
    string s;
    cin >> s;
    int tem = 0;
    int ans = 0;
    for(int i = 0; i < s.size() ; i++){
         if (s[i] == 'b') tem ++;
		if (s[i] == 'o' && s[i-1] != 'b') tem++;
		if (s[i] == 'y' && s[i-1] !='o'&& s[i-2] != 'b') tem++;
		if (s[i] == 'g') ans++;
		if (s[i] == 'i'&& s[i-1] != 'g') ans++;
		if (s[i] == 'r'&& s[i-1] != 'i' && s[i-2] != 'g') ans++;
		if (s[i] == 'l'&& s[i-1] != 'r' && s[i-2] != 'i' && s[i-3] != 'g') ans++;
    }
    cout << tem << '\n' << ans;
    return 0;
 }