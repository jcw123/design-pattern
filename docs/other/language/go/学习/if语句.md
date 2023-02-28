# if语句

```go
package main

import (
    "fmt"
) 

a := 2
b := 1
if a % b == 1 {
    fmt.Println("test1")
} else if a % b == 2 {
    fmt.Println("test2")
} else {
    fmt.Println("no no")
}
```