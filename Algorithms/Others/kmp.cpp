#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int kmp(const string &s, const string &t) {
    int m = t.length();
    int n = s.length();

    if (m == 0) return 0;  // 空模式串默认匹配在位置 0
    if (n == 0 || m > n) return -1;  // 无法匹配

    // 构建 next 数组
    vector<int> next(m, 0);
    int j = 0;
    for (int i = 1; i < m; ++i) {
        while (j > 0 && t[i] != t[j]) {
            j = next[j - 1];
        }
        if (t[i] == t[j]) {
            ++j;
        }
        next[i] = j;
    }

    // KMP 搜索过程
    j = 0;
    for (int i = 0; i < n; ++i) {
        while (j > 0 && s[i] != t[j]) {
            j = next[j - 1];
        }
        if (s[i] == t[j]) {
            ++j;
        }
        if (j == m) {
            return i - m + 1;  // 返回匹配的起始位置
        }
    }

    return -1;  // 未找到匹配
}

int main() {
    string s = "aaabaaa";
    string t = "aabaaa";
    cout << kmp(s, t) << endl;
}