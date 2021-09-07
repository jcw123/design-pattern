# SPFA算法

## 核心思想
这种算法是对Bellman Ford算法的优化，通过借助于一个队列，好的情况下可以将实现复杂度从O(m * n)降为O(m * k), k是一个常数；


## 核心代码
```java
void spfa() {
  Arrays.fill(vis, false);
  Arrays.fill(dist, INF);
  dist[k] = 0;
  Deque<Integer> d= new ArrayDeque<>();
  d.addLast(k);
  vis[k] = true;
  while(!d.isEmpty()) {
    int poll = d.pollFirst();
    vis[poll] = false;
    for(int i = he[poll]; i != -1; i = ne[i]) {
      int j = e[i];
      // 入队是为了以poll为跳板然后求k到poll的直接相连的最短距离；
      // 如果已经在队列中的节点就不要再进行入队了，因为dist已经更新了，出队一次即可动态更新其他值；
      if(dist[j] > dist[poll] + w[i]) {
        dist[j] = dist[poll] + w[i];
        if(vis[j]) continue;
        d.addLast(j);
        vis[j] = true;
      }
    }
  }
}
```
