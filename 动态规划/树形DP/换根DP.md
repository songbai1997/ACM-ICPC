Cf 1324F. Maximum White Subtree

https://codeforces.com/problemset/problem/1324/F

C++代码
```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10;
int a[N];
int v[N];
int ans[N];

int dfs1(int rt, int f, vector<vector<int>>& g)
{
    int val = a[rt];
    for (int c : g[rt]) {
        if (c == f) continue;
        val += max(0, dfs1(c, rt, g));
    }
    return v[rt] = val;
}

void dfs2(int rt, int f, vector<vector<int>>& g)
{
    ans[rt] = v[rt];
    for (int c : g[rt]) {
        if (c == f) continue;
        int old_v = v[rt];
        int old_c = v[c];
        v[rt] -= max(0, v[c]);
        v[c] += max(0, v[rt]);
        dfs2(c, rt, g);
        v[rt] = old_v;
        v[c] = old_c;
    }
}

int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        if (a[i] == 0) a[i] = -1;
    }
    vector<vector<int>> g(n + 1);
    for (int i = 1; i < n; i++) {
        int x, y;
        cin >> x >> y;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    dfs1(1, 0, g);
    dfs2(1, 0, g);
    for (int i = 1; i <= n; i++) cout << ans[i] << " ";
    cout << endl;
    return 0;
}

```