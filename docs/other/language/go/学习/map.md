# map

```go
a := make(map[string]int)

a["k1"] = 3
a["k2"] = 4

v1 := a["k1"]

delete(a, "k1")

// prs表示k2这个健是否存在
_, prs := a["k2"] 

b := map[string]int{"t1":2, "t2":3}
 
```