#! /usr/bin/python3

# 初始化
set1 = {'1', '2', '3'}
set2 = set()
set3 = set(('1', '3', '4'))

# 遍历
for v in set1:
    print(v, "")

size = len(set1)
print("size:%s" %(size))

set1.add('4')
set2.clear()
set2 = set1.copy()  
set4 = set1.difference(set3)
print(set4)
set1.discard('3')

