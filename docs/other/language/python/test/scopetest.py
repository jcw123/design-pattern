#! /usr/bin/python3

v = 1
def a():
    global v
    print(v)
    v = 2

a()
print(v)

def b():
    t = 1
    def c():
        nonlocal t
        print(t)
        t = 2
    return c
b()()