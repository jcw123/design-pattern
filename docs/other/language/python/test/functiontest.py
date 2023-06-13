#! /usr/bin/python3

def a(a, b):
    return a + b 
print("a + b:", a(1, 2))

print("a + b:", a(b=1, a=2))

def b(a, *, b):
    print("a:%s, b:%s" %(a, b))

b(1, b = 2)

def c(a, *vTuple):
    print("a:", a)
    for v in vTuple:
        print("v:" + str(v), end = " ")

c(1, 2, 3)

dict = { "test":1}
print("1:" + str(dict["test"]))