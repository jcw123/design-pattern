package main

import (
	"fmt"
)

type ThreadTest struct {
	lock chan int
}

func (t *ThreadTest) produce() {
	for {
		t.lock <- 10
		fmt.Println("produce:", 10)
	}
}

func (t *ThreadTest) consume() {
	for {
		v := <-t.lock
		fmt.Println("consume:", v)
	}
}

func main() {
	maxLen := 10
	t := &ThreadTest{
		make(chan int, maxLen),
	}
	// 重点在这里，开启新的协程，配合通道，让go的多线程变成非常优雅
	go t.consume()
	go t.produce()
	select {}

}
