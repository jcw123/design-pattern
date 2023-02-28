# range

```go
package main

import (
    "fmt"
) 

func main() {
    a := []string{"1", "2", "3"}

    for _, v := range a {
        fmt.Println(v)
    }

    for i, v := range a {
        fmt.Println("i:", i, ", v:", v)
    }

    b := map[string]int{"t1":1, "t2":2}
    for k, v := range b {
        fmt.Println("k:", k, ", v:", v)
    }

    for k := range b {
        fmt.Println("k:", k, ", v:", b[k])
    }
}
```