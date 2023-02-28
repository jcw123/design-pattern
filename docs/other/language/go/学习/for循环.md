# for循环

```go
package main

import (
    "fmt"
)

// 类似java中的while(i < 10)
i := 0
for i < 10 {
    fmt.Println("hello, world")
} 

// 类型java中的while(true) or for(;;) {}
for {
    fmt.Println("hello, world")
}

for i := 1; i < 3; i++ {
    fmt.Prinltn("hello, world")
}
```