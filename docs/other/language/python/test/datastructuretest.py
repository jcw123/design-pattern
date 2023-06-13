#! /usr/bin/python3

# 栈的使用
stack = [1, 2, 3]
stack.append(4)
stack.pop()

while len(stack) > 0:
    print(stack.pop())

# 遍历dict
mydict = {"test1":1, "test2":2}
for k, v in mydict.items():
    print("k:{0}, v:{1}".format(k, v))

# 同时遍历多个序列
list1 = [2, 3, 4]
list2 = [4, 5, 6]
for a, b in zip(list1, list2):
    print("a:{0}, b:{1}".format(a, b))

# 遍历序列的时候同时获取索引
for idx, v in enumerate(list1):
    print("idx:{0}, v:{1}".format(idx, v))