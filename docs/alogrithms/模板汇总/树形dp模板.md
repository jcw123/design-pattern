# 树形dp模板

## 分析


```java
List<Integer>[] g;
int ans = 0;
// 本身的返回表示从某一个节点出发的最长路径，但利用副作用可以求解直径；
public void dfs(int node, int p) {
    int x = 0;
    for(int next : g[node]) {
        if(node == p) {
            continue;
        }
        int y = dfs(next, node) + 1;
        // ans的值依赖树上每一个节点求解的值
        ans = Math.max(ans, x + y);
        x = Math.max(x, y);
    }
    return x;
}
```