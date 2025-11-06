#include <iostream>
#include <algorithm>
#include <vector> 
#include <string>      

using namespace std;

/*
如果Xn==Ym
LCS(X[1...n],Y[1...m])=LCS(X[1...n-1],Y[1...m-1])+1
如果Xn!=Ym
LCS(X[1...n],Y[1...m])=max{LCS(X[1...n-1],Y[1...m]),LCS(X[1...n],Y[1...m-1])}
*/
/*
int LCS(string X, int n, string Y, int m) {
    if (n < 0 || m < 0) {
        return 0;
    }
    if (X[n] == Y[m]) {
        return LCS(X, n - 1, Y, m - 1) + 1;
    }
    else {
        int len1 = LCS(X, n - 1, Y, m);
        int len2 = LCS(X, n, Y, m - 1);
        return max(len1, len2);
    }
}

int main() {
    string str1 = "helloworld";
    string str2 = "hlweord";
    int size = LCS(str1, str1.size()-1, str2, str2.size()-1);
    cout << "最长公共子序列长度为: " << size << endl;
    return 0;
}
*/

//dp[n][m]:n代表第一个串的长度，m代表第二个串的长度，n行m列元素的值，记录的就是这两个子串的LCS长度
string str1 = "helloworld";
string str2 = "hlweord";
int **dp = nullptr;

int LCS(string X, int n, string Y, int m) {
    if (n < 0 || m < 0) {
        return 0;
    }

    if (dp[n][m] >= 0) {
        return dp[n][m];
    }
    if (X[n] == Y[m]) {
        dp[n][m] = LCS(X, n - 1, Y, m - 1) + 1;
        return dp[n][m];
    }
    else {
        int len1 = LCS(X, n - 1, Y, m);
        int len2 = LCS(X, n, Y, m - 1);
        if (len1 >= len2) {
            dp[n][m] = len1;
        }
        else {
            dp[n][m] = len2;
        }
        return dp[n][m];
    }
}

int main() {
    int n = str1.size();
    int m = str2.size();
    dp = new int*[n];
    for (int i = 0; i < n; ++i) {
        dp[i] = new int[m];
    }
    int size = LCS(str1, n-1, str2, m-1);
    cout << size << endl;
    return 0;
}
