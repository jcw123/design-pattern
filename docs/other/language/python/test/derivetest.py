#! /usr/bin/python3

# 列表推导式
list1 = [x for x in range(10)]
print(list1)

list2 = [x**2 for x in range(10) if x < 5]
print(list2)

#字典推导式
dict1 = {x:x**2 for x in range(10)}
print(dict1)

dict2 = {x:x**2 for  x in range(10) if x < 5}
print(dict2)

# 集合推导式
set1 = {x for x in range(10)}
print(set1)

set2 = {x for x in range(10) if x < 5}
print(set2)

# 元组推导式
tuple1 = tuple((x for x in range(10)))
print(tuple1)

tuple1 = tuple((x for x in range(10) if x < 5))
print(tuple1)

