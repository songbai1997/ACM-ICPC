#include <bits/stdc++.h>

using namespace std;

int random(int n)
{
    return (long long)rand() * rand() % n;
}

// 随机生成n<=1e5个绝对值在1e9之内的整数
void gen1()
{
    srand((unsigned)time(0));
    int n = random(1e5) + 1;
    int m = 1e9;
    printf("%d\n", n);
    for (int i = 1; i <= n; i++) {
        printf("%d ", random(2 * m + 1) - m);
    }
    printf("\n");
}

// 随机生成n<=1e5个之内的整数
void gen2()
{
    srand((unsigned)time(0));
    int a = random(1e5);
    int b = random(1e5);
    printf("%d %d\n", a, b);
}

void gen_interval(int m, int n)
{
    for (int i = 1; i <= m; i++) {
        int l = random(n) + 1;
        int r = random(n) + 1;
        if (l > r) swap(l, r);
        printf("%d %d\n", l, r);
    }
}

void gen3(int size)
{
    srand((unsigned)time(0));
    int n = random(size) + 1;
    int m = random(size) + 1;
    printf("%d %d\n", n, m);
    for (int i = 1; i <= n; i++) {
        int x = random(n) + 1;
        printf("%d ", x);
    }
    printf("\n");
    gen_interval(m, n);
    printf("\n");
}

int main()
{
    gen3(5e4);
    return 0;
}