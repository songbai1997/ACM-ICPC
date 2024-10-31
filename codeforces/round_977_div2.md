# 比赛链接
[round_977_div2](https://codeforces.com/contest/2021)

# A. Meaning Mean
[A. Meaning Mean](https://codeforces.com/contest/2021/problem/A)

每次取最小的数。
```cpp
#include<bits/stdc++.h>

using namespace std;

void solve()
{
    int n;
    scanf("%d", &n);
    priority_queue<int, vector<int>, greater<int>> hq;
    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        hq.push(x);
    }
    while (hq.size() > 1) {
        int f1 = hq.top();
        hq.pop();
        int f2 = hq.top();
        hq.pop();
        hq.push((f1 + f2) / 2);
    }
    printf("%d\n", hq.top());
}

int main()
{
    int t;
    scanf("%d", &t);
    while (t--) {
        solve();
    }
    return 0;
}
```
# B. Maximize Mex
[B. Maximize Mex](https://codeforces.com/contest/2021/problem/B)
```cpp
#include<bits/stdc++.h>

using namespace std;

void solve()
{
    int n, x;
    scanf("%d %d", &n, &x);
    vector<int> a(n + 1, 0);
    for (int i = 0; i < n; i++) {
        int num;
        scanf("%d", &num);
        if (num < n) a[num]++;
    }
    for (int i = 0; i < n; i++) {
        if (a[i] == 0) {
            printf("%d\n", i);
            return;
        }
        int j = i + x;
        if (j < n) a[j] += a[i] - 1;
    }
    printf("%d\n", n);
}

int main()
{
    int t;
    scanf("%d", &t);
    while (t--) {
        solve();
    }
    return 0;
}
```
# C1. Adjust The Presentation (Easy Version)
[C1. Adjust The Presentation (Easy Version)](https://codeforces.com/contest/2021/problem/C1)
```cpp
#include<bits/stdc++.h>

using namespace std;

void solve()
{
    int n, m, q;
    scanf("%d %d %d", &n, &m, &q);
    vector<int> a(n), b(m);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    for (int i = 0; i < m; i++) {
        scanf("%d", &b[i]);
    }
    vector<bool> left(n + 1, false);
    for (int i = 0, idx = 0; i < m; i++) {
        if (left[b[i]]) {
        } else if (idx < n && a[idx] == b[i]) {
            left[a[idx]] = true;
            idx++;
        } else {
            printf("TIDAK\n");
            return;
        }
    }
    printf("YA\n");
}

int main()
{
    int t;
    scanf("%d", &t);
    while (t--) {
        solve();
    }
    return 0;
}
```
# C2. Adjust The Presentation (Hard Version)
[C2. Adjust The Presentation (Hard Version)](https://codeforces.com/contest/2021/problem/C2)
```cpp
#include<bits/stdc++.h>

using namespace std;

int MAX = 1e7;

void solve()
{
    int n, m, q;
    scanf("%d %d %d", &n, &m, &q);
    vector<int> a(n), b(m), c(n + 1), v(n);
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        c[a[i]] = i;    
    }

    vector<set<int>> idx(n + 1);
    for (int i = 0; i < m; i++) {
        scanf("%d", &b[i]);
        idx[b[i]].insert(i);
    }

    for (int i = 0; i < n; i++) v[i] = (idx[a[i]].empty() ? MAX : *(idx[a[i]].begin()));
    vector<bool> valid(n, true);
    int invalid_cnt = 0;
    for (int i = 0; i < n - 1; i++) {
        if (v[i] > v[i + 1]) {
            valid[i] = false;
            invalid_cnt++;
        }
    }
    printf("%s\n", (invalid_cnt > 0 ? "TIDAK" : "YA"));

    auto update = [&](int y) {
        int p = c[y];
        if (!valid[p]) {
            invalid_cnt--;
            valid[p] = true;
        }
        if (p - 1 >= 0 && !valid[p - 1]) {
            valid[p - 1] = true;
            invalid_cnt--;
        }
        v[p] = (idx[y].empty() ? MAX : *(idx[y].begin()));
        if (p + 1 < n && v[p] > v[p + 1]) {
            valid[p] = false;
            invalid_cnt++;
        }
        if (p - 1 >= 0 && v[p - 1] > v[p]) {
            valid[p - 1] = false;
            invalid_cnt++;
        }
    };

    while (q--) {
        int x, y;
        scanf("%d %d", &x, &y);
        x--;
        // 有变动才更新
        if (b[x] != y) {
            int old_y = b[x];
            b[x] = y;
            idx[old_y].erase(x);
            idx[y].insert(x);
            if (c[y] > c[old_y]) {
                swap(old_y, y);
            }
            update(old_y);
            update(y);
        }
        printf("%s\n", (invalid_cnt > 0 ? "TIDAK" : "YA"));
    }
}

int main()
{
    int t;
    scanf("%d", &t);
    while (t--) {
        solve();
    }
    return 0;
}
```
# D. Boss, Thirsty
[D. Boss, Thirsty](https://codeforces.com/contest/2021/problem/D)

```cpp
#include<bits/stdc++.h>

using namespace std;

using ll = long long;

ll MIN = -1e15;

void solve()
{
    int n, m;
    scanf("%d %d", &n, &m);
    vector<vector<int>> a(n, vector<int>(m + 1));
    for (int i = 0; i < n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%d", &a[i][j]);
    
    vector<vector<ll>> dpl(n, vector<ll>(m + 1)), dpr(n, vector<ll>(m + 1));
    vector<ll> sum(m + 1);
    sum[0] = 0;
    for (int i = 1; i <= m; i++) sum[i] = sum[i - 1] + a[0][i];
    
    dpl[0][m] = a[0][m];
    ll mx = dpl[0][m];
    for (int i = m - 1; i >= 1; i--) {
        dpl[0][i] = mx - sum[i - 1];
        mx = max(mx, sum[i]);
    }
    ll mi = 0;
    for (int i = 1; i <= m; i++) {
        dpr[0][i] = sum[i] - mi;
        mi = min(mi, sum[i]);
    }

    for (int i = 1; i < n; i++) {
        for (int j = 1; j <= m; j++) sum[j] = sum[j - 1] + a[i][j];
        
        dpl[i][m] = MIN;
        dpl[i][m - 1] = max(MIN, sum[m] - sum[m - 2] + dpl[i - 1][m]);
        
        ll mx_sum = sum[m];
        ll mx_dp = MIN;s
        for (int j = m - 2; j >= 1; j--) {
            mx_dp = max(mx_dp, max(dpl[i - 1][m - 1], dpr[i - 1][m - 1]) + mx_sum);

            dpl[i][j] = mx_dp - sum[i - 1];
            mx_sum = max(mx_sum, sum[j]);
            mx_dp = max(mx_dp, max(dpl[i - 1][j], dpr[i - 1][j]));
        }
    }
}

int main()
{
    int t;
    scanf("%d", &t);
    while (t--) {
        solve();
    }
    return 0;
}
```
