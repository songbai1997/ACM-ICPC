#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N = 5e4 + 10;

int pos[N];

struct Node {
    int l, r, id;
} Q[N];

long long Ans[N];
long long Ans2[N];

int a[N];
int cnt[N];
int L = 1, R = 0, k;
ll ans = 0;

bool cmp(Node a, Node b) {
    return (pos[a.l] == pos[b.l] ? a.r < b.r : pos[a.l] < pos[b.l]);
}

void del(int i)
{
    i = a[i];
    ans -= (ll)cnt[i] * (cnt[i] - 1);
    cnt[a[i]]--;
    ans += (ll)cnt[i] * (cnt[i] - 1);
}

void add(int i)
{
    i = a[i];
    ans -= (ll)cnt[i] * (cnt[i] - 1);
    cnt[a[i]]++;
    ans += (ll)cnt[i] * (cnt[i] - 1);
}

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);
    int block = sqrt(n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        pos[i] = i / block;
    }
    for (int i = 1; i <= m; i++) {
        scanf("%d %d", &Q[i].l, &Q[i].r);
        Q[i].id = i;
    }
    sort(Q + 1, Q + m + 1, cmp);
    for (int i = 1; i <= m; i++) {
        while (L < Q[i].l) del(L++);
        while (L > Q[i].l) add(--L);
        while (R < Q[i].r) add(++R);
        while (R > Q[i].r) del(R--);
        ll sum = Q[i].r - Q[i].l + 1;
        sum *= (sum - 1);
        
        ll g = gcd<int64_t>(ans, sum);
        Ans[Q[i].id] = (g == 0 ? 0 : ans / g);
        Ans2[Q[i].id] = (g == 0 ? 1 : sum / g);
    }
    for (int i = 1; i <= m; i++) printf("%lld/%lld\n", Ans[i], Ans2[i]);
    return 0;
}