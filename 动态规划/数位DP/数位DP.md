# 【模板】数位DP


## No1、3747. 统计移除零后不同整数的数目
https://leetcode.cn/problems/count-distinct-integers-after-removing-zeros/description/

## 题意
给你一个 正 整数 n。

对于从 1 到 n 的每个整数 x，我们记下通过移除 x 的十进制表示中的所有零而得到的整数。

返回一个整数，表示记下的 不同 整数的数量。

## 解题思路
统计指定范围内，数位没有0的整数个数。枚举每个数位的取值，当且仅当是前导0的时候数位才能取0。

```cpp
class Solution {
public:
    using ll = long long;
    ll digitDP(ll num) {
        string num_s = to_string(num);
        int n = num_s.size();

        vector<ll> memo(n, -1);
    
        auto dfs = [&](this auto&& dfs, int i, bool leading, bool limit) -> ll {
            if (i == n) {
                return !leading;
            }
            if (!limit && !leading && memo[i] >= 0) {
                return memo[i];
            }
            int lo = leading ? 0 : 1;
            int hi = limit ? num_s[i] - '0' : 9;
            ll res = 0;
            for (int d = lo; d <= hi; d++) {
                res += dfs(i + 1, leading && d == 0, limit && d == hi);
            }
            if (!limit && !leading) {
                memo[i] = res;
            }
            return res;
        };
    
        return dfs(0, true, true);
    }
    
    long long countDistinct(long long n) {
        return digitDP(n);
    }
};
```

## No2、100903. 范围内总波动值 II
https://leetcode.cn/problems/total-waviness-of-numbers-in-range-ii/description/

## 题意
给你两个整数 num1 和 num2，表示一个 闭 区间 [num1, num2]。

一个数字的 波动值 定义为该数字中 峰 和 谷 的总数：

- 如果一个数位 严格大于 其两个相邻数位，则该数位为 峰。
- 如果一个数位 严格小于 其两个相邻数位，则该数位为 谷。
- 数字的第一个和最后一个数位 不能 是峰或谷。
- 任何少于 3 位的数字，其波动值均为 0。
返回范围 [num1, num2] 内所有数字的波动值之和。

## 解题思路
维护如下状态
- 当前处理的数位下标
- 前一个位置的值
- 前一个数与其更前一个数的大小关系
- 当前的结果
```cpp
class Solution {
public:
    using ll = long long;
    ll digitDP(ll num) {
        string num_s = to_string(num);
        int n = num_s.size();
        
        ll memo[18][10][3][18];
        memset(memo, -1, sizeof(memo));
    
        auto dfs = [&](this auto&& dfs, int i, int pre, int order, int cnt, bool leading, bool limit) -> ll {
            if (i == n) {
                return cnt;
            }
            if (!limit && !leading && memo[i][pre][order][cnt] >= 0) {
                return memo[i][pre][order][cnt];
            }
            int hi = limit ? num_s[i] - '0' : 9;
            ll res = 0;
            for (int d = 0; d <= hi; d++) {
                int new_order = ((pre == 0 && leading) || d == pre ? 0 : (d < pre ? 1 : 2));
                int new_cnt = cnt + (order == 0 || new_order == 0 || order == new_order ? 0 : 1);
                res += dfs(i + 1, d, new_order, new_cnt, leading && d == 0, limit && d == hi);
            }
            if (!limit && !leading) {
                memo[i][pre][order][cnt] = res;
            }
            return res;
        };
    
        return dfs(0, 0, 0, 0, true, true);
    }
    
    long long totalWaviness(long long num1, long long num2) {
        return digitDP(num2) - digitDP(num1 - 1);
    }
};
```
## No3、2719. 统计整数数目
https://leetcode.cn/problems/count-of-integers/description/x

## 题意
给你两个数字字符串 num1 和 num2 ，以及两个整数 max_sum 和 min_sum 。如果一个整数 x 满足以下条件，我们称它是一个好整数：

- num1 <= x <= num2
- min_sum <= digit_sum(x) <= max_sum.
请你返回好整数的数目。答案可能很大，请返回答案对 109 + 7 取余后的结果。

注意，digit_sum(x) 表示 x 各位数字之和。

## 解题思路
统计指定范围内，数位和在某个区间的数的个数。
```cpp
int mod = 1e9 + 7;

class Solution {
public:
    int digitDP(string num_s, int min_sum, int max_sum) {
        int n = num_s.size();
        vector memo(n, vector<int>(200, -1));
    
        auto dfs = [&](this auto&& dfs, int i, int sum, bool leading, bool limit) -> int {
            if (i == n) {
                return min_sum <= sum && sum <= max_sum;
            }
            if (!limit && !leading && memo[i][sum] >= 0) {
                return memo[i][sum];
            }
            int hi = limit ? num_s[i] - '0' : 9;
            int res = 0;
            for (int d = 0; d <= hi; d++) {
                res = (res + dfs(i + 1, sum + d, leading && d == 0, limit && d == hi)) % mod;
            }
            if (!limit && !leading) {
                memo[i][sum] = res;
            }
            return res;
        };
        return dfs(0, 0, true, true);
    }

    int count(string num1, string num2, int min_sum, int max_sum) {
        for (int i = num1.size() - 1, sub = 1; i >= 0 && sub > 0; i--) {
            if (num1[i] > '0') num1[i]--, sub--;
            else num1[i] = '9';
        }
        return (digitDP(num2, min_sum, max_sum)  - digitDP(num1, min_sum, max_sum) + mod) % mod;
    }
};
```

## No4、2376. 统计特殊整数
https://leetcode.cn/problems/count-special-integers/description/

## 题意
如果一个正整数每一个数位都是 互不相同 的，我们称它是 特殊整数 。

给你一个 正 整数 n ，请你返回区间 [1, n] 之间特殊整数的数目。

## 解题思路
统计指定范围内，数位不重复的正整数数目。记录当前已经使用过的数位。
```cpp
class Solution {
public:
    int digitDP(int num) {
        string num_s = to_string(num);
        int n = num_s.size();
        vector memo(n, vector<int>(1 << 10, -1));
    
        auto dfs = [&](this auto&& dfs, int i, int s, bool leading, bool limit) -> int {
            if (i == n) {
                return !leading;
            }
            if (!limit && !leading && memo[i][s] >= 0) {
                return memo[i][s];
            }
            int hi = limit ? num_s[i] - '0' : 9;
            int res = 0;
            for (int d = 0; d <= hi; d++) {
                if ((s >> d) & 1) continue;
                int ns = ((d > 0 || !leading) ? s | (1 << d) : s);
                res += dfs(i + 1, ns, leading && d == 0, limit && d == hi);
            }
            if (!limit && !leading) {
                memo[i][s] = res;
            }
            return res;
        };
        return dfs(0, 0, true, true);
    }

    int countSpecialNumbers(int n) {
        return digitDP(n);
    }
};
```