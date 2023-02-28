# recover
可以在监控到panic错误时，程序不进行中断，而是继续往下执行

```go 
package main

import "fmt"

func myPanic() {
	panic("my problem")
}

func main() {
	defer func() {
		if p := recover(); p != nil {
			fmt.Println("error occur, catch it, error:", p)
		}
	}()

	myPanic()

	fmt.Println("go")
}
```