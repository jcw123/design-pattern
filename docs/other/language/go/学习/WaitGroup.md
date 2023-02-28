# WaitGroup

```go
package main

import (
    "fmt"
    "time"
    "sync"
) 

func Worker(i int) {
    fmt.Println("worker ", i, " start")
    time.Sleep(time.Second)
    fmt.Println("worker ", i, " end")
}

func main() {
    var wtg sync.WaitGroup

    for i := 0;  i < 5; i++ {
        wtg.Add(1)
        i := i
        go func() {
            defer wtg.Done()
            Worker(i)
        }()
    }
    wtg.Wait()
}

```