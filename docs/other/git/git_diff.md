# git_diff

## Myers 算法实现

### 算法原理
首先，定义参数 d 和 k，d 代表路径的长度，k 代表当前坐标 x - y 的值。定义一个”最优坐标“的概念，最优坐标表示 d 和 k 值固定的情况下，x 值最大的坐标。x 大，表示向右走的多，表示优先删除。

### diff算法特点
1. 路径长度最短(删除和新增字符都会算一个路径长度)
2. 优先删除，后新增
```go
type node struct {
    op int // 1：新增；-1：删除；0：不变
    s byte // 当前行的字符串
}

type count struct {
    nodes []node
    total int
}

// 相当于找从(0,0)到(m - 1, n - 1)的最优路径
func myers(s string, t string) []node {
    m := len(s)
    n := len(t)
    dp := make([][]count, m + 1)
    for i := 0; i <= m; i++ {
        dp[i] = make([]count, n + 1)
    }
    dp[0][0] = count{nodes:[]node{}, total:0}
    for i := 1; i <= m; i++ {
        dp[i][0] = count{nodes:[]node{}, total:0}
    }
    for i := 1; i <= n; i++ {
        dp[0][i] = count{nodes:[]node{}, total:0}
    }
    for i := 1; i <= m; i++ {
        for j := 1; j <= n; j++ {
            v1 := s[i - 1]
            v2 := t[j - 1]
            if v1 == v2 {
                c := dp[i - 1][j - 1]
                nodes := append([]node(nil), c.nodes...)    
                nodes = append(nodes, node{op:0, s:v2})
                dp[i][j] = count{nodes:nodes, total:c.total}
            }else {
                num1 := dp[i - 1][j].total
                num2 := dp[i][j - 1].total
                if num2 <= num1 {
                    c := dp[i][j - 1]
                    nodes := append([]node(nil), c.nodes...)
                    nodes = append(nodes, node{op:1, s:v2})
                    dp[i][j] = count{nodes:nodes, total:c.total + 1}
                }else {
                    c := dp[i - 1][j]
                    nodes := append([]node(nil), c.nodes...)
                    nodes = append(nodes, node{op:1, s:v1})
                    dp[i][j] = count{nodes:nodes, total:c.total + 1}
                }
            
            }
        }
    }
    return dp[m][n].nodes
    
}
```

## 参考文档
[diff算法原理](https://cjting.me/2017/05/13/how-git-generate-diff/)

