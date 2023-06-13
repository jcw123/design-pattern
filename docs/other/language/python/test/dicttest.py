#! /usr/bin/python3

#初始化
mydict = {'test1':1, 'test2':2}

mydict2 = {}

mydict3 = dict()

mytuple = ('key1', 'key2', 'key3')

# 初始化填充
print(str(dict.fromkeys(mytuple, 2)))

# 查询
v = mydict.get('test1')
print(v)

v = mydict.get('test3', 100)
print(v)

# 遍历
for k, v in mydict.items():
    print("k:%s, v: %s" %(k, v))

for k in mydict.keys():
    print("k:%s, v: %s" %(k, mydict[k]))

mylist = list(mydict.values())
print(mylist)

# 设置值
mydict.setdefault('test1', 100)
mydict.setdefault('test5', None)
print(mydict)

mydict2['test1'] = 1000
mydict2['test6'] = 100
mydict.update(mydict2)
print(mydict)

# 删除一个key
del mydict['test1']
mydict.pop('test8', None)