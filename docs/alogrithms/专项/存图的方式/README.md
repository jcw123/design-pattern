# 存图的方式

## 邻接矩阵
```java
int[][] grids = new int[N][N];

void add(int a, int b, int c) {
  grids[a][b] = c;
}
```

## 领接表
```java
// 方式一
// 链式前向星存图
int[] he = new int[N];
int[] e = new int[M];
int[] ne = new int[M];
int[] w = new int[M];
int idx = 0;

void init() {
  Arrays.fill(he, -1);
}

void add(int a, int b, int c) {
  e[idx] = b;
  w[idx] = c;
  ne[idx] = he[a];
  he[a] = idx;
  idx++;
}

for(int i = he[a]; i != -1; i = ne[i]) {
  int b = e[i];
  int c = w[i];
}

// 方式二
// 通过列表存储
Map<Integer, List<Node>> edges = new HashMap<>();

void add(int a, int b, int c) {
  Node node = new Node(b, c);
  List<Node> list = edges.computeIfAbsent(a, k -> new ArrayList<>());
  list.add(node);
}

class Node {
  int v;

  int w;

  Node(int v, int w) {
    this.v = v;
    this.w = w;
  }
}
```

## 类的方式
```java
class Edge {
  int a;
  int b;
  int c;

  Edge(int a, int b, int c) {
    this.a = a;
    this.b = b;
    this.c = c;
  }
}
```
