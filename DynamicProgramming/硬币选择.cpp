#include <iostream>
#include <algorithm>

using namespace std;


//分治算法
//递归+记忆化搜索
/*
int func1(int n, int dp[]) {
    if (dp[n] > 0) {
        return dp[n];
    }
    if (n == 1 || n == 3 || n == 5) {
        dp[n] = 1;
        return 1;
    }
    else if (n == 2 || n == 4) {
        dp[n] = 2;
        return 2;
    }
    else {
        int n1 = func1(n - 1, dp) + 1;
        int n2 = func1(n - 3, dp) + 1;
        int n3 = func1(n - 5, dp) + 1;
        dp[n] = min(n1, min(n2, n3));;
        return dp[n];
    }
}

int main() {
    int n;
    cin >> n;
    int dp[n+1] = {0};
    cout << func1(n, dp) << endl;
    return 0;
}
*/

int main() {
    int v[] = {1, 3, 5};
    int length = sizeof(v) / sizeof(v[0]);
    int c = 18;
    int *dp = new int[c + 1]();
    for (int i = 1; i <= c; ++i) {
        dp[i] = i;
        for (int j = 0; j < length; ++j) {
            if (i >= v[j] && (1 + dp[i - v[j]]) < dp[i]) {
                dp[i] = 1 + dp[i - v[j]];
            } 
        }
    }
    cout << dp[c] << endl;
    return 0;
}