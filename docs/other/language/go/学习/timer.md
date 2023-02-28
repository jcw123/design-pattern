# timer

```go
package main

import (
	"fmt"
	"time"
)

func main() {
	timer1 := time.NewTimer(1 * time.Second)

	<-timer1.C
	fmt.Println("timer1 start")

	timer2 := time.NewTimer(1 * time.Second)

	go func() {
		<-timer2.C
		fmt.Println("timer2 start")
	}()

	stop2 := timer2.Stop()
	if stop2 {
		fmt.Println("timer2 stopped")
	}

	time.Sleep(2 * time.Second)
}

```