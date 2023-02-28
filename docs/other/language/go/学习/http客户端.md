# http客户端

```go
package main 

import (
    "fmt"
    "net/http"
    "bufio"
) 

func main() {
    res, err := http.Get("https://baidu.com")
    if err != nil {
        panic(err)
    }

    defer res.Body.Close()

    fmt.Println("res status:", res.Status)
    
    scanner := bufio.NewScanner(res.Body)
    for i := 0; scanner.Scan() && i < 5; i++ {
        fmt.Println("text:", scanner.Text())
    }
    
    if err := scanner.Err(); err != nil {
        panic(err)
    }
}
```