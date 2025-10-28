#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

//状态：dp[i]以第i个元素结尾的字段和的值
int main() {
    vector<int> nums = {-2, 11, -4, 13, -5, -2};
    int n = nums.size();
    vector<int> dp(n, 0);
    dp[0] = nums[0] < 0 ? 0 : dp[0];
    int max = dp[0];
    for (int i = 1; i < n; ++i) {
        dp[i] = dp[i-1] + nums[i];
        if (dp[i] < 0) {
            dp[i] = 0;
        }
        if (dp[i] > max) {
            max = dp[i];
        }
    }
    cout << max << endl;

}