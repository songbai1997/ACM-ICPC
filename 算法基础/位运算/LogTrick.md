# LogTrick
`AND`的数越多，结果越小。`OR`的数越多，结果越大。

学习链接：https://zhuanlan.zhihu.com/p/1933215367158830792

# 练习场
## No1、3171.找到按位或最接近K的子数组
https://leetcode.cn/problems/find-subarray-with-bitwise-or-closest-to-k/description/

## 题意
给你一个数组 nums 和一个整数 k 。你需要找到 nums 的一个 子数组 ，满足子数组中所有元素按位或运算 OR 的值与 k 的 绝对差 尽可能 小 。换言之，你需要选择一个子数组 nums[l..r] 满足 |k - (nums[l] OR nums[l + 1] ... OR nums[r])| 最小。

## 解题思路一 `O(nlogU)`
优化暴力算法，当新增元素是旧集合的子集时，其或值不会使旧集合的值变大，提前退出
```cpp
class Solution {
public:
    int minimumDifference(vector<int>& nums, int k) {
        int ans = abs(nums[0] - k);
        for (int i = 0; i < nums.size(); i++) {
            ans = min(ans, abs(nums[i] - k));
            for (int j = i - 1; j >= 0 && (nums[j] | nums[i]) != nums[j]; j--) {
                nums[j] |= nums[i];
                ans = min(ans, abs(nums[j] - k));
            }
        }
        return ans;
    }
};
```
## 解题思路二 `O(n)`
滑动窗口+栈

https://leetcode.cn/problems/find-subarray-with-bitwise-or-closest-to-k/solutions/2798206/li-yong-and-de-xing-zhi-pythonjavacgo-by-gg4d/
```cpp
class Solution {
public:
    int minimumDifference(vector<int>& nums, int k) {
        int ans = INT_MAX, left = 0, bottom = 0, right_or = 0;
        for (int right = 0; right < nums.size(); right++) {
            right_or |= nums[right];
            while (left <= right && (nums[left] | right_or) > k) {
                ans = min(ans, (nums[left] | right_or) - k);
                left++;
                if (bottom < left) {
                    // 重新构建一个栈
                    for (int i = right - 1; i >= left; i--) {
                        nums[i] |= nums[i + 1];
                    }
                    bottom = right;
                    right_or = 0;
                }
            }
            if (left <= right) {
                ans = min(ans, k - (nums[left] | right_or));
            }
        }
        return ans;
    }
};
```

## No2、2411. 按位或最大的最小子数组长度
https://leetcode.cn/problems/smallest-subarrays-with-maximum-bitwise-or/description/

## 题意
给你一个长度为 n 下标从 0 开始的数组 nums ，数组中所有数字均为非负整数。对于 0 到 n - 1 之间的每一个下标 i ，你需要找出 nums 中一个 最小 非空子数组，它的起始位置为 i （包含这个位置），同时有 最大 的 按位或运算值 。

换言之，令 Bij 表示子数组 nums[i...j] 的按位或运算的结果，你需要找到一个起始位置为 i 的最小子数组，这个子数组的按位或运算的结果等于 max(Bik) ，其中 i <= k <= n - 1 。
一个数组的按位或运算值是这个数组里所有数字按位或运算的结果。

请你返回一个大小为 n 的整数数组 answer，其中 answer[i]是开始位置为 i ，按位或运算结果最大，且 最短 子数组的长度。

## 解题思路一 `O(nlogU)`
新增元素不是旧集合的子集时，更新答案
```cpp
class Solution {
public:
    vector<int> smallestSubarrays(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans(n, 1);
        for (int i = 0; i < n; i++) {
            for (int j = i - 1; j >= 0 && (nums[j] | nums[i]) != nums[j]; j--) {
                nums[j] |= nums[i];
                ans[j] = i - j + 1;
            }
        }
        return ans;
    }
};
```

## No3、1521. 找到最接近目标值的函数值
https://leetcode.cn/problems/find-a-value-of-a-mysterious-function-closest-to-target/description/

## 题意
给你一个长度为 n 下标从 0 开始的数组 nums ，数组中所有数字均为非负整数。你需要找到一个子数组，子数组元素的与值与目标值target相差最小，输出这个最小值。

## 解题思路一 `O(nlogU)`
新增元素不是旧集合的超集时，更新答案
```cpp
class Solution {
public:
    int closestToTarget(vector<int>& nums, int target) {
        int ans = INT_MAX;
        for (int i = 0; i < nums.size(); i++) {
            ans = min(ans, abs(nums[i] - target));
            for (int j = i - 1; j >= 0 && (nums[j] & nums[i]) != nums[j]; j--) {
                nums[j] &= nums[i];
                ans = min(ans, abs(nums[j] - target));
            }
        }
        return ans;
    }
};
```

## No4、3209. 子数组按位与值为 K 的数目
https://leetcode.cn/problems/number-of-subarrays-with-and-value-of-k/description/

## 题意
给你一个整数数组 nums 和一个整数 k ，请你返回 nums 中有多少个子数组满足：子数组中所有元素按位 AND 的结果为 k 。

## 解题思路一 `O(nlogU)`
在`LogTrick`的基础上，保存每个不同与值的最左下标和数值
```cpp
class Solution {
public:
    long long countSubarrays(vector<int>& nums, int k) {
        using ll = long long;
        ll ans = 0;
        vector<pair<int, int>> left;
        for (int i = 0; i < nums.size(); i++) {
            int x = nums[i];
            for (auto& [val, _] : left) {
                val &= x;
            }
            left.emplace_back(x, i);
            // 原地去重（相同值只保留最左边的）
            int m = 1;
            for (int j = 1; j < left.size(); j++) {
                if (left[j].first != left[j - 1].first) {
                    left[m++] = left[j];
                }
            }
            left.resize(m);
            for (int j = 0; j < m; j++) {
                if (left[j].first != k) continue;
                ans += (j == m - 1 ? i + 1 : left[j + 1].second) - left[j].second;
            }
        }
        return ans;
    }
};
```
## 解题思路二 `O(nlogU)`
在`LogTrick`的基础上，维护等于`k`的子数组个数
```cpp
class Solution {
public:
    long long countSubarrays(vector<int>& nums, int k) {
        using ll = long long;
        ll ans = 0;
        int cnt = 0;
        for (int i = 0; i < nums.size(); i++) {
            cnt += nums[i] == k;
            for (int j = i - 1; j >= 0 && (nums[j] & nums[i]) != nums[j]; j--) {
                cnt -= nums[j] == k;
                nums[j] &= nums[i];
                cnt += nums[j] == k;
            }
            ans += cnt;
        }
        return ans;
    }
};
```