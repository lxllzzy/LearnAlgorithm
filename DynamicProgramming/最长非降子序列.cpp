#include <iostream>
#include <algorithm>
#include <vector>   
using namespace std;

//状态：dp[i]以第i个元素结尾的非降子序列的长度
int main() {
    int arr[] = {5, 3, 4, 1, 8, 6, 7, 10};
    const int n = sizeof(arr) / sizeof(arr[0]);
    int dp[n] = {0};
    int maxval = 0;
    for (int i = 0; i < n; ++i) {
        dp[i] = 1;
        for (int j = 0; j < i; ++j) {
            if (arr[j] <= arr[i] && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
            }
        }
        if (dp[i] > maxval) {
            maxval = dp[i];
        }
    }
    cout << "最长非降子序列的长度为: " << maxval << endl;
    return 0;
}