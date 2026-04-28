#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;
int main() {
    map<string, vector<string>> families;
    families["王"].push_back("大锤");
    families["王"].push_back("二锤");
    families["李"].push_back("四");
    families["李"].push_back("白");
    families["张"].push_back("三");
    families["赵"].push_back("云");
    string query = "王";
    auto it = families.find(query);
    if (it != families.end()) {
        cout << query << " 家族的孩子有: ";
        for (const string& child : it->second) {
            cout << child << " ";
        }
        cout << '\n';
    } else {
        cout << "未能找到该家族\n";
    }
    return 0;
}