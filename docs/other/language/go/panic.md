# panic
当系统出现未知的错误时，可以通过panic进行标识

```go
package main

import "os"

func main() {
    panic("a error occur")

    _, error := os.Create("/tmp/test")


    if error != nil {
        panic(error)
    }
} 
```