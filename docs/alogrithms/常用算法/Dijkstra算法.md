# Dijkstra算法

## 核心思想
通过BFS的思想，进行求解。比如求A节点到其他节点的最短距离。首先需要维护两个集合S和U，其中集合S用于记录哪些节点的最短路径
已经求出，同时记录A节点到这些节点的最短路径。U集合用于记录哪些节点未求出，同时记录记录A节点到这些节点的最短距离。

首先从U中找到从A节点到这些节点距离最短的节点，假设这个节点时v，然后将v节点加入到S中，同时更新U集合中其他节点的最短距离。

## 代码实现
假设共有n个节点，节点编号分别为1、2、... n。用arr数组表示两个节点之间的距离。求从节点k到所有节点最短距离的最大值。

```java
class Solution {
  int N = 100;
  int[][] w = new int[N][N];
  int[] dist = new int[N];
  boolean[] vis = new boolean[N];
  int INF = 0x3f3f3f3f;
  int n, k;

  public int shortestDistance(int[][] arr, int _n, int _k) {
    n = _n;
    k = _k;
    for(int i = 1; i <= n; i++) {
      for(int j = 1; j <= n; j++) {
        w[i][j] = w[j][j] = i == j ? 0 : INF;
      }
    }

    for(int[] t : arr) {
      int u = t[0];
      int v = t[1];
      int c = t[2];
      w[u][v] = c;
    }

    dijkstra();

    for(int i = 1; i <= n; i++) {
      ans = Math.max(ans, dist[i]);
    }
  }

  void dijkstra() {
    Arrays.fill(vis, false);
    Arrays.fill(dist, INF);
    dist[k] = 0;
    int t = -1;
    for(int p = 1; p <= n; p++) {
      for(int i = 1; i <= n; i++) {
        if(!visit[i] && (t == -1 || dist[i] < dist[t])) {
            t = i;
        }
      }
      vis[t] = true;
      // 冗余处理了下
      for(int i = 1; i <= n; i++) {
        dist[i] = Math.min(dist[i], dist[t] + w[t][i]);
      }
    }
  }
}
```
