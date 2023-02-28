# switch

```go
package main

import (
    "fmt"
    "time"
)

i := 1
switch i {
    case 1 :
        fmt.Println("i am 1")
    case 2 :
        fmt.Println("i am 2")
    default :
        fmt.Println("i don't know who i am")
}

switch {
    case i < 3 :
        fmt.Println("i am lower than 3")
    default :
        fmt.Println("i am default")
}

switch time.Now().WeekDay() {
    case time.Saturday :
        fmt.Println("i am Saturday")
    default :
        fmt.Println("i don't know say what")
}

timeCheck := func(t interface{}) {
    switch i.(type) {
        case int :
            fmt.Println("i am int")
        case string :
            fmt.Println("i am string")
        default :
            fmt.Println("i don't know what type it is")
    }
}
```