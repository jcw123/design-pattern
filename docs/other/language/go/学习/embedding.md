# embedding

```go
package main

import "fmt"

type a struct {
    num  int
} 

func (a a) say() {
    fmt.Println("hello, world")
}

type container struct {
    a
    age int
}

func main() {
    p := container{
        t : a{num:1}
        age : 10
    }
    fmt.Println(p.num)
    fmt.Println(p.t.num)
    fmt.Println(p.age)

    type c interface {
        say()
    }
    
    var t c = p
    fmt.Println(t.age)
}
```