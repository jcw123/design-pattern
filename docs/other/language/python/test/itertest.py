#! /usr/bin/python3

import sys

class IterTest:
    def __iter__(self):
        self.a = 1
        return self

    def __next__(self):
        if self.a <= 20:
            x = self.a 
            self.a += 1
            return x
        else:
            raise StopIteration

test = IterTest()
for x in iter(test):
    print(x)

def fib(n):
    a, b, counter = 0, 1, 0
    while True:
        if counter > n:
            return 
        yield a
        a, b = b, a + b 
        counter += 1
f = fib(10)
while True:
    try:
        print(next(f), end = " ")
    except StopIteration:
        sys.exit()