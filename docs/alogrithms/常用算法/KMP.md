## KMP算法
> 一种字符串匹配算法

### 核心思想
最常见的暴力解法是当主串和模式串某一位匹配不上时，主串只移动一个位置，时间复杂度O(n * m)，n为主串的长度，m为模式串的长度。KMP算法通过维护一个next数组，如果主串和模式串某一位匹配不上时，能够确定下次从模式串的哪一位开始匹配，主串的移动位置不会往前面移动，能够保证时间复杂度为O(m + n)。

### 复杂度分析

时间复杂度O(m + n): n为主串的长度，m为子串的长度；
空间复杂度O(n): n为主串的长度；

### 例题

**例题一**

有两个字符串s和p，其中p的长度小于等于s，如果p是s的子串，返回最左边的匹配索引值，如果不是，返回-1；

1. 方法一
> 暴力求解法

```java 
/**
 * Created by jiangchangwei on 2019/7/9.
 * 前缀蛮力匹配算法
 */
public class PreBruteForce {

    public static void main(String[] args) {
        System.out.println(strIndex("abcdeabdabdfe", "abdabd"));
    }

    public static int strIndex(String s , String t) {
        int i = 0;
        int j = 0;
        while(i < s.length() && j < t.length()) {
            if(s.charAt(i) == t.charAt(j)) {
                i++;
                j++;
            }else {
                i = i - j + 1;
                j = 0;
            }
        }
        if(j == t.length()) {
            return i - j;
        }else {
            return -1;
        }
    }
}
```

2. 方法二
> KMP算法

```java 
public class KMP_V1 {

    public static void main(String[] args) {
        String s = "dsfsfa";
        String p = "sfa";
        System.out.println(search2(s, p));
    }

    public static int search2(String s, String pattern) {
        int n = s.length();
        int m = pattern.length();
        if(m > n) {
            return -1;
        }
        int[] next = buildNext(pattern);
        int i = 0;
        int j = 0;
        while(i < n && j < m) {
            if(s.charAt(i) == pattern.charAt(j)) {
                i++;
                j++;
            }else if(j != 0) {
                j = next[j - 1];
            }else {
                i++;
            }
        }
        if(j == m) {
            return i - j;
        }
        return -1;
    }

    // 这个方法至关重要，如果某一个字符没法匹配，可以根据这个方法获取的索引值进行移动
    private static int[] buildNext(String p) {
        int m = p.length();
        int[] next = new int[m];
        int count = 0;
        int i = 1;
        while(i < m  - 1) {
            if(p.charAt(count) == p.charAt(i)) {
                count++;
                next[i] = count;
                i++;
            }else if(count > 0) {
                count = next[count - 1];
            }else {
                i++;
            }
        }
        return next;
    }
}
```

### 思考
建立next数组太有意思了，kmp算法的含义是理解了，编码上还是写的有点糟糕，需要加强训练

### 参考文档
[参考一：理解KMP算法](https://www.zhihu.com/question/21923021)