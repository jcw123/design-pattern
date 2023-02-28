# json

```go
package main 

import (
    "os"
    "fmt"
    "encoding/json"
) 

type response1 struct {
    Name string
    Vals []string
}

type response2 struct {
    Name string `json:name`
    Vals []string `json:vals`
}

func main() {
    a := json.Marshal(1)
    fmt.Println(string(a))

    b := []int{1, 2, 3}
    c = json.Marshal(b)
    fmt.Println((string(c)))

    d := []byte(`{"name": "test", "vals":[1, 2]}`)
    e := map[string]struct{}
    
    json.Unmarshal(d, &e)
    f := e["name"].(string)
    fmt.Println(f)

    g := e["vals"].([]int)
    fmt.Println(g)
    
    h := json.NewEncoder(os.Stdout)
    h.encode(g)
}
```