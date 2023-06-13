#! /usr/bin/python3

mylist = ['test1', 'test2', 'test3']
for v in mylist:
    print(v)

i = 0;
while i < len(mylist):
    print(mylist[i])
    i += 1

for t in range(5):
    print(t, end=',')