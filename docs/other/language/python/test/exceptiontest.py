#! /usr/bin/python3

class MyError(Exception):
    def __init__(self, a, b):
        self.a = a 
        self.b = b 

    def __str__(self):
        return "a:{0},b:{1}".format(self.a, self.b)

try:
    a = 1
    b = 0
    raise MyError(1, 2)
except MyError as err:
    print(err)
except Exception as e:
    print("other err:{0}".format(e))
finally:
    print("i am finally")
