# floyd算法

## 核心思想
假设有n个节点，分别用编号0，1，...n-1进行编号。dp表示图的邻接矩阵，其中dp[i][j]表示i到j的最短距离，初始化时，若i和j的值相等，则dp[i][j]等0，若i和j节点之前有边相连，则dp[i][j]等于边的权重，否则dp[i][j]等于无穷大。通过不断地往i和j之间加入中转节点，进行最短路径地更新。
比如加入中转节点w，比对dp[i][j]和dp[i][w] + dp[w][j]的最短距离。

## floyd算法思想证明。
证明，dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);
（1）当不加入任何中转节点时，dp[i][j]就等于初始值，满足条件。
（2）假设已经往i和j之间加入了0、1、2、...k个中转节点，dp[i][j]是i和j之间的最小值。
（3）当新加入k+1这个节点时，dp[i][j] = min(dp[i][j], dp[i][k+1] + dp[k+1][j]);
因为dp[i][k+1]的最小值在加入0、1、2....k这些节点值已经求出，dp[k+1][j]在加入0、1、2...k这些节点时也已经求出。
所以当新加入一个节点时，这个节点可以作为中转节点，也可以不作为中转节点。当不作为中转节点时，dp[i][j]的值不变，当作为
中转节点时，此时的最小值为dp[i][k + 1] + dp[k + 1][j]，只需要比较dp[i][j] 和 dp[i][k + 1] + dp[k + 1][j]，就可以
得到当出现一个新的节点后，i和j之间的最小值。


## 代码实现
假设有一个图，用一个邻接矩阵表示，如果两点之间没有直接边，值用Integer.MAX_VALUE表示，求
任意两个顶点之间的最短距离。

```java
public void shortestDistance(int[][] vertex) {
  int n  = vertex.length;
  for(int p = 0; p < n; p++) {
    for(int i = 0; i < n; i++) {
      for(int j = 0; j < n; j++) {
        if(vertex[i][p] != Integer.MAX_VALUE && vertex[p][j] != Integer.MAX_VALUE) {
          vertex[i][j] = Math.min(vertex[i][j], vertex[i][p] + vertex[p][j]);
        }
      }
    }
  }
}
```
