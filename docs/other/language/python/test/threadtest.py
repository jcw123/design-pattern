#! /usr/bin/python3

import threading
import random
import time

total = 100
lock = threading.Lock()
totalTime = 10
gTime = 0

class Consumer(threading.Thread):
        def run(self):
                global total
                global gTime
                while True:
                        cur = random.randint(10, 100)
                        lock.acquire()
                        if total >= cur:
                                total -= cur
                                print("{}使用了{}, 当前剩余{}".format(threading.current_thread(), cur, total))
                        else:
                            print("{}准备使用{}，当前剩余{}，不足，不能消费".format(threading.current_thread(), cur, total))
                        if gTime == totalTime:
                               lock.release()
                               break
                        lock.release()
                        time.sleep(0.7)

class Producer(threading.Thread):
    def run(self):
           global total
           global gTime
           while True:
                  cur = random.randint(10, 100)
                  lock.acquire()
                  if gTime == totalTime:
                         lock.release()
                         break
                  total += cur
                  print("{}生产了{}, 剩余{}".format(threading.current_thread(), cur, total))
                  gTime+= 1
                  lock.release()
                  time.sleep(0.5)
if __name__ == '__main__':
       t1 = Producer(name="生产者")
       t1.start()
       t2 = Consumer(name="消费者")
       t2.start()