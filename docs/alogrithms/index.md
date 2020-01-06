2019-13-03
1、https://leetcode.com/problems/binary-number-with-alternating-bits/
> 给一个正整数，判断这个数的二进制表示是否相邻的比特位都不相同

2、https://leetcode.com/problems/count-binary-substrings/
> 给一个只包含0和1字符的字符串，查找其中包含连续0和1数目相同的子字符串的数目。
```java
// solution1
class Solution {
    public int countBinarySubstrings(String s) {
        // prev等于0这个设置的好，不像我写的还得标识是否再次重复了
        int ans = 0, prev = 0, cur = 1;
        for (int i = 1; i < s.length(); i++) {
            if (s.charAt(i-1) != s.charAt(i)) {
                ans += Math.min(prev, cur);
                prev = cur;
                cur = 1;
            } else {
                cur++;
            }
        }
        return ans + Math.min(prev, cur);
    }
}

// solution2
class Solution {
    public int countBinarySubstrings(String s) {
        int[] groups = new int[s.length()];
        int t = 0;
        groups[0] = 1;
        for (int i = 1; i < s.length(); i++) {
            if (s.charAt(i-1) != s.charAt(i)) {
                groups[++t] = 1;
            } else {
                groups[t]++;
            }
        }

        int ans = 0;
        for (int i = 1; i <= t; i++) {
            ans += Math.min(groups[i-1], groups[i]);
        }
        return ans;
    }
}
```

3、https://leetcode.com/problems/degree-of-an-array/submissions/
> 求数组的等级，数组的等于等于数组中元素出现最频繁的次数。求连续的
子数组也有相同的等级。
