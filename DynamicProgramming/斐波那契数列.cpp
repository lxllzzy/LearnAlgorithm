#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int foo(int n, int dp[]) {
    if (n == 1 || n == 2) {
        dp[n] = 1;
        return 1;
    }
    else {
        dp[n] = foo(n - 1, dp) + foo(n - 2, dp);
        return dp[n];
    }
}

int main() {    
    int n;
    cin >> n;;
    int *dp = new int[n+1]();
    foo(n, dp); 
    cout << dp[n] << endl;
    delete[] dp;
    return 0;
}