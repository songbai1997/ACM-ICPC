# 考虑前导
## 说明
计数时需要考虑前导0。

## 题目
P6218 [USACO06NOV] Round Numbers S

https://www.luogu.com.cn/problem/P6218

## C++代码
```cpp
#include <bits/stdc++.h>

using namespace std;

int dp[36][36 * 2][2];
int base = 32;

int dfs(int i, int cnt, int leading, bool limit, vector<int>& v)
{
    if (i == v.size()) return (cnt >= base ? 1 : 0);
    if (!limit && dp[i][cnt][leading] != -1) return dp[i][cnt][leading];
    int ans = 0;
    int up = (limit ? v[i] : 1);
    for (int j = 0; j <= up; j++) {
        int new_cnt = cnt;
        if (!(leading && j == 0)) new_cnt += (j == 0 ? 1 : -1);
        if (new_cnt + v.size() - i - 1 < base) continue;
        ans += dfs(i + 1, new_cnt, leading && j == 0, limit && j == up, v);
    }
    if (!limit) dp[i][cnt][leading] = ans;
    return ans;
}

int cal(int x)
{
    vector<int> v;
    while (x) {
        v.push_back(x % 2);
        x >>= 1;
    }
    reverse(v.begin(), v.end());
    memset(dp, -1, sizeof(dp));
    return dfs(0, base, 1, 1, v);
}

void solve()
{
    int l, r;
    scanf("%d %d", &l, &r);
    printf("%d\n", cal(r) - cal(l - 1));
}

int main()
{
    int t = 1;
    while (t--) {
        solve();
    }
    return 0;
}
```