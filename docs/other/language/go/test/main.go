package main

import "fmt"

type node struct {
	op int  // 1：新增；-1：删除；0：不变
	s  byte // 当前行的字符串
}

type count struct {
	nodes []node
	total int
}

// 相当于找从(0,0)到(m - 1, n - 1)的最优路径
func myers(s string, t string) []node {
	m := len(s)
	n := len(t)
	dp := make([][]count, m+1)
	for i := 0; i <= m; i++ {
		dp[i] = make([]count, n+1)
	}
	dp[0][0] = count{nodes: []node{}, total: 0}
	for i := 1; i <= m; i++ {
		c := dp[i-1][0]
		nodes := append([]node(nil), c.nodes...)
		nodes = append(nodes, node{op: -1, s: s[i-1]})
		dp[i][0] = count{nodes: nodes, total: c.total + 1}
	}
	for i := 1; i <= n; i++ {
		c := dp[0][i-1]
		nodes := append([]node(nil), c.nodes...)
		nodes = append(nodes, node{op: 1, s: s[i-1]})
		dp[0][i] = count{nodes: nodes, total: c.total + 1}
	}
	for i := 1; i <= m; i++ {
		for j := 1; j <= n; j++ {
			v1 := s[i-1]
			v2 := t[j-1]
			if v1 == v2 {
				c := dp[i-1][j-1]
				nodes := append([]node(nil), c.nodes...)
				nodes = append(nodes, node{op: 0, s: v2})
				dp[i][j] = count{nodes: nodes, total: c.total}
			} else {
				// 减一个
				num1 := dp[i-1][j].total
				// 加一个
				num2 := dp[i][j-1].total
				if num2 <= num1 {
					c := dp[i][j-1]
					nodes := append([]node(nil), c.nodes...)
					nodes = append(nodes, node{op: 1, s: v2})
					dp[i][j] = count{nodes: nodes, total: c.total + 1}
				} else {
					c := dp[i-1][j]
					nodes := append([]node(nil), c.nodes...)
					nodes = append(nodes, node{op: -1, s: v1})
					dp[i][j] = count{nodes: nodes, total: c.total + 1}
				}

			}
		}
	}
	return dp[m][n].nodes

}

func main() {
	s := "abcd"
	t := "ace"
	nodes := myers(s, t)
	fmt.Println(nodes)
}
