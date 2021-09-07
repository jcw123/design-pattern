# 最长上升子序列问题

## 基本思路
对于数组nums, 用dp[i]表示为以nums[i]结尾的的最长递增子序列，如果需要求dp[i]，只需要遍历j 从0到i-1，当nums[j]小于nums[i]时，dp[j]的最大值即可。
如果按照这样遍历的解法，时间复杂度为O(n^2)，可以借助一个g[len]数组，用来维护当子序列长度为len时，g[len]的最小值，可以将时间复杂度降为O(nlogn)。

## 解法

#### 解法一
```java
public largestCommonIncreaseSequence(int[] arr) {
    int len = arr.length;
    int[] dp = new int[len];
    int max = 0;
    for(int i = 0; i < n; i++) {
        int v  = arr[i];
        int cLen = 0;
        int j = i - 1;
        while(j >= 0 {
            if(arr[j] < arr[i]) {
                cLen = Math.max(cLen, dp[j]);
            }
            j--;
        }
        dp[i] = cLen;
        max = Math.max(max, cLen);
    }
    return max;
}
```

#### 解法二
```java
public largestCommonIncreaseSequence(int[] arr) {
  int len = arr.length;
  int[] dp = new int[len];
  int[] g = new int[len + 1];
  Arrays.fill(g, Integer.MAX_VALUE);
  int max = 0;
  for(int i = 0; i < n; i++) {
    int v = arr[i];
    int l = 0;
    int h = i;
    int mid;
    while(l <  h) {
      mid = l + h + 1 >> 1;
      if(g[mid] < v) {
        l = mid;
      }else {
        h = mid - 1;
      }
    }
    dp[i] = h + 1;
    g[h + 1] = Math.min(g[h + 1], v);
    max = Math.max(max, h + 1);
  }
  return max;
}
```

### 杂谈
2021-8-8号周赛考了一套最长子序列问题，我使用了treeMap结构，出现了TLE了，最后一些单元测试没法通过。这道题的解法二完全不记得了，只记得解法一的写法。
真是无语了。

### 参考文档
https://leetcode-cn.com/problems/longest-increasing-subsequence/solution/dong-tai-gui-hua-er-fen-cha-zhao-tan-xin-suan-fa-p/
