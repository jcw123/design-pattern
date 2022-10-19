题目描述：
输入 n(≤1e5) 和 m (≤1e5)，两个长度都为 n 的数组 a 和 b（元素范围在 [-1e9,1e9] 内，下标从 1 开始）。
然后输入 m 个操作：
操作 1 形如 1 x y k，表示把 a 的区间 [x,x+k-1] 的元素拷贝到 b 的区间 [y,y+k-1] 上（输入保证下标不越界）。
操作 2 形如 2 x，输出 b[x]。

```java
public void dealResult(int n, int m, int[] a, int[] b,  int[][] arr) {
  TreeMap<Integer, int[]> treeMap = new TreeMap<>();
  for(int i = 0; i < m; i++) {
    int[] cur = arr[i];
    if(cur.length == 4) {
      int x = cur[1];
      int y = cur[2];
      int k = cur[3];
      Map.Entry<Integer, int[]> entry = treeMap.floorEntry();
      if(entry.getKey() + entry.getValue()[1] - 1 >= y) {
        treeMap.remove(entry.getKey());
        int[] newA = new int[]{entry.getValue()[0], y }
      }
    }else {
      int x = cur[1];
      Map.Entry<Integer, int[]> entry = map.floorEntry(x);
      if(entry == null) {
        System.out.println(b[x]);
      }else {
        int key = entry.getKey();
        int[] value = entry.getValue();
        if(key + value[1] - 1 >= x) {
          System.out.println(a[x - key + value[0]]);
        }else {
          System.out.println(b[x]);
        }
      }
    }
  }
}
```
