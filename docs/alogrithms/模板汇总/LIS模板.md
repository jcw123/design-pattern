# LIS模板

```java 
/**
思考：
维护一个数组，其中索引0记录长度为1的右端点最小值、索引i记录长度为i+1的右端点最小值；
每遍历到一个新的元素时，寻找< x的最右侧的位置
*/
public int[] LIS(int[] arr) {
    int n = arr.length;
    int count = 0;
    int[] tmp = new int[n];
    for(int i = 0; i < n; i++) {
        int idx = lower_bound(tmp, count, v);
        if(idx == count) {
            tmp[idx] = v;
            count++;
        }else {
            tmp[idx] = v;
        }
    }
    return tmp;
}

private int lower_bound(int[] tmp, int n, int v) {
    int s = 0;
    int e = n;
    int mid;
    while(s < e) {
        mid = s + (e - s)/ 2;
        if(tmp[mid] < v) {
            s = mid + 1;
        }else {
            e = mid;
        }
    }
    return s;
}
```


```go
 
```

## 思考
对于1个字符串，涉及最长上升子序列问题。对于两个字符串涉及子串匹配问题、序列匹配问题、最长公共子序列问题，最短超序列问题；

## 参考文档
[c++ lower_bound写法](https://en.cppreference.com/w/cpp/algorithm/lower_bound)