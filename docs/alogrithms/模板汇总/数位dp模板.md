# 数位DP模板

## 参考题目一：https://leetcode.cn/problems/numbers-with-repeated-digits/description/
状态定义为f(i, mask, isLimit, isNum):表示从i位置开始选择，前面元素已经选了的集合为mask可以选择的数量。
mask：每一个位置是否为1表示元素已经选择；
isLimit：如果为true，表示前面选择的元素都是对应的上界，比如3212，如果前两位选择的是32，则isLimit为true；
isNum：表示是否已经选择了数字，如果选择过数字，则下一次不能选择0，可以直接不选；
```java
class Solution {
    char[] s;
    int[][] dp;
    public int numDupDigitsAtMostN(int n) {
        s = Integer.toString(n).toCharArray();
        int m = s.length;
        dp = new int[m][1 << 10];
        for(int i = 0; i < m; i++) {
            Arrays.fill(dp[i], -1);
        }
        return n - dfs(0, 0, true, false);
    }

    private int dfs(int i, int mask, boolean isLimit, boolean isNum) {
        if(i == s.length) {
            return isNum ? 1 : 0;
        }
        if(!isLimit && isNum && dp[i][mask] != -1) {
            return dp[i][mask];
        }
        int res = 0;
        if(!isNum) {
            res += dfs(i + 1, mask, false, false);
        }
        int up = isLimit ? (s[i] - '0') : 9;
        for(int j = isNum ? 0 : 1 ; j <= up; j++) {
            if((mask >> j & 1) == 0) {
                res += dfs(i + 1, mask | (1 << j), isLimit && j == up, true);
            }
        }
        if(!isLimit && isNum) {
            dp[i][mask] = res;
        }
        return res;
    }
} 
```