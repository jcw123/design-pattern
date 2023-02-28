# defer 
类似java中的finally，在函数执行完之后进行执行

``` go
package main

import (
	"fmt"
	"os"
)

func main() {
	f := createFile("/tmp/test")
	defer closeFile(f)
	writeFile(f)
}

func createFile(path string) *os.File {
	fmt.Println("creating")
	f, e := os.Create(path)
	if e != nil {
		panic(e)
	}
	return f
}

func writeFile(f *os.File) {
	fmt.Println("writing")
	fmt.Fprintln(f, "data")
}

func closeFile(f *os.File) {
	fmt.Println("closing")
	error := f.Close()
	if error != nil {
		fmt.Fprintf(os.Stderr, "error: %v\n", error)
	}
	os.Exit(1)
}
```