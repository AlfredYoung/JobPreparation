#include <iostream>
#include <vector>
#include <string>
using namespace std;

string banker(vector<int> &total, vector<vector<int>> &max ,vector<vector<int>> &allc) {
    int n = max[0].size();
    int m = max.size();
    vector<vector<int>> need(m, vector<int> (n));
    vector<int> avail(n);
    // 计算 need 和 avail
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            need[i][j] = max[i][j] - allc[i][j];
        }
    }

    for (int j = 0; j < n; ++j) {
        int allocated_sum = 0;
        for (int i = 0; i < m; ++i) {
            allocated_sum += allc[i][j];  // 计算每类资源已分配总量
        }
        avail[j] = total[j] - allocated_sum;  // 系统总量减去已分配总量
    }


    vector<int> finish(m, 0);  // 标记每个进程是否完成
    vector<int> safeSequence;  // 存储安全序列

    int finishedCount = 0;     // 已完成的进程数
    while (finishedCount < m) { // 当所有进程都完成时，退出循环
        bool found = false;     // 是否找到符合条件的进程

        for (int i = 0; i < m; ++i) {
            if (!finish[i]) {   // 如果该进程还未完成
                int j;
                // 检查该进程的需求是否小于或等于当前可用资源
                for (j = 0; j < n; ++j) {
                    if (need[i][j] > avail[j]) {
                        break;  // 该进程不能被满足
                    }
                }

                // 如果 j == n，表示该进程所有需求都能被满足
                if (j == n) {
                    // 释放该进程的资源
                    for (int k = 0; k < n; ++k) {
                        avail[k] += allc[i][k];
                    }

                    // 标记该进程完成，加入安全序列
                    finish[i] = 1;
                    safeSequence.push_back(i);
                    ++finishedCount;  // 更新已完成的进程数
                    found = true;     // 找到一个符合条件的进程
                }
            }
        }

        // 如果一轮遍历没有找到任何满足条件的进程，则系统处于不安全状态
        if (!found) {
            return "系统处于不安全状态，无法找到安全序列。";
        }
    }
    string ans;
    for (int i = 0; i < m - 1; ++i) {
        ans += ("P" + to_string(safeSequence[i]) + "->");
    }
    ans += ("P" + to_string(safeSequence[m - 1]));
    return ans;
}


int main() {
    vector<int> total = {10, 5, 7};
    vector<vector<int>> max = {{7, 5, 3}, {3, 2, 2}, {9, 0, 2}, {2, 2, 2}, {4, 3, 3}};
    vector<vector<int>> allc = {{0, 1 ,0}, {2, 0, 0}, {3, 0, 2}, {2 ,1 ,1}, {0, 0, 2}};
    cout << banker(total, max, allc);
}