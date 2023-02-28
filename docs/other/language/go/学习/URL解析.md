# URL解析

```go
package main

import (
    "fmt"
    "net"
    "net/url"
) 

func main() {
    s := "test://jcw:123@test.com/test?p=1&c=3#hehe"

    u, _ := url.Parse(s)
    p := fmt.Println

    p(u.Schema)
    p(u.User)
    p(u.User.Username())
    p(u.User.Password())
    p(u.Host)
    host, port, _ := net.SplitHostPort(u.Host)
    p(host)
    p(port)
    p(u.Path)
    p(u.Fragment)
    p(u.RawQuery)
    m, _ := url.ParseQuery(u.RawQuery)
    p(m["c"][0])
}
```