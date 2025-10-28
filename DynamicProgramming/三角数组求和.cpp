#include <iostream>
#include <vector>

using namespace std;

/*
//自底向上
//第一版
int main() {
    vector<int> v1 = {2};
    vector<int> v2 = {3, 4};
    vector<int> v3 = {6, 5, 7};
    vector<int> v4 = {4, 1, 8, 3};
    vector<vector<int>> v = {v1, v2, v3, v4};

    int **dp = nullptr;
    dp = new int*[v.size()];
    for (int i = 0; i < v.size(); ++i) {
        dp[i] = new int [v4.size()];
    }

    int n = v.size() - 1;
    for (int i = 0; i < v[n].size(); ++i) {
        dp[n][i] = v[n][i];
    }

   for (int i = n - 1; i >= 0; --i) {
        for (int j = 0; j < v[i].size(); ++j) {
            dp[i][j] = std::min(dp[i+1][j], dp[i+1][j+1]) + v[i][j];
        }
   }
   cout << dp[0][0] << endl;

    for (int i = 0; i < v.size(); ++i) {
        delete[]dp[i];
    }
    delete[]dp;
    return 0;
}
*/

/*
int minimumTotal(vector<vector<int>> &triangle) {
    int n = triangle.size();
    vector<vector<int>> dp(n);

    dp[n-1] = triangle[n-1];
    for (int i = n - 2; i >=0; --i) {
        dp[i].resize(triangle[i].size());
        for (int j = 0; j < triangle[i].size(); ++j) {
            dp[i][j] = min(dp[i+1][j], dp[i+1][j+1]) + triangle[i][j];
        }
    }
    return dp[0][0];
}

int main() {
    vector<vector<int>> triangel = {
        {2},
        {3, 4},
        {6, 5, 7},
        {4, 1, 8, 3}
    };
    cout << minimumTotal(triangel) << endl;
    return 0;
}
*/

//空间优化版
/*
int minimumTotal(vector<vector<int>> &triangle) {
    int n = triangle.szie();
    vector<int> dp(triangel.back());

    for (int  i = n - 2; i >= 0; --i) {
        for (int j = 0; j <= i; ++j) {
            dp[j] = min(dp[j], dp[j+1]) + triangle[i][j];
        }
    }
    return dp[0];
}
*/

//==========================================================================================
//==========================================================================================
//==========================================================================================
//自顶向下
int dfs(int i, int j, const vector<vector<int>> &tri, vector<vector<int>> &memon) {
    int n = tri.size();
    if (i == n) return 0;
    int &res = memon[i][j];
    if (res != INT_MAX) return res;
    return res = tri[i][j] + min(dfs(i+1, j, tri, memon), dfs(i+1, j+1, tri, memon));
}


int minimumTotal(vector<vector<int>> &triangle) {
    int n = triangel.size();
    vector<vector<int>> memon(n, vector<int>(n, INT_MAX));
    return dfs(0, 0, triangle, memon);
}

int main() {
    vector<vctor<int>> triangle = {
        {2},
        {3, 4},
        {6, 5, 7},
        {4, 1, 8, 3}
    };

    cout << minimumTotal(triangle) << endl;
    return 0;
}

/*
最小路径和======》不同路径 II
*/